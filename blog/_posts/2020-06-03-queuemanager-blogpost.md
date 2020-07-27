---
layout: post
title: "Queue Manager Implementation"
date: 2020-06-03
author: Juan Chavez
---

## Introduction to Prisoners Dilemna World
  The Prisoner's Dilemna is an example of decision analysis within game theory. In this example, we take two individuals (prisoners) who are given choices that will not only ultimately impact their own self, but the other party as well. Each individual is given the option to either stay silent in when being questioned (cooperate), or betray the other prisoner by admitting the other's crimes (defect). If both prisoners stay silent, both only have a one-year sentence. If one betrays and the other stays silent, the betrayer becomes free and the silent prisoner is sentenced to three years. If both prisoners betray each other, then each are sentenced to two years. This simulation analyzis why individuals may not want to work together, even if it's beneficial to do so.
A very visually detailed video explaing this simulation is here: https://www.youtube.com/watch?v=t9Lo2fgxWHw
  
## Simple PD World application
  - Describe how the simulation explained above is shown through this already existing web app in Empirical (SpatialCoop17)
  - Explain the queue-like process that allows the application to hold and run multiple simulations
  - Describe some of the strengths and weaknesses of the pre-existing code
    - Example pros -> run-time performance, visually appealling for users
    - Example cons -> Although this implementation was meant to only handle the Simple PD World simulation, a more flexible tool can be created to handle different types of simulations, not just Simple PD World, limited configuration flexibility
    
## QueueManager Implementation
  - Describe why this tool was created (mentioning how it can solve some of the issues with Simple PD World)
  - Describe how this tool was created
    - C++ Class within Empirical
    - Cookiecutter template
    - Config library from Empirical
    - SettingConfig library from Empirical
    - Queue from STL - main structure used
    - HTML5/CSS3 to create testing visualizations
    
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

