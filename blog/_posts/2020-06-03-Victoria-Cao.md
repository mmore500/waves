---
layout: post
title: "Victoria Cao Project"
date: 2020-07-17
author: Victoria Cao
---

## Problem at Hand
Genomes are often large and on cloning and mutating those genomes, runtime on copying and memory movement operations on shift mutations takes a toll on runtime and memory consumption. 

When copying and mutating, offsprings from the same parents will often contain stretches of identical data.

![binary](https://data.whicdn.com/images/251897145/original.gif){:width="100%"}

To conserve as much space as possible, optimize run time, and still give the researcher random access to the genome, I propose a lightweight genome version built off of a segmented link list of genome site locations with a random accessing indexing table.

## Naive Approach
The naive approach is to have a piece of contiguous memory for every genome, to copy the whole genome for an offstring and apply shift mutations by standard memory move functions. 

![binary](https://media0.giphy.com/media/ctWSqhTv0LXd6/giphy.gif){:width="100%"}


The downsides to creating a new genome for every organism is apparent; if the entropy between genomes within the population is low, then condensing non-unique data will lower memory consumption and optimize shifts on large scale genomes.

- image of lots of offspring that share similar genome

Though random access will be conserved, the cost of the excess memory and speed of insertion and deletion outweighs that benefit.

## Proposed Method
To alleviate excess copying, my proposed method uses a linked list of segment nodes and an indexing table.

- SegmentNode
    - The side of the data segment maxes out around a standard page size in bytes (4098 bytes) for genome segments, which localizes retrieval of data from within the page. of nodes in a node pool utililizes temporal and spacial locality.
    - The data segments are controlled through shared pointers, so once a node is no longer pointing to the gene segment, the mutations will be deallocated from memory.
    - On mutations, if the data is non unique, the nodes holding the virtual memory address split and or change to reflect the data without altering shared genes.
    ![binary](https://thumbs.gfycat.com/GoodAgileAtlasmoth-small.gif){:width="100%"}

- SegmentList
    - The segment list is comprised of a linked list of SegmentNodes.
    - simple info graphic

- traversing the nodes updates the index table, and linked list allows for O(1) shift mutations
- To suppliment the O(n) search time, an index table will give an amortized search time of O(1)

## Linked List Methods
The linking of virtual references to memory allows a segment of data to be edited if it is the only genome using the data, and if not, then the overhead of allocating and copying the segment will not be needed if it is non-unique.


Insertion Demo
![binary]({{ site.baseurl }}/assets/caovicto/insertDemo.gif){:width="100%"}
- Insertion into non-unique data conserves as much memory as possible, while also giving *O(1) shift mutations.

- Deletion Demo
- Overwrite Demo


## Memory Pooling
To allow fast copying for the structure, a memory pool is created for each genome. The memory pool is a vector of reserved memory that allocates segment nodes.

- visual of organization of memory


## Random Access Indexing Table
The Linked list structure gives a simple and eaily modifiable structure, but slow indexing speeds. To improve O(n), n is the nunber of nodes in the list, an index table with the offsets of each node into the genome will give an amortixed O(1) random access to any index.

Index table is a vector that contains the offset index into the genome and the node that the offset starts at.

- Visual of Index table 
![binary]({{ site.baseurl }}/assets/caovicto/IndexTableDemo.png){:width="100%"}
    - To index into 400, there will be a binary search on the vector to find the lowest bound offset that contains the index by comparing if the index is within the offset plus the node size. Since 400 is within the boundary of 0-3000, the algorithm moves to the first node and from there subtracts the index by the offset of the node. The local index in the node for 400 is 400-0, so index 400 is in index 400 at the first node.

- The index table will be updated on traversal and truncated on mutations
    - graphic of index table updating on mutation
    - graphic of index table updating on traversal

## Results 
Comparing the naive approach and my current version highlights the improvements made to both memory consumption and runtime.

- Graph of comparing GenomeLite results to naive genome mutation benchmarks
- Visual graphic comparing GenomeLite Byte usage vs naive genome
