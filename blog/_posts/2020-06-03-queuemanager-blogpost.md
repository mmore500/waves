---
layout: post
title: "Empirical Queue Manager"
date: 2020-06-03
author: Juan Eduardo Chavez
---

## Introduction to Prisoners Dilemna World

The Prisoner's Dilemna is an example of decision analysis within game theory. In this example, we take two individuals (prisoners) who are given choices that will not only ultimately impact their own self, but the other party as well. Each individual is given the option to either stay silent in when being questioned (cooperate), or betray the other prisoner by admitting the other's crimes (defect). If both prisoners stay silent, both only have a one-year sentence. If one betrays and the other stays silent, the betrayer becomes free and the silent prisoner is sentenced to three years. If both prisoners betray each other, then each are sentenced to two years. This simulation analyzis why individuals may not want to work together, even if it's beneficial to do so.

A very visually detailed video explaing this simulation is here:

<iframe width="560" height="315" src="https://www.youtube.com/watch?v=t9Lo2fgxWHw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Simple PD World application

Within Empirical, there exists a tool that allows users to simulate the Prisoners Dilemma through there browser (SpatialCoop17). In this tool, users are easily able to manipulate certain variables within the world; epochs (period of time simulation is running), population size, cost/benefit ratio, and radius (neighborhood radius). Once the user is satisfied with the configurations, they then have the option to run this simulation for a period of time (number of epochs). While this simulation is running, a figure displaying the simulation shows how the organisms are interacting with each other in real-time. Furthermore, the user also has an option to establish a queue of runs onto a table. While a run is in progress, along with the figure, the table is updated to show how the organisms are interacting with each other. Because the user can establish multiple runs within the queue, as soon as one run is finished, the next run automatically starts, resetting the table and restarting the simulation, as well as displaying the new results onto the table as well.

Because this was only intended to be used for the Prisoners Dilemma, this tool is not functional for other simulations. The task of my project was to take the fundamental structure of this current application in Empirical but allow for more user versatility. The user would not only be able to change the configurations for the Prisoners Dilemma simulation, but to also choose to run any simulation they choose, should they meet the configuration requirements, allowing for a more versatile tool.

(Add visual of PD App)

## QueueManager Implementation

Queue Manager is a project desinged to address the versatility constraints presenet within the Prisoners Dilemma application. Queue Manager not only allows users to run the Prisoners Dilemma simlation while displaying real-time statistics of the runs, but it also gives flexibility to run any other simulation they so chose, as long as they fill in the current configuration requirements within QueueManager.

Tools/technologies used:

- Cookiecutter template
- Empirical math tools
- Empirical web tools
- C++17
- HTML5/CSS3 - testing visualizations
- JavaScript - browser capabilities from C++

(Overview of how these were used in QueueManager)
(Add in a code walkthrough)

## Project challenges

- First using regular Config library from Empirical
  - Discuss big challenges with using that (Ugly Macros)
- Switching to SettingConfig library and how that solved primary issues with using regular Config Library
- Scoping issues
- Not-yet created SettingConfig features that were just implemented

## Project improvements

- Discuss how QueueManager could be improved

  - Additonal features that would be cool to have

## WAVES take-away/conclusion

- Describe how all of these experiences benefited my development, teamwork, and communication skills
- How this project specifically further improved my understanding of C++, HTML5, CSS3
- My experiences with working with a mentor and other developers and how they impacted not only my project experience, but my overall experience as a waves participant

Mentor: Emily Dolson
[Emily Dolson]({{ site.baseurl }}/assets/headshots/square-EmilyDolson.png){:style="width: 130px; align: center;"}

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.
