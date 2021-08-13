---
layout: post
title: "Avida-ED 4 Evolves For Better Usability"
date: 2021-08-09
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
   Honestly, the way I think about web pages in general changed tremendously working on this project. I was constantly astounded by, and am still being astounded by the variety of ways JavaScript, and JQuery, and the dollar signs (who knew that $ had so many meanings) and various Javascript libraries confuse each other! and give me frustration! but allow me to do magic on the page at the end :) And yes, something as simple as a dragbar, is rather complicated in its inner workings! 
   
Steps I took to implement it:
1. I realized Avida-ED is a pretty big project (kudos to Diane!). I had to spend a few days simply looking at the code (literally) to get my eyes adjusted to all the namespaces and file structure!
2. I was tasked with creating the dragbars at first. I've never done that. Where should I start?
3. I made a proof of concept, sandbox type website to experiment with different components and mock up a dragbar.
4. I copied, pasted, modified my poc dragbar into the codebase, and tweaked a lot of things (it turned out) to make it actually compatible with the rest of the Avida-ED code and layout (Hello, maquetta grid!).

This might be a great time to bring up..

### The Importance of Proof of Concept
   #### (Image of Proof of Concept)
   What I learned is that, if you ever run into a situation where you don't know what the heck is going on in the codebase, and you don't know where to start? Do a proof of concept, it will save you big time. First, it is a great chance for you get yourself familiar with the Javascript functions that will be handy for your task. Second, it is a medium to communicate to stakeholders or your mentors what you are working on and how you plan on implementing the component onto the actual website. And lastly, and perhaps most importantly, it gives you a template, a kind of jumping off point to get you going (and with confidence) when you actually touch the codebase. Fear not! 

When you do actually start working on the code though..

### Approach code like a surgeon 
What I mean by that is, my honest impression of working on the codebase was me constantly feeling like I was making small incisions in the code to insert whatever solution I had to offer the website (in this case, a dragbar). Like all beginner programmers, I was fearful. What if I break something really bad, and I mess something up, and the world comes to an end? (right...) Anyhow, I was always careful what I tweak and how I tweak it. I am a forgetful person, too. So I left a bunch of "yemi:(comment)" comments where I was changing anything, first leaving some breadcrumbs for me to pick back up if I do end up breaking something, and second to communicate to Diane what I was changing and why I was changing it, so if I do break something, she can at least follow what I was doing to perhaps offer up some higher level insight..(thank you, Diane!) But I learned that, if you approach code like a surgeon, and be very aware of every change you make precisely, you will save much energy later down the road where you need to back track not knowing where you messed up if you do (and you most likely will!) 

### (Possibly essential code snippets)

Still working on it!

Dragula, the New Way to Drag and Drop (perhaps a more clever title)
-- 
It was a web of dependencies from which I knew no escape. And then, I saw the light. Its name was 'Dragula: Drag and Drop So Easy It Hurts," and yes I was hurt. It was thanks to Raheem, a participant who worked on the Avida-ED project before me, who did his dilligent research looking for the best drag and drop library to support the next generation of Avida-ED. His very neat proof of concept website was very helpful(see? it does help!). Turns out, drag and drop forms the foundation of all actions on Avida-ED. I was ambitious, and Diane was patient!

# The Deets

