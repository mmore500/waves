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

This is where interactive tutorials come in. :raised_hands:	

Interactive tutorials are becoming increasingly common. Big name apps like Photoshop, Slack, Discord, and many others provide interactive tutorials. I think we can safely say they're the gold standard when it comes to showing users the basics of your app, or even beyond!

However, creating an interactive tutorial can be a decent bit of extra work. Therefore, we've created this library to streamline the process for Empirical web apps. It's a flexible and extensible system for creating virtually any kind of interactive tutorial.

So here we have a tutorial... about how to create tutorials. Ironically, this is a written, non-interactive guide. But hopefully it will serve as a useful reference and introduction to the tutorial system.

<br>
<br>

## Conceptual Structure of a Tutorial
In this framework, a tutorial is essentially made up of 3 things:
* **States** - the different states your tutorial can move between.
* **Triggers** - events or actions that move the tutorial from one state to another.
* **VisualEffects** - any visual changes made to the web app as part of the tutorial.

You'll need all 3 of these things to make a tutorial that does anything useful!

It's helpful to visualize a tutorial as a directed graph. In this graph, the nodes are what we're calling states, and the edges are our triggers:

![Tutorial Graph]({{ site.baseurl }}/assets/djrain/interactive-tutorials-graph.png){:style="width: 80%"}

One can see the flexibility of this system. It supports complex, nonlinear tutorials out of the box. Notice how states can have multiple triggers, to multiple different states. Also note that triggers can be reused between different states (such as Trigger A in the example above). 

Visualeffects are not pictured in this graph, but you can imagine them existing inside of the individual states. Actually, both triggers and visualeffects exist only within states. So each state has a list of triggers, and a list of visualeffects, that will all be activated when the state is entered (and deactivated when the state is exited).

<br>
<br>

## Code Preview

The code for a very simple tutorial might look something like this (the method arguments are omitted for now):
```c++
Tutorial tut();

tut.AddState(...);
tut.AddState(...);
tut.AddState(...);

tut.AddManualTrigger(...);
tut.AddEventListenerTrigger(...);

tut.AddCSSEffect(...);
tut.AddOverlayEffect(...);
tut.AddCustomVisualEffect(...);

tut.StartAtState(...);
```

As you can see, the **Tutorial** class provides the entire programming interface for the tutorial. Everything you do to manage your tutorial will be done via method calls on this object. :open_mouth:	

Most Tutorial methods can be chained, so you could also write that same code like this:

```C++
Tutorial tut();

tut.AddState(...)
.AddState(...)
.AddState(...);

tut.AddManualTrigger(...)
.AddEventListenerTrigger(...);

tut.AddCSSEffect(...)
.AddOverlayEffect(...)
.AddPopoverEffect(...);

tut.StartAtState(...);
```

Now let's take a closer look at how this all works!

<br>
<br>

## Tutorial Class
To begin, you must instantiate a Tutorial object. This is easy:
```C++
Tutorial tut;
```

As stated before, all setup and manipulation of the tutorial will be done through this object.
<br>
<br>

## States

An active tutorial is always in a certain state. For example, you might have a state where you wait for the user to click a particular button. Of course, just having a state by itself is pretty much useless. :stuck_out_tongue_closed_eyes: 

A state gains meaning by having triggers and visualeffects associated with it. But we'll get to those shortly.

<br>

### Creating States
To create and add a state to the tutorial, simply call AddState() and give your new state a unique name:
```C++
tut.AddState("start_state");
```

We can now refer to this state in our other method calls. :sunglasses:	

<br>

### End States

A state that does not contain any triggers is called an end state. If an end state is entered, the tutorial will automatically stop. This means you don't have to do anything special to make a state an end state! :)

<br>
<br>

## Triggers

Triggers are things that move the tutorial from one state to another when they are "fired". 

With the exception of manual firing, triggers must be active in order to fire. States automatically activate all their triggers upon being entered.

There are a few built-in trigger types, or you can define custom trigger types. 


<br>

### Trigger Parameters

All methods for adding triggers use the following parameters:

* current_state - name of the state that this trigger should be activated for.
* next_state - name of the state that the tutorial should move to when this trigger fires.
* trigger_id - (optional for all but custom triggers) a unique string ID for this trigger.
* callback - (optional) a callback function to be called when this trigger fires. The function must return void and have no parameters.

