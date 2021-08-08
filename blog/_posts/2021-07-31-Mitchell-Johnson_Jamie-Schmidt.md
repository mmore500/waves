---
layout: topic
title: "Development of MABE2"
date: 2021-07-31
author: Mitchell Johnson & Jamie Schmidt
---

### Development of MABE2

## Introduction
-what is MABE2
For our project, we focused our work mostly on 
-improving the end user experience through the development of DynamicOrg.
-adding support for brains and genomes, both of which have base classes

To quote the [Github for MABE2](https://github.com/mercere99/MABE2), MABE is a software framework deigned to easily build and customize software for evolutionary computation or artificial life.  The resulting systems should be useful for studying evolutionary dynamics, solving complex problems, comparing evolving systems, or exploring the open-ended power of evolution.  

MABE, accessible [here](https://github.com/Hintzelab/MABE/wiki), stands for Modular Agent-Based Evolution and was one of the first true digital evolution frameworks.  It was structured in this fashion:

![MABE structure](https://github.com/Hintzelab/MABE/wiki/images/MABE_Overview.png)

and, though powerful, could of course be improved.  The creation of the 2.0 version of MABE, called MABE2, was the focus of our project.  Our main focus was on refining the underlying architecture of MABE to be more end user-friendly, particularly in designing custom experiments.  The culmination of our efforts was in the creation of DynamicOrg, an Organism which was near-completely abstracted to allow for any combination of Genomes and Brains, as assigned through the config file. 

## Genomes / author: jamie
Genomes in MABE2 are just repositories of mutatable information.  The most basic kinds are vectors of some type, and (unlike in MABE), they aren't hidden inside Organisms which manage everything about them, but they are actively added to them and manage themselves.  This means that to mutate a Genome, any Genome, the Organism just tells the Genome to mutate itself and the Genome does.  No longer will the Organism run all the mutation functions itself, now it just delegates.  This, critically, means that Organisms now no longer need to know what kinds of Genomes they have at all.

Genomes in MABE2 are also accessed differently -- regardless of what type the Genome is, it can be read from and written to as if it were made of doubles, ints, bytes, or bits.  They can also be read from and written to in bulk, and they can be "scaled", where what you see is automatically scaled to whatever the Genome's actual range of values is.  

Moreover, Genomes are often handled through the Genome::Head class, which allows for easy and abstract use of Genomes.  Heads move along a Genome, and through a Head, any Genome operation can be accomplished, including searching (for values, ranges, multiple values, and ranges of multiple values) and all aforementioned reads and writes.  

This means that it is often beneficial to pass Genomes as Heads if you want to be as generic as possible while still allowing full functionality of the Genome.

## DynamicOrg / author: mitchell and jamie, predominantly michell though
-what is an organism in MABE2 and how it was originally used to create an expiriment
-how DynamicOrg makes the entire process of designing, implementing, and running an expiriment much easier

In MABE2, an Organism can be thought of as a box which contains some number of Genomes and some number of Brains.  An Organism has three main functions: 
1. An Organism needs to be able to copy itself to form one or more children.
2. An Organism needs to be able to mutate itself in some way for evolution to happen.
3. An Organism needs to return some kind of object which consists of all the data the Evaluator needs. 

Of course, different Organisms can handle things differently, so for example an Organism in MABE (call it a BitOrg) could consist entirely of one TypedGenome<bool>, which is a Genome that is composed entirely of bits.  It can copy that whenever it reproduces, it can flip some random number of bits every time it mutates, and it can simply return the bits of that Genome in a BitVector (a specialized vector of bits which Empirical uses in place of std::BitMaps and std::vector<bool>s).
  
But what's a DynamicOrg?  Well, a DynamicOrg is an Organism that is nearly totally built by the config file.  Unlike our previous example, where the BitOrg knew it had a Genome of bits and how to mutate and return it, a DynamicOrg can't.  Ideally, you'd be able to specify what Genomes and Brains were in this DynamicOrg, and that would be it.  Specifying Genomes is relatively easy, since they're all completely self-contained, but the Brains pose a more significant challenge, which is why we'll be discussing them in the section after this.

Now, a DynamicOrg must necessarily be significantly less restrictive.  Copying itself is fine, we just copy all its Genomes and Brains.  Mutations are also reasonably simple, since all we need to do is mutate every Genome in it.  But how on earth do we know what to return?  Simply put, we don't, so we just want to return an emp::DataMap.  The Evaluator is what knows, so we let the Evalutor decide.  The Brains then all edit this emp::DataMap in order, in whatever way they are designed to do.  
  
In the config file, this means all a DynamicOrg needs is a list of names of all the Genomes and Brains it will contain.  So long as all these Genomes and Brains are properly named in the confic file, this will work seamlessly. 
  
## Brains / author: jamie
-how new brain functionality was implemented before we made the switch
-how/where the functionality lives now, how its better this way
  
Brains are the processors of all the Genomes in an Organism.  They are only ever accessed through their process function, which takes an emp::DataMap and then processes all the relevent information.  In DynamicOrg in particular, they are all given a DataMap containing the Genomes in the DynamicOrg, and as each Brain will know which Genomes matter for its calculations, it will then access those Genomes, process them, and write its output to the DataMap.
  
The Brain will be configured with the names of the Genomes it works with, along with the name of its output.  This means that you can make identical Brains which still deal with different Genomes and write their outputs to different addresses in the DataMap.  
  
Many Brains, such as Markov Brains, are built from Genomes themselves, and this also occurs in the process function.  This allows for Brains that evolve over time, and the Evaluator can either receive the Brain itself or whatever decision-making process it has built from the Genomes the Brain was given.
  
## Evaluators / author: jamie
-how new evaluator functionality was implemented before we made the switch
-how/where the functionality lives now, how its better this way
  
An Evaluator is, perhaps, the thing most users will spend the most time with for their custom experiments.  In any evolutionary situation, Organisms will need to be evaluated on whatever traits they are supposed to be evolving, and the Evaluator assigns their fitness value from whatever outputs the Brains provide.  
  
When coding an Evaluator, the most important thing is to make sure that, for whatever inputs your evaluate function requires, you've got Brains that can supply it.  They're configured in the same way that Brains and Genomes are, by being given a list of input names that correspond to the types that the Evaluator is expecting.
  
We did not make many changes to the Evaluator model, aside from making it compatible with DynamicOrgs, which in turn made them significantly easier to customize since every DynamicOrg Evaluator follows the same steps: 
  1. Get the emp::DataMap
  2. Get all the input values you want from it
  3. Calculate fitness from them
  4. Return fitness

## Tutorial - creating and running Aagos using DynamicOrg / author: mitchell
-explanation of aagos and how it works
-writing the evaluator
-writing the aagos brain
-putting it all together in the .gen file -> .mabe file
-running the expiriment

## Conclusion
-reiterate how our work greatly simplified the end user expirience using mabe2

## Future plans / Work we didn't complete
-anything we wish we could have completed but didn't have time to
