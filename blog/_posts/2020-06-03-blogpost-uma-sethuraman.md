---
layout: post
title: "MABE Blog Post - Uma Sethuraman"
date: 2020-06-03
author: Uma Sethuraman
---

## Introduction to Genomes in MABE
- **Genomes in MABE currently (version 1.0)**
    - Genomes in MABE are now represented as lists of values which can be read from, written to, and mutated from parent to offspring.
    - Every genome has a contiguous piece of memory to store its values. 
    - Genomes are copied from parent to offspring and mutations are then done on offspring genomes.
- **Issues with how genomes work currently**
    - Genomes are often very large, from hundreds of thousands of sites to millions of sites. Since the number of sites mutated in an offspring is usually significantly less than the number of sites which remain the same between parent and offspring, directly copying genomes from parent to offspring can be very inefficient in terms of time and memory. 

## The Change Logging Problem
- With change logging, genomes will only store the differences between parent and offspring genomes. Each genome will keep track of a log of changes, documenting the mutations between the last saved “parent” genome and the current genome. The “parent” genome will be reset whenever the changelog becomes too large. 
- Using the changelog, the current genome can be reconstructed. Any random site in the current genome can also be accessed without having to store a full copy of the current genome. Thus, change logging can save significant time and memory, especially for larger genomes. 

## My Algorithm for Change Logging
- **Data Structures:**
  - Each genome stores a changelog and an offset map.
    - **Changelog: ordered map**
      - The key represents the position in the current genome and the value represents the value at that position in the current genome.
      - Everything in the changelog will be values that aren’t in the parent genome, that have either been inserted or changed in the current genome through mutations.
    - **Offset map: ordered map**
      - We use the offset map for all keys that are not in the changelog. The key represents a position in the current genome. The value is the offset (how much that position has shifted from the parent genome to the current genome). 
      - When a key x isn’t in the changelog, we find the closest key in the offset map and subtract its offset from x to get the position in the parent. We can then access the correct value in the parent.
    <img align="left" src="Changelogging_Data_Structures.png">
    <p>&nbsp<p>
- **Insertion, Deletion, and Overwrite Mutations:**
  - **Insertion mutation:** inserts value(s) at a certain position in current genome and changes genome size
     <img src="Insertion_Demo_Once.gif" width="700" height="400" />
  - **Deletion mutation:** deletes value(s) at a certain position in current genome and changes genome size
    - Deletion Animation
  - **Overwrite mutation:** change the value of a single or multiple sites in the genome
    <img src="Overwrite_Demo_Once.gif" width="700" height="400" />
      
- **Random Access:**
  - To access position p in the current genome:
    - Check if p is in the changelog. If it is, that means it has been either inserted or modified since the parent, so we return p’s value from the changelog.
    - If p is not in the changelog, then find the closest key to p in the offset map. Subtract this key’s offset from p, and return that position’s value from the parent. In this case, the value at position p was never changed but position p was offsetted since the parent genome.
  - This implementation allows for fast random access, with time complexity of O(logn), where n is the number of elements in the changelog. This is because we always check if the requested position is in the changelog before returning the value directly from the changelog or from the parent.
  - Animation of random access with example mutations
  
## Algorithm Demonstration
  - Animation (or slides) showing a full walkthrough of my implementation with multiple mutations
  
## Results and Conclusion: 
  - Analysis of time and space complexity of my implementation
  - Graphs comparing the time/space complexity and performance of the current MABE genome implementation to my implementation
