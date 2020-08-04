---
layout: post
title: "Performance of Genome Class when Using Change Log"
date: 2020-07-31
author: Tetiana D
---

# Introduction

For a short introduction about MABE (Modular Agent-Based Evolution platform) as well as description and performance analysis of other approaches see [this post](https://mmore500.com/waves/blog/Team-MABE.html).

## Genome Class

Genome is a source of heritable and mutable data. 
Genome is a sequence of sites with data, which is used by other MABE modules (e.g., a genome could provide the data necessary to construct a brain in MABE).

In biology, a genome is a sequence of four types of nucleotides (A, C, G, T). In MABE, the genome data could be any type, and for this project we will use std::byte as out data type.

The genome class interface provides several mutation methods, which are used to create an offspring genome from a parent genome, specifically: 
* **Overwrite** - the value at one or more sites is overwritten by a different value
* **Insert** - one or  more sites are inserted into the genome
* **Remove** - one or more sites are removed from the genome

### Naive Implementation

Genome is a list of sites with specific values:

![genome example]({{ site.baseurl }}/assets/TetianaBlogFigs/GenomeExample.png){:style="width: 60%; align: center;"}  

Genome can be naively implemented as a `std::vector` data structure from the standard library.

In this naive implementation, there mutations can be implemented using the standard library algorithms on `std::vector`, specifically:

```cpp
std::vector<std::byte> sites{std::byte(1), std::byte(2), std::byte(3)}; // this genome consists of three sites with values 1, 2 and 3

// Overwrite sites starting at index with values from segment
void overwrite(size_t index, const std::vector<std::byte>& segment) {
    for (size_t i(0); i < segment.size(); i++) {
        sites[index + i] = segment[i];
    }
}

// Insert mutation: a segment is inserted at index
void insert(size_t index, const std::vector<std::byte>& segment) {
    sites.insert(sites.begin() + index, segment.begin(), segment.end());
}

// Remove mutation: segmentSize sites are removed starting at index 
void remove(size_t index, size_t segmentSize) {
    sites.erase(sites.begin() + index, sites.begin() + index + segmentSize);
}

```

The advantages of this approach include:
* All the sites are in contiguous memory -> fast operations due to cache-friendliness (e.g. random access or iterations)  
* Use of C++ standard library data structures -> code is simple, readable, expressive and optimized for performance  
<br/>
However, there are also disadvantages:  
* Every generation, the whole genome (the whole `sites` vector) is copied and then the mutations are applied to it -> In a common situation of large genome and low mutation rates, it means copying a lot of values that didn't change  
* The `insert()` and `erase()` algorithms have linear time complexity -> inefficient time  
  
**The goal of this project was to investigate if storing only the mutations (as opposed to storing the whole genome) would provide a better time and memory performance.**

### Optimized Implementation Using Change Log  

One of the ways to improve the time complexity as well as optimize for memory use is to have a change log. 
The change log will keep track of the mutations that occurred between the parent and the offsprings over generations. 
This means only storing the differences between parent genome and it's offsprings as opposed to storing the whole genome for every offspring. 

As we've seen above, the algorithm has to support the following mutations:
* Overwrite
* Insert
* Remove

My implementation consists of two maps, which, for each offspring genome, store all the necessary information on how this genome is different from the parent:
* **change_log** is implemented as `std::map` and contains the information about the **number of inserted and removed sites**. It is used to calculate the relationship between a particular site in the offspring genome and either the parent genome or the newly inserted values stored in the segments_log (see next)
* **segments_log** is implemented as `std::unordered_map` and stores the segments that were inserted into the map during mutation  
  
![Schematics of change_log and segments_log]({{ site.baseurl }}/assets/TetianaBlogFigs/maps_init_cut.png){:style="width: 75%; align: center;"}  
  
Each genome will have it's own change_log and segments_log, which in combination with the parent genome will allow the random access to any value in the offspring genome as well as the reconstruction of complete offspring genome or a part of it as a contiguous memory block of necessary sites.

One important detail of the change_log is that it doesn't store every removed or inserted index. Instead, to optimize for memory use, it stores only one index for each range of a particular shift in indices due to insertion of removal (see example below). I.e. each key in the change_log represents all the keys in the range from the current key until the next key. 

{% raw %}  
For example, a change_log with entries `{{3 : -2}, {5 : 3}}` corresponds to the following mapping:  
{% endraw %}

![range map]({{ site.baseurl }}/assets/TetianaBlogFigs/range_map.png){:style="width: 75%; align: center;"}  

To access any index, the following code can be used:
```cpp
--map.upper_bound(index); // "upper_bound" returns the key, which is higher than the index, "--" moves to the previous key
```
<br\>
In the case of the change_log above,  `--map.upper_bound(7);` will return 5.

For each key change_log stores how many sites were removed and inserted up until this key. 

  
#### Remove mutation :hammer:

When one or more sites are removed from the genome, a new element is added in the change_log map: the map key corresponds to the index, at which the remove mutation starts and the map value corresponds to the number of sites that were removed. The following animation shows how the remove mutation is stored int eh change_log and how the change_log is then used to reconstruct the offspring genome:

![remove animation]({{ site.baseurl }}/assets/TetianaBlogFigs/remove_animation_1_small.gif){:style="width: 100%; align: center;"}  

In the animation above, the remove(3, 2) method is called, which corresponds to removing two sites at index 3. The index and the number of removed sites are stored int eh change_log as map key and value.

The change_log can then be used to reconstruct the offspring genome, specifically, the values at indices < 3 are the same as in parent genome. And the sites at the  indices >= 3 were shifted to the left by two sited, therefore in order to access the corresponding values, we need to shift two sites to the right in the parent genome:
```
offspring[index] = parent[index + 2]
```

In the change_log map, each value is the the accumulation of all the changes up to corresponding key, for example, if **two** elements were removed at index 3 and then **three** elements were removed at index 5, the accumulated shift at index >= 5 will be -5:

![remove animation]({{ site.baseurl }}/assets/TetianaBlogFigs/remove_animation_2_small.gif){:style="width: 100%; align: center;"}  

Using this change_log and the parent genome, it is possible to reconstruct the offspring genome by calculating a specific index in the offspring genome in relationship to the parent genome, i.e. for indices:
* < 3: same value as in the parent genome
* \>= 3 && <5: `offspring[index] = parent[index + 2]`
* \>= 5: `offspring[index] = parent[index + 5]`


#### Insert mutation :wrench:
Each value in the change_log map corresponds to the index shift relative to the parent genome. The values of the newly inserted sites do not have any relation to the parent genome, therefore, the values for such keys is set to zero. In order to not confuse it with zero sites shift, an additional variable is added to the map: a boolean, which specifies whether sites were inserted at this key:
```
{key : {val, insert}} // insert = true if there are sites inserted at this key
```

The animation shows an example, where our previous change_log is updated with an insertion of 3 elements {20, 21, 22} at index 6:

![]({{ site.baseurl }}/assets/TetianaBlogFigs/insert_animation_small.gif){:style="width: 100%; align: center;"}  


In addition to change_log, we use `std::unordered_map`, called segments_log to store the inserted segments. The `std::unordered_map` allows constant time access by key. 

After the insert mutation is added to the change_log `{6, {0, true}}` and segments_log `{6, {20, 21, 22}}`, we also add an additional element to know where the inserted segment ends. Specifically, in this case the element is `{9, {-2, false}}`, where key corresponds to the (insert index + segment size): `9 = 6 + 3` and value corresponds to the sites shift up to now (remove 2 sites && remove 3 sites && insert 3 sites): `-2 = -2 + (-3) + 3`.


For index 10 and above, there had been accumulated 2 sites removals (two sites removal at index 3 and 3 sites removal at index 5 and 2 sites insertion ar index 10 => (-2) + (-3) + 3 = -2). To reconstruct the offspring genome now using the parent genome and change_log + segments_log:

Using this change_log and the parent genome, it is possible to reconstruct the offspring genome by calculating a specific index in the offspring genome in relationship to the parent genome, i.e. for indices:
* < 3: same value as in the parent genome
* \>= 3 && <5: `offspring[index] = parent[index + 2]`
* \>= 5: `offspring[index] = parent[index + 5]`

parent genome:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}

