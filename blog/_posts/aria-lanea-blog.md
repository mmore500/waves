---
layout: post
title: "Planning for the Future of MABE2"
date: 2021-08-06
author: Aria Killibrew Bruehl and Lanea Rohan
---

## Outline

# :soon: Planning for the Future of MABE2: A Summer of Documentation and Testing
​
Hello! This summer we (Lanea Rohan, '22 Grinnel College, and Aria Killebrew Bruehl,
'23 Reed College) participated in the WAVES workshop through Michigan State University.
We dedicated our summer to documenting and testing MABE2, an open-source research platform that provides accessible tools for conducting evolutionary computation and digital evolution research.
​
This project was guided by our wonderful mentors [Acaica Ackles](https://alackles.github.io/) (documentation) and Austin Ferguson (testing).
​
## :interrobang: Why Document and Test Code
​
The ???Michegan State University devolab??? has spent countless hours developing MABE2 and preparing for its release. Proper documentation and testing are essential for ensuring that MABE2 is accepted into and used by as large of a community as possible.
​
Write the Docs (link!), BLURB, puts the importance of proper documentation quite plainly:
​
> If people don’t know why your project exists,they won’t use it.
> If people can’t figure out how to install your code, they won’t use it.
> If people can’t figure out how to use your code, they won’t use it.
​
This is particularly important for the end-users of MABE2 who simply want to run experiments and do not want to waste time trying to understand the source code on their own, especially users who have less coding experience.
​
Documentation is also important for the MABE2 users who wish to write their own modules or otherwise contribute to this software. Write the Docs stresses the importance of documentation for potential contributors: 
​
> You only get contributions after you have put in a lot of work.
> You only get contributions after you have users.
> You only get contributions after you have documentation.
​
Software must also be tested before it is released to the community. End-users will (and should) be cautious of code that has no testing framework. Without code being tested how can we expect it to preform as expected? We must provide a testing suite to assure MABE2 users that this software runs correctly.
​
Testing frameworks are also helpful for future developers who want to make sure their contributions to this software does not break any previously functioning code.
​
## :book: Documentation

Prior to this summer there was no documentation for MABE2, meaning we had to familiarize ourselves with a huge library of files without any written guidance. Trying to understand MABE2 using only the source code and frequent discussions with our mentors was challenging. This made us appreciate the value of well documented software, and underlined the importance of documenting MABE2 for future users. 
​
The main page of MABE2's documentation has a more *sales-pitchy* feel to it. This page overviews what MABE is and why researchers should use it. We also provide an example project to showcase the many benefits of running an experiment with MABE2. 
​
The documentation also offers step-by-step installation and quickstart guides so users can quickly familiarize themselves with the fundamentals of running a MABE2 experiment. In addition to these basics we dive deeper into the inner workings of MABE2 with an overview of source (modules, tools for analysis, the MABE core, and MABE dependencies), a detailed description of the different types of modules, explanations of different evaluators, and guide to the essential TraitInfo object.
​
Despite our diligent efforts to document all of MABE2, there are some features that we were unable to document because their implementation has yet to be finalized. These include:

Because MABE2 is still under active development there are some features whose implementation has yet to be finalized, meaning that for the time being, they have been left out of the documentation. These include: 
​
* genomes
* brains
* worlds

​If you're curious to learn more, you can check out a live version of the documentation [here](https://mabe2.readthedocs.io/en/latest/).

## Testing
### The Beginning

Many large projects contain complex webs of dependencies, which are files that rely on other files. This is the case with MABE2. Dependencies make deciding where to start testing difficult. You need to be sure that the code you are testing does not rely on any untested files, since they could contain unknown bugs which may lead to errors in your current code. To avoid potential errors from untested dependencies, our mentor Austin suggested that we start with code that had no dependencies. This method is called "bottom up" testing. 

One way to organize the system of dependencies is to "levelize" the code your working with. Levelizing is the process of sorting all files in a project based on the number of dependencies that they have. Then, you can organize the files into "levels", each level representing the addition of one dependency. Levelization can be a great tool to help understand how a large code base is organized. 
** CHECK THIS *****

In our case, Austin used the levelization of MABE2 to decide which files we should begin testing. We've included his visualization below. 

[ include his levelization here ]

One really important thing to note about levelizing MABE2 is that MABE2 has a library of third-party dependencies that are used throughout MABE2 source code, including Empirical. We worked under the assumption that all of these third-party resources were working correctly, and thus any error we found was occurring from within MABE2. 

### The Process
The process of testing is not linear, and is more involved than most people first assume. In its most basic form, the testing process can be summed up as below. 

1. Decide what you're testing. 
2. Write the test. 
3. Check that the tests work. If they don't, return to step 2.  
4. Make sure you have tested everything you want to test. If you find areas that you missed, return to step 1. 
5. You're done!

Since we both were thrown head-first into MABE2 and had little biology/evolution background, deciding how to test a specific file was pretty hard. 

At the beginning, Austin gave us checklists of what to test in a file, and gave us guidance on how to test it.  Once we finished his checklist, we would go through and decide if there was something that we missed. 
 
After testing a couple of files with this method, we decided to push ourselves to come up with tests on our own. This lead to a new testing workflow, demonstrated in the image below. 

[insert his flowchart]

In essence, we began by meeting with Austin to do a high-level overview of the code to make sure we understood what we would be testing. Then, on our own, we created a comprehensive test suite for the specific file with a variety of unit tests. Afterwards, we would send our tests to Austin who would come up with his own independent list of things to test. He would compare his test suite with ours and give us feedback on what we missed. We would then go back and review our own tests with his advice in mind. We then repeat that cycle until all of us were satisfied with the testing coverage for the file. Then we repeat this process for the next file.

### Catch2
We used a testing framework called Catch2 to test MABE2. Catch2 is an easy to use C++ unit testing framework. You can check out more of Catch2 in their [github](https://github.com/catchorg/Catch2). When writing out tests for MABE2, we relied heavily on Catch2's assertion macros, which you can find [here](https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md#top). 

### Testing MABE2
#### Words of Wisdom
Throughout our testing journey, we have come to learn a lot about the intricacies of writing tests. We thought we would share a couple of tips and tricks we learned from tackling testing this summer! 

1. Creating new Test Files: Test files can have large boiler plates (setup before the actual code is written, lots of `#include`s and `#define`s) which can make setting up a new testing file tricky to get right. We found that the easiest way to get the boiler plate right was to simply copy a preexisting test file and "rip out its guts" and replace it with new test code. When doing this you must rename or replace anything specific to the previous test file. When including the file to test, do not `#include` any of its dependencies because they should be included in that file.  

2. Deciding what to Test: When you first open up a file that you're going to test, it's okay not to understand everything that you see! Take a breath, read any documentation at the top of the file. Start with things that you understand or something chose something that looks simple to start with (like a constructor!). As you work through their implementation, you will get more familiar with the code. 

Also keep in mind that if you are struggling to understand what a specific chunk of code is doing, reach out and ask for help! It's better to write useful tests after asking for help rather than writing tests that are inappropriate for the file because you misunderstood the code. 

3. Getting the First Test to Pass: Setting up a test file and understanding the code that you are to test can be difficult and time consuming. You'll probably get a lot of errors before you're able to get an actual test to pass. But don't give up! Once you get that first test to pass the others are much easier to write since you'll most likely understand the code to be tested much better by that point.
 

#### MABE2 Specific Advice
Here are a couple of things that you might find helpful when testing MABE2 files! We have included some things to watch out for, but also some fixes to testing bugs that cropped up and gave us some issues. 

1. A good place to start when testing a MABE2 file is by checking that all booleans are working correctly. Another good place to start is to check that simple checking functions work correctly. For example, a function that returns whether or not an input is a double should work correctly. Another example is a function that modifies a boolean. 
2. Most of the time, you will end up testing every method in a file, so make sure you have a clear list of the methods/a comprehensive strategy to make sure you get them all. Also, make sure you test all variations of a function: if a function has both a templated and non-templated version, both should get checked. 
3. Many times MABE2 files will inherit from a parent class. It is always a good idea to glance through the parent class. You should check specifically for virtual functions/variables that should get overrriden in the file you're checking. Don't forget to also look for functions from the parent class that aren't overridden though!
4. When you see that an error message would be printed to the console, make sure you check that the error gets triggered correctly! Bonus points if you also check that the correct error message is written out to the console. You can do that by modifying your



+ Assert issue
- Makefile must have debugging turned on (use with pointer tracking)
- NDEFDEBUG flag in ErrorManager. 
+ Put things in MABE.cpp file to check if they work (isolate the issue)
+ lldb/gdb then bt to frame number
- check Empirical test files for example usage/tests (only helpful if they're implemented)
+ Copy paste from old test files to preserve boiler plate stuff
+ ONLY INCLUDE the file you're testing, not stuff included from .hpp file
+ once you get one test up and running, it gets easier!
+ ask for help! especially for understanding what the .hpp file does
- check booleans actually reset 

What to look for when testing
+ test all booleans
+ test every method
+ make sure to check parent class for virtual overrrides in derived class
+ make sure to check parent class for non-overridden functions
- any time you print an error message to the console, you should check that an error is thrown
- side note, also check error message is the right one
- 



- Testing Asserts: In almost every file we wanted to be able to test that asserts had been thrown when expected. However, asserts typically terminate a program, making this difficult. Luckily, empirical has a file that implements a "non-terminating assert trigger" which is perfect for unit testing. All we had to do was use the macro `#define EMP_TDEBUG` and the boolean `emp::assert_last_fail` combined with `emp::assert_clear` to reset the boolean to test that asserts had been thrown when expected.

- Segmentation Faults: When setting up mabe objects or calling methods on these objects we would sometimes run into segmentation faults (files trying to read/write to an illegal memory location). Catch2 made this difficult to debug since it would crash at the beginning of the test case and not give specific line numbers of what calls caused the crash. To work around this we would put the broken code into `MABE.cpp` along with the function:

```cpp
void REQUIRE(bool b){
  std::cout << b << std::endl;
}
```

to work around the `REQUIRE`s in Catch2. When we ran the `MABE.cpp` file we could use lldb (gdb on Windows) to find the memory leaks. With lldb we would run the program, then use backtrace to look at the individual frames and see where the memory leak was coming from.



- Levelization and bottom up
    - Austin's vizualization of MABE2
    - Assuming everything in Empirical was working correctly
    - Flowchart process (insert the flowchart Austin made)
        - Why use this?
- Using CATCH2
    - Words of Wisdom (what was easy/hard)
        - Assert issue
        - What to look for when testing
        
## Wrap Up
At the end of the WAVES internship, we were given the opportunity to present our summer of work at the BEACON congress. The BEACON congress is the annual meeting for researchers who belong to the [BEACON Center of Evolution in Action](https://www3.beacon-center.org/welcome/), a consortium of affiliated universities that focuses on the study of evolution in action through an interdisciplinary lens. Specifically, BEACON aims to bring together biologists, computer scientists and engineers to both study evolution in action, as well as use evolution to solve complex real-world problems. 

We attended the summer 2021 BEACON congress as both participants and speakers. We presented our talk "Planning for the Future of MABE2: A Summer of Documentation and Testing". Below you can find both our abstract, as well as a video recording for our talk. 

"The second Modular Agent-Based Evolver framework (MABE2) is an open-source research platform that provides accessible tools for conducting evolutionary computation and digital evolution research. MABE2 reduces the time between constructing a hypothesis and generating results by providing a library of modules that connect to form a variety of experiments. To promote use among interdisciplinary researchers, modules are connected and adjusted via a simple text interface (i.e., the user does not need to add or edit any code). However, if the user requires modules beyond the existing library, MABE2 provides a set of practical tools for developing additional modules. With the understanding that MABE2 is a large piece of software, this summer we created a documentation guide and testing framework as part of the 2021 Workshop for Avida-ED Software Development (WAVES). In this talk, we will highlight the role of the documentation and testing framework in the  MABE2 user experience through a demonstration of constructing and running a custom experiment. By creating the documentation and testing framework, we hope to make MABE2 more approachable to new users and more useful to the interdisciplinary research community." 

- Include video of our talk?

## Acknowledgements
​
We would like to give a huge thank you to our mentors Acaica Ackles and Austin Ferguson
for their continued support and dedication throughout the summer!
​
We would also like to thank Charles Offria and Cliff Bohm for their support in understanding MABE2!
​
Finally, we would like to thank all the WAVES mentors who led us in enrichment seminars and everyone who gave us feedback on our documentation!