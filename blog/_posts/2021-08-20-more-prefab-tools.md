---
layout: post
title: "More Prefabricated Web Tools!"
date: 2021-08-20
author: Tait Weicht
---

* Introduction, summarize previous work
* Building of the work of my predecessor Sarah
* Checkout her blog [here](http://mmore500.com/waves/blog/prefab-tools.html), for an overview of the great work she did!

## Goals
The goal of the project this summer was to enhance existing prefabricated components and to create new ones.
In addition, some prefabricated components had issues which needed to be addressed.
* Loads of ideas, new and old, for prefab components
* A number of juicy issues to try and close

#### It will be simple they said, "a button", they said
Thinking it would be a relatively simple project, I chose an enhancement to the config panel as my first task.

* Starting simple, just add a reload button to the config panel
* Discovering and fixing bugs in the Config panel

#### How _Card_ could it be?
Digging deeper into the issue list I decided I would try my hand at a problem that was still unsolved: how do we override the default stream operator for a component?
* Override used loosely, since the function is templated!
* Using `static_cast<Div>(*this)` to prevent infinite recursion.

#### The Config Panel Conundrum
The next issue we tackled was a strange bug with the Config Panel.
* Discovering the bug that forced ConfigPanel to be global
* Refactoring to make it more modular

#### ReadoutPanel: Live Variables in the Limelight
As a counterpart to the configuration panel, Matthew suggested making a component that could display values live from a simulation.
* Fun with forwarding a parameter pack
 Just for anyone curious about where the ellipses go, the syntax is
 ```cpp
 OuterFunc(VALUE_TYPES && ... others) {
   InnerFunc(std::forward<VALUE_TYPES>(others)...);
 }
 ```
* Keeping a low footprint in mind when deciding on the styling

#### Control Panel

* Managing simulation with some standard controls
* Ideas for helpful user interfaces: ToggleButtonGroups and AugmentedButtons

## Some Takeaways
Having worked on projects from fixing small bugs to writing entire components, I've been able to see a good portion of Empirical's web framework.
I'm really excited for where things are going and want to try and want leave things in a good state for the next person to work on this code base.
As such, here are some ideas and principles I've come across or come up with when working on this project.
* Came across a number of ideas that could prove valuable as design principles
* Some opinions about the direction prefab component development should go

#### Modularity is King, Inheritance is Queen
* Making small components is valuable even if we don't think users will use them raw
* Building off existing components is necessary but we need a somewhat standard system
 * Idea for inheritance model + code
 * Pros and cons of this

#### You know... there's CSS for that
* Making components less opinionated and doing more with CSS

## Thoughts on the Future
* Challenges of eventually upgrade to Bootstrap v5.0
* Challenges of responsive web design
* How to make Bootstrap grid accessible

## Acknowledgements
* Matthew, my mentor!
* NSF Grant ####### ...
