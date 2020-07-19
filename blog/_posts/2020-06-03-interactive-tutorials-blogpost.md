---
layout: post
title: "Interactive Tutorials"
date: 2020-06-03
author: Dylan Rainbow
---

## Project Overview

The goal of this project is to create a framework that facilitates the creation of interactive user tutorials within Empirical web apps. 


## What is an interactive tutorial?

An interactive tutorial created using this library is simply called a Tutorial. A Tutorial is made up of 3 things:
* States
* Triggers
* VisualEffects

A Tutorial can be visualized as a directed graph where the nodes are States, and the edges are Triggers. Both Triggers and VisualEffects are tied to States.

#### Creating a Tutorial
```C++
Tutorial tut();
```

### States

An active Tutorial is always in a certain State. For example, you might have a state where you wait for the user to click a particular button. A State doesn't do much by itself -- it gains meaning by having Triggers and VisualEffects associated with it.

#### Creating States
```C++
tut.AddState("state_name");
```
#### End States

### Triggers

A Trigger is any action that moves the Tutorial from one State to another. There are different types of Triggers, such as EventListenerTrigger (listens for an event on a DOM element), and ManualTrigger (triggered manually from your code). It's also possible to define custom Trigger types.

#### Creating Triggers
```C++
tut.AddEventListenerTrigger(...);
```
```C++
tut.AddEventManualTrigger(...);
```

### VisualEffects

A VisualEffect is any visual change to the web app Tutorial. This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a custom VisualEffect class.

#### Creating VisualEffects
```C++
tut.AddCSSEffect(...);
```

### Callbacks
Any Trigger or State can be provided a callback function. For States, the callback will be called when the state is entered. And for Triggers, the callback will be called when the Trigger is...uh, triggered. 
