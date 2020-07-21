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
- Input fields with proper error-checking capabilities that allow users to set **vertical transmission** and **grid** for the population. The change in these two parameters cause organisms to undertake diverging paths of evolution.
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
- On command line, navigate to your native Symbulation project directory and type `python3 -m http.server` in your command line. It is recommended that you use a separate terminal specifically for serving your local project.


# Difficulties

Hovering capabilities/mouse tracking on canvas

Depiction of a single Host/Symbiont pair


# Future Direction

Allowing user to select and view genomes of specific symbionts

Integrating the more complex genomes


# Conclusion and Takeaways

