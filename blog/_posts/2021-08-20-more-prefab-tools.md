---
layout: post
title: "More Prefabricated Web Tools!"
date: 2021-08-20
author: Tait Weicht
---

Prior to learning of [Empirical](https://github.com/devosoft/Empirical), a library of tools for developing efficient, reliable, and accessible scientific software, I had no idea that people actually did web development in C++.
Thanks to [emscripten](https://emscripten.org/), it _is_ possible turn your C++ into WebAssembly to run quickly in the browser.
With this framework, it becomes simple to turn a C++ command line tool into single page web application.
However, developing a graphical user interface is a lot more work than making a command line one.
To expedite porting from command line to browser, Empirical supports some prefabricated components using the  open source front-end toolkit, [Bootstrap](https://getbootstrap.com/docs/5.1/getting-started/introduction/).
My predecessor Sarah Boyd developed a large number of components and you can read about her work [here]({{ site.baseurl }}/blog/prefab-tools.html).
I took up the torch this summer to add to this previous work!

## Goals
The goal of the project this summer was to enhance existing prefabricated components and to create new ones.
In addition, some prefabricated components had issues which needed to be addressed (:bug:).
The following [issue](https://github.com/devosoft/Empirical/issues/334) listed some components to develop and along the way we thought up some more (:bulb:)!

#### "It will be simple," they said, "a button", they said
Thinking it would be a relatively simple thing to start with, I began work adding a reload button to the `ConfigPanel` (find the demo [here](https://devosoft.github.io/empirical-prefab-demo/empirical-prefab-demo.html)) as one of my first tasks.
However, this task almost immediately stalled on discovery of a bug!

:bug: __Bug__: In an attempt to make Config objects flexible, `stringstream` was being used to extract `double`s, `float`s and `int`s from text entered by the user.
This worked fine until you tried it with `std::string`s.
The `stringstream` method resulted in only the first word being copied!

:butterfly: __Solution__: Keeping a function template was necessary for efficiency and clarity. However, we needed different behavior for a specific type. Luckily since C++11 we have `constexpr` and type traits. Using
```c++
  if constexpr(std::is_same<MY_TYPE, std::>::value) {
    // do something ...
  }
```
inside a function template, we can do a compile time type check as to whether it should generate the code inside the `if`.
Pretty nifty!

Knowing this pattern means that in the future if new types become supported in config files there's already a good example of how to handle their parsing smartly.
While fixing this problem it was also necessary to normalized the way config parameters are passed through a URL.
In a URL query string both `%20` and `+` encode a space character (`' '`) and the standard does not differentiate between them.
However, Empirical's `ArgumentManager` class supports multiple values for a key.
By assigning `+` the role of a value separator it became possible to have support for keys with multiple values and support whitespace _in_ string values.

#### How _Card_ could it be?
Digging deeper into the issue list I decided I would try my hand at a problem that was still unsolved: how do we override the default stream operator for a component?
Here the term override used loosely since in C++ you can only override a virtual function, but our web components use a function template, which cannot be virtual.

:lemon: __Problem__: A number of methods had been tried to get streaming into a `Card` to place components into the `Card`'s body element but all led to the cryptic error `too much recursion`.

:tropical_drink: __Solution__: The root of the problem was that `Card` itself needed sub-components (it has a header div and a body div).
To get these components in place `Card` uses, you guessed it, the stream operator.
So replacing the stream operator for `Card` had the effect that when the constructor tried to add the body div, it tried to put the body div inside _itself_.

![A gif of zooming in on cup with a small table next to it with a cup with a small table next to it with...]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-droste.gif){:style="width: 100%"}
*TOO MUCH RECURSION!!!*

Using `static_cast<Div>(*this)` will prevent infinite recursion by using `Div`'s default method of streaming components.


#### The Config Panel Conundrum
The next issue we tackled was a strange bug with the `ConfigPanel`.

:bug: __Bug__: A `ConfigPanel` only works if it is a global object.

This indicated that something was going wrong with our memory management.
The problem was a rather subtle one, while the `ConfigPanel` _was_ a div, it also _had_ a div.
Like Dr. Jekyll and Mr. Hyde caught mid transformation the `ConfigPanel` was caught trying to be two things at once, a class to setup a div :hammer_and_wrench: and a div with some extra frills :ribbon:.
The result was that when time came to add the component to the document object model (DOM), the inner shell member div was properly placed and the outer shell destructed, but the inner shell kept references to the outer.

:exclamation: And since the outer shell didn't exist anymore things were seriously borked. :exclamation:

Keeping the component global kept the outer shell in existence which is why the component could function.
Once the problem was identified it wasn't to hard to fix its identity crisis.
In addition, the alterations provided the opportunity to break the component into some smaller reusable pieces.

![A "refactor all the things" meme]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-refactor.png){:style="width: 100%"}
*I had to be a little careful not get carried away*

#### ReadoutPanel: Live Variables in the Limelight
As a counterpart to the configuration panel, Matthew suggested making a component that could display values live from a simulation.
While Empirical has a visualization component using [D3](https://d3js.org/), this component would serve the need for a lighter style of display for simulation statistics.

Here's its bio:
* Inheriting from the collapsible `Card` prefab component, the Readout Panel provides a simple way to animate a collection of live values.
* A user can specify a refresh rate the panel will attempt to update at without choking execution.
* A close cousin in style and spirit to the `ConfigPanel` by reusing components developed in the `ConfigPanel refactor.

However, the ReadoutPanel's development was complicated by being the prefab component to be derived from another prefab component.
When I modified the `Card` class to include an "on toggle" handler so that

* Fun with forwarding a parameter pack
Just for anyone curious about where the ellipses go, the syntax is
```cpp
OuterFunc(VALUE_TYPES && ... others) {
  InnerFunc(std::forward<VALUE_TYPES>(others)...);
}
```

#### Control Panel
One of the

* Managing simulation with some standard controls
* Ideas for helpful user interfaces: ToggleButtonGroups and AugmentedButtons

## Some Takeaways
Having worked on projects from fixing small bugs to writing entire components, I've been able to see a good portion of Empirical's web framework.
I'm really excited for where things are going and want to try and want leave things in a good state for the next person to work on this code base.
As such, here are some ideas and principles I've come across or come up with when working on this project.

#### Modularity is King, Specialization is Queen
With the bugs in the `ConfigPanel`, tracking down the root cause was made much trickier by the size of the component.

![The Titanic sinking]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-titanic.png){:style="width: 100%"}
*The bigger they are, the harder they fall*

In the refactor, I created a sub-component called a `ValueBox` and a number of derived classes that added or specialized features (i.e. `ValueDisplay`, `ValueControl`, `NumericValueControl`, etc).
While these components are not much use on their own to an Empirical user, they were instrumental in creating the `ReadoutPanel` and keeping its style and structure aligned with that of the `ConfigPanel`.
Thus, the real power of prefabricated components is __modularity__.
In addition, it was helpful to realize that not only are we making components for end users, but we can also make them for ourselves as developers to make the job easier. Modularity also helps with testing since breaking into smaller components that could be individually tested eliminated redundancies in the `ConfigPanel`'s unit tests.

However, building components out of others isn't enough.
Sometimes we need a souped up version of a component :racing_car:.
However, until recently we didn't have prefab components inheriting from other prefab components, everything was just one step in inheritance above a web component.


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
