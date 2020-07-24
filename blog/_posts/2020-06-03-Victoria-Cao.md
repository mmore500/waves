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

Like in the case of eevee and it's evolutions, if identical data between the mutations can be conserved, instead of copying the same shared gene semgments to all of the mutations, running an evolution loop will ideally take up less time with less page faults. 

To conserve as much space as possible, optimize run time, and still give the researcher random access to the genome, I propose a lightweight genome version built off of a segmented link list of genome site locations with a random accessing indexing table.

## Naive Approach ##
The naive approach is to have a piece of contiguous memory for every genome, to copy the whole genome for an offstring and apply shift mutations by standard memory move functions. 

![cloning goat](https://media0.giphy.com/media/ctWSqhTv0LXd6/giphy.gif){:width="50%"}

But why manually copy identical, or near identical, offspring when it's much faster to point to the areas that are the same and create local mutations when needed?

The downsides to creating a new genome for every organism is apparent; if the entropy between genomes within the population is low, then condensing non-unique data will lower memory consumption and optimize shifts on large scale genomes.

## The Proposed Method ##
To alleviate excess copying, my proposed method uses a linked list of segment nodes and an indexing table.

### SegmentNode ###
The SegmentNode structure contains:
    - Basic linked list node vairables (previous, next)
    - Shared pointer to vector of bytes
    - Starting index of data
    - Size of the data

![SegmentNode]({{ site.baseurl }}/assets/caovicto/SegmentNode.png){:width="60%"}

### SegmentList ###
Comprised of linked SegmentNodes, the SegmentList contains a linear readthrough of bytes that the gene contains. 

![SegmentList]({{ site.baseurl }}/assets/caovicto/SegmentList.png){:width="70%"}

If the data is not shared with another genome, insertion and deletion can occur directly on the genome. If not, two segments pointing towards the original data can be made, one pointing to the data before the insertion and one pointing after.

#### Insertion Demo on Shared Data ####
![insertion demo]({{ site.baseurl }}/assets/caovicto/insertDemo.gif){:width="100%"}

Insertion into non-unique data conserves as much memory as possible!

#### Largest Data Segment Size ####
To make insertions and deletions faster on unique data, a larger genome is broken up into segments of smaller data chunks.

![SegmentNode]({{ site.baseurl }}/assets/caovicto/SplitSize.png){:width="60%"}

<details>
  <summary>Nitty (not so) Gritty on Perfect Chunk Size</summary>

  With how much theory did me dirty, I decided to manually bench sizes that felt about right for the genomes without making the list too long. After using a basic linear regression on the chunk sizes and genome sizes that had the best results from my thought up many, I settled on 0.13*genomeSize. 

  How it settled on 0.13 nicely is a mystery.
</details>


## The Proposed Method that was Actually Faster ##
With that idea, it seemed much faster to use the splitting of nodes instead of actual data to insert into relatively large genomes (roughly 20,000 bytes and up); but benchmarks don't lie, and after benchmaking on genomes of size 100,000, 250,000 and 500,000 bytes, the benefits were only apparent on genomes larger than 250,000.

![sad graph]({{ site.baseurl }}/assets/caovicto/graphs/SadGraph.png){:width="100%"}

At least it does better at some point I thought! Until an avid user of computational evolution (mentor) pointed out genomes larger than 100,000 are seldom used.

![sad pikachu](https://media.comicbook.com/2017/04/pokemon-sad-moments-pikachu-crying-990351-1280x0.jpg){:width="50%"}

The only bright side of the benchmarks pointed at the tests of newly created genomes. In other words, smaller vector stringed together was still faster than creating a changelog.

Surprisingly just breaking up the vectors made significant improvements to runtime on various genome sizes. See <a href="https://caovicto.github.io/waves/blog/Victoria-Cao.html#results">results</a> to fast forward!


### Memory Pooling ###
To allow fast copying for the structure, a memory pool is created for each genome. The memory pool is a vector of reserved memory that allocates segment nodes.

![MemoryPool]({{ site.baseurl }}/assets/caovicto/MemoryPool.png){:width="100%"}


## Faster Access with Indexing Table ##
The Linked list structure gives a simple and eaily modifiable structure, but slow indexing speeds. To improve O(n), n is the nunber of nodes in the list, an index table with the offsets of each node into the genome will give an amortixed O(1) random access to any index.

Index table is a vector that contains the offset index into the genome and the node that the offset starts at.

![IndexTable]({{ site.baseurl }}/assets/caovicto/IndexTableDemo.png){:width="100%"}

### Pseudo-Code Find Algorithm ###

```python
TableEntry Find(index):
   # binary sesarch through Index Table 
    auto entry = lower_bound(IndexTable.begin(), IndexTable.end(), pair(index, 0)) 
   entry -= IndexTable.begin()

    if entry >= IndexTable.size() || (IndexTable[entry].first != index && entry)
        --entry

    found = IndexTable[entry]
    node = found.second
    localIndex = found.first   # Index to start inside the data vector

    # iterate through segment list if not in node
    while localIndex + Pool->GetSize(node)-1 < index && localIndex + Pool->GetSize(node) < SiteCount
        localIndex += Pool->GetSize(node)
        node = Pool->GetNext(node)

        # update index table
        IndexTable.push_back( {localIndex, node} )
        ++entry

    return {entry, node, localIndex}
```

Accessing a random location within the genome will give O(log(n)), with n being the size of the index table, if the index is within the table. If not, accessing will cost O(log(n)+m), with m being the extra nodes needed to traverse to find the segment with the index.

## Results ##
Comparing the naive approach and my current version highlights the improvements made to both memory consumption and runtime on a 100 replicates of each experiment. All benchmarking is done with Catch2's benchmarking functions.

Note: "Random" mutations are taken from a predetermined random list to fairly compare the performance of the genomes, with the mutations loop between an overwrite, insertion, and deletion.

The TestGenome is an implementation of the naive approach and GenomeLite of my proposed idea, the simple list of vectors.

### Cost of Reallocating ###
- graphs

### All Mutation Types ###
- graphs

### Evolution Loop with Random Mutation ###
- graphs

## Take-Aways ##
Through trying different implemtations and actually benchmarking them compared to the naive approach, the stark differences between theorized optimizations and actual optimizations were apparent. 

Even if those shiny new ideas were great, if the simple and plain idea works...

A man gotta do
<iframe width="560" height="315" src="https://www.youtube.com/watch?v=XejVB_fba04" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>