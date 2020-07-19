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

A Tutorial can be visualized as a directed graph where the nodes represent States, and the edges represent Triggers. Both Triggers and VisualEffects are tied to States.


### States

A State represents a state of your app's tutorial. For example, your Tutorial might have a state where you wait for the user to click a particular button. A state doesn't do much by itself -- it gains meaning by having Triggers and VisualEffects associated with it.

#### Creating Triggers


### Triggers

A Trigger is any action that moves the Tutorial from one State to another. There are different types of Triggers, such as EventListenerTrigger (listens for an event on a DOM element), and ManualTrigger (triggered manually from your code). It's also possible to define custom Trigger types.

#### Creating Triggers

### VisualEffects

A VisualEffect is any visual change to the web app. This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a vustom VisualEffect class.

#### Creating VisualEffects

