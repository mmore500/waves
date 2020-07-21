---
layout: post
title: "Visualizing Sorting Algorithms with D3"
date: 2020-07-17
author: Oliver Baldwin Edwards
---

Empirical's web tools allow developers to easily deisgn a web page using C++ (and the Emscripten compiler). 
This allows research code written in C++ to be easily visualized on the web without having to port the code into JavaScript (and who wants to write research code in JavaScript?). 
Plus, using the Emscripten compiler means that the JavaScript code produced will be optimized to work on the web with minimal slowdowns.

The project I worked on this summer—along with the wonderful Elizabeth, Emily, and Alex—was to revamp Empirical's support for web visualizations.  

Specifcally, this meant replacing the old Empirical D3 wrapper (built on D3 version 3) with one that supports the newest version of D3 (version 5).

## Why D3?
[D3](d3js.org) (_Data Driven Documents_) is a JavaScript library that allows for all sorts of custom-made, interactive visualizations. 
Some cool examples include:  
* [An interactive graph](https://archive.nytimes.com/www.nytimes.com/interactive/2013/02/20/movies/among-the-oscar-contenders-a-host-of-connections.html) highlighting the connections between Oscar contenders in 2013
* [An animation](https://observablehq.com/@d3/world-tour) of the world globe
* [A chord diagram](https://observablehq.com/@d3/chord-diagram) of consumer's smartphone brand loyalty
* [An interactive cartogram](9https://observablehq.com/@d3/non-contiguous-cartogram) displaying obesity in the US

_(talk more about motivation for choosing D3 over other visualization libraries such as its flexibility, creative allowance, and interactivity)_

## How Does the Wrapper Work?
(_Here talk briefly about the big picture of how this wrapper works in tandem with Emscripten: mention the `library_d3.js` file, how everything is stored as an object on the JS side that we can access based on an ID on the C++ side, how we call all of the D3 functions within macros, and a few other details._)

(_Also mention the biggest struggles in creating the wrapper such as how we often have to deal with messiness of going between JS and C++ e.g. creating a Date struct on the C++ side in order to properly use ScaleTime._) 

(_The point here is to provide a high-level picture of how it works so it doesn't seem like magic._)

## Writing Web Code with Empirical
Before diving into the D3 wrapper, I figured it would be helpful to give a whirlwind overview of writing web code using Empirical and Empscripten. (_Talk about built in Emscripten macros, helpful Empirical web utils/functions that a user might want to use, etc. (but keep it brief)_) 

(_Include a few code chunks as examples and link to the full `enrichment.cc` file that Elizabeth and I made to demonstrate all of the functionality I discuss here._)

## Creating a Demo of the D3 Wrapper
As a way to test the user-friendliness of the new wrapper, I deicded to create an Empirical web-app from scratch that focused on harnessing the power of D3. 
(_Talk about the specific visualizations I ended up making for different sorting algorithms here._)

(_A large portion of my blogpost will be in this section, I plan to lay out step by step how I created the visualization with informative code snippets and images as well as talk through my motivation for each step_)

(_The point of this section is to give the reader a useful example of how one would create something from scratch using the D3 wrapper_)

(_Likely section headers here would be:_)

### A Brief Intro to D3
(_Keep this to a few sentences_)

### Getting Set Up
(_Outline important set up steps, such as Emscripten compiler set up (I can link to the existing WAVES tutorial), getting the HTML in order, and how to layout the C++ code_)

### Visualizing
(_Here's where the code I wrote when making my visualizations (and motivations behind each step) will go_)

(_I'll walk the reader through any particular weirdness or trickiness with using the wrapper or D3 in general_)

## How to Use the D3 Wrapper Without Knowing D3
(_Here I'm going to talk about how to use the prepackaged barplot and/or scatterplot class that I created in making this web-app._) 
(_These classes allow users who don't know D3 to avoid the messiness of figuring it all out, they can just pass in their data and go._)

(_Include a point how in the future we hope to have more and more visualizations pre-packaged and ready to go, but that the best way to have complete control is to start learning D3_)

(_Links for places to get started with learning D3 go here_)

## Conclusion
(_I'll rename this header later, but I figure I should include some sort of concluding paragraph/section_)