<br>

### Built-in Triggers

#### ManualTrigger
The simplest type of trigger is the ManualTrigger. It only fires when you fire it manually from your code. Amazing, right?

```C++
tut.AddEventManualtrigger(state, next_state, trigger_id, callback);
```

<br>

#### EventListenerTrigger
The EventListenerTrigger listens for the given html event on an Empirical widget, and fires when the event occurs. 

You might use it to move to the next state when a button is clicked.

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

    friend class Tutorial;
    friend class State;

    Customtrigger(...) {};

    void Activate() {}
    void Deactivate() {}
};
```

* The friend declarations are necessary, and the Activate/Deactivate methods must be defined. 
* Activate() is called every time a state containing the trigger is entered. It will also be called immediately if a trigger is added to the current state.
* Deactivate() is called when a state containing the trigger is exited, or when the trigger is removed.

Then, to add your custom trigger:
```C++
tut.AddCustomTrigger(current_state, next_state, custom_arg_1, custom_arg_2, ..., trigger_id, callback);
```
* Between next_state and trigger_id, you supply the arguments to the custom trigger you defined.
* In order to avoid potential conflicts with custom parameters, the trigger_id is **required** for custom triggers. The callback, as always, is optional.

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
tut.FireTrigger(trigger_id);
```

This must only be done for triggers in the current state, but the trigger does _not_ have to be currently active.

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

This could be adding an element to the page, changing the CSS styling of an element, or anything you want via a custom visualeffect class!

As with triggers, states automatically activate all their visualeffects upon being entered.

<br>

### VisualEffect Parameters

All methods for adding visualeffects use the following parameters:

* current_state - name of the state that this visualeffect should be added to.
* visual_id - (optional for all but custom visualeffects) a unique string ID for this visualeffect.
<br>

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
tut.AddOverlayEffect(current_state, parent, color, opacity, z-index, intercept_mouse, visual_id);
```
* _parent_ is the Div you want the overlay to be added to. Typically, the Document (which is a Div) where all your widgets live works fine here.

Optional parameters:
* _color_ is the CSS string describing the color of the overlay. Default = "black"
* _opacity_ is a float for the opacity of the overlay. Default = 0.4
* _z-index_ is the z-index of the overlay. Default = 1000
* _intercept_mouse_ is a bool indicating whether or not the overlay should receive pointer events. Can be set to prevent elements under the overlay from being clicked. Default = false

This effect is an easy way to help draw a user's attention to a particular widget (you can make the widget appear above the overlay using a CSSEffect to change its z-index).


<br>


#### PopoverEffect (Experimental)

PopoverEffect is essentially a message bubble that you can set to appear over a particular widget. This would be super handy because it serves as a visual cue while also providing useful text information to the user. It's named after the Bootstrap Popover class, because that's what we hoped to use within our class. 

Unfortunately, we weren't able to make the Bootstrap popovers work, because of some restrictions currently within Empirical (described [here](#difficulties-and-future-directions))

We began trying to create a custom popover class using Empirical functionality, but it turns out to be no trivial task to get these working reliably. So this feature is not really usable as of now. :frowning_face:

<br>

### Custom VisualEffects

To create a custom visualeffect, define a class that inherits from VisualEffect:

```C++
class CustomVisualEffect : public VisualEffect {

    friend class Tutorial;
    friend class State;

    CustomVisualEffect(...) {};

