---
layout: post
title: ""
date: 2020-07-29
author: Stephanie Zendejo
---

# Introduction
I designed a genome class named StephanieGenome in MABE. The goal was to improve the time and memory taken to process genome mutations. Genomes in MABE were copied over from a parent genome to an offspring genome at every generation. The offspring genome at the last generation would contain a mutated parent genome. I implemented a way to reduce the number of copies at every generation by using a changelog. The changelog stores values, and offsets for multiple types of mutations. In order to generate a offspring genome, the changelog is referenced and applied to the parent genome. 

> Changelog? Huh? An introduction to MABE and the problem can be found [here!](https://szendejo.github.io/waves/blog/Team-MABE.html)  

# My Approach To The Changelog Problem  
The parent genome is represented as a **std::vector** of sites. Each site in the parent genome contains a numeric value that is represented as a **std::byte** in memory. The position of the site in the parent genome is the **index**. A changelog is represented as an **ordered std::map<size_t, Site>**. Size_t is the index of the site mutated, and Site is the struct to contain the mutated site's information. The Site struct identifies what type of mutation has been applied to the site, and what the new value is (if applicable).  
```c++
struct Site {
	size_t insertOffset;  	  // Insert mutation at site
	size_t removeOffset;   	  // Remove mutation at site
	std::byte value;       	  // Mutated number value
};	
std::map<size_t, Site> changelog; // Map key is index of site in the parent genome
                                  // Map value is Site structure
std::vector<std::byte> sites;     // parent genome
```  
<!-- ![Parent Genome in all its glory](https://i.imgur.com/mekOG1s.png) -->
<img src="https://i.imgur.com/mekOG1s.png" width="600" height="65" border="10" />  

**Figure Parent Genome.** Parent Genome contains values at each of its sites.  

### Mutation Signatures
Here's a basic idea of what each of the functions do. To view the mutations in action, click on the linked images.  
**Overwrite**  
  * Loops through segment vector
  * Adds overwrite mutations to the changelog  
<!--![OverWrite Example](https://i.imgur.com/wu7gBxK.gif) -->
<a href="https://i.imgur.com/wu7gBxK.gif
" target="_blank"><img src="https://i.imgur.com/B3HiqBW.jpg" 
alt="Overwrite Example Gif" width="400" height="180" border="10" /></a>  

**Insert**  
  * Shift sites in the changelog to the right by size of the segment vector
  * Loops through segment vector
  * Adds insert mutations to the changelog  
<!--![Insert Example](https://i.imgur.com/0rZ4Bai.gif) -->
<a href="https://i.imgur.com/0rZ4Bai.gif
" target="_blank"><img src="https://i.imgur.com/0lcBnvV.jpg" 
alt="Overwrite Example Gif" width="500" height="180" border="10" /></a>  

**Remove**  
  * Removes sites in the changelog if they exist
     * Takes into account if sites removed in the changelog had insert or remove mutations
  * Shift sites in the changelog to the left
  * Adds remove mutation to the changelog  
<!-- ![Remove Example](https://i.imgur.com/tus7plB.gif) -->
<a href="https://i.imgur.com/tus7plB.gif
" target="_blank"><img src="https://i.imgur.com/6EihJZ9.jpg" 
alt="Overwrite Example Gif" width="400" height="180" border="10" /></a>  

 
The overwrite and insert signatures contain a **segment std::vector** as an argument. The segment vector is a collection of mutations that will be added to the changelog starting at the given index. 
> _insert(6, {44, 55, 66}) is the equivalent of inserting the following mutations to the changelog:_   
> _site at index 6 with a value of 44_  
> _site at index 7 with a value of 55_  
> _site at index 8 with a value of 66_  

```c++
virtual void overwrite(size_t index, const std::vector<std::byte>& segment); 
		// Ex. Starting at index 5, overwrite 3 sites with the values 11, 22, 33

virtual void insert(size_t index, const std::vector<std::byte>& segment);    
		// Ex. Starting at index 6, insert 3 new sites with the values 44, 55, 66

virtual void remove(size_t index, size_t segmentSize); 	     
		// Ex. At index 7, remove 3 sites
```

### Adding Entries In The Changelog
Let's apply some basic mutations to a parent genome.  
<!--![Parent Genome Example](https://i.imgur.com/agc2bAi.png) -->
<img src="https://i.imgur.com/agc2bAi.png" width="600" height="45" border="10" />  

1. Overwrite mutation to site at index 2. The overwritten sites will have values of 11, 22, 33.  

   | Key | Site Value | Remove Offset  | Insert Offset |  
   | --- |:----------:|:--------------:| -------------:|  
   |  2  |     11     |       0        |       0       |    
   |  3  |     22     |       0        |       0       |    
   |  4  |     33     |       0        |       0       |  
   
   > _Segment vector contains 3 site values. Starting at index 2, each site value will be either added in the Changelog or edited if it exists. Index key 2 does   not exist, so it's inserted in the Changelog. Site Value is set to 44. Since this is an overwrite mutation, the size of the offspring genome is not affected. Remove Offset and Insert offset are both set to zero. The steps are repeated for each site value in the segment vector._    

2. Insert mutation to site at index 1. The inserted site will have values of 44, 55, 66.  

   | Key | Site Value | Remove Offset  | Insert Offset |   
   | --- |:----------:|:--------------:| -------------:|  
   |  1  |     44     |       0        |       1       |    
   |  2  |     55     |       0        |       1       |    
   |  3  |     66     |       0        |       1       |   
   |  5  |     11     |       0        |       0       |    
   |  6  |     22     |       0        |       0       |    
   |  7  |     33     |       0        |       0       |  
   
   > _Shift all sites in the Changelog to the right by 3, the number of sites inserted. Site at key 2 becomes site at key 5. Add entries to the Changelog map starting at index 1 with their values. Because these are insert mutations, Insert Offset is set to 1. Offspring genome size increases by 3._  
 
3. Remove mutation to site at index 6. Remove 3 sites.   

   | Key | Site Value | Remove Offset  | Insert Offset |   
   | --- |:----------:|:--------------:| -------------:|  
   |  1  |     44     |       0        |       1       |    
   |  2  |     55     |       0        |       1       |    
   |  3  |     66     |       0        |       1       |   
   |  5  |     11     |       0        |       0       |    
   |  6  |      0     |       3        |       0       |   
   
   > _Starting at index 6, sites 6 7 and 8 will be removed. Sites 6 and 7 exist in the Changelog. The overwrite mutations are removed. A new entry is added at site 6, with a Remove Offset of 3._    

4. Insert mutation to site at index 6. The inserted site will have values of 88, 99.  

   | Key | Site Value | Remove Offset  | Insert Offset |   
   | --- |:----------:|:--------------:| -------------:|  
   |  1  |     44     |       0        |       1       |    
   |  2  |     55     |       0        |       1       |    
   |  3  |     66     |       0        |       1       |   
   |  5  |     11     |       0        |       0       |    
   |  6  |     88     |       0        |       1       |       
   |  7  |     99     |       0        |       1       |       
   |  8  |      0     |       3        |       0       |   
   
   > _Shift all sites in the Changelog to the right by 2, the number of sites inserted. Site at key 6 becomes site at key 8. Add entries to the Changelog map starting at index 6 with their values. Because these are insert mutations, Insert Offset is set to 1. Offspring genome size increases by 2._    

5. Remove mutation to site at index 5. Remove 3 sites.  

   | Key | Site Value | Remove Offset  | Insert Offset |   
   | --- |:----------:|:--------------:| -------------:|  
   |  1  |     44     |       0        |       1       |    
   |  2  |     55     |       0        |       1       |    
   |  3  |     66     |       0        |       1       |   
   |  5  |      0     |       3        |       0       |   
   
   > _Starting at index 5, sites 5 6 7 will be removed. The affected overwrite and insert mutations sites are removed. The remaining sites in the changelog are shifted over to the left by 3, the number of sites removed. Site at key 8 becomes site at key 5._     
  

Great! All mutations have been recorded. Much like this rendition of Celine Dion's _My Heart Will Go On_,  

<a href="https://www.youtube.com/watch?v=X2WH8mHJnhM
" target="_blank"><img src="https://i.imgur.com/EntZNrV.png" 
alt="Flute Rendition of My Heart Will Go On" width="450" height="240" border="10" /></a>  

this genome ~~heart~~ will go on to the next generation.

### Generating The Offspring Genome  
A **std::vector** named **modifiedSites** contains the offspring genome. Each position in the modifiedSites vector will be populated from either the changelog if an entry exists, or from the parent genome. Every insert mutation in the changelog increases the parent genome size by one. Every remove mutation in the changelog decreases the parent genome by the number of sites removed. **Offset** represented as an integer, keeps track of the position difference between the parent genome and the offspring genome.
```c
void StephanieGenome::generateNewGenome() {
	modifiedSites.resize(genomeSize);
	int offset = 0;

	// Create an offspring genome
	for (int i = 0; i < genomeSize; i++) {

		// Index does not exist in the changelog
		if (!changelog.count(i)) {
			modifiedSites[i] = sites[i + offset];
		}

		// Index exists in changelog and site is a overwrite mutation
		else if (changelog.count(i) && (changelog[i].removeOffset == 0 && changelog[i].insertOffset == 0)) {
			modifiedSites[i] = changelog[i].value;
		}

		// Index exists in changelog and site is an insert mutation
		else if (changelog.count(i) && changelog[i].insertOffset > 0) {
			modifiedSites[i] = changelog[i].value;
			offset -= 1;
		}

		// Index exists in changelog and site is a remove mutation
		else if (changelog.count(i) && changelog[i].removeOffset > 0) {
			offset += (int)changelog[i].removeOffset;
			modifiedSites[i] = sites[i + offset];
		}
	}
}
```  
A position counter starts at 0 in the parent genome. An index counter starts at 0 in the offspring genome and begins populating the sites.  
* **Index exists in changelog**, type of mutation is identified   
   * Insert mutation, offset is subtracted by one  
   * Remove mutation, offset is added by the remove offset value   
* **Index does not exist in changelog**, new position of the parent genome is calculated  
   * New position = index + offset.  
   _ex. index 4 does not exist in the changelog and the offset = -3_  
   _new position in parent genome = 4 + (-3) = 2_  
   _get value in parent genome at position 2_  

![Changelog Gif](https://i.imgur.com/djVEX3n.gif)  
**Figure Generating the Offspring Genome.** 

# Time vs. Memory  
## Benchmarking  
Let's put StephanieGenome to the test and compare it to TestGenome. TestGenome is an implementation of the naive approach. Mutations were applied to genomes at the mutation rate of 0.001. The mutation rate modifies the starting values of the parent genome. The genome sizes were 5,000 through 100,000 std::bytes.
![Overwrite Graph](https://i.imgur.com/HZAmJjL.png)  
![Insert Graph](https://i.imgur.com/13sT2cI.png)  
![Remove Graph](https://i.imgur.com/hMD6uwP.png)  

## Verdict  
Although the speeds are somewhat similar for overwrite and insert mutations, there is a significant slowdown for remove mutations. I experienced a lot of trouble designing and implementing the remove signature, which most likely explains the slowdown. In the end, TestGenome is found to be faster. The StephanieGenome solution is not optimal for a random access model because of the need to call generateNewGenome() to create the offspring genome. However, it has potential use using a gene centric view. In the gene centric view, only the details about the genomes are needed. The details would be where the genes are in a genome (changelog entries) and what is in the genome that is not a part of the gene (changelog entries with remove offsets).  

## Conclusion
In summary, implementing the proposed solution proved to be less efficient than the naive solution. I learned benchmarking is key to figuring out the best implementation for code. Despite the fact that each team member implemented a unique solution, discussing implementations allowed us to bounce ideas off one another and ask plenty of questions. Many brains is better than one! Research may not always give the preferred answer, but the learning experience is invaluable. To quote Zora Neale Hurston, _"Research is formalized curiosity. It is poking and prying with a purpose."_  
  
# Acknowledgements  
I would like to give a sincere thank you to my mentors, my team members, and the WAVES Workshop for the wonderful experience! :smile: I have gained a deeper understanding of how to design and implement algorithms, harness the power of the C++ standard library, and optimize code. 

**Mentors:** Clifford Bohm, Jory Schossau, Jose Hernandez  
**Team Members:** Jamell Dacon, Tetiana Dadakova, Victoria Cao, Uma Sethuraman  

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

