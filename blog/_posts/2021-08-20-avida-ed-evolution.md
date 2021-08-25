---
layout: post
title: "Avida-ED 4 Evolves For Better Usability"
date: 2021-08-20
author: Yemi Shin
---
**Description**: This summer, I worked on re-implementing and enhancing parts of Avida-ED 4 to improve design and usability.

Objectives
--
* #### Implement dragbars to allow for freely resizable windows.
* #### Overhaul legacy dojo framework for drag and drop and implement a new framework with Dragula, which has minimal dependencies and will enable Avida-ED to be usable on a touch device.


# Overview

Dragbars : The New Way to Raise the Bar (Get it?)
--
Wow, it was harder than I thought.
   Honestly, the way I think about web pages in general changed tremendously working on this project. I was constantly astounded by, and am still being astounded by the variety of ways plain JavaScript, JQuery, and the dollar signs (who knew that $ had so many meanings) and various other Javascript libraries are similar and yet at times frustratingly incompatible with each other. In the end, however, they coped with me to do magic on the page. :) In addition, I learned the precious lesson that I should not take even something as simple as a dragbar for granted!

Steps I took to implement a Dragbar:
1. Avida-ED is a pretty big project (kudos to Diane for developing it this far!). I had to spend a few days simply looking at the code (literally) to get my eyes adjusted to all the namespaces and file structure!
2. I was tasked with creating the dragbars at first. I've never done that. Where do I start?
3. I made a proof of concept, sandbox type website to experiment with different web components, and mocked up a dragbar (mostly for my sanity).
4. I copied, pasted, and modified my poc dragbar into the codebase, and tweaked a lot of things (as it turned out) to make it actually compatible with the rest of the Avida-ED code and layout (Hello, maquetta grid!)

This might be a great time to bring up..

### The Importance of Proof of Concept
   #### (Image of Proof of Concept)
   What I learned is that, if you ever run into a situation where you don't know what is going on in the codebase, and you don't know where to start? Do a proof of concept, it will save you big time. First, whipping up a proof of concept is a great chance for you get yourself familiar with the Javascript functions that will be handy for your task. Second, it is a medium to articulate to stakeholders or your mentors what you are working on and how you plan on implementing the component onto the actual website. And lastly, and perhaps most importantly, it gives you a template, a kind of jumping off point to get you going (and with confidence) when you do finally touch the codebase. Fear not!

When you start working on the code though..

### Approach code like a surgeon
What I mean by that is, my honest impression of working on the codebase was me constantly feeling like I was making small incisions in the code to insert whatever solution I had to offer the website (in this case, a dragbar). Like all beginner programmers, I was fearful. What if I break something really bad, and I mess something up, and the world comes to an end? (right...) Anyhow, I was always careful about what I was tweaking and how I was tweaking it. I am a forgetful person, too. So I left a bunch of "yemi:(comment)" comments where I was changing anything, first of all to leave some breadcrumbs for me to pick back up if I do end up breaking something, and second to communicate to Diane what I was changing and why I was changing it, so in the worst case scenario, she could at least follow what I was doing to perhaps offer up some higher level insight..(thank you, Diane!) But I learned that, if you approach code like a surgeon, and are very aware of every change you make precisely, you will save much energy later down the road when you likely will be scrutinizing the code for the insidious mistake that are not the most pleasant to search for!

After a while, I was done implementing dragbars. It was time for me to discover..,

Dragula, the New Way to Drag and Drop
--
It was a web of dependencies from which I knew no escape.

And then, I saw the light. Its name was 'Dragula: Drag and Drop So Easy It Hurts," and yes I was hurt. It was thanks to Raheem, a participant who worked on the Avida-ED project before me, who did his dilligent research looking for the best drag and drop library to support the next generation of Avida-ED. His very neat proof of concept website was very helpful for me to get onboarded (see? it does help!). Turns out, drag and drop forms the foundation of all actions on Avida-ED. I was ambitious, and did not exactly see what was coming ahead of me. But it was all for good.

# The Deets

Implementing Features
--
### Final Product Overview
---
* dragbar

