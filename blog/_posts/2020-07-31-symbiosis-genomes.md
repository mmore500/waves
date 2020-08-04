---
layout: post
title: "Symbiosis Summer Project"
date: 2020-07-31
author: Edwin Flores-Cardoso
---

 
# Introduction to Symbiosis in Avida-ED
  This summer with the help of my mentor Anya, I have been focusing on simulating symbulation. Symbiosis is the interaction between two organisms(Host and symbiont). Some types of interactions between these organisms are mutalism, parasitism, and commensalism. To make this project work using Empiricals' library, I used Avida genomes that are included in this library for the project to be implemented with Avida-ED 5 in the future.
   
# Symbulation project
  When first starting to work on this big project, I tried to skim and learn the whole library. That was my first mistake, but later on I just focused on files that were crucial to inhert from to build a world filled with Hosts and Symbionts. With the guidance of my mentor, making each file necessary to build this project was a tough task, especially with creating constructors for each organism.
  Working with the world file, Setting up functions such as a fitness one. The world needed to be populated with hosts and each host with a symbiont. After this step we need to update the world any number of times given. Also within each update, the best fitness organism needed to be found and kept. The rest of the hosts would move to the next generation by a tournament function which could kill them or move them onto the next update. Which is showed here in the follwing snippet of code:

    // Do the run...
    for (size_t ud = 0; ud < UPDATES; ud++){ 
  
    // Update the status of all organisms.;
    world.ResetHardware();
    world.Process(200);
    double fit0 = world.CalcFitnessID(0);

    // Keep the best individual.
    EliteSelect(world, 1, 1);

    // Run a tournament for the rest...
    TournamentSelect(world, 5 , POP_SIZE-1);

    world.Update();

    // // Mutate all but the first organism.
    world.DoMutations(1);

    }
  
# Problems Encountered
  One of the problems I came across was when setting up files to inhert from was a challenge because the files I inherted from had many functions that I did not know how to use. As a result this took time for me to learn but was a great experience to challenge my ability to adapt to learn tons of files of code.
  Also keeping track of symbionts and making them pass on to new hosts and mutating them. Eventually this problem was solved by debugging and calling the function that would give the next generation of organisms.
  (add code showing problem solved)
# Conclusion 
  Approached the end of this internship I have gain valuable skills such as analyzing files and working with others. For future collaborators, working on this project I have commented on the files I have worked on. My advice to others working on this project is to only focus on the files that used in similar project examples in Empirical. Trying to learn every single file in this library is time consuming, you might not need to use all of the cool features the library has to offer. Due to minimal prior knowledge of symbulation the biology aspect of this project was also a tough. However, doing some research and referencing Anyas' research paper, I was able to understand the scientific process to try and recreate something similar with this project. 
  
 # Acknowledgements
 
  Mentor : Anya Vostinar 
  ![PD Choice Image](/assets/headshots/square-anyaevostinar.png)
  
  This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563). Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

