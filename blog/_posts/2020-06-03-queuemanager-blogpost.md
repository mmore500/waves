---
layout: post
title: "Empirical Queue Manager"
date: 2020-06-03
author: Juan Eduardo Chavez
---

## Introduction to Prisoners Dilemma World

The Prisoner's Dilemma is an example of decision analysis within game theory. In this example, we take two individuals (prisoners) who are given choices that will not only ultimately impact their own self, but the other party as well. Each individual is given the option to either stay silent when being questioned (cooperate), or betray the other prisoner by admitting the other's crimes (defect). If both prisoners stay silent, both only have a one-year sentence. If one betrays and the other stays silent, the betrayer becomes free and the silent prisoner is sentenced to three years. If both prisoners betray each other, then each are sentenced to two years. This simulation analyzes why individuals may not want to work together, even if it's beneficial to do so.

![PD Choice Image](/assets/chavez-ju/PDDecisionChart.png "PrisonerChart")
(Chart representing each prisoners choice with the respective consequences)

A very visually detailed video explaining this simulation is here:
https://www.youtube.com/watch?v=t9Lo2fgxWHw

## Simple Prisoners Dilemma World Application

Within Empirical, there exists a tool that allows users to simulate the Prisoners Dilemma through there browser (SpatialCoop17). In this tool, users are easily able to manipulate certain variables within the world; epochs (period of time simulation is running), population size, cost/benefit ratio, and radius (neighborhood radius). Once the user is satisfied with the configurations, they then have the option to run this simulation for a period of time (number of epochs). While this simulation is running, a figure displaying the simulation shows how the organisms are interacting with each other in real-time. Furthermore, the user also has an option to establish a queue of runs onto a table. While a run is in progress, along with the figure, the table is updated to show how the organisms are interacting with each other. Because the user can establish multiple runs within the queue, as soon as one run is finished, the next run automatically starts, resetting the table and restarting the simulation, as well as displaying the new results onto the table as well.

Because this was only intended to be used for the Prisoners Dilemma, this tool is not functional for other simulations. The task of my project was to take the fundamental structure of this current application in Empirical but allow for more user versatility. The user would not only be able to change the configurations for the Prisoners Dilemma simulation, but to also choose to run any simulation they choose, should they meet the configuration requirements, allowing for a more versatile tool.

## Queue Manager Implementation

Queue Manager is a project designed to address the versatility constraints present within the Prisoners Dilemma application. Queue Manager not only allows users to run the Prisoners Dilemma simulation while displaying real-time statistics of the runs, but it also gives flexibility to run any other simulation they so choose, as long as they fill in the current configuration requirements within Queue Manager.

![PD World Image](/assets/chavez-ju/PDWorldGraph.png "PDWorld")

Tools/technologies used:

- CookieCutter template
- Emscripten compiler
- Empirical math tools
- Empirical web tools
- Empirical SettingConfig Library
- C++17
- HTML5/CSS3 - testing visualizations
- JavaScript - browser capabilities from C++

The CookieCutter was used to initiate all of necessary directories/files required in order to compile my software with the Emscripten compiler. Queue Manager is implemented as a header-only library in C++17. It’s comprised of multiple classes, the primary one being the actual Queue Manager class. In this class, an STL Queue is the primary structure that the Queue Manager tool utilizes. Within this class, several member functions utilize Empirical’s web/math tools. This allows for the tool to be displayable for users onto a browser. Once the user configures this class to their preference, using the imbedded SettingConfig Library, visuals are rendered by the Emscripten compiler onto a browser.

## Project Improvements

- Allow Queue Manager to be more optimized for Command Line use. Users should be allowed to configer the the settings for their runs through the command line, instead of having to enter the files and change it from there.

- Make the tool more presentable by better styling the HTML/CSS elements

## WAVES Take-away/Conclusion

This workshop/project has enlightened me not only on the complexity of the Empirical Library, but also on the different capabilities different software tools have when used together, particularly C++17 with Empirical's web tools. Aside from this project, the WAVES seminars helped further my understanding in a variety of areas such as web development/testing, C++, and software design to name a few. The friendly and very knowledgeable team working on Avida-ED and Empirical made my experience one to remember, and I am ever so grateful for everything they've taught me!

## Acknowledgements

Mentor: Emily Dolson

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.