![dragbar](https://media.giphy.com/media/bGGKFk6sefEcGEN1XW/giphy.gif)

* drag and drop

![drag and drop](https://media.giphy.com/media/Dyrnna2ZsOpSX3wqZh/giphy.gif)

### Code

#### **DISCLAIMER**: The following code snippets may not be coherent pieces of code within the actual codebase. They are in order, just not guaranteed to be strictly next to each other.
---
#### **Dragbars**

`resizePageParts.js`

```Javascript
function dragbarLeftResize() {
```
1. Capture the x coordinate of the mouse on the screen.
```Javascript
  $(document).on('mousemove touchmove', function(e){
    av.grd.drawGridSetupFn(); // yemi: redraw the grid when page resized
    var x;
    if(e.type == 'touchmove'){
      var touch = e.originalEvent.touches[0] ||
                  e.originalEvent.changedTouches[0];
      x = touch.pageX;
    } else if (e.type == 'mousemove') {
      x = e.pageX;
    }
```
2. Calculate the width of the gridColumns based on this coordinate.
```Javascript
    var rightSideWidth = $('#rightInfoHolder').css("width");
    var rightSideWidthNum = parseInt($('#rightInfoHolder').css("width")); /* yemi: extract only the number */
    var widthAvailable = window.innerWidth - rightSideWidthNum - 6; /* yemi: hard-coded 400px (right panel) 6px (left dragbar + right dragbar), need to fix */
    var percentage = (x / widthAvailable);
    var widthOfNav = widthAvailable * percentage;
```
3. Entirely collapse or open a sidebar based on threshold.
```Javascript
    /* yemi: if the width of the user's cursor is smaller than the minimum width of the navigation column, choose the minimum width */
    if (widthOfNav < parseInt($('#navColId').css("min-width"))) {
      widthOfNav = 0; /* yemi: if width too small, collapse it*/
    }
    /* yemi: if thhe width of the user's cursor is larger than the maximum width of the navigation column, choose the maximum width */
    else if (widthOfNav > parseInt($('#navColId').css("max-width"))) {
      widthOfNav = parseInt($('#navColId').css("max-width"));
    }
```
4. Change the css of the grid with the newly calculated column widths.
```Javascript
    /* yemi: when modifying the column sizes, need to modify all three layouts */
    var population_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
    var organism_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
    var analysis_colInfo = widthOfNav + "px 3px auto";
    $('.all2lft').css("grid-template-columns", analysis_colInfo); /* yemi: you need to resize again on the analysis page to resize it correctly */
    $('.all3pop').css("grid-template-columns", population_colInfo);
    $('.all3org').css("grid-template-columns", organism_colInfo);
```
The above code will resize the sidebar widths every time the user's mouse cursor moves. If you wish to make the changed grid layout stick even after the user release's the mouse, just add this line
```Javascript
  $(document).on('mouseup touchend', function(e){
```
and repeat the code from `1` through `4`.

The keywords `touchmove` and `touchend` enable touch actions on the screen.

If you are unfamiliar with the css grid, here is one of the grid layouts we are modifying.

`avidaEdEco.css`

```css
.all3pop{
  display: grid;
  grid-template-rows: 2.5em 1fr;
  grid-template-columns: 240px 3px auto 3px 400px;
  grid-template-areas: 'headerRow headerRow headerRow headerRow headerRow'
                        'navColClass dragbarLeft mainBlockHolder dragbarRight rightInfoHolder';
  height: 99vh;
  width: 100vw;
  min-height: 98vh;
  min-width: 100vw;
  max-height: 99vh;
  max-width: 100vw;
  margin: 0;
  background:  #F5F5F5;   /* lightsalmon;  */
}
```
----

#### **Dragula Drag and Drop**

`dragulaDnd.js`
1. Summon the players (aka draggable containers)
```Javascript
var containers = [
                    $.map($(".freezerContainer"), (value, key) => { return value }),
                    $.map($("#testConfig"), (value, key) => { return value }),
                    $.map($("#activeConfig"), (value, key) => { return value }),
                    $.map($("#trashCan"), (value, key) => { return value }),
                    $.map($("#gridCanvas"), (value, key) => { return value }),
                    $.map($("#ancestorBox"), (value, key) => { return value }),
                    $.map($("#ancestorBoTest"), (value, key) => { return value }),
                    $.map($("#activeOrgan"), (value, key) => { return value }),
                    $.map($("#organCanvas"), (value, key) => { return value }),
                    $.map($("#organIcon"), (value, key) => { return value }),
                    $.map($("#anlDndChart"), (value, key) => { return value }),
                    $.map($("#popDish0"), (value, key) => { return value }),
                    $.map($("#popDish1"), (value, key) => { return value }),
                    $.map($("#popDish2"), (value, key) => { return value }),
                   ].flat();

  av.dnd.fzConfig = containers[0]
  av.dnd.fzOrgan = containers[1]
  av.dnd.fzWorld = containers[2]
  av.dnd.fzTdish = containers[3]
  av.dnd.testConfig = containers[4]
  av.dnd.activeConfig = containers[5]
  av.dnd.trashCan = containers[6]
  av.dnd.gridCanvas = containers[7]
  av.dnd.ancestorBox = containers[8]
  av.dnd.ancestorBoTest = containers[9]
  av.dnd.activeOrgan = containers[10]
  av.dnd.organCanvas = containers[11]
  av.dnd.organIcon = containers[12]
  av.dnd.anlDndChart = containers[13]
  av.dnd.popDish0 = containers[14]
  av.dnd.popDish1 = containers[15]
  av.dnd.popDish2 = containers[16]
```
Below line extracts the actual dom object from the JQuery wrapper.
```Javascript
$.map($("#activeConfig"), (value, key) => { return value })
```
2. Initiate the Dragula engine.

    `el` is the dom object being dragged,

    `source` is the dom object where `el` was dragged from,

    `target` is the dom object that `el` is being dragged to.

    All of `el`, `source`, and `target` are basically things you could `.id` to.

    Object that is returned is more formally called an 'event emitter'. See [Dragula](https://github.com/bevacqua/dragula#readme) documentation for more detail.
```Javascript
var dra = dragula(containers, {
    isContainer: function (el) {
      return false; // only elements in drake.containers will be taken into account
    },
    moves: function (el, source, handle, sibling) {
      return true; // elements are always draggable by default
    },
    accepts: function (el, target, source, sibling) {
      return true; // by default all items are accepted everywhere
    },
    invalid: function (el, handle) {
      return false; // don't prevent any drags from initiating by default
    },
    copy: function (el, source) {
      //Makes sure the only item that will be copied instead of moved is in the FreezerMove div
      return source === av.dnd.activeOrgan || source === av.dnd.activeConfig || source === av.dnd.fzConfig || source === av.dnd.fzOrgan || source === av.dnd.fzWorld || source === av.dnd.fzTdish;
    },
    direction: 'vertical',             // Y axis is considered when determining where an element would be dropped
    copySortSource: false,             // elements in copy-source containers can be reordered
    revertOnSpill: true,               // spilling will put the element back where it was dragged from, if this is true
    removeOnSpill: false,              // spilling will `.remove` the element, if this is true
    mirrorContainer: document.body,    // set the element that gets mirror elements appended
    ignoreInputTextSelection: true     // allows users to select input text, see details below
  });
```
3. Specify the what is accepted where. Taken out of the dragula constructor to be reusable in other parts of the code.
```Javascript
av.dnd.accepts = function(el, target, source) {
    if (target === source) {
      return true;
    }
    if ((source === av.dnd.ancestorBox) && (target === av.dnd.fzOrgan || target === av.dnd.organIcon || target === av.dnd.gridCanvas)) {
      return true;
    }
    if (source === av.dnd.activeConfig && (target === av.dnd.fzConfig || target === av.dnd.fzWorld)) {
      return true;
    }
    if (source === av.dnd.activeOrgan && (target === av.dnd.fzOrgan || target === av.dnd.organIcon || target === av.dnd.organCanvas)) {
      return true;
    }
    if ((source === av.dnd.fzConfig || source === av.dnd.fzWorld) && target === av.dnd.activeConfig) {
      return true;
    }
    if (source === av.dnd.fzWorld && (target === av.dnd.gridCanvas || target === av.dnd.anlDndChart || target === av.dnd.popDish0 || target === av.dnd.popDish1 || target === av.dnd.popDish2)) {
      return true;
    }
    if (source === av.dnd.fzOrgan && (target === av.dnd.activeOrgan || target === av.dnd.organCanvas || target === av.dnd.organIcon || target === av.dnd.gridCanvas || target === av.dnd.ancestorBox || target === av.dnd.ancestorBoTest)) {
      return true;
    }
    if (source === av.dnd.fzTdish && target === av.dnd.testConfig) {
      return true;
    }
    if (target === av.dnd.trashCan) {
      return true;
    }
    else {
      return false;
    }
  }
```
4. Capture 'drag' event.
```Javascript
dra.on('drag', (el, source) => {
    dragging = true;
    if (source === av.dnd.fzOrgan) { // necessary because for some reason inside mouse events, dra 'source' and 'target' are messed up
      sourceIsFzOrgan = true;
    } else sourceIsFzOrgan = false;

    if (source === av.dnd.fzWorld) {
      sourceIsFzWorld = true;
    } else sourceIsFzWorld = false;

    if (source === av.dnd.ancestorBox) {
      sourceIsAncestorBox = true;
    } else sourceIsAncestorBox = false;

    elForGrid = el;
  });
```
The three `if` cases in the function are specifically for handling drag events on the gridCanvas. This is because as I found out, Dragula event emitter and regular mouse events that are essential for locating cursor within the grid are incompatible. The `target` and `source` was not correctly being registered within the gridCanvas mouse event handler, so I created separate global variables `sourceIsFzOrgan` and so forth to capture this information. Not the cleanest, but does the job!

5. Capture 'drop' event.
```Javascript
  dra.on('drop', (el, target, source) => {
    // el, target, source are dom objects aka stuff you could 'target.id' to
    if ((target === av.dnd.activeConfig || target === av.dnd.ancestorBox) && av.grd.runState === 'started') {
      av.dom.newDishModalID.style.display = 'block'; // show the 'please save' modal
      dra.cancel(); // cancel the drag event
    } else if (target === av.dnd.activeConfig) {
      av.dnd.landActiveConfig(el, target, source);
    }

    ...


    if (target === av.dnd.fzOrgan) {
      av.dnd.landFzOrgan(el, target, source); // I don't think it's getting called
    }

    if (target === av.dnd.organIcon) {
      av.dnd.landOrganIcon(el, target, source);
    }
```
And here it is. A sore thumb it was, handling drop events on gridCanvas.

```Javascript
    $(document).on('mouseup touchend', function (evt) {
      'use strict';
      if (dragging) {
        var x;
        var y;
        if(evt.type == 'touchend'){
          var touch = evt.originalEvent.touches[0] || evt.originalEvent.changedTouches[0];
          x = touch.pageX;
          y = touch.pageY;
        } else if (evt.type == 'mouseup') {
          x = evt.clientX;
          y = evt.clientY;
        }
        av.mouse.UpGridPos = [x, y];
        var elements = $.map(document.elementsFromPoint(x, y), (x) => {return x.id});
        if (elements.indexOf("gridCanvas") != -1 && sourceIsFzOrgan) {
          av.dnd.landGridCanvas(el, target, source);
          av.grd.drawGridSetupFn('av.dnd.gridCanvas where target = gridCanvas');
        }
      }
      dragging = false;
      $(document).unbind('mousemove touchmove');
    });
```

6. Handle 'drop'.

    Below is one of many drop handlers.
```Javascript
av.dnd.landGridCanvas = function(el, target, source) {
```
* Find where the user's mouse landed.
```Javascript
    // to correctly place the organism, need to calculate offsets
    var offsetXLocal = ($("#gridHolder").width() - av.dom.gridCanvas.width) / 2;
    var offsetYLocal = ($("#gridHolder").height() - av.dom.gridCanvas.height) / 2;
    var widthOfNav = parseInt($('#navColId').css('width'));
    var heightOfTop = parseInt($('#popTopRw').css('height')) + parseInt($('#headerMain').css('height'));
    var mouseX = av.mouse.UpGridPos[0] - av.grd.marginX - av.grd.xOffset - offsetXLocal - widthOfNav - 5; // yemi: hardcoded 5; works for now
    var mouseY = av.mouse.UpGridPos[1] - av.grd.marginY - av.grd.yOffset - offsetYLocal - heightOfTop - 5;
    if (av.debug.dnd) console.log('mouse.UpGridPosX, y', av.mouse.UpGridPos[0], av.mouse.UpGridPos[1]);
    if (av.debug.dnd) console.log('mouseX, y', mouseX, mouseY);
    av.parents.col[nn] = Math.floor(mouseX / av.grd.cellWd);
    av.parents.row[nn] = Math.floor(mouseY / av.grd.cellHt);
```
* If the mouse cursor landed within the gridCanvas, process it.
```Javascript
    // check to see if in the grid part of the canvas
    var nn = av.parents.name.length;
    if (av.parents.col[nn] >= 0 && av.parents.col[nn] < av.grd.cols && av.parents.row[nn] >= 0 && av.parents.row[nn] < av.grd.rows) {
      av.parents.AvidaNdx[nn] = av.parents.row[nn] * av.grd.cols + av.parents.col[nn];
      // start setting up for getting data for parents structure
      nn = av.parents.name.length;  // get index into parents
      // clone the element
      el = el.cloneNode(true);
```
* Update the backend.

  Namely `av.fzr.dir` and `av.fzr.domid`
```Javascript
      // get the data for the dragged element
      var dir = av.fzr.dir[el.id];
      // give a new id to the new dom object
      el.id = 'g' + av.fzr.gNum++;
      mostRecentlyAddedDomid = el.id;
      // add an entry to av.fzr.dir for this new new dom id
      av.fzr.dir[el.id] = dir;
      // and vice versa
      av.fzr.domid[dir].push(el.id);
```
* Update the frontend.

  Namely `containerMap` (which keeps track of which draggable items are in what container) and the DOM.
```Javascript
      // give a new name
      el.textContent = av.dnd.nameParent(el.textContent.trim());
      // insert element into ancestorBox containerMap
      av.dnd.insert(av.dnd.ancestorBox, el, 'g');
      // insert element into ancestorBox DOM
      av.dnd.insertToDOM(av.dnd.ancestorBox, el);
```
* Insert a `parent`, which is an Avidian organism that are initially placed on the grid.

  This is an essential step in order for the experiment to run successfully.
```Javascript
      // Push the item to av.parents
      av.parents.domid.push(el.id);
      //update parents structure
      av.parents.handNdx.push(nn);
      av.parents.howPlaced[nn] = 'hand';
      av.parents.injected[nn] = false;
      if (av.debug.dnd) console.log('av.dnd.landGridCanvas; domId', el.id, '; av.fzr.genome', av.fzr.genome);
      av.parents.genome.push(av.fzr.file[dir+'/genome.seq']);
      //Find color of ancestor
      if (0 < av.parents.Colors.length) {av.parents.color.push(av.parents.Colors.pop());}
      else {av.parents.color.push(av.color.defaultParentColor);}
      //Re-Draw Grid - done in routine that calls this one.
    }
```

# Results

Drag and drop works on a touch screen!!

Below is a simulation of an iPad.

*Population Page*

![touchscreen_pop](https://media.giphy.com/media/1eqJVElzAs16IMIGRY/giphy.gif?cid=790b7611bb359af2851bb38ef6ef2bf46479ec2d8d790670&rid=giphy.gif&ct=g)

*Organism Page*

![touchscreen_org](https://media.giphy.com/media/zOhal1mfv8mfd3MEUO/giphy.gif?cid=790b76111b024e9f0b5ecc71ccdbd2b91a506b82305c4f0b&rid=giphy.gif&ct=g)

*Analysis Page*

![touchscreen_anl](https://media.giphy.com/media/tI8gRQ7hEakVn1DNF4/giphy.gif?cid=790b7611d4561a125affcb97e765c0977fb4c01cb1eb8993&rid=giphy.gif&ct=g)
# Moving forward

My goal was to make Avida-ED 4 more user-friendly and accesible to more people. Implementing the dragbar and the new drag&drop definitely came with its challenges, but in the end I think I got so much out of the experience, beyond just what I was coding. Namely, the fact that I was working on a meaningful, and historical! software that is Avida-ED 4, as well interacting with like-minded peers and seeing my often futile attempts come to fruition on the webpage!! was simply pure joy.

# Acknowledgments

Of course, I cannot forget to express my great thanks to Diane Blackwood, without whom I would not have been able to achieve as much as I did. Talking with Diane on Zoom (and Wesley!) about not just work but also different aspects of our lives was delightful! And to all of the WAVE mentors, collegues, and Matthew: Thank you for organizing WAVES and giving me an opportunity to learn so much about software development as well as educational outreach. I really enjoyed hearing about everyone's contributions and progress throughout the workshop, and I hope our paths cross again in the future!

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

# Sources

[Link to Avida-ED GitHub](https://github.com/yemi33/Avida-ED-Eco/tree/yemi-dnd)

# About Author

I'm currently a rising senior at Carleton College, studying Computer Science! :)

[Learn More About Me](https://yemi33.github.io/)
