---
layout: post
title: "Advancing Genomes in MABE"
date: 2020-07-31
author: Uma Sethuraman
---

## Project Introduction
MABE, or Modular Agent Based Evolution Framework, is a platform which allows users to create populations of digital organisms and analyze the effects of virtually evolving these populations. One of the key components of MABE is the genome class, which represents genomes for digital organisms in the population. The goal of this project is to advance the genome class in MABE by optimizing its memory consumption and runtime.

If you would like to learn more about the MABE framework, take a look at this *[Introduction to MABE](https://szendejo.github.io/waves/blog/Team-MABE.html)* blogpost co-written by my teammates and I!

## Genomes in MABE 1.0
In biology, genomes are an organism's entire set of DNA and allow organisms to maintain themselves and function properly. Similarly, in MABE. the genomes of digital organisms are represented as lists of values which can be read from, written to, and mutated from parent to offspring. Every genome has a contiguous piece of memory to store its values.

## The Problem
- Genomes are often very large, from **hundreds of thousands** of sites to **millions** of sites.
- Genomes in MABE 1.0 are copied from parent to offspring, and the offspring will contain some mutations from the parent.
- However, with large genome sizes and low mutation rates, the number of sites mutated in an offspring is usually significantly less than the number of sites which remain the same between parent and offspring. 
- This makes the current genome class’s approach of directly copying genomes from parent to offspring very inefficient in terms of time and memory, much like the gif below!

![genome copies]({{ site.baseurl }}/assets/uma-sethuraman/GenomeCopies.gif){:style="width: 100%;"}

## Change Logging as a Solution
- With change logging, genomes will only store the differences between parent and offspring genomes. 
- Each genome will keep track of a log of changes, documenting the mutations between the last saved “parent” genome and the current genome. The “parent” genome should be reset whenever the changelog becomes too large. 
- Using the changelog, the current genome can be reconstructed. 
- Any random site in the current genome can also be accessed without having to store a full copy of the current genome. 
- Thus, change logging can save significant time and memory, especially for larger genomes. 

## My Algorithm for Change Logging
- **Data Structures:**
  - Each genome stores a **changelog** and an **offset map**.
    - **Changelog: ordered map**
      - The **key** represents the **position** in the current genome.
      - The **value** represents the **value at that position** in the current genome.
      - Everything in the changelog will be values that aren’t in the parent genome, that have either been **inserted or changed** in the current genome through mutations.
    - **Offset map: ordered map**
      - We check the offset map for all keys that are not in the changelog. 
      - The **key** represents a **position** in the current genome. 
      - The **value** is the **offset** (how much that position has shifted from the parent genome to the current genome). 
      - The offset map can be viewed in ranges, where keys between key A and B have the offset of key A (the lower bound).
      - When a key x isn’t in the changelog, we find the closest key in the offset map that is less than x and subtract its offset from x to get the position in the parent. We can then access the correct value in the parent.
      - The offset map will always begin with a single key-value pair (0,0) to indicate that all positions 0 onward have not been offsetted yet.
    
    ![changelog structures]({{ site.baseurl }}/assets/uma-sethuraman/ChangeloggingDataStructures.png){:style="width: 100%;"}

- **Insert, Remove, and Overwrite Mutations:**
  - **Insert mutation:** inserts value(s) at a certain position in current genome and changes genome size
    - The demo below goes through all of the steps involved in an insertion:
     ![insertion demo]({{ site.baseurl }}/assets/uma-sethuraman/InsertionDemo.gif){:style="width: 100%;"}
  - **Remove mutation:** deletes value(s) at a certain position in current genome and changes genome size
    - The demo below goes through all of the steps involved in a deletion/remove:
     ![remove demo]({{ site.baseurl }}/assets/uma-sethuraman/RemoveDemo.gif){:style="width: 100%;"}
  - **Overwrite mutation:** change the value of a single or multiple sites in the genome
    - The demo below goes through all of the steps involved in an overwrite:
    ![overwrite demo]({{ site.baseurl }}/assets/uma-sethuraman/OverwriteDemo.gif){:style="width: 100%;"}
      
- **Random Access:**
  - The `getCurrentGenomeAt` function below shows how to access position (pos) in the current genome.
  
    ``` C++
    std::byte UmaGenome::getCurrentGenomeAt(int pos) {
    
        /* create an iterator for the changelog
           and check if the changelog contains pos */
        std::map<int,std::byte>::iterator changelog_it;
        changelog_it = changelog.find(pos);
        
        if (changelog_it != changelog.end()) {
            /* changelog does contain pos
               so just return the value from changelog */
            return changelog_it->second;
        }
        else {
            /* changelog does not contain pos
               so get the value from the parent */
            
            /* create an iterator for the offset map
               and check if pos is in the offset map */
            std::map<int,int>::iterator offsetmap_it;
            offsetmap_it = offsetMap.find(pos);
            
            int pos_offset = 0; // the offset used to index into the parent
            
            if (offsetmap_it != offsetMap.end()) {
                // offset map contains pos, so just get pos' offset
                pos_offset = offsetmap_it->second;
            }
            else {
                /* offset map doesn't contain pos
                   so must get offset of the closest key
                   less than pos (pos' lower bound) */
                std::map<int,int>::iterator lb_it;
                lb_it = offsetMap.lower_bound(pos);
                if (lb_it != offsetMap.begin())
                    --lb_it;
                pos_offset = lb_it->second;
        }

        // get value from parent at index (pos-pos_offset)
        return parent->at(pos-pos_offset);
    }
    ```
  - This implementation allows for fast random access. In the case that the requested position is in the changelog, the time complexity is `O(logn)`, where `n` is the number of elements in the changelog. This is because we check if the requested position is in the changelog before returning the value. In the case that the requested position is not in the changelog, the time complexity is `O(log(mn))`, where `m` is the number of elements in the offset map and `n` is the number of elements in the changelog. This is because we check if the requested position is in the changelog first (`logn`). Since it isn't in this case, we also check if the position is in the offset map (`logm`), and `logm+logn = O(log(mn))`.
  
## Results: 
  - Analysis of time and space complexity of my implementation
  - Graphs comparing the time/space complexity and performance of the current MABE genome implementation to my implementation
  - Benchmarking of the different implementations is done through catch2.
  - Results not yet finalized
  
## Conclusion:
- I’ve really enjoyed working on this project with a great team of participants and mentors. It’s been so helpful to have a team to collaborate with, debug with, bounce ideas off of, and learn from. Each participant in my team implemented a different algorithm for this problem in order to test out multiple diffferent solutions. I’m really excited to have contributed to advancing genomes in MABE through my project this summer. I can’t wait to see how not only genomes but all parts of MABE will continue to evolve (pun intended😂) in the future! Thank you to my wonderful mentors and great teammates who I’ve listed below! Thank you also to the entire WAVES team who has made this summer program's experience so amazing!

## Team MABE 🎉
- **Mentors:** Clifford Bohm, Jory Schossau, Jose Hernandez
- **Teammates:** Stephanie Zendejo, Tetiana Dadakova, Victoria Cao, Jamell Dacon



###### This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.