ind < 3: same value as in the parent genome
ind >= 3 && ind < 5: `offspring[index] = parent[index + 2]`
ind >= 5 && ind < 6: `offspring[index] = parent[index + 5]`
ind >= 6 && ind < 9: segment from `segments_log.at(6)`
ind > 9: `offspring[index] = parent[index + 2]`

<!--
#### Overwrite mutation :hammer: :wrench:
(Need to change the algorithm - will add description later)
-->

#### All mutations combined

The algorithms for `overwrite()`, `insert()` and `remove()`,  are designed in a way to keep the change_log and insertions_log correct after every mutation, so that we can have random access to a genome site and can reconstruct the offspring genome.


To sum up, the change log consists of two data structures:
* **change_log**: keeps track of shifts in sites when the remove or insert mutation happens
  * Implemented as `std::map`: keeping the keys in sorted order allows updating only the keys larger than current key; accessing the key takes logarithmic time
* **segments_log**: stores inserted segments
  * `std::unordered_map`: accessing a segment by key takes constant time


### Algorithm performance
The plots below show the performance of my approach compared to the naive one for the `overwrite()`, `remove()` and `insert()` mutations methods as well as multi-mutation, when all three methods are applied together. The performance is shown for a number of genome sizes, specifically (each site corresponds to one byte) 5kB, 20kB, 50kB, 75kB, 100kB, 250kB and 500kB. The mutation rate is 0.1%, which corresponds to the 5, 20, 50, 75, 100, 250 and 500 mutations respectively for each genome size.

