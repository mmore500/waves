---
layout: post
title: "symbulation blogpost"
date: 2020-07-20
author: Molly Kammann, Yi Qin
---

# Project Description: Symbulation GUI
[Symbulation GUI](https://anyaevostinar.github.io/SymbulationEmp/web/symbulation.html) is a web interface that animates the evolution of hosts and symbionts. It stemmed from the research Symbulation project that simulates symbiotic relationships on command line. Our goal is to make Symbulation GUI an educational tool for biology students hoping to explore symbiosis and insert it as a a sub-module into [Avida-Ed](https://avida-ed.msu.edu/).

# Project Features
- Colorful virtual petri dish (50 times 50) with color-blind-friendly gradient to represent the genes of hosts and symbionts.
- Symbionts are placed inside their corresponding hosts to allow for better visual comparison. It is assumed that each host coexists with only one symbiont.
- Input fields with proper error-checking capabilities that allow users to set **vertical transmission** and **spatial structure** for the population. The change in these two parameters cause organisms to undertake diverging paths of evolution.
- Buttons that control the animation. A pause/start button toggles the animation's activeness, and a reset button resets the whole population to be its original state using the default random seed.
- A game mode which users can switch on/off at will. When game mode is on, the browser prompts users to undertake two challenges -- "make all organisms mutualistic" and "make all organisms parasitic." Users cannot reach the next challenge when the current challenge is uncompleted.
- This interface is mobile-compatible, and the page contents are arranged dynamically according to window size.

# Configurations and Tools
- Languages: C++, JavaScript, HTML
- Compiler: Emscripten
- Local Server: Python3 http server
- [Compilation configuration (see Makefile)](https://github.com/anyaevostinar/SymbulationEmp/blob/master/Makefile)

# Getting Started
- Go to [Symbulation GUI](https://anyaevostinar.github.io/SymbulationEmp/web/symbulation.html) and clone the project (See [GitHub's cloning a repository](https://docs.github.com/en/enterprise/2.13/user/articles/cloning-a-repository) for help)
- Install the Emscripten compiler (See [this tutorial](http://mmore500.com/waves/tutorials/lesson04.html#installing-the-emscripten-compiler) for help)
- Update Python to 3.5 or above if necessary (if you run into issues, see [this thread](https://github.com/emscripten-core/emscripten/issues/9036) for help)
- To compile the project after making changes, navigate to your local *SymbulationEmp* repository on command line and type `make web`.
- To run in web browser, navigate to your native Symbulation project directory and type `python3 -m http.server` in your command line. It is recommended that you use a separate terminal specifically for serving your local project.
- Navigate to *http://localhost:8000/web/* to see the web interface.

# Difficulties
#### Issues with hover-and-show
- Context: the virtual petri dish uses colored squares and dots to represent organisms. However, the information provided by colors is still limited. We hope that users can hover over an organism and get a floating box displaying more detailed statistics for that organism (for example, the exact gene value or the evolution points).
- Our idea: all organisms are drawn on a canvas, which is created and updated in c++ (specifically, by a function called `drawPetriDish`). So we decided to: 
  - Set up an `OnMouseMove` event (a function in [Widget.h](https://github.com/devosoft/Empirical/blob/master/source/web/Widget.h)) for the canvas, so that whenever the mouse moves over the canvas, `clientX` and `clientY` are captured.
  - Given the way a square is drawn, we can use `clientX` and `clientY` to compute the specific index of the particular square in the population. 
  - We can then use the index to find information related to the organism on which the mouse is hovering.
  - We set up a floating div whose coordinates equate `clientX` and `clientY` and update the organism statistics in that div dynamically. Then, as long as the mouse movse on the canvas, the div's position and contents are updated.
  - Finally, we set up an `OnMouseOut` event (a function in [Widget.h](https://github.com/devosoft/Empirical/blob/master/source/web/Widget.h)) to make the floating div disappear when the mouse moves off the canvas.
- Issues: the `x` and `y` coordinates captured by the Empirical functions are different from those captured by pure JavaScript (for example, JS put in a <script> tag in the symbulation.html file). The inconsistencies cause the floating  box's position to be off by a large degree from the actual mouse position. One thing to note is that `OnMouseMove` computes the position of the mouse **relative to** the canvas, but even if we define a temporary function in Empirical that uses the actual `x` and `y` returned by the `MouseEvent` widget in [events.h](https://github.com/devosoft/Empirical/blob/master/source/web/events.h), the inconsistencies still exist. 
- Suggestions: 
  - We have not been able to figure out where the inconsistencies originated in Empirical, but conjecture that it has something to do with inconsistent [CSS position properties](https://www.w3schools.com/cssref/pr_class_position.asp). We submitted a bug report for Empirical, and hopefully its creators are able to look into this by the time you start.
  - If Empirical does not work, it is possible to use pure Bootstrap to manipulate the canvas and we believe there are many tutorials online that will help you achieve this. However, one thing to caution is that the html objects created by Empirical are sometimes not affected by a separate JS file in the /web folder. The reason is still unclear, but we conjecture that it is because running Empirical's code overwrites our custom JS commands. If you run into this issue and still want to manipulate canvas using pure Bootstrap, you can consider using [EM_JS](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html), an emscripten tool that allows for in-line JavaScript in C++.
#### Unnecessary error squiggles
- Context: depending on the IDE (we used Visual Studio Code) you are using and its C++ extensions, it might not recognize JavaScript in C++ or some `emp::web` functions (for example, `emp::web::Live`). But those codes are **not** erroneous, and they compile & run successfully. Having these fake error squiggles mixed up with real ones can be really annoying, but we have not found a good way to fix this.
- Suggetions:
    - If you are using Visual Studio Code, you can try running the "C/C++: Edit Configurations (UI)" command from the command pallette and editing the "Include Path" setting to include the path to your Empirical directory. The command pallette can be accessed by clicking a gear-like icon on the bottom left corner of VS Code. This method **did not** work for us, though.
    - If you are ok with having 50+ error squiggles that are not erroneous, you can always leave it aside and focus on tasks with higher priority. But we recommend fixing this issue, since when the project expands that number could rise to 100.

# Future Directions
- Create pop-ups that display detailed information of organisms on hover.
- Design & Build more complex symbiont-host interactions. So far, Symbulation GUI assumes that each host coexists with only **one** symbiont, but future research will match multiple symbionts to each host. Therefore, our future petri dish should be able to represent the coexistence of multiple symbionts with one host.
- Refine the game mode. Our current game is a very rudimentary series of challenges. Future games can allow users to do things like: create an account, record their progress, view a score board, and resume/exit at will. It would also be preferable if all code related to gaming are refactored into a separate class following industry-standard design principles.
- Convert SymOrg into Avida-Ed representations. This will be a total revamp of the organism design and will likely change how the web interface accesses organism data, so be sure to clarify the design of the organism with Anya when taking over.
- Integrate our interface with some useful modules that other teams have built. One example would be a [configuration tool](https://github.com/anyaevostinar/SymbulationEmp/projects/1) that can help build fancy configuration panels. 

# Conclusion and Takeaways
- Taking over a new project is hard. When we took over, it took us 2 weeks to figure out what Empirical's functions are and what Anya's research Symbulation code does. Do not be ashamed by your "unproductivity" in the familiarization phase -- a beard well lathered is half shaved.
- We strongly recommend learning by doing. Whenever we run into unfamiliar functions, we put them into a toy project and test their effects before using them in Symbulation.
- Ask questions. Learning by doing is great, but don't bang your head against the wall too hard, and NEVER consider asking questions a sign of incapacity. Hearing suggestions from different people can help. You never know whose solution will work, however unplausible it seems.
- Software development can get tricky. It is so easy to get stuck on something for a few days. Do not panick or get angry at yourself. This happens to every programmer, even experienced ones. Treat this as a good learning opportunity and have faith that you will ultimately solve the problem.
- Live a balanced life and don't be a workaholic. Sometimes, having a life outside of work can make you do better at your work. 
- As programmers, protect your eyes! I cannot tell you how regretful I am for not taking care of my eyes, and now I can't see people's face clearly with naked eyes from 20 feet away.
- This project was done remotely during the COVID-19 crisis. It was a completely new learning experience for everyone, and it posed significant challenges on productivity. Many of us were able to practice time management, self-discipline, and remote communication during this novel period, and what we have acquired from this experience will be beneficial throughout our lives.