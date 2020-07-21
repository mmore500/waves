---
layout: post
title: "Wrapped D3.js Visualizations"
date: 2020-07-31
author: Elizabeth Carney
---

## Wrapping D3.js Visualizations
---
Hi!

A brief introductory blurb about the summer: WAVES and Empirical.

#### Empirical and the Internet
An explanation of what Empirical can do and how it's often used.

Include bits about experiments as web apps, Emscripten, and data visualization. Description of how web tools have been wrapped.

#### What Does "Data-Driven Documents" Mean?
Blurb about what D3 is; no built-in visualizations. Here's an example of how you could use D3 to create a simple graph:

```js
// JavaScript code block to be filled in
var greeting = "wazzup";
```
< And an image of the output here >

Blurb that an older version had already been wrapped by Emily Dolson, but it needed to be updated and revamped.

#### Wrapping a Library
Discuss the goals and methods of wrapping the library. Each D3 module has its own header file. Here's an example of how we want to be able to use D3.js through C++ to create the same simple graph:

```c++
// C++ code block to be filled in
size_t my_num = 0;
```
Blurb that in wrapping we updated functions to match current D3, cleaned stuff up, added helpful functions to make the switching between C++ and JS easier, etc.

##### Wrapping Axis.h
Things I ran into while re-wrapping a D3 module. I'll probably have code blocks in here:

```c++
// another C++ code block to be filled in
size_t my_num_again = 0;
```

##### Web Testing
Blurb about how we wanted a good testing framework, used Emily's Karma/Mocha/Chai system, Alex built TestRunner, etc.

##### A Big Ol' Bug
Info about Widgets and D3 incompatibility here.

#### How to Make a Visualization with the Wrapper
> Tip: Build something in JS with D3 first

Blurbs about building visualizations with the wrapper.

##### A Scatterplot
Info about the scatterplot I make, hopefully with link to working demo.

< Screenshot of output graph here >

How to use the pre-built scatterplot visualization:

```c++
// a third C++ code block to be filled in
size_t my_num_yet_again = 0;
```
Explanation here.

---

#### Thank you!
Many thanks!

**Check out these wonderful people:**
*(these blurbs will be fleshed out with more info, links, headshots?)*

- Oliver Baldwin Edwards, a senior at Amherst College studying CS and Statistics. We worked on this D3-Wrapper project together!

- Emily Dolson and Alex Lalejini, my mentors for the summer!

If you'd like to take a look at some of my other projects, please [click here to go to GitHub](https://github.com/elizabethcarney).

#### Other resources to peruse:

- Link to my scatterplot visualization demo
- Empirical repo/docs
- Other things I've found useful