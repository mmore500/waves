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

Dragbars : (clever title)
--
* Wow, it was harder than I thought.
* Steps I took to implement it:
1. Importance of Proof of Concept
   ### (Image of Proof of Concept)
2. Approaching code like a surgeon 
3. Some javascript/jQuery that I had not previously used before that was helpful?
   ### (Possibly essential code snippets)
----

Dragula, the New Way to Drag and Drop (perhaps a more clever title)
-- 
* It was a web of dependencies from which I saw no escape. 
* Until.. I did see one.
* Thanks Raheem! Mini philosophy piece on the art of handing over.

# The Deets

Implementing Features
--
### Final Product

(GIF of the newest Avida-ED 4)

## (Some code for...see descriptions below)

#### Dragbars
----
* Some mouse coordination
* Modifying the grid!

#### Dragula Drag and Drop
----
* The players (the av.dnd's)
* containerMap to replace dojo's 'map'
* Other replacements (i.e. addContextMenu, various freezer naming functions..)

# Moving forward

My goal was to make Avida-ED 4 more user-friendly and accesible for more people. Implementing the dragbar and the new drag and drop definitely came with its challenges, but in the end I think I got so much out of the experience, beyond just what I was doing. Namely, the fact that I was working on a meaningful, and historical! software that is Avida-ED 4 and seeing my often futile attempts come to fruition on the webpage was simply pure joy. 

Acknowledgements
--
Of course, I cannot forget to express my utmost gratitude to Diane Blackwood, without whom I would not have been able to achieve as much as I did. Talking with Diane on Zoom (and Wesley!) about not just work but also different aspects of our lives was delightful! And to all of the WAVE mentors, collegues, and Matthew!: Thank you so much for supporting me and encouraging me all this way; I really enjoyed hearing about everyone's contributions and progress throughout the workshop! It was inspiring, especially when coding wasn't going smooth, haha. So thank you. I hope our paths cross again in the future!