Implementing Features
--
### Final Product
* dragbar
![dragbar](https://media.giphy.com/media/bGGKFk6sefEcGEN1XW/giphy.gif)

* drag and drop
![drag and drop](https://media.giphy.com/media/Dyrnna2ZsOpSX3wqZh/giphy.gif)

## (Some code for...see descriptions below)

#### Dragbars
----
* Some mouse coordination
```Javascript
/* yemi: functions for left dragbar */
function dragbarLeftResize() {
  console.log('navColID=', parseInt($('#navColId').css("min-width")));
  var dragging = false;

  /* yemi: when there's a mousehover over dragbar, dragbar changes color */
  $('#dragbarLeft').on('mouseover touchstart', function(e) {
    $('#dragbarLeft').css('background-color', 'blue');
  });

  $('#dragbarLeft').on('mouseout touchend', function(e) {
    $('#dragbarLeft').css('background-color', 'gray');
  });

  $('#dragbarLeft').on('mousedown touchstart', function(e) {
    dragging = true;
    
    $(document).on('mousemove touchmove', function(e){
      av.grd.drawGridSetupFn(); // yemi: redraw the grid
      
      // yemi: need to account for both touch and mouse event
      var x;
      if(e.type == 'touchmove'){
        var touch = e.originalEvent.touches[0] || e.originalEvent.changedTouches[0];
        x = touch.pageX;
      } else if (e.type == 'mousemove') {
        x = e.pageX;
      }

      /* yemi: on mouse move, dragbar changes color */
      $('#dragbarLeft').css('background-color', 'blue');

      var rightSideWidth = $('#rightInfoHolder').css("width");
      var rightSideWidthNum = parseInt($('#rightInfoHolder').css("width")); /* yemi: extract only the number */
      var widthAvailable = window.innerWidth - rightSideWidthNum - 6; /* yemi: hard-coded 400px (right panel) 6px (left dragbar + right dragbar), need to fix */
      var percentage = (x / widthAvailable);
      var widthOfNav = widthAvailable * percentage;


      /* yemi: if the width of the user's cursor is smaller than the minimum width of the navigation column, choose the minimum width */
      if (widthOfNav < parseInt($('#navColId').css("min-width"))) {
        widthOfNav = 0; /* yemi: if width too small, collapse it*/
        IS_LEFT_CLOSED = true;
      } 
      /* yemi: if thhe width of the user's cursor is larger than the maximum width of the navigation column, choose the maximum width */
      else if (widthOfNav > parseInt($('#navColId').css("max-width"))) {
        widthOfNav = parseInt($('#navColId').css("max-width"));
        IS_LEFT_CLOSED = false;
      }
      else {
        IS_LEFT_CLOSED = false;
      }

      /* yemi: when modifying the column sizes, need to modify all three layouts */
      var population_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
      var organism_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
      var analysis_colInfo = widthOfNav + "px 3px auto";
      $('.all2lft').css("grid-template-columns", analysis_colInfo); /* yemi: you need to resize again on the analysis page to resize it correctly */
      $('.all3pop').css("grid-template-columns", population_colInfo);
      $('.all3org').css("grid-template-columns", organism_colInfo);

      /* yemi: make the following divs take up the entire width of their containers */
      $('orgInfoHolder').css("width", "100%");

      /* yemi: update organism canvas */
      av.ind.updateOrgTrace();
    });
  });

  $(document).on('mouseup touchend', function(e) {

    if (dragging) {
      av.grd.drawGridSetupFn(); // yemi: redraw the grid

      // yemi: need to account for both touch and mouse event
      var x;
      if(e.type == 'touchmove'){
        var touch = e.originalEvent.touches[0] || e.originalEvent.changedTouches[0];
        x = touch.pageX;
      } else if (e.type == 'mouseup') {
        x = e.clientX;
      }

      /* yemi: dragbar changes color back to original */
      $('#dragbarLeft').css('background-color', 'gray');

      var rightSideWidth = $('#rightInfoHolder').css("width");
      var rightSideWidthNum = parseInt($('#rightInfoHolder').css("width")); /* yemi: extract only the number */
      var widthAvailable = window.innerWidth - rightSideWidthNum - 6; /* yemi: hard-coded 400px (right panel) 6px (left dragbar + right dragbar), need to fix */
      var percentage = (x / widthAvailable);
      var widthOfNav = widthAvailable * percentage;

      /* yemi: if the width of the user's cursor is smaller than the minimum width of the navigation column, choose the minimum width */
      if (widthOfNav < parseInt($('.navColClass').css("min-width"))) {
        widthOfNav = 0; /* yemi: if width too small, collapse it */
        IS_LEFT_CLOSED = true;
        /* yemi: change the button's contents and look */
        $('#leftPanelButton').val('>> ');
        $('#leftPanelBUtton').css('background', '#ccc');
      } 
      /* yemi: if thhe width of the user's cursor is larger than the maximum width of the navigation column, choose the maximum width */
      else if (widthOfNav > parseInt($('.navColClass').css("max-width"))) {
        widthOfNav = parseInt($('#navColId').css("max-width"));
        IS_LEFT_CLOSED = false;
        /* yemi: change the button's contents and look */
        $('#leftPanelButton').val('<< ');
        $('#leftPanelBUtton').css('background', 'inherit');
      }
      else {
        IS_LEFT_CLOSED = false;
        /* yemi: change the button's contents and look */
        $('#leftPanelButton').val('<< ');
        $('#leftPanelBUtton').css('background', 'inherit');
      }
  });
};
```
* Modifying the grid!
```Javascript
/* yemi: when modifying the column sizes, need to modify all three layouts */
      var population_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
      var organism_colInfo = widthOfNav + "px 3px " + "auto 3px " + rightSideWidth;
      var analysis_colInfo = widthOfNav + "px 3px auto";
      $('.all2lft').css("grid-template-columns", analysis_colInfo); /* yemi: you need to resize again on the analysis page to resize it correctly */
      $('.all3pop').css("grid-template-columns", population_colInfo);
      $('.all3org').css("grid-template-columns", organism_colInfo);

      /* yemi: make the following divs take up the entire width of their containers */
      $('orgInfoHolder').css("width", "100%");
      
      $(document).unbind('mousemove touchmove'); // yemi: need it
      
      dragging = false;
    }
```

#### Dragula Drag and Drop
----
* The players (the av.dnd's)
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
  console.log('dragula containters: ', containers);

  // currently only have draggable containers on the Population page. 
  // Organism and Analysis page draggable containers will be implemented soon.
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
* initiating the Dragula engine
```Javascript
var dra = dragula(containers, {
    isContainer: function (el) {
      return false; // only elements in drake.containers will be taken into account
    },
    moves: function (el, source, handle, sibling) {
      return true; // elements are always draggable by default
    },
    accepts: function (el, target, source, sibling) {
      if (target === source) {
        return true;
      }
      if ((source === av.dnd.ancestorBox) && (target === av.dnd.organIcon || target === av.dnd.gridCanvas)) {
        return true;
      }
      if (source === av.dnd.activeConfig && (target === av.dnd.fzConfig || target === av.dnd.fzWorld)) {
        return true;
      }
      if (source === av.dnd.activeOrgan && (target === av.dnd.fzOrgan)) {
        return true;
      }
      if ((source === av.dnd.fzConfig || source === av.dnd.fzWorld) && target === av.dnd.activeConfig) {
        return true;
      }
      if (source === av.dnd.fzWorld && (target === av.dnd.anlDndChart || target === av.dnd.popDish0 || target === av.dnd.popDish1 || target === av.dnd.popDish2)) {
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
        // el.style.cursor = 'not-allowed'; // not working yet 
        return false;
      }
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
* dragging it away
```Javascript
dra.on('drag', (el, source) => { 
    // el.style.background = 'rgb(189, 229, 245)';
    el.style.cursor =  'default';
    console.log("dragging");
    dragging = true;
    //When mouse button is released, return cursor to default values
    if (source === av.dnd.fzOrgan) { // necessary because for some reason inside mouse events, dra 'source' and 'target' are messed up
      sourceIsFzOrgan = true;
    } else sourceIsFzOrgan = false;
  });

  // main function that determines the logic for drag and drop
  dra.on('drop', (el, target, source) => {

    // el, target, source are dom objects aka stuff you could 'target.id' to
    if ((target === av.dnd.activeConfig || target === av.dnd.ancestorBox) && av.grd.runState === 'started') {
      av.dom.newDishModalID.style.display = 'block'; // show the 'please save' modal
      dra.cancel(); // cancel the drag event
    } else if (target === av.dnd.activeConfig) {
      av.dnd.landActiveConfig(el, target, source);
    }

    if (target === av.dnd.testConfig || target === av.dnd.ancestorBoTest && av.grd.runState === 'started') {
      av.dom.newDishModalID.style.display = 'block';
      dra.cancel();
    } else if (target === av.dnd.testConfig) {
      av.dnd.landTestConfig(el, target, source);
    }

    if (target === av.dnd.trashCan) {
      // yemi: however, if the drag is being initiated from the gridCanvas aka, then the event handler is in mouse.js
      // refer to av.mouse.ParentMouse or av.mouse.KidMouse
      av.dnd.landTrashCan(el, source);
    }
    
    if (target === av.dnd.fzConfig) {
      av.dnd.landFzConfig(el, target, source);
    }

    if (target === av.dnd.ancestorBox) {
      av.dnd.landAncestorBox(el, target, source);
    }

    if (target === av.dnd.ancestorBoTest) {
      av.dnd.landAncestorBoTest(el, target, source);
    }

    if (target === av.dnd.fzWorld) {
      // yemi: does not trigger because techinically there are no 'items' on the grid right now.
      // on the grid, mouse movements overtake. Code for that is in mouse.js (av.mouse.kidMouse)
      av.dnd.landFzWorld(el, target, source);
    }

    if (target === av.dnd.fzOrgan) {
      av.dnd.landFzOrgan(el, target, source); // I don't think it's getting called
    }

    if (target === av.dnd.organIcon) {
      av.dnd.landOrganIcon(el, target, source);
    }

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
        if (elements.indexOf("gridCanvas") != -1 && sourceIsFzOrgan) { // if gridCanvas is behind this mouse point
          av.dnd.landGridCanvas(el, target, source);
          av.grd.drawGridSetupFn('av.dnd.gridCanvas where target = gridCanvas');
        }
      }
      dragging = false;
      $(document).unbind('mousemove touchmove');
    });

    if (target === av.dnd.activeOrgan) {
      av.dnd.landActiveOrgan(el, target, source);
    }

    if (target === av.dnd.organCanvas) {
      av.dnd.landOrganCanvas(el, target, source);
    }

    if (target === av.dnd.anlDndChart) {
      av.dnd.landAnlDndChart(el, target, source);
    }

    if (target === av.dnd.popDish0 || target === av.dnd.popDish1 || target === av.dnd.popDish2) {
      if (target === av.dnd.popDish0) {
        av.dnd.landpopDish(el, target, source, 0);
      }
      else if (target === av.dnd.popDish1) {
        av.dnd.landpopDish(el, target, source, 1);
      }
      else if (target === av.dnd.popDish2) {
        av.dnd.landpopDish(el, target, source, 2);
      }
    } 
  });