The performance of the `overwrite()` mutation of my approach is very similar to the naive approach:
![overwrite benchmark]({{ site.baseurl }}/assets/TetianaBlogFigs/BenchmarkOverwrite.png){:style="width: 75%; align: center;"}

The performance of the `remove()` mutation is very similar between two approaches too. In the naive approach, the this mutation has linear time complexity relative to the genome size. In my approach, the time complexity is linear with the change_log size (as I need to update all the keys, which follow current key). Normally, the genome would be much larger than the change_log, however, the `std::vector` data structure stores the values in the contiguous memory (as opposed to `std::map` data structure), which makes the iteration much fasted dues to the utilization of cache-friendliness.
![remove benchmark]({{ site.baseurl }}/assets/TetianaBlogFigs/BenchmarkRemove.png){:style="width: 75%; align: center;"}

The performance of the `insert()` mutation is very similar between two approaches for the smaller genomes (< 100kB), however, as the size of the genome increases, the plots start to diverge, showing the strengths of standard library. In this case both approaches still have the linear time complexity, however, my approach becomes more complicated with more edge cases and the necessity to update two maps, both not contiguos in the memory.
![insert benchmark]({{ site.baseurl }}/assets/TetianaBlogFigs/BenchmarkInsert.png){:style="width: 75%; align: center;"} 

Finally, multi-mutation behaves similar to the `insert()` mutation, which mean that the performance is dominated by the `insert()` mutation in this case.
![multi benchmark]({{ site.baseurl }}/assets/TetianaBlogFigs/BenchmarkMulti.png){:style="width: 75%; align: center;"}  


### Conclusion
Initially, using change log to only store the differences between the parent genome and the offspring genome seemed like a great idea to improve both the time and the memory use of the genome class. However, careful time benchmarking shows that it is very hard to beat the data structures and the algorithms from the standard library. This information (combined with the similar outcomes from my teammates, who developed different algorithms for the change logging) will hopefully be helpful for the future developments of MABE.

My algorithms improves the memory use, because it alleviate the need for deep copy of genome at every generation (iteration when the mutations occur) and only stores the mutations instead.

### A brainstorm of potential improvements and optimizations :thinking:
There are multiple things in the algorithm that could be optimized, from both algorithms and code perspective. Some of them are:
* As the benchmarking graph shows, `insert()` function is currently the bottleneck - optimizing it will result in better performance of the whole genome class
* Currelty, the reconstruction algorithm will always reconstruct a full offspring genome, which is very inefficient, as sometimes only a part of genome is needed. Couple of improvement could be dome here:
  * Reconstruct only the sites that are requested
  * Use change_log to check if there was a mutation within the requested sites. If not - return a pointer to the requested index in the parent genome

## Acknowledgments
I would like to thank the organizers of the WAVES workshop. It was extremely valuable experience for me and I learned so much I couldn't have imagined was possible 10 weeks ago. :exploding_head:

In addition, I would like to thank my mentors Cliff and Jory for giving me the opportunity to work on super cool and interesting project, as well as for all the brainstorming sessions and for answering my questions and helping throughout the workshop. <br /><br />

![Cliff]({{ site.baseurl }}/assets/headshots/square-cliff-bohm.png){:style="width: 130px; align: center;"} ![Jory]({{ site.baseurl }}/assets/headshots/square-JorySchossau.png){:style="width: 130px; align: center;"}  

Last but not least, I want to thank team MABE for creating friendly and encouraging atmosphere and for always being there when I needed help! I wish everyone sucess in their studies and career and I hope we will stay in touch! :tada::tada::tada: <br /><br />

![Jamell]({{ site.baseurl }}/assets/headshots/square-daconjam.png){:style="width: 130px; align: center;"} ![Stephanie]({{ site.baseurl }}/assets/headshots/square-szendejo.png){:style="width: 130px; align: center;"} ![Uma]({{ site.baseurl }}/assets/headshots/square-uma-sethuraman.png){:style="width: 130px; align: center;"} ![Victoria]({{ site.baseurl }}/assets/headshots/square-caovicto.png){:style="width: 130px; align: center;"}

___________
This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

