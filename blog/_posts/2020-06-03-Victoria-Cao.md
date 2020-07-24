---
layout: post
title: "Victoria Cao Project"
date: 2020-07-17
author: Victoria Cao
---

## The Problem at Hand ##
Genomes are often large and on cloning and mutating those genomes, runtime on copying and memory movement operations on shift mutations takes a toll on runtime and memory consumption. 

When copying and mutating, offsprings from the same parents will often contain stretches of identical data.

![eevee gif](https://data.whicdn.com/images/251897145/original.gif){:width="100%"}

<details>
  <summary>Haven't seen Pokemon?</summary>
  The gif shows many evolutions from eevee! You can think of eevee like the parent genome, and the evolutions as mutated offsprings.
</details>

Like in the case of eevee and it's evolutions, if identical data between the mutations can be conserved, instead of copying the same shared gene semgments to all of the mutations, running an evolution loop will ideally take up less time with less page faults. To conserve as much space as possible, optimize run time, and still give the researcher random access to the genome, I propose a lightweight genome version built off of a segmented link list of genome site locations with a random accessing indexing table.

## Naive Approach ##
The naive approach is to have a piece of contiguous memory for every genome, to copy the whole genome for an offstring and apply shift mutations by standard memory move functions. 

![cloning goat](https://media0.giphy.com/media/ctWSqhTv0LXd6/giphy.gif){:width="50%"}

But why manually copy identical, or near identical, offspring when it's much faster to point to the areas that are the same and create local mutations when needed?

The downsides to creating a new genome for every organism is apparent; if the entropy between genomes within the population is low, then condensing non-unique data will lower memory consumption and optimize shifts on large scale genomes. Though random access will be conserved in this naive genome architecture, the cost of the excess memory and speed of insertion and deletion outweighs that benefit.

## Proposed Method ##
To alleviate excess copying, my proposed method uses a linked list of segment nodes and an indexing table.

### SegmentNode ###
The SegmentNode structure contains:
    - Basic linked list node vairables (previous, next)
    - Shared pointer to vector of bytes
    - Starting index of data
    - Size of the data

![SegmentNode]({{ site.baseurl }}/assets/caovicto/SegmentNode.png){:width="100%"}

### SegmentList ###
Comprised of linked SegmentNodes, the SegmentList contains a linear readthrough of bytes that the gene contains. 

![SegmentList]({{ site.baseurl }}/assets/caovicto/SegmentList.png){:width="100%"}

## SegmentList Details ##
The linking of virtual references to memory allows a segment of data to be edited if it is the only genome using the data, and if not, then the overhead of allocating and copying the segment will not be needed if it is non-unique.


### Insertion Demo ###
![insertion demo]({{ site.baseurl }}/assets/caovicto/insertDemo.gif){:width="100%"}

Insertion into non-unique data conserves as much memory as possible, while also giving *O(1) shift mutations.


### Memory Pooling ###
To allow fast copying for the structure, a memory pool is created for each genome. The memory pool is a vector of reserved memory that allocates segment nodes.

![MemoryPool]({{ site.baseurl }}/assets/caovicto/MemoryPool.png){:width="100%"}

Instead of pointing to an address, the previous and next pointers within the SegmentNodes are indicies into the memory pool, allowing for a relatively shallow copy on reallocation on cloning the genome.

<details>
  <summary>Nitty Gritty Optimization Boosters</summary>
  
  #### Unique vs Non-Unique Data ####
  With the use of shared pointers, the algorithm is privy to the number SegmentNode's that use the data segment. If only that node is using the data, then instead of "splitting" the data into two nodes, the data can be altered directly, saving time on copying the broken up segments to a new list when it needs reallocation.

  #### Customizing Data Size ####
  On creation of the SegmentList based on a desginated genome size, a custom vector is designated as the starting allocation of each SegmentNode. To save time on unique insertions and deletions, with a genome of size 200,000 for example, instead of allocating one node with a size of 200,000 to start, multiple nodes with a maximum size of 64,000 will be strung together.

</details>

## Faster Access with Indexing Table ##
The Linked list structure gives a simple and eaily modifiable structure, but slow indexing speeds. To improve O(n), n is the nunber of nodes in the list, an index table with the offsets of each node into the genome will give an amortixed O(1) random access to any index.

Index table is a vector that contains the offset index into the genome and the node that the offset starts at.

![IndexTable]({{ site.baseurl }}/assets/caovicto/IndexTableDemo.png){:width="100%"}

### Pseudo-Code Find Algorithm ###

> TableEntry Find(index):
>   // binary sesarch through Index Table 
>    auto entry = lower_bound(IndexTable.begin(), IndexTable.end(), pair(index, 0)) 
>   entry -= IndexTable.begin()
>
>    if entry >= IndexTable.size() || (IndexTable[entry].first != index && entry)
>        --entry
>
>    found = IndexTable[entry]
>    node = found.second
>    localIndex = found.first   // Index to start inside the data vector
>
>    // iterate through segment list if not in node
>    while localIndex + Pool->GetSize(node)-1 < index && localIndex + Pool->GetSize(node) < SiteCount
>        localIndex += Pool->GetSize(node)
>        node = Pool->GetNext(node)
>
>        // update index table
>        IndexTable.push_back( {localIndex, node} )
>        ++entry
>
>    return {entry, node, localIndex}
>
>

Accessing a random location within the genome will give O(log(n)), with n being the size of the index table, if the index is within the table. If not, accessing will cost O(log(n)+m), with m being the extra nodes needed to traverse to find the segment with the index.

## Results 
Comparing the naive approach and my current version highlights the improvements made to both memory consumption and runtime.

Note: "Random" mutations are taken from a predetermined random list to fairly compare the performance of the genomes.

### Single Clone Random Mutation ###
![single clone 0.5% mutation]({{ site.baseurl }}/assets/caovicto/graphs/singleClone_005.png)
![single clone 1% mutation]({{ site.baseurl }}/assets/caovicto/graphs/singleClone_01.png)