```
* one of (many) drag event handlers
```Javascript
av.dnd.landGridCanvas = function(el, target, source) {
    'use strict';
    if (av.debug.dnd) console.log('inside gridCanvas dnd');
    if (av.debug.dnd) console.log('parents', av.parents);

    var nn = av.parents.name.length;
    av.post.addUser('DnD: ' + source.id + '--> GridCanvas: by: ' + el.textContent.trim() + ' on (' +  av.mouse.UpGridPos[0] + ', ' + av.mouse.UpGridPos[1] + ')' );

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
    //check to see if in the grid part of the canvas
    if (av.parents.col[nn] >= 0 && av.parents.col[nn] < av.grd.cols && av.parents.row[nn] >= 0 && av.parents.row[nn] < av.grd.rows) {
      av.parents.AvidaNdx[nn] = av.parents.row[nn] * av.grd.cols + av.parents.col[nn];

      //Start setting up for getting data for parents structure
      nn = av.parents.name.length;  // get index into parents
      el.textContent = av.dnd.nameParent(el.textContent.trim());
      //Add organism to av.dnd.ancestorBox in settings.
      var domid = el.id;
      var dir = domid;
      av.dnd.insert(av.dnd.ancestorBox, el, 'g');
      av.dnd.insertToDOM(av.dnd.ancestorBox, el);

      if (av.debug.dnd) console.log('containerMap[#ancestorBox]', containerMap[container]);

      // Push the item to av.parents
      av.parents.domid.push(domid);
      //update parents structure
      av.parents.handNdx.push(nn);
      av.parents.howPlaced[nn] = 'hand';
      av.parents.injected[nn] = false;
      if (av.debug.dnd) console.log('av.dnd.landGridCanvas; domId', domid, '; av.fzr.genome', av.fzr.genome);
      var dir = av.fzr.dir[domid];
      av.parents.genome.push(av.fzr.file[dir+'/genome.seq']);
      //Find color of ancestor
      if (0 < av.parents.Colors.length) {av.parents.color.push(av.parents.Colors.pop());}
      else {av.parents.color.push(av.color.defaultParentColor);}
      //Re-Draw Grid - done in routine that calls this one.
    }
    else {
      // not on grid
      av.post.addUser('DnD: ' + source.id + '--> GridCanvas: by: ' + el.textContent.trim());
    }
    //In all cases remove the ancestor from the gridCanvas so we only keep them in the av.dnd.ancestorBox.
    av.dnd.empty(av.dnd.gridCanvas);  //http://stackoverflow.com/questions/11909540/how-to-remove-delete-an-item-from-a-dojo-drag-and-drop-source
    if (av.debug.dnd) console.log('parents', av.parents);
  };
