---
layout: post
title: "Building Interactive Tutorials for Empirical Web Apps"
date: 2020-07-31
author: Dylan Rainbow
---

## Project Introduction

As web apps become bigger and more complex, it becomes more and more important to provide good learning resources for users. Simple text guides are great to have, but they have numerous shortcomings:

* They give you more information than you need.
* It can be difficult to find the exact info you're looking for.
* Users have to spend time and energy connecting what they see in the docs to the real app.
* They're not interactive.
* Navigating to the documentation disrupts the app experience.

Well produced documentation can mitigate the first three issues, but even the best written docs can't solve the last two.

This is where interactive tutorials come in.

Interactive tutorials are becoming increasingly common. Big name apps like Photoshop, Slack, Discord, and many others provide interactive tutorials. I think we can safely say they're the gold standard when it comes to showing users the basics of your app, or even more!

However, creating an interactive tutorial can be a decent bit of extra work. Therefore, we've created this library to streamline the process for Empirical web apps. It's a flexible and extensible system for creating virtually any kind of interactive tutorial.

So here we have a tutorial... about how to create tutorials. Ironically, this is a written, non-interactive guide. But hopefully it will serve as a useful reference and introduction to the tutorial system.

## Conceptual Structure of a Tutorial
In this framework, a tutorial is essentially made up of 3 things:
* **states** - the different states your tutorial can move between.
* **triggers** - events or actions that move the tutorial from one state to another.
* **visualeffects** - any visual changes made to the web app as part of the tutorial.

You'll need all 3 of these things to make a tutorial that does anything useful!

![Tutorial Graph]({{ site.baseurl }}/assets/djrain/interactive-tutorials-graph.png){:style="width: 100%"}

You can think of triggers and visualeffects as being contained inside of states. However, they can also belong to multiple states at once. So there is a many-to-many relationship between states and triggers, and between states and visualeffects.



## Getting Started

The code for a very simple tutorial might look something like this (method arguments are omitted for now):
```C++
tutorialManager tut();

tut.AddState(...);
tut.AddState(...);
tut.AddState(...);

tut.AddManualTrigger(...);
tut.AddEventListenerTrigger(...);

tut.AddCSSEffect(...);
tut.AddOverlayEffect(...);
tut.AddPopoverEffect(...);

tut.StartAtState(...);
```

As you can see, the **TutorialManager** class provides the entire programming interface for the tutorial. Everything you do to manage your tutorial will be done via method calls on this object.

Now let's take a closer look at how this all works.

## TutorialManager
To start creating a tutorial, first you must instantiate a TutorialManager. This is simple:
```C++
TutorialManager tut;
```

## States

An active tutorial is always in a certain state. For example, you might have a state where you wait for the user to click a particular button. Just having a state by itself is pretty much useless though. A state gains meaning by having triggers and visualeffects associated with it.

<br>

### Creating States
To create and add a state to the tutorial, simply call Addstate() and give your new state a unique string identifier:
```C++
tut.AddState("start_state");
```

We can now refer to this state in our other method calls.

<br>

### End States

A state that does not contain any triggers is called an end state. If an end state is entered, the tutorial will stop.

<br>
<br>

## Triggers

Triggers are things that move the tutorial from one state to another when they are "fired". 
* There are a few built-in trigger types, or you can define custom trigger types. 
* The same trigger may be reused for multiple states.

<br>

### Trigger Parameters

All Add...Trigger() methods have some parameters in common. These are:

* current_state - name of the state that this trigger should be activated for.
* next_state - name of the state that the tutorial should move to when this trigger fires.
* trigger_id - (optional) a unique string ID for this trigger.
* callback - (optional) a callback function to be called when this trigger fires. The function must return void and have no parameters.

<br>

### Built-in Triggers

#### ManualTrigger
The simplest type of trigger is the ManualTrigger. It only fires when you fire it manually from your code. 

```C++
tut.AddEventManualtrigger(state, next_state, trigger_id, callback);
```

<br>

#### EventListenerTrigger
The EventListenerTrigger listens for the given html event on an Empirical widget, and fires when the event occurs.

```C++
tut.AddEventListenerTrigger(state, next_state, widget, event_name, trigger_id, callback);
```

* _widget_ is the Empirical widget the event listener should be placed on (you must pass the actual widget, not its ID). 
* _event_ is the name of the html event to listen for, but without the "on" at the beginning (e.g. "click"). 

<br>

### Custom Triggers

To create a custom trigger, define a class that inherits from trigger:

```C++
class CustomTrigger : public Trigger {

    friend class tutorial;
    friend class State;

    Customtrigger(...) {};

    void Activate() {}
    void Deactivate() {}
};
```

* The friend declarations are necessary, and the Activate/Deactivate methods must be defined. 
* Activate() is called every time a state containing the trigger is entered. It will also be called immediately if a trigger is added to the current state.
* Deactivate() is called when a state containing the trigger is exited.

