---
layout: post
title: "Planning for the Future of MABE2"
date: 2021-08-20
author: Aria Killibrew Bruehl and Lanea Rohan
---

## Outline

# :soon: Planning for the Future of MABE2: A Summer of Documentation and Testing
​
Hello! This summer we (Lanea Rohan, '22 Grinnel College, and Aria Killebrew Bruehl,
'23 Reed College) participated in the WAVES workshop through Michigan State University.
We dedicated our summer to documenting and testing MABE2, an open-source research platform that provides accessible tools for conducting evolutionary computation and digital evolution research.
​
This project was guided by our wonderful mentors [Acaica Ackles](https://alackles.github.io/) (documentation) and [Austin Ferguson](http://fergusonaj.com/) (testing).

​

## :interrobang: Why Document and Test Code
​
The [Digital Evolution Lab](https://devolab.org/) has spent countless hours developing MABE2 and preparing for its release. Proper documentation and testing are essential for ensuring that MABE2 is accepted into and used by as large of a community as possible.
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

<br/>
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

<br/>

## Testing
### The Beginning
Many large projects contain complex webs of dependencies, which are files that rely on other files. This is the case with MABE2. Dependencies make deciding where to start testing difficult. You need to be sure that the code you are testing does not rely on any untested files, since they could contain unknown bugs which may lead to errors in your current code. To avoid potential errors from untested dependencies, our mentor Austin suggested that we start with code that had no dependencies. This method is called "bottom up" testing. 

One way to organize the system of dependencies is to "levelize" the code your working with. Levelizing is the process of sorting all files in a project based on the number of dependencies that they have. Then, you can organize the files into "levels", each level representing the addition of one dependency. Levelization can be a great tool to help understand how a large code base is organized. 
** CHECK THIS *****

In our case, Austin used the levelization of MABE2 to decide which files we should begin testing. We've included his visualization below. 

[ include his levelization here ]

One really important thing to note about levelizing MABE2 is that MABE2 has a library of third-party dependencies that are used throughout MABE2 source code, including Empirical. We worked under the assumption that all of these third-party resources were working correctly, and thus any error we found was occurring from within MABE2. 

<br/>

### _The Process_
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

<br/>

### _Catch2_
We used a testing framework called Catch2 to test MABE2. Catch2 is an easy to use C++ unit testing framework. You can check out more of Catch2 in their [github](https://github.com/catchorg/Catch2). When writing out tests for MABE2, we relied heavily on Catch2's assertion macros, which you can find [here](https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md#top). 

<br/>

### **Testing MABE2**
#### _Words of Wisdom_
Throughout our testing journey, we have come to learn a lot about the intricacies of writing tests. We thought we would share a couple of tips and tricks we learned from tackling testing this summer! 

<br/>

1. **Creating new Test Files:** Test files can have large boiler plates (setup before the actual code is written, lots of `#include`s and `#define`s) which can make setting up a new testing file tricky to get right. We found that the easiest way to get the boiler plate right was to simply copy a preexisting test file and "rip out its guts" and replace it with new test code. When doing this you must rename or replace anything specific to the previous test file. When including the file to test, do not `#include` any of its dependencies because they should be included in that file.  

2. **Deciding what to Test:** When you first open up a file that you're going to test, it's okay not to understand everything that you see! Take a breath, read any documentation at the top of the file. Start with things that you understand or something chose something that looks simple to start with (like a constructor!). As you work through their implementation, you will get more familiar with the code. 

    Also keep in mind that if you are struggling to understand what a specific chunk of code is doing, reach out and ask for help! It's better to write useful tests after asking for help rather than writing tests that are inappropriate for the file because you misunderstood the code. 

3. **Getting the First Test to Pass:** When you write your first test, you'll probably get a lot of errors before you're able to get it to pass. But don't give up! Once you get that first test to pass the others are much easier to write since you'll understand the setup of the file you're testing. 
 
<br/>

#### **MABE2 Specific Advice**
Here are a couple of things that you might find helpful when testing MABE2 files! We have included some things to watch out for and bug fixes/workarounds that might prove to be helpful in the future. 

1. **First Tests:** A good place to start when testing a MABE2 file is by checking that getter, setter and boolean functions work correctly. 
2. **Test Coverage:** Most of the time, you will end up testing every method in a file, so make sure you have a clear list of the methods/a comprehensive strategy to make sure you get them all. Also, make sure you test all variations of a function: if a function has both a templated and non-templated version, both should get checked. 
3. **Parent Classes:** Many times MABE2 files will inherit from a parent class. It is always a good idea to glance through the parent class. You should check specifically for virtual functions/variables that should get overridden in the file you're checking. Don't forget to also look for functions from the parent class that aren't overridden!
4. **ErrorManager:** Currently in the ErrorManager (`source/core/ErrorManager.hpp`) we have commented out the `#ifndef NDEBUG` line in the `AddError` function. This is on purpose and is a temporary fix. With this line active, if an error is added to the manager the entire program halts. This is not helpful when trying to check to see that errors are being thrown appropriately. A couple of possible fixes for this would be a) to modify the Makefile to use a flag when compiling the tests or b) create some type of macro work around. 
5. **Error Messages:** When you see that an error message would be printed to the console, make sure you check that the error gets triggered correctly! Bonus points if you also check that the correct error message is written out to the console. 

    If you are using the ErrorManager, one way to do this is by capturing the error message in a variable in the `error_function` for the ErrorManager and then comparing the generated string to the expected string in a `REQUIRE`. 
6. **Segmentation Faults:** When setting up or calling methods on mabe objects we would sometimes run into segmentation faults (files trying to read/write to an illegal memory location). Catch2 made this difficult to debug since it would crash at the beginning of the test case and not give specific line numbers of what caused the crash. To work around this we would put the broken code into `MABE.cpp` along with the function:

    ```cpp
    void REQUIRE(bool b){
    std::cout << b << std::endl;
    }
    ```

    to work around the `REQUIRE`s in Catch2. When we ran the `MABE.cpp` file we could use lldb (gdb on Windows) to find the memory leaks. With lldb we would run the program, then use a backtrace to look at the individual frames and see where the memory leak was coming from.
7. **Testing Asserts:** In almost every file we wanted to be able to test that asserts had been thrown when expected. However, asserts typically terminate a program, making this difficult. Luckily, Empirical has a file that implements a "non-terminating assert trigger" which is perfect for unit testing. All we had to do was use the macro `#define EMP_TDEBUG` and the boolean `emp::assert_last_fail`. 

    [insert code example] 

    Make sure you use `emp::assert_clear` to reset the boolean.
8. **Empirical**: A good resource for modeling both tests as well as implementation examples is the Empirical files, located in `source/third_party`. Empirical's library includes a lot of implementation of classes and files included throughout MABE. Checking out those base class files (like Ptr.hpp or vector.hpp) can be helpful when understanding different MABE files. 
9. **Manager Booleans:** One thing to be careful of is to check that booleans who depend on a Manager are actually reset after a test is run. For example, if you want to check a specific feature's Manager throws an error, most times manually setting the boolean back to false is not sufficient. Because the Managers persist, that same feature you just tested to throw an error will again trigger the boolean, regardless of what the new feature actually does in the Manager. For example: 

    ```cpp
    bool has_error_been_thrown = false; 

    /* 
    Do something to add an error in the Manager
    ...
    */

    REQUIRE(has_error_been_thrown); // Error is thrown correctly!

    has_error_been_thrown = false; // Manually reset the boolean

    /*
    Start testing something unrelated that doesn't add an error
    ...
    */
    REQUIRE_FALSE(has_error_been_thrown); // Will FAIL 
    ```
    To get around this issue you can set up multiple Managers and first check things that won't add an error, and end with checking one thing that does throw an error. 

    One note for this: if the next thing you test should get rid of the error. For example: a module A requires that at least one other module of type B exists. First you check that adding a module A by itself throws and error. However, if your very next step is to add a module of type B, this should appease the manager, and the no error is thrown. In this case, the Manager can be re-used. 

<br/>
        
## Wrap Up
At the end of the WAVES internship, we were given the opportunity to present our summer of work at the BEACON congress. The BEACON congress is the annual meeting for researchers who belong to the [BEACON Center of Evolution in Action](https://www3.beacon-center.org/welcome/), a consortium of affiliated universities that focuses on the study of evolution in action through an interdisciplinary lens. Specifically, BEACON aims to bring together biologists, computer scientists and engineers to both study evolution in action, as well as use evolution to solve complex real-world problems. 

We attended the summer 2021 BEACON congress as both participants and speakers. We presented our talk "Planning for the Future of MABE2: A Summer of Documentation and Testing". Below you can find both our abstract, as well as a video recording of our talk. 

> The second Modular Agent-Based Evolver framework (MABE2) is an open-source research platform that provides accessible tools for conducting evolutionary computation and digital evolution research. MABE2 reduces the time between constructing a hypothesis and generating results by providing a library of modules that connect to form a variety of experiments. To promote use among interdisciplinary researchers, modules are connected and adjusted via a simple text interface (i.e., the user does not need to add or edit any code). However, if the user requires modules beyond the existing library, MABE2 provides a set of practical tools for developing additional modules. With the understanding that MABE2 is a large piece of software, this summer we created a documentation guide and testing framework as part of the 2021 Workshop for Avida-ED Software Development (WAVES). In this talk, we will highlight the role of the documentation and testing framework in the  MABE2 user experience through a demonstration of constructing and running a custom experiment. By creating the documentation and testing framework, we hope to make MABE2 more approachable to new users and more useful to the interdisciplinary research community.

<br/>

## Acknowledgements
​
We would like to give a huge thank you to our mentors Acaica Ackles and Austin Ferguson
for their continued support and dedication throughout the summer!
​
We would also like to thank Charles Offria and Cliff Bohm for their support in understanding MABE2!
​
Finally, we would like to thank all the WAVES mentors who led us in enrichment seminars and everyone who gave us feedback on our documentation!

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.