```

* containerMap to replace dojo's 'map'
```Javascript
/*
  Helpers for Inserting and Removing Items from Dragula Containers
  */

  av.dnd.empty = function(target) {
    var container = target.id !== undefined ? "#" + target.id : "." + target.className;
    $(container).empty();
    if (Object.keys(containerMap).indexOf(container) != -1) {
      containerMap[container] = {}
    }
  }

  av.dnd.remove = function(target, el) {
    var container = target.id !== undefined ? "#" + target.id : "." + target.className;
    $(container).remove(el);
    document.querySelector(container).removeChild(document.getElementById(el.id));
    delete containerMap[container][el.id];
  }

  av.dnd.insert = function(target, el, type) {
    var domid = el.id;
    var container = target.id !== undefined ? "#" + target.id : "." + target.className;
    if (Object.keys(containerMap).indexOf(container) === -1) {
      containerMap[container] = {}
    }
    console.log(el);
    console.log($(el));
    containerMap[container][domid] = {'name': el.textContent.trim() , 'type': type};
  }

  av.dnd.insertToDOM = function(target, el) {
    var container = target.id !== undefined ? "#" + target.id : "." + target.className;
    $(container).append(el);
  }

  av.dnd.getAllItems = function (source) {
    'use strict';
    var container = source.id !== undefined ? "#" + source.id : "." + source.className;
    try {
      var items = Object.keys(containerMap[container]);
    } catch (error) {
      var items = [];
    }
    return items;
  };
```
* I realize these snippets are kind of huge. I will get the essential snippets for the actual blog. :)

# Moving forward

My goal was to make Avida-ED 4 more user-friendly and accesible for more people. Implementing the dragbar and the new drag and drop definitely came with its challenges, but in the end I think I got so much out of the experience, beyond just what I was doing. Namely, the fact that I was working on a meaningful, and historical! software that is Avida-ED 4 and seeing my often futile attempts come to fruition on the webpage was simply pure joy. 

Acknowledgements
--
Of course, I cannot forget to express my utmost gratitude to Diane Blackwood, without whom I would not have been able to achieve as much as I did. Talking with Diane on Zoom (and Wesley!) about not just work but also different aspects of our lives was delightful! And to all of the WAVE mentors, collegues, and Matthew!: Thank you so much for supporting me and encouraging me all this way; I really enjoyed hearing about everyone's contributions and progress throughout the workshop! It was inspiring, especially when coding wasn't going smooth, haha. So thank you. I hope our paths cross again in the future!

