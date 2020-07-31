---
layout: post
title: "Investigating use of change log for genome class"
date: 2020-07-15
author: Tetiana
---

# Genome change logging using range map  

For more information about MABE (Modular Agent-Based Evolution platform) see [this introduction](https://szendejo.github.io/waves/blog/Team-MABE.html).

## Genome Class

### Naïve Implementation

The naïve implementation of the genome is using a vector data structure from the standard library. The overwrite, insert and remove operations are, therefore, implemented using the standard library algorithms, specifically:
```cpp
std::vector<std::byte> sites{std::byte(1), std::byte(2), std::byte(3)}; // this genome consists of three sites with values 1, 2 and 3

// Overwrite sites startin at index with values from segment
virtual void overwrite(size_t index, const std::vector<std::byte>& segment) override {
    for (size_t i(0); i < segment.size(); i++) {
        sites[index + i] = segment[i];
    }
}

// Insert mutation: a segment is inserted at index
virtual void insert(size_t index, const std::vector<std::byte>& segment) override {
    sites.insert(sites.begin() + index, segment.begin(), segment.end());
}

// Remove mutation: segmentSize sites are removed atarting at index 
virtual void remove(size_t index, size_t segmentSize) override {
    sites.erase(sites.begin() + index, sites.begin() + index + segmentSize);
}

```

The advantages of such approach include:
* All the sites are in contiguous memory -> fast operations due to cache-friendliness (e.g. random access or iterations)  
* Use of C++ standard library data structures -> code is simple, readable, expressive and optimized for performance  
  
However, there are also disadvantages:  
* Every generation, the whole genome (the whole `sites` vector) is copied and then the mutations are applied to it -> In a common situation of large genome and low mutation rates, it means copying a lot of values that didn't change  
* The `insert()` and `erase()` algorithms have linear time complexity -> inefficient time  
  
**The goal of this project was to investigate if storing only the mutations (as opposed to storing the whole genome) would provide a better time and memory performance.**

### Optimized Implementation Using Change Log  

One of the ways to improve the time complexity as well as optimize for memory use is to have a change log. The change log will keep track of the mutations that occurred between the parent and the offsprings over generations. This means only storing the differences between parent genome and it's offsprings as opposed to storing the whole genome for every offspring. 

As we've seen above, the algorithm has to support the following mutations:
* Overwrite - the values at one or more sites is overwritten by a new value
* Insert - one or more sites are inserted into at specific location
* Remove - one or more sites are removed at specific location

My implementation consists of two maps from the standard library:
* **change_log** is implemeted as std::map and contains the information about the **number of inserted and removed sites**. It is used to calculate the relationship between a particular site in the offspring genome and either the parent genome or the newly inserted values stored in the segments_log (see next)
* **segments_log** is implemented as std::unordered_map and stores the segments that were inserted into the map dusing mutation  
  
![Schematics of change_log and segments_log]({{ site.baseurl }}/assets/TetianaBlogFigs/maps_init.png){:style="width: 100%; align: center;"}  
  
Each genome will have it's own change_log and segments_log, which in combination with the parent genome will allow the random access to any value in the offspring genome as well as the reconstruction of complete offsping genome or a part of it as a contiguous memory block of necessary sites.

One important detail of the change_log is that it doesn't store every every deleted or inserted index. Instead, to optimize for memory use, it stores only one index for each range of a particular shift in indices due to insertion of deletion (see example below). I.e. each key in the cahnge_log represents all the keys in the range from the current key until the nex key. 
  
For example, a change_log with entries `{3 : -2}, {5 : 3}` corresponds to the following mapping (this will be replace by a figure):
```
3 : -2
4 : -2
5 : 3
6 : 3
7 : 3
...
```
  
To access any index, the following code can be used:
```cpp
--map.upper_bound(index); // "upper_bound" returns the key, which is higher than the index, "--" moves to the previous key
```
  
In the case of the change_log above,  `--map.upper_bound(7);` will return 5, which is a key in the change_log map before 7

For each key change_log stores how many sites were removed and inserted up until this key. 

  
#### Deletion mutaiton :hammer:
For example, the following element in the change_log (all the examples below will be replaced by gifs)
```
{3 : -2}
```
would correspond to deletion of two sites at index 5. This element means that all the values at indexes < 5 are at the same locations as in the parent genome; all the values at indexes >= 5 were shifted by two to the left due to the mutation, which deleted two sites. Therefore, in order to access the values at index 5 or above, we need to shift two sites to the right in the parent genome, specifically the index in the offspring genome would correspond to the (index + 2) in parent genome.

Each key is the accumulation of all the changes up to corresponding index, for example, if **two** elements were removed at index 5 and then **three** elements were removed at index 10, the accumulated shift at index >= 10 will be -5:
```
{3 : -2}
{5 : -5}
```

Using this change log and the parent genome, it is possible to reconstruct the offspring genome by relating a specific index in the offspring genome to the index in the parent genome, e.g. for deletion mutation
```
parent genome:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}

delete(3, 2) // delete two sites at index 5 

change_log:       {{3 : -2}} // deletion of two sites at index 5 and three sites at index 8

// Can reconstruct the following offspring using the parent genome and change_log
offspring genome: {0, 1, 2, 5, 6, 7, 8, 9, 10, 11}
```

As you can see, the values at indices <3 are the same as in parent genome; to find the value at indices >=3:
```
offspring[index] = parent[index + 2]
```

Now let's delete three sites at index 5:

```
parent genome:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}

delete(3, 2) // delete two sites at index 3
delete(5, 3) // delete three sites at index 5

change_log:       {{3 : -2}}, {{5 : -5}} // deletion of two sites at index 5 and three sites at index 8

// Can reconstruct the following offspring using the parent genome and change_log
offspring genome: {0, 1, 2, 5, 6, 10, 11}
```

Now, for indexes:
* < 3: same value as in the parent genome
* \>= 3 && <5: offspring[index] = parent[index + 2]
* \>= 5: offspring[index] = parent[index + 5]


#### Insertion mutation :wrench:
Each value in the change_log map corresponds to the index shift relative to the parent genome. The values of the newly inserted sites do not have any relation to the parent genome, therefore, the values for such keys could be arbitrary, as long as it can't be confused with shift. In order to not confuse it with shift, an additional variable can be added to the map, a boolean, which specifies whether key is an insertion:
```
{key : {val, inseet}}
```

E.g. updating our previous map with an insertion of 3 elements {20, 21, 22} at index 7:
```
{3 : {-2, false}}
{5 : {-5, false}}
{7 : {0, true}}
```

Now we see that starting from index 7 there are no values in the parent genome, we need to store inserted values somewhere else. In addition to range map, another data structure is needed to store the inserted segments. I decided to use the std::unordered_map, as it allows constant time access by key. Let's see an example of how change_log and segments_log will work together to store mutations.
```
// Change log (std::map)
{3 : {-2, false}}
{5 : {-5, false}
{7 : {0, true}}

// Segments log (std::unordered_map)
{7 :  {20, 21, 22}}
```

To figure out where the insertion ends, we could also store the shift, which corresponds to the indexes after the insertion (size of the segment can be used insted), e.g.:
```
// change_log (std::map)
{3 : {-2, false}}
{5 : {-5, false}
{7 : {0, true}}
{10 : {-2, false}} // for index >= 10, offspring[index] = parent[index + 2]

// segments_log (std::unordered_map)
{7 :  {20, 21, 22}}
```

For index 10 and above, there had been accumulated 2 sites removals (two sites removal at index 3 and 3 sites removal at index 5 and 2 sites insertion ar index 10 => (-2) + (-3) + 3 = -2). To reconstruct the offspring genome now:
```
parent genome:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}

ind < 3: same as in parent
ind >= 3 && ind < 5: offspring[index] = parent[index + 2]
ind >= 5 && ind < 7: offspring[index] = parent[index + 5]
ind >= 7 && ind < 10: offspring[index] = segment from segments_log
ind > 7: offspring[index] = parent[index + 2]

offspring genome:    {0, 1, 2, 6, 7, 10, 11, 20, 21, 22, 12}
```

#### Overwrite mutation :hammer: :wrench:
(Need to change the algorithm - will add description later)

#### All mutations combined

The algorithms for `overwrite()`, `insert()` and `remove()`,  are designed in a way to keep the change_log and insertions_log correct after every mutation, si that we can have randon access to a genome site and can reconstruct the offspring genome.

(Here I will add pseudo code fot the above three methods)

To sum up, change log consists of two data structures:
* change_log: keeps track of shifts in indexes when the insertions or deletions happen
  * Implemented as std::map: keping the keys in sorted order allows updating only the keys > current key; searching for key takes logarithmic time
* segments_log: stores inserted segments
  * std::unordered_map: accessing a segment by key is constant time


### Algorithm performance
(The following figures will be updated with prettier ones, the data might change, but my genome will still be slower)  

![Comparison of performance for insert() method]({{ site.baseurl }}/assets/TetianaBlogFigs/Insert.png){:style="width: 20%; align: center;"}  
![Comparison of performance for remove() method]({{ site.baseurl }}/assets/TetianaBlogFigs/Remove.png){:style="width: 20%; align: center;"}  


This section will include more figures and text regarding comparison with naive approach.
This section will also include the analysis of time complexities in comparison with original algorithm. And memory calculation in comparison with original algorithm. 

### Conclusion
The naive algorithm is faster. (This section will also include more discussion on the calculations in previous section, when I finich them.)

### A brainstorm of potential improvements and optimizations :thinking:
There are multiple things in the algorithm that could be optimized, from both algorithms and code perspective. Aome of them are:
* As the benchmarking graph shows, `insert()` function is currently the bottleneck
* Currelty, the reconstruction algorithm will always reconstruct a full offspring genome, which is very inefficient, as sometimes only a part of genome is needed. Couple of improvement could be dome here:
  * Reconstruct only the sites that are requested
  * Use change_log to check if there was a mutation within the requested sites. If not - return a pointer to the requested index in the parent genome

## Acknowlegements
I would like to thank my mentors:    

![Cliff]({{ site.baseurl }}/assets/headshots/square-cliff-bohm.png){:style="width: 130px; align: center;"}
![Jory]({{ site.baseurl }}/assets/headshots/square-JorySchossau.png){:style="width: 130px; align: center;"}  
![Jose]  
as well as team members:  
![Jamell]({{ site.baseurl }}/assets/headshots/square-daconjam.png){:style="width: 130px; align: center;"}  
![Stephanie]({{ site.baseurl }}/assets/headshots/square-szendejo.png){:style="width: 130px; align: center;"}  
![Uma]({{ site.baseurl }}/assets/headshots/square-uma-sethuraman.png){:style="width: 130px; align: center;"}  
![Victoria]({{ site.baseurl }}/assets/headshots/square-caovicto.png){:style="width: 130px; align: center;"}  
  
---
This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

