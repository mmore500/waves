---
layout: post
title: "Visualizing Sorting Algorithms with D3"
date: 2020-07-17
author: Oliver Baldwin Edwards
---

# Writing D3.js code in C++

TODO: My actual web app (or at least part of it) will be added to the webpage here

Although it's embedded here (on the web!) the above visualization was written entirely in C++ using [Empirical](https://github.com/devosoft/Empirical)!


Empirical's web tools allow developers to easily deisgn a web page using C++ (and the [Emscripten](https://emscripten.org/) compiler). 
This allows research code written in C++ to be visualized on the web without having to port the code into JavaScript (and who wants to write research code in JavaScript?). 
Plus, using the Emscripten compiler means that the JavaScript code produced will be optimized to work on the web with minimal slowdowns.

This summer I was a [WAVES](https://mmore500.com/waves/index.html) participant and helped to revamp Empirical's support for web visualizations for use in the next version of [Avida-ED](https://avida-ed.msu.edu/).

Specifcally, this meant replacing the old Empirical D3-wrapper (built on D3 version 3) with one that supports the newest version of D3 (version 5). I tackled this project with the wonderful Elizabeth, Emily, and Alex.
TODO: include links to Elizabeth, Emily, and Alex's names

## Why D3?
[D3](https://d3js.org/) (_Data Driven Documents_) is a JavaScript library that allows for all sorts of custom-made, interactive visualizations. 
Some cool examples include:  
* [An interactive graph](https://archive.nytimes.com/www.nytimes.com/interactive/2013/02/20/movies/among-the-oscar-contenders-a-host-of-connections.html) highlighting the connections between Oscar contenders in 2013
* [An animation](https://observablehq.com/@d3/world-tour) of the world globe
* [A chord diagram](https://observablehq.com/@d3/chord-diagram) of consumer's smartphone brand loyalty
* [An interactive cartogram](https://observablehq.com/@d3/non-contiguous-cartogram) displaying obesity in the US
* [A phylogeny tree](https://observablehq.com/@mbostock/tree-of-life?collection=@observablehq/visualization) 

<a href="https://ibb.co/1Z3HzX0"><img src="https://i.ibb.co/dBSnmpf/row1.png" alt="D3 examples row 1" border="0" /></a>
<a href="https://ibb.co/sbjGVYj"><img src="https://i.ibb.co/k5KfSCK/row2.png" alt="D3 examples row 2" border="0" /></a>

Although it has a steep learning curve, D3 provides complete control over all aspects of a visualization, leading to all sorts of creative, interactive creations.  

## Writing web code with Empirical and Emscripten
While creating the D3-wrapper, we relied heavily on writing JavaScript code from inside C++. 
We were able to do so by using both Emscripten's built-in functionality (which covers basic features) and Empirical's web tools (which deal with more advanced features).

The Emscripten compiler gives you access to [C++ functions](https://emscripten.org/docs/api_reference/emscripten.h.html#calling-javascript-from-c-c) that can be used to hop into JavaScript and return values to C++. 
For example, the following `EM_ASM_INT({})` function will return the integer value 22 from JavaScript and save it to the `cpp_x` variable in C++: 
```c++ 
int cpp_x = EM_ASM_INT({
                const js_x = 11 * 2;
                return js_x;
            });
```

While Emscripten allows you to return integers and doubles (as well as write raw JavaScript without returning anything), it does not allow you to easily return more complicated data types such as strings and arrays.
Empirical's web tools cover these holes and allow you to pass more complicated data types back and forth from C++ to JavaScript.

For a list of things that are possible with Emscripten and Empirical, see this attached file. (TODO: attach the enrichment.cc file)

## How does the wrapper work?
The D3-wrapper works by taking advantage of Emscripten and Empirical's web tools to expose D3.js functionality through C++. 
We created a custom JavaScript library (which is accessible through an Emscripten compiler tag) that—among other things—holds a reference to different D3 objects (such as a selection or scale). When called upon to create a D3 object, the C++ wrapper hops into JavaScript, accesses the proper D3 object (each object has a unique ID), and calls the desired D3.js function on that object.  

While this workflow is concise for many D3 functions, the challenges of creating this wrapper included the messiness of having to constantly jump between C++ and JavaScript. For example, the main chunk of code that I worked on this summer was the `scales.h` file, which wraps almost the entirety of the [d3-scales module](https://github.com/d3/d3-scale). In d3-scales a scale called `d3.scaleTime()` takes JavaScript `Date` objects as an input. But since there's no notion of a Date object on the C++ side, I had to create a custom `Date` struct that mimicked a JavaScript `Date` and deal with the unpleasantness of passing a C++ `Date` into JavaScript (and vice versa).

The goal of the D3-wrapper is to do all of this messy C++/Javascript work behind the scenes so that users can focus on making awesome visualizations!

We were able to test the wrapper using [Emily's Karma/Mocha/Chai system](https://devolab.org/javascript-testing-on-travis-ci-with-karma-and-mocha/) and [Alex's `TestRunner`](https://mmore500.com/waves/enrichment/week5.html) (which deals with the complexity of JavaScript code running out of sync with C++ code during testing). 

## How to use the D3-wrapper
As a way to show off the new D3-wrapper, I deicded to create an Empirical web app that visualized how different sorting algorithms work. 
A portion of the web app is at the top of this post, but the link to the full one is [here](https://github.com/Oliver-BE/sorting-algorithms-d3).

Below I'm going to explain the steps I took to create my web app in an effort to help those new to the wrapper get started with making their own visualizations.

###  How to use the D3-wrapper without knowing D3
Before I get started, it's worth mentioning that part of our goal for this summer was to create stand alone visualizations that users without D3 knowledge could use. 
While we ultimately ran out of time to do so (D3 is __huge__), we hope that [my](https://github.com/Oliver-BE/sorting-algorithms-d3) and [Elizabeth's](https://elizabethcarney.github.io/wrapped-d3-visualizations/) web apps will provide a good foundation for the next person to pick up the project. 

### A (super) brief intro to D3
Even when pre-packaged visualizations are built into the D3-wrapper, the best way to have complete control is to start learning D3 (since the D3-wrapper attempts to mimic the syntax of D3.js).
While I won't go in to any details here, below is a list of the most helpful resources I used to learn D3:
* [A useful, brief intro](https://bost.ocks.org/mike/circles/) written by the creator of D3
* [A multi-step tutorial](https://alignedleft.com/tutorials/d3/fundamentals) that walks you through everything D3 from the ground up
  * Although slightly outdated, it's a great tutorial that provides useful motivation behind confusing steps that many others leave out
* [An in depth guide to D3](https://www.d3indepth.com/) that dives into some of the finer D3 details and explains concepts with easy-to-understand examples 
* [A gallery of D3 viualizations](https://www.d3-graph-gallery.com/index.html) that provides the step-by-step code needed to recreate each one
  * I used this site religiously over the summer and it's a fantastic resource
  * There's also [a good intro to D3](https://www.d3-graph-gallery.com/intro_d3js.html) hidden away here



### Getting set up
Getting set up with an Empirical project can be tricky at first, but luckily there are some great resources to make this as easy as possible.

I used this [cookiecutter](https://github.com/devosoft/cookiecutter-empirical-project) outline to build my project on top of Empirical. If you don't want all of the extra bells and whistles that come along with the cookiecutter outline, you can follow [this tutorial](https://mmore500.com/waves/tutorials/lesson04.html) that gets you set up with all the basics needed to write Empirical web code.  

### Visualizing!!
It's finally time to use the D3-wrapper and create a visualization! I started by... TODO: copy and paste code from web app here
```c++
// insert relevant code chunks here
```

## Next steps
TODO:  
Explain the priority of wrapping more modules  
Explain how we need more tests for current modules (selection/transition/data)  
Reiterate how nice it would be to have prepackaged visualizations (look at d3-old/visualizations.cc for inspiration)

## Thank You!
I'm so greatful to have been a WAVES participant this summer! 
It was an incredible experience and I've learned a tremendous amount over such a short 10 weeks (I came in with no C++ and minimal web development knowledge).
Everyone I interacted with was extremely welcoming and willing to help explain difficult C++ concepts and/or debug messy code. 

TODO: Add a special shoutout to the other members of the D3-wrapper team (the wonderful Elizabeth, Emily, and Alex)

>_This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). 
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation._