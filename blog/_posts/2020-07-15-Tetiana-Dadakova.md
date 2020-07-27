---
layout: post
title: "Future blogpost about MABE"
date: 2020-07-15
author: Tetiana
---

# Genome change logging using range map  

(Short introduction to the MABE and Genomes)

## Current Genome Class

(Description of Genome class methods will be added here)

### How it is implemented
The Genome class is implemented as a vector of values, where the insert and remove mutations are using the corresponding standard library algorithms on vector.

### Advantages and disadvantages of current implementation  
  
Advantages:
* Simple, readable, safe code
* Contiguous in memory - cache-friendly
* Site access time complexity is constant    

Disadvantages:
* The whole genome is copied each generation. In a common situation of large genome and low mutation rates, it means copying a lot of values that didn't change
* Insertion and deletion are slow (linear time complexity), because new memory has to be allocated

## New Genome 1.0 Class
One of the ways to improve the time complexity as well as optimize for memory use is to have a change log. The change log will keep track of the mutations that occurred between the parent and the offsprings over generations. This means only storing the differences between parent genome and it's offsprings as opposed to storing the whole genome for every offspring

The algorithm has to support the following mutations:
* overwrite - the values at one or more sites is overwritten by a new value
* insert - one or more sites are inserted into at specific location
* remove - one or more sites are removed at specific location

### Change logging using range map
Range map is implemented based on std::map data structure. It allows mapping the site index in current genome to the site index in parent genome by storing the changes during mutations. Each key in the range map represents all the keys in the range from the current key until the nex key. This allows decreasing the memory footprint of changes log.
E.g. range map with entries `{3, -2}, {5, 3}` corresponds to the following mapping:
```
3 : -2
4 : -2
5 : 3
6 : 3
7 : 3
...
```
To access any key, the following code can be used:
```
--map.upper_bound(key);
```

Range map stores all the information about insertion and removal of sites, specifically, for each key it stores how many sites were removed and inserted up until this key. 

#### Deletion mutaiton and change_log
For example, the following element in the change_log
```
{3 : -2}
```
would correspond to deletion of two sites at index 5. This element mean that all the values at indexes < 5 are at the same locations as in the parent genome; all the values at indexes >= 5 were shifted by two to the left due to the mutation, which deleted two sites. Therefore, in order to access the values at index 5 or above, we need to shift two sites to the right in parent genome / the index in the offspring genome would correspond to the (index + 2) in parent genome.
Each key is the accumulation of all the changes up to corresponding index, for example, if two elements were removed at index 5 and then three elements were removed at index 10, the accumulated shift at index >= 10 will be -5:
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
As you can see, the sites at indexes <3 are the same as in parent genome; to find the value at indexes >=3:
```
offspring[index] = parent[index + 2]
```
Now let's delete three sites at index 5:

```
parent genome:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}

delete(3, 2) // delete two sites at index 3
delete(5, 3) // delete three sites at index 5

change_log:       {{3 : -2}, {5 : -5}} // deletion of two sites at index 5 and three sites at index 8

// Can reconstruct the following offspring using the parent genome and change_log
offspring genome: {0, 1, 2, 5, 6, 10, 11}
```
Now, for indexes:
* < 3: same value as in the parent genome
* >= 3 && <5: offspring[index] = parent[index + 2]
* >= 5: offspring[index] = parent[index + 5]



#### Insertion mutation and change_log
Each value in the change_log map corresponds to the index shift relative to the parent genome. The values of the newly inserted sites do not have any relation to the parent genome, therefore, the values for such keys could be arbitrary, as long as it can't be confused with shift. In order to not confuse it with shift, an additional variable can be added to the map, a boolean, which specifies whether key is an insertion:
```
{key : {val, inseet}}
```

E.g. updating our previous map with an insertion of 3 elements {20, 21, 22} at index 7:
```
{3 : {-2, false}}
{5 : {-5, false}
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

#### Deletions and insertion mutation and change_log

To sum up, change log consists of two data structures:
* change_log - keeps track of shifts in indexes when the insertions or deletions happen -> std::map -> keping the keys in sorted order allows updating only the keys > current key; searching for key takes logarithmic time
* segments_log - stores inserted segments -> std::unordered_map -> accessing a segment by key is constant time

If we keep both change_log and segments_log updated after every insertion, we can have randon access to a genome site and can reconstruct the offspring genome.


### Algorithm details
More details will be added on how the overwrite, insert, remove methods are implemented. This section will also include the analysis of time complexities and comparison with original algorithm. This section will also include animated explanation.

### Benchmarking compared with current Genome
Benchmarking was performed using Catch2 testing framework. The performance results will be shown here

