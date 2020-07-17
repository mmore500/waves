---
layout: post
title: "Victoria Cao Project"
date: 2020-06-03
author: Victoria Cao
---

## Problem at Hand

- The cost of large, relatively similar genomes takes a toll on memory space and speed while running digital evolution.
- To conserve as much space as possible, optimize run time, and still give the researcher random access to the genome, I propose a lightweight genome version built off of a segmented link list of genome site locations with a random accessing indexing table.

## Overall Method
- linked list of page size and localization of nodes in a node pool utililizes temporal and spacial locality
- traversing the nodes updates the index table, and linked list allows for O(1) shift mutations
- To suppliment the O(n) search time, an index table will give an amortized search time of O(1)


## Linked List for Memory Conservation
- cloning using smart pointers to data, and whenever a mutation is not used anymore, it it thrown away automatically
    - visual of organization of memory

- gif with insertion
![binary]({{ site.baseurl }}/assets/caovicto/insertDemo.gif){:width="100%"}

- gif with deletion
- gif with overwrite

## Random Access Indexing Table for List
- graphic of index table to linked list

- The index table will be updated on traversal and truncated on mutations
    - graphic of index table updating on mutation
    - grpahic of index table updating on traversal


## Results 
- Graph of comparing GenomeLite results to naive genome mutation benchmarks
- Visual graphic comparing GenomeLite Byte usage vs naive genome
