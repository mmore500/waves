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

So if a tutorial teaches you how to do something, an _interactive_ tutorial is one that lets you "learn by doing". Interactive means that the system gives you real-time feedback about the actions you're taking.

If you're building an Empirical web app, an interactive tutorial is a great way to teach users how to use your app. However, coding up such a tutorial from scratch isn't a trivial task. We've come up with this system and put it into a library to streamline the tutorial-making process. 

So here we have a written tutorial... about how to create tutorials. Somewhat ironically, it's not an interactive one, but hopefully this page will serve as a useful startup guide for using the Tutorial system.

## Conceptual Structure of a Tutorial
An interactive tutorial created using this library is simply called a Tutorial. A Tutorial is conceptually made up of 3 things:
* **States** - the different states your Tutorial can move between.
* **Triggers** - events or actions that move the Tutorial from one State to another.
* **VisualEffects** - any visual changes made to the web app as part of the tutorial.

You can think of Triggers and VisualEffects as being contained inside of States. However, they can also belong to multiple States at once. So there is a many-to-many relationship between States and Triggers, and between States and VisualEffects.


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

As you can see, the **TutorialManager** class provides the entire programming interface for the tutorial. Everything you do to manage your tutorial will be done via method calls on this object.

Now let's take a closer look at how this all works.

#### Creating the TutorialManager
To start creating a tutorial, first you must instantiate a TutorialManager. This is simple, as it takes no arguments:
```C++
TutorialManager tut();
```

### States

An active Tutorial is always in a certain State. For example, you might have a state where you wait for the user to click a particular button. Just having a State by itself is pretty much useless though. A State gains meaning by having Triggers and VisualEffects associated with it.

#### Creating States
To create and add a State to the tutorial, simply call AddState() and give your new State a unique string identifier:
```C++
tut.AddState("start_state");
```

We can now refer to this state in our other method calls.

#### End States

A State that does not contain any Triggers is called an End State. If an End State is entered, the tutorial will stop.

<br>
<br>

### Triggers

Triggers are things that move the Tutorial from one State to another when they are fired. There are a few built-in Trigger types, or you can define custom Trigger types. The same Trigger may be reused for multiple States.

#### Trigger Parameters

All Add...Trigger() methods have some parameters in common. These are:

* current_state - name of the State that this Trigger should be activated for.
* next_state - name of the State that the tutorial should move to when this Trigger fires.
* trigger_id - (optional) a unique string ID for this Trigger.
* callback - (optional) a callback function to be called when this Trigger fires. The function must return void and have no parameters.

#### Built-in Triggers

##### ManualTrigger
The simplest type of Trigger is the ManualTrigger. It only fires when you fire it manually from your code. 

```C++
tut.AddEventManualTrigger(state, next_state, trigger_id, callback);
```

##### EventListenerTrigger
The EventListenerTrigger listens for the given html event on an Empirical Widget, and fires when the event occurs.

```C++
tut.AddEventListenerTrigger(state, next_state, widget, event_name, trigger_id, callback);
```

* _widget_ is the Empirical widget the event listener should be placed on (you must pass the actual widget, not its ID). 
* _event_ is the name of the html event to listen for, but without the "on" at the beginning (e.g. "click"). 



#### Custom Triggers

To create a custom Trigger, define a class that inherits from Trigger:

```C++
class CustomTrigger : public Trigger {

    friend class Tutorial;
    friend class State;

    CustomTrigger(...) {};

    void Activate() {}
    void Deactivate() {}
};
```

The friend declarations are necessary, and the Activate/Deactivate methods must be defined. 
Activate() is called every time a State containing the Trigger is entered. It will also be called immediately if a Trigger is added to the current State.
Deactivate() is called when a State containing the Trigger is exited.


#### Reusing Triggers
If you've previously added a Trigger to some State, you may add it to another State with this method:
```C++
tut.AddExistingTrigger(current_state, next_state, trigger_id);
```

#### Manually Firing Triggers
All Triggers can be manually fired, as long as you have their Trigger ID:
```C++
tut.FireTrigger(trigger_id);
```

This should only be done if you are certain that the current state contains the Trigger.

#### Removing Triggers
You may remove a Trigger from any State containing it:
```C++
tut.RemoveTrigger(trigger_id, state_name)
```
Note that this will deactivate the Trigger if it is active.

<br>
<br>

### VisualEffects

A VisualEffect is any visual change made to your web page within the context of the Tutorial. This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a custom VisualEffect class.

#### VisualEffects Parameters

All Add...Effect() methods have the following parameters in common:

* current_state - name of the State that this VisualEffect should be activated for.
* visual_id - (optional) a unique string ID for this VisualEffect.

#### Built-in VisualEffects

##### CSSEffect
A CSSEffect applies a change to the CSS styling of a particular Widget.
```C++
tut.AddCSSEffect(current_state, widget, attr_name, attr_value, visual_id);
```

* _widget_ is the widget to apply the change to
* _attr_name_ is the string name of the attribute to change
* _attr_value _is the new value of the attribute

The given attribute will be reverted back to its previous state when the effect is deactivated.


##### OverlayEffect
An OverlayEffect adds a colored overlay on top of everything else on the page. 
```C++
tut.AddOverlayEffect(current_state, color, opacity, z-index, visual_id);
```

* _color_ is the CSS string describing the color of the overlay
* _opacity_ is a float for the opacity of the overlay
* _z-index_ is the z-index of the overlay

This effect can be used to draw a user's attention to a particular Widget (you can make the Widget appear above the overlay using a CSSEffect to change its z-index).

It can also serve to "disable" any Widgets below the overlay, as they will not be able to receive input.


#### Removing VisualEffects
As with Triggers, You may also remove a VisualEffect from any State containing it:
```C++
tut.RemoveVisualEffect(state_name, visual_id);
```

Note that this will deactivate the VisualEffect if it is active.
<br>
<br>


### Tutorial Flow
#### Starting the tutorial
The tutorial does not become active until you start it. To do this, you call StartAtState(), and provide it the name of a state:
```C++
tut.StartAtState("add_task");
```

This will activate all VisualEffects and Triggers in the given state.

#### Stopping the tutorial

```C++
tut.Stop();
```

This will deactivate all visuals and triggers in the current state.

The tutorial will automatically stop if a State is entered that does not contain any Triggers. This would be expected if a user completed the tutorial.
<br>
<br>

### Callbacks
Any Trigger or State can be provided a callback function. 
* For States, the callback will be called when the state is entered.
* For Triggers, the callback will be called when the Trigger fires (but before the next state is entered).

#### Setting Callbacks
You can set callbacks when the State/Trigger is added, by providing the optional callback argument that you saw in previous sections.

You can also set a callback at any time using the SetStateCallback() / SetTriggerCallback() methods:
```C++
tut.SetStateCallback(state_id, callback);
```

```C++
tut.SetTriggerCallback(trigger_id, callback);
```
<br>
<br>

### Full Code Example

(Still need to add this)
