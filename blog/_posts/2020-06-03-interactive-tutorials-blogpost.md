---
layout: post
title: "Interactive Tutorials"
date: 2020-06-03
author: Dylan Rainbow
---

## Project Overview

The goal of this project is to build a framework that facilitates the creation of interactive user tutorials within Empirical web apps. 
<br>
<br>

#### What is an interactive tutorial?

If you're reading this, you've probably followed many tutorials. And probably even some interactive ones.

But first, let's make sure we're on the same page about how we're using these terms. Wikipedia says this about "tutorial":

> A tutorial, in education, is a method of transferring knowledge and may be used as a part of a learning process. More interactive and specific than a book or a lecture, a tutorial seeks to teach by example and supply the information to complete a certain task.

And what about the "interactive" part?

> In computer science, interactive refers to software which accepts and responds to input from people—for example, data or commands.

So if a tutorial teaches you how to do something, an _interactive_ tutorial is one that lets you "learn by doing". The interactive part means that the system gives you real-time feedback about the actions you're taking.

If you're building an Empirical web app, an interactive tutorial is a great way to teach users how to use your app. However, coding up such a tutorial from scratch isn't a trivial task. We've come up with this system and put it into a library to streamline the tutorial-making process. 

So here we have a written tutorial... about how to create tutorials. Somewhat ironically, it's not an interactive one, but hopefully this page will serve as a useful startup guide for using the Tutorial system.

## Conceptual Structure of a Tutorial
An interactive tutorial created using this library is simply called a Tutorial. A Tutorial is conceptually made up of 3 things:
* **States** - the different states your Tutorial can move between.
* **Triggers** - events or actions that move the Tutorial from one State to another.
* **VisualEffects** - any visual changes made to the web app as part of the tutorial.


## Getting Started

The code for a very simple Tutorial might look something like this (method arguments are omitted for now):
```C++
TutorialManager tut();

tut.AddState(...);
tut.AddState(...);
tut.AddState(...);

tut.AddTrigger(...);
tut.AddTrigger(...);

tut.AddVisual(...);
tut.AddVisual(...);
tut.AddVisual(...);

tut.StartAtState(...);
```

As you can see, the TutorialManager class provides the entire programming interface for the tutorial. Everything you do to manage your tutorial will be done via method calls on this object.

Now let's take a closer look at how this all works.

#### Creating the TutorialManager
To start creating a tutorial, first you must instantiate a TutorialManager. This is simple, as it takes no arguments:
```C++
TutorialManager tut();
```

#### Starting/Stopping a Tutorial
```C++
tut.StartAtState("add_task");
```

```C++
tut.Stop();
```
<br>
<br>

### States

An active Tutorial is always in a certain State. For example, you might have a state where you wait for the user to click a particular button. Just having a State by itself is pretty much useless though. A State gains meaning by having Triggers and VisualEffects associated with it.

#### Creating States
```C++
tut.AddState("state_name");
```
#### End States

<br>
<br>

### Triggers

Triggers are what move the Tutorial from one State to another. There are a few built-in Trigger types, such as EventListenerTrigger (listens for an event on a DOM element), and ManualTrigger (triggered manually from your code). It's also possible to define custom Trigger types.

#### Built-in Triggers

##### EventListenerTrigger
```C++
tut.AddEventListenerTrigger(...);
```

##### ManualTrigger
```C++
tut.AddEventManualTrigger(...);
```

#### Custom Triggers

Describe how to define a custom trigger here.

```C++
tut.AddCustomTrigger(...);
```

#### Manually Firing Triggers
All Triggers can be manually fired:
```C++
tut.FireTrigger(trigger_id);
```

#### Removing Triggers

<br>
<br>

### VisualEffects

A VisualEffect is any visual change made to your web page within the context of the Tutorial. This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a custom VisualEffect class.

#### Built-in VisualEffects

##### CSSEffect
```C++
tut.AddCSSEffect(...);
```

##### PopoverEffect
```C++
tut.AddPopoverEffect(...);
```

##### OverlayEffect
```C++
tut.AddOverlayEffect(...);
```

#### Custom VisualEffects

Describe how to define a custom trigger here.

```C++
tut.AddCustomVisualEffect(...);
```

#### Removing VisualEffects

```C++
tut.RemoveVisualEffect(visual_id);
```
<br>
<br>

### Callbacks
Any Trigger or State can be provided a callback function. For States, the callback will be called when the state is entered. And for Triggers, the callback will be called when the Trigger is...uh, triggered.

#### Setting Callbacks
You can set callbacks when the State/Trigger is added:

```C++
tut.AddState(...);
```

 ...or anytime using the SetStateCallback() / SetTriggerCallback() methods:
```C++
tut.SetStateCallback(state_id, callback_func);
```
<br>
<br>

### Full Example
