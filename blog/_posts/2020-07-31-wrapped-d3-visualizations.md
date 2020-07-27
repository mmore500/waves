---
layout: post
title: "Wrapped D3.js Visualizations"
date: 2020-07-31
author: Elizabeth Carney
---
<link rel="stylesheet" type="text/css" media="all" href="{{ site.baseurl }}/assets/elizabethcarney/wrapped-d3-visualizations-styles.css"/>

## Wrapping D3.js Visualizations
---
![Elizabeth Carney headshot]({{ site.baseurl }}/assets/elizabethcarney/wrapped-d3-visualizations-ec-headshot.jpg)  
{:style="width: 15%;"}{:.headshot}
  
_Hi! I'm Elizabeth Carney, a senior at Smith College studying Computer Science and East Asian Languages with a concentration in Translation Studies. I'm especially interested in data visualization, robotics, and machine translation. In my free time, I love tinkering in makerspaces :hammer_and_wrench:, doing nail art :nail_care:, and cooking :fried_egg:. To see some of my other projects, check out [my GitHub](https://github.com/elizabethcarney)!_  
{.next-to-headshot}

This summer I got to join the WAVES team to develop tools for the next version of [Avida-ED](https://avida-ed.msu.edu/). It teaches students about evolution with visual, interactive experiments that run on Avida, a platform for digital evolution research. Avida creates digital organisms and lets them evolve based on various parameters like mutation rate; their survival is always dictated by natural selection, just like it is in the real world. Both softwares were created by the [Digital Evolution Lab](https://devolab.org/) at Michigan State University. 

As WAVES participants, our job was to develop new features for Avida-ED, or reinforce the tools that it uses. For my project, I focused on the development of a mammoth library that Avida's built on: [Empirical](https://github.com/devosoft/Empirical).

### Empirical and the Internet
An explanation of what Empirical can do and how it's often used.

Include bits about experiments as web apps, Emscripten, and data visualization. Description of how web tools have been wrapped.

### What Does "Data-Driven Documents" Mean?
Blurb about what D3 is; no built-in visualizations. Here's an example of how you could use D3 to create a simple graph:

```js
// JavaScript code block to be filled in
var greeting = "wazzup";
```
< And an image of the output here >

Blurb that an older version had already been wrapped by [Dr. Emily Dolson](#check-out-these-wonderful-people:), but it needed to be updated and revamped.

### Wrapping a Library
Discuss the goals and methods of wrapping the library. Each D3 module has its own header file. Here's an example of how we want to be able to use D3.js through C++ to create the same simple graph:

```c++
// C++ code block to be filled in
size_t my_num = 0;
```
Blurb that in wrapping we updated functions to match current D3, cleaned stuff up, added helpful functions to make the switching between C++ and JS easier, etc.

#### Wrapping Axis.h
Things I ran into while re-wrapping a D3 module. I'll probably have code blocks in here:

```c++
// another C++ code block to be filled in
size_t my_num_again = 0;
```

#### Web Testing
Blurb about how we wanted a good testing framework, used Emily's Karma/Mocha/Chai system, Alex built TestRunner, etc.

#### A Big Ol' Bug
Info about Widgets and D3 incompatibility here.

### How to Make a Visualization with the Wrapper
> Tip: Build something in JS with D3 first

Blurbs about building visualizations with the wrapper.

#### A Scatterplot
Info about the scatterplot I make, hopefully with link to working demo.

< Screenshot of output graph here >

How to use the pre-built scatterplot visualization:

```c++
// a third C++ code block to be filled in
size_t my_num_yet_again = 0;
```
Explanation here.

---

### Thank you!
I am so thankful to have been a part of the 2020 WAVES team! Thank you to [Dr. Charles Ofria](https://ofria.com/) and [Matthew Andres Moreno](https://mmore500.com/) for organizing such an educational and well-thought-out workshop. My summer was looking bleak, but WAVES turned that upside down; I got to code and learn alongside so many incredible collaborators and mentors. Every single person I met (be it virtually) was welcoming. It was a fantastic experience!

I especially want to thank the other three members of the d3-wrapper team: [**Oliver Baldwin Edwards**](#check-out-these-wonderful-people:), and my two wonderful mentors, [**Dr. Emily Dolson**](#check-out-these-wonderful-people:) and [**Alex Lalejini**](#check-out-these-wonderful-people:).

#### Check out these wonderful people:

> **Oliver Baldwin Edwards** (collaborator), a senior at Amherst College studying Computer Science and Statistics. We worked on this wrapper project together, and he's an amazing programmer!  
[Github](https://github.com/Oliver-BE) | [Twitter](https://twitter.com/oliver_be2)

> **Dr. Emily Dolson** (mentor), an Assistant Professor in Computer Science at Michigan State University starting this fall with formal training in Computer Science, Evolutionary Biology, and Ecology. She creates mind-blowing web apps and visualizations for her research!  
[Github](https://github.com/EmilyDolson) | [Twitter](https://twitter.com/emilyldolson) | [Website](https://cse.msu.edu/~dolsonem/)

> **Alex Lalejini** (mentor), a fifth year PhD student working with Dr. Charles Ofria in Computer Science and Ecology, Evolutionary Biology, & Behavior at Michigan State University. He is a super welcoming researcher and a brilliant coder!  
[Github](https://github.com/amlalejini) | [Twitter](https://twitter.com/amlalejini) | [Website](https://lalejini.com/)

---

### Other resources to peruse:

- [My **wrapped d3 scatterplot** visualization demo!]()
- **Empirical** library [repo](https://github.com/devosoft/Empirical), [docs](https://empirical.readthedocs.io/en/latest/), [cookiecutter](https://github.com/devosoft/cookiecutter-empirical-project), and [example gallery](https://empirical.readthedocs.io/en/latest/BuiltWithEmpiricalGallery)
- Empirical's [**Web Tools** docs](https://empirical.readthedocs.io/en/latest/library/web/web.html)
- **Emscripten** [docs](https://emscripten.org/docs/getting_started/Tutorial.html) (compiles C and C++ into JavaScript to run on the web)
- **D3.js** [docs](https://github.com/d3/d3/wiki) and [Graph Gallery](https://www.d3-graph-gallery.com/index.html)
- [Javascript Testing on Travis CI with Karma and Mocha](https://devolab.org/javascript-testing-on-travis-ci-with-karma-and-mocha/) (by Emily Dolson) - this is how our **web testing** is set up!
- [The Curiously Recurring Template Pattern (CRTP)](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/) - this is used in our wrapper's `selection.h`!
- [Salmon Run](http://avida-ed-mirror1.beacon-center.org/SalmonRun/game/), a fun game—or is it an evolutionary playground?
- If you'd like to take a look at some of my other projects, please [click here to go to **my GitHub**](https://github.com/elizabethcarney)!