(todo: adding custom triggers)
<br>

### Reusing Triggers
If you've previously added a trigger to some state, you may add it to another state with this method:
```C++
tut.AddExistingTrigger(current_state, next_state, trigger_id);
```

<br>

### Manually Firing Triggers
All triggers can be manually fired, as long as you have their trigger ID:
```C++
tut.Firetrigger(trigger_id);
```

This should only be done if you are certain that the current state contains the trigger.

<br>

### Removing Triggers
You may remove a trigger from any state containing it:
```C++
tut.RemoveTrigger(trigger_id, state_name)
```
Note that this will deactivate the trigger if it is active.

<br>
<br>

## VisualEffects

A visualeffect is any visual change made to your web page within the context of the tutorial. 
* This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a custom visualeffect class. 
* The same trigger may be added to multiple states.

<br>

### VisualEffect Parameters

All Add...Effect() methods have the following parameters in common:

* current_state - name of the state that this visualeffect should be added to.
* visual_id - (optional) a unique string ID for this visualeffect.

### Built-in VisualEffects

#### CSSEffect
A CSSEffect applies a change to the CSS styling of a particular widget.
```C++
tut.AddCSSEffect(current_state, widget, attr_name, attr_value, visual_id);
```

* _widget_ is the widget to apply the change to
* _attr_name_ is the string name of the attribute to change
* _attr_value_ is the new value of the attribute

The given attribute will be reverted back to its previous state when the effect is deactivated.

<br>

#### OverlayEffect
An OverlayEffect adds a colored overlay on top of everything else on the page. 
```C++
tut.AddOverlayEffect(current_state, color, opacity, z-index, visual_id);
```

* _color_ is the CSS string describing the color of the overlay
* _opacity_ is a float for the opacity of the overlay
* _z-index_ is the z-index of the overlay

This effect can be used to draw a user's attention to a particular widget (you can make the widget appear above the overlay using a CSSEffect to change its z-index).

It can also serve to "disable" any widgets below the overlay, as they will not be able to receive input.

<br>

### Custom VisualEffects

To create a custom visualeffect, define a class that inherits from visualeffect:

```C++
class CustomVisualEffect : public VisualEffect {

    friend class tutorial;
    friend class State;

    CustomVisualEffect(...) {};

    void Activate() {}
    void Deactivate() {}
};
```

* The friend declarations are necessary, and the Activate/Deactivate methods must be defined. 
* Activate() is called every time a state containing the visualeffect is entered. It will also be called immediately if a visualeffect is added to the current state.
* Deactivate() is called when a state containing the visualeffect is exited.

### Adding Custom VisualEffects
```C++
tut.AddCustomVisualEffect(current_state, visual_id);
```


<br>

### Reusing VisualEffects
If you've previously added a visualeffect to some state, you may add it to another state with this method:
```C++
tut.AddExistingVisualEffect(current_state, visual_id);
```

<br>

### Removing VisualEffects
As with triggers, You may also remove a visualeffect from any state containing it:
```C++
tut.RemoveVisualEffect(state_name, visual_id);
```

Note that this will deactivate the visualeffect if it is active.

<br>
<br>


## Tutorial Flow
### Starting the tutorial
The tutorial does not become active until you start it. To do this, you call StartAtstate(), and provide it the name of a state:
```C++
tut.StartAtState("add_task");
```

This will activate all visualeffects and triggers in the given state.

<br>

### Stopping the Tutorial

```C++
tut.Stop();
```

This will deactivate all visuals and triggers in the current state.

The tutorial will automatically stop if a state is entered that does not contain any triggers. This would be expected if a user completed the tutorial.
<br>
<br>

## Callbacks
Any trigger or state can be provided a callback function. 
* For states, the callback will be called when the state is entered.
* For triggers, the callback will be called when the trigger fires (but before the next state is entered).

### Setting Callbacks
You can set callbacks when the state/trigger is added, by providing the optional callback argument that you saw in previous sections.

You can also set a callback at any time using the SetstateCallback() / SetTriggerCallback() methods:
```C++
tut.SetstateCallback(state_id, callback);
```

```C++
tut.SetTriggerCallback(trigger_id, callback);
```
<br>
<br>

### Full Code Example

(todo)


### Difficulties and Future Directions


### Thanks!

In closing, I'd like to give credit to Austin Ferguson (@FergusonAJ) for being an excellent mentor on this project. He came up with the rough outline for this system, and contributed to every aspect of its design, as well as some of the code itself. Thanks also to everyone on the WAVES team who helped with advice, tips, and feedback.

This project gave me the opportunity to learn a lot about web development, the Empirical library, and contributing to real-life distributed software. I hope that our contribution will prove to be a valuable addition to the library. 