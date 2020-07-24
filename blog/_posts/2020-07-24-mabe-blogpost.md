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
E.g. range map with entries `{2, -2}, {5, 3}` corresponds to the following mapping:
```
2 : -2
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

### Algorithm details
More details will be added on how the overwrite, insert, remove methods are implemented. This section will also include the analysis of time complexities and comparison with original algorithm. This section will also include animated explanation.

### Benchmarking compared with current Genome
Benchmarking was performed using Catch2 testing framework. The performance results will be shown here