    void Activate() {}
    void Deactivate() {}
};
```

* The friend declarations are necessary, and the Activate/Deactivate methods must be defined. 
* Activate() is called every time a state containing the visualeffect is entered. It will also be called immediately if a visualeffect is added to the current state.
* Deactivate() is called when a state containing the visualeffect is exited, or when the visualeffect is removed.

Then, to add your custom visualeffect:
```C++
tut.AddCustomVisualEffect(current_state, custom_arg_1, custom_arg_2, ..., visual_id);
```
* As with custom triggers, the visual_id is **required** for custom visualeffects.

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
### Starting the Tutorial
The tutorial does not become active until you start it. To do this, you call StartAtstate(), and provide it the name of a state:
```C++
tut.StartAtState("add_task");
```

This will activate all visualeffects and triggers in the given state.

<br>

### Stopping the Tutorial
The tutorial will stop automatically if an end state is entered. But if you wish to stop it manually:

```C++
tut.Stop();
```

This will deactivate all visuals and triggers in the current state.


<br>

## Callbacks
Any trigger or state can be provided a callback function. 
* For states, the callback will be called when the state is entered.
* For triggers, the callback will be called when the trigger fires (but before the next state is entered).

One potential use for callbacks is disabling any widgets that are not involved in the current state.

### Setting Callbacks
You can set callbacks when the state/trigger is added, by providing the optional callback argument that you saw in previous sections.

You can also set a callback at any time using the SetStateCallback() / SetTriggerCallback() methods:
```C++
tut.SetStateCallback(state_id, callback);
```

```C++
tut.SetTriggerCallback(trigger_id, callback);
```
<br>
<br>


## Full Code Example

Here is a full, runnable example of app with a tutorial. This app doesn't do anything meaningful, but hopefully it's helpful :)

Our app has two widgets, a button and an input text box. Our tutorial will involve have two steps:
1. Click the button.
2. Type something into the text box and press enter.

We'll use an EventListenerTrigger for the button, and a ManualTrigger for the text box.

For visuals, we simply use two OverlayEffects to dim out everything but the widget for each step, combined with CSSEffects to pop the widgets above. We set intercept_mouse to true for the overlays, so that we can't click on anything below.

```C++

#include "web/web.h"
#include "web/KeypressManager.h"
#include <iostream>
#include "web/Tutorial.h"

namespace UI = emp::web;

UI::Document doc("emp_base");
UI::Button my_button([](){}, "Click me!");
UI::Input my_input([](std::string s){}, "text", "");

Tutorial tut;


void OnInputEnter(UI::KeyboardEvent evt) {

    if (evt.keyCode == 13) {

        std::string inputStr = my_input.GetCurrValue();

        if (!inputStr.empty())
            tut.FireTrigger("enter_input_trigger");
    }
}

void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }



int main() {

    doc << my_button;
    doc << my_input;

    my_input.On("keypress", &OnInputEnter);
    
    // since z-index can only be set on positioned elements...
    my_button.SetCSS("position", "relative");
    my_input.SetCSS("position", "relative");
    

    tut.AddState("first_state");
    tut.AddState("second_state");
    tut.AddState("end_state", &PrintComplete);

    tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click");
    tut.AddManualTrigger("second_state", "end_state", "enter_input_trigger");

    tut.AddOverlayEffect("first_state", doc, "black", 0.5, 1000, true);
    tut.AddCSSEffect("first_state", my_button, "z-index", "10000");

    tut.AddOverlayEffect("second_state", doc, "blue", 0.5, 1000, true);
    tut.AddCSSEffect("second_state", my_input, "z-index", "10000");

    tut.StartAtState("first_state");
    
}

```


If you click the button, then enter something in the text box, you should see "Tutorial Complete" printed to the console!

And there you have it, a complete tutorial created with exactly 14 lines of code! :sunglasses:	


<br>
<br>

## Difficulties and Future Directions

We encountered several obstacles while working on this project. 

The first issue was that Empirical's Listeners class could only apply a single event handler for any event at a time. This was a problem because our EventListenerTrigger needed to add its own event handlers, in addition to any that the user may have set. So first, we enhanced the Listeners class to support adding any number of event handlers.

The second big issue, which we weren't able to address, is that Empirical's web system does not play nicely with JavaScript code. Any changes made to a widget's properties must be made from the C++ side, or else those changes will be wiped out when Empirical redraws the widget. This caused us quite a bit of confusion before we identified the issue, and it also prevented us from being able to implement a JavaScript popover library. Popovers are probably the most useful feature that the system is currently lacking, so we hope that the necessary changes to support this can be made to Empirical.

We're not sure whether a system like this might also be useful for native Empirical apps. The high-level framework is not web-specific, so this may be an area for potential development. 

<br>

## Acknowledgements

I'd like to give credit to Austin Ferguson (@FergusonAJ) for being an excellent mentor on this project. He came up with the rough outline for the system, and contributed to every aspect of its design, as well as some of the code itself! 

Thanks also to everyone on the WAVES team who helped with advice, tips, and feedback. :blush:	

This project gave me the opportunity to learn a lot about web development, Empirical, and contributing to real-life distributed software. I hope that our contribution will prove to be a valuable addition to the library. 
