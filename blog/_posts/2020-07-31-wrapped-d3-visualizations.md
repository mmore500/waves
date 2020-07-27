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
{:style="width: 15%;"}{:class="headshot"}
  
_Hi! I'm Elizabeth Carney, a senior at Smith College studying Computer Science and East Asian Languages with a concentration in Translation Studies. I'm especially interested in data visualization, robotics, and machine translation. In my free time, I love tinkering in makerspaces :hammer_and_wrench:, doing nail art :nail_care:, and cooking :fried_egg:. To see some of my other projects, check out [my GitHub](https://github.com/elizabethcarney)!_  
{:class="next-to-headshot"}

**This summer I got to join the WAVES team to develop tools for the next version of [Avida-ED](https://avida-ed.msu.edu/).** It teaches students about evolution with visual, interactive experiments that run on Avida, a platform for digital evolution research. Avida creates digital organisms and lets them evolve based on various parameters like mutation rate; their survival is always dictated by natural selection, just like it is in the real world. Both softwares were created by the [Digital Evolution Lab](https://devolab.org/) at Michigan State University. 

As WAVES participants, our job was to develop new features for Avida-ED, or reinforce the tools that it uses. For my project, I focused on the development of a **mammoth** library that Avida is built on: [**Empirical**](https://github.com/devosoft/Empirical).

### Empirical and the Internet
[Empirical](https://github.com/devosoft/Empirical)—which was also built by the MSU devolab—is a C++ library for scientific software development. It especially facilitates building evolutionary computation tools, because you can easily create digital organisms and worlds for them to evolve in. [Here's an example](http://mmore500.com/dishtiny/53vgh/) of a web app built with Empirical that illustrates evolutionary computation in action!

[![digital evolution timelapse](http://img.youtube.com/vi/yOhryHORQxE/0.jpg)](https://www.youtube.com/watch?v=yOhryHORQxE)  
[**Click the image above** for an evolution timelapse!](#vid-timelapse)
{:id="vid-timelapse"}

As you can see, **creating a web app is an amazing way to share and showcase your work**. Lots of researchers want to publish their experiments and results online so that more people can access and understand them. Luckily, Empirical was built with the internet in mind! Experiments written in C++ can be compiled into _super-fast_ JavaScript using Empirical tools that work with [Emscripten](https://emscripten.org/docs/getting_started/Tutorial.html). On top of that, lots of web elements are wrapped in Empirical as well, like tables  :spiral_notepad:, animations :next_track_button:, buttons :white_check_mark:, text areas :pencil2:, canvases :art:, and more, which means that you can easily create web pages while coding in C++!

Data visualization is particularly important to researchers trying to share their results. Incorporating colors and graphics into a report catches the reader's eye and definitely helps them understand the content better. That's why (in my opinion) one of the coolest web tools in Empirical's collection is the **C++-wrapped version of D3.js**, a JavaScript data visualization library!

### What Does "Data-Driven Documents" Mean?
The "D3" in D3.js stands for **Data-Driven Documents**, meaning that **D3.js allows you to bind data to actual HTML document elements** (like circles or lines) instead of abstracting the data binding through some toolkit. Because of that, using the library is an exceptionally transparent process. As a bonus, all of the visualizations you create with D3.js are SVGs; that means they're scalable and won't get "fuzzy" because the graphics are based on equations instead of pixels.

![D3.js visualization examples]({{ site.baseurl }}/assets/elizabethcarney/wrapped-d3-visualizations-d3-examples.jpg)  
{:style="width: 80%;"}   
Here are some examples of the different visualizations you can create with D3.js!

One downside to D3.js is that _it doesn't come with any pre-packaged visualizations_ out of the box. Whether you want a line graph, histogram, scatterplot, or something entirely different—**you have to build it yourself** out of axes, circles, and other simple elements. There's a beauty to this system, though. The D3.js community is huge and very active, so there are **tons** of examples of building all types of visualizations online ([see this gallery to start!](https://www.d3-graph-gallery.com/index.html)). And, if you want, you can customize your graph endlessly until it's exactly how you want it.

Here's an example of how you could use D3.js to create a simple line graph: TODO

```js
// JavaScript code block to be filled in with lots of comments
var greeting = "wazzup";
```
< Add an image of the resulting line graph here >  TODO  
![D3.js line graph]({{ site.baseurl }}/assets/elizabethcarney/wrapped-d3-visualizations-d3-line-graph.jpg)  
{:style="width: 60%;"}    
Here's the resulting line graph!

D3.js had already been wrapped for Empirical a few years ago by [**Dr. Emily Dolson**](#check-out-people) at the devolab, but a new version came out since then and it needed to be **revamped**. :star2: So, I took on the project of **updating the Empirical D3-wrapper** over the summer along with [**Oliver Baldwin Edwards**](#check-out-people) and my two amazing mentors, [**Dr. Emily Dolson**](#check-out-people) and [**Alex Lalejini**](#check-out-people)!

### Wrapping a Library
:bellhop_bell: The number-one reason to wrap D3.js in C++ for Empirical was **convenience**. Many researchers want to be able to code data visualizations that integrate seamlessly into their C++-based experiments and web apps.   
:bangbang: And, if the original library goes through frequent changes, then having a wrapper can make it **easier to update** things on your end (you only have to change the code inside the wrapper).   
:zap: Moreover, using Emscripten to compile C++ into JavaScript results in **wicked-fast** (near-native!) code on the web side.   
:mag_right: However, it's important to note that we definitely wanted the wrapper to be **recognizable** to people who'd used D3 in JavaScript before. We needed to strike a balance between convenience in C++ and similarity to JavaScript.

**Basic D3-wrapper structure:** Each D3.js module (e.g. selection, transition, axis, scale, etc.) has its own header file in `Empirical/source/web/d3`. Some modules, like scales, contain a base class for shared methods as well as other classes that build off of it. **Each D3.js method has a wrapped equivalent**, though a method might be templated or have multiple versions in the C++ code because its corresponding D3.js method could take several different types of input or return several different types of output. 

Here's an example of how we want to be able to use the C++ version of D3.js to create the same simple line graph: TODO  

```c++
// C++ code block to be filled in with lots of comments
size_t my_num = 0;
```
In the process of wrapping D3.js for Empirical, we:
  - rewrote function calls to match the current version of D3.js
  - added functionality to make using the library from C++ even easier
  - wrote new functions to help us pass data between C++ and JS cleanly
  - generally cleaned up the code and increased readability

#### Wrapping Axis.h
The D3-wrapper team took on the selection and transition modules together, but [**Oliver**](#check-out-people) and I each re-wrapped another module as well. I took on Axis! The major changes I've made from the old wrapper include:  
  1. **Added a padding parameter** to the default constructor so that a value other than 60px can be specified (padding depends on the type of axis; e.g. for axisLeft, there is only padding between the axis line and the left side of the svg)  
  2. **Added a constructor with shift_x and shift_y parameters** in order to set the initial location of the axis exactly  
  3. **Modified the DrawAxes() convenience function** to take both axes' padding into account if it's specified; otherwise the padding is 60px   
  4. **Added a version of SetTicks()** that takes both the number of ticks and the tick format to reflect common usage of the D3.js .ticks() method  
  5. **Wrote three versions of Rescale()**, each one taking a different input type, since SetDomain() can take three different types of arguments   for the min and max of the new domain
  6. **Created axis.cc**, a comprehensive testing file for axes and related their methods  
  7. **Added emp_asserts** to methods that should not be called before Draw() for debugging since they'll be overwritten  
  8. **Updated variable names and EM_ASM macros**, and generally kept to best practices  

Here are some interesting parts of the code: TODO

```c++
// another C++ code block to be filled in with lots of comments
size_t my_num_again = 0;
```

#### A Big Ol' Bug
Unfortunately, [**Oliver**](#check-out-people) and I discovered a Big Ol' Bug:copyright: during the testing phase (with [**Dr. Emily Dolson's Karma/Mocha/Chai system**](https://devolab.org/javascript-testing-on-travis-ci-with-karma-and-mocha/) and [**Alex Lalejini's**](#check-out-people) new test-running framework). In a nutshell, the D3-wrapper is currently incompatible with the rest of Empirical's web tools. When you create an Empirical Document object, it needs to know exactly what it encompasses, because it redraws itself from time to time. Unfortunately, Documents currently have no way of knowing when you add a D3 object onto them, so all of the D3 disappears when they redraw. We will document this issue well in our hand-off notes!

### How to Make a Visualization with the Wrapper
> Tip: Build something in regular D3.js first before jumping into the wrapper!

An easy way to start a project that's built on Empirical is by using the [**cookiecutter**](https://github.com/devosoft/cookiecutter-empirical-project)! In terms of coding with the D3-wrapper after that, here are some quick tips:

  1. **Know what you want.** Try drawing out the visualization you're imagining before sitting down to code.  
  
  2. **Look at some examples.** It might be helpful to get a feel for the structure of a visualization—or just see how constructing an object works—by looking at one of the **testing** or **pre-built visualization files**. For example, `Empirical/tests/web/d3/axis.cc` is the testing file for Axis, and in it I construct several selections, scales, and axes, as well as modify the axes with almost all of the available functions. The code should work since the tests are passing right now! :sweat_smile:  
  
  3. **Start with absolute basics.** First, make a selection. Check that it works. Then, make a scale. Check that it works. Then, apply that scale to an axis. And so on. To test that something works, I suggest compiling your C++ file into JS with Emscripten, and creating a simple HTML file that uses `<script src="{JS filepath}"></script>` to import it. Then start a server, point your browser to it, and inspect the DOM through developer tools to see what's there.  
  
  4. **Play around.** Maybe you didn't know what you wanted after all! You can always modify the objects you construct; for example, after you create an Axis object, you can use functions like `Move()`, `SetTicks()`, and `AdjustLabelOffset()` to customize it further. Try changing things around a bit, adding color, and making your visualization as clear and exciting as possible.   

#### A Scatterplot
As a final project after working on the D3-wrapper for the summer, I decided to create a **pre-built scatterplot visualization** within Empirical. That way, someone who wasn't very familiar with D3.js could easily and successfully add a graph to their web app. I believe pre-built visualizations are incredibly helpful, because:  
  1. they're accessible (D3.js has a particularly steep learning curve)
  2. they fill an important void in terms of _easy_ data visualization
  3. they can get more people interested in learning D3.js themselves (if you want to tinker with the graph, you have to learn about how it's made!)

< Screenshot of output graph here > TODO
![D3.js line graph]({{ site.baseurl }}/assets/elizabethcarney/wrapped-d3-visualizations-d3-line-graph.jpg)  
{:style="width: 60%;"}    
Here's a scatterplot generated by the pre-built visualization!

Here's how to use the pre-built scatterplot visualization to create the graph shown above: TODO

```c++
// a third C++ code block to be filled in with lots of comments
size_t my_num_yet_again = 0;
```

And here's how I created the pre-built visualization itself: TODO

```c++
// a fourth C++ code block to be filled in with lots of comments
size_t my_num_yet_again_2 = 0;
```

---

### Thank you!
I am so thankful to have been a part of the 2020 WAVES team! Thank you to [Dr. Charles Ofria](https://ofria.com/) and [Matthew Andres Moreno](https://mmore500.com/) for organizing such an educational and well-thought-out workshop. My summer was looking bleak, but WAVES turned that upside down; I got to code and learn alongside so many incredible collaborators and mentors. Every single person I met (be it virtually) was welcoming. It was a fantastic experience!

I especially want to thank the other three members of the d3-wrapper team: [**Oliver Baldwin Edwards**](#check-out-people), and my two wonderful mentors, [**Dr. Emily Dolson**](#check-out-people) and [**Alex Lalejini**](#check-out-people).

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.  

#### Check out these wonderful people: 
{:id="check-out-people"}

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
