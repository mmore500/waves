---
layout: post
title: "Interactive Tutorials"
date: 2020-06-03
author: Dylan Rainbow
---

## Project Overview

The goal of this project is to create a framework that facilitates the creation of interactive user tutorials within Empirical web apps. 
<br>
<br>

## What is an interactive tutorial?

An interactive tutorial created using this library is simply called a Tutorial. A Tutorial is essentially made up of 3 things:
* States
* Triggers
* VisualEffects

A Tutorial can be visualized as a directed graph where the nodes are States, and the edges are Triggers:
<br>
[graph diagram goes here]

#### Creating a Tutorial
```C++
Tutorial tut();
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

An active Tutorial is always in a certain State. For example, you might have a state where you wait for the user to click a particular button. A State doesn't do much by itself -- it gains meaning by having Triggers and VisualEffects associated with it.

#### Creating States
```C++
tut.AddState("state_name");
```
#### End States

<br>
<br>

### Triggers

A Trigger is any action that moves the Tutorial from one State to another. There are a few built-in Trigger types, such as EventListenerTrigger (listens for an event on a DOM element), and ManualTrigger (triggered manually from your code). It's also possible to define custom Trigger types.

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
