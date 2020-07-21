---
layout: post
title: "Queue Manager Implementation"
date: 2020-06-03
author: Juan Chavez
---

## Introduction to Prisoners Dilemna World
  - Briefly discuss the simulation (using figures)
  
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

