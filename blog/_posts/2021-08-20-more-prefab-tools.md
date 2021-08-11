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
Pretty nifty! Knowing this pattern means that in the future if new types become supported in config files there's already a good example of how to handle their parsing smartly.

While fixing this problem it was also necessary to normalized the way config parameters are passed through a URL.
In a URL query string both `%20` and `+` encode a space character (`' '`) and the standard does not differentiate between them.
However, Empirical's `ArgumentManager` class supports multiple values for a key.
By assigning `+` the role of a value separator it became possible to have support for keys with multiple values and support whitespace _in_ string values.

#### How _Card_ could it be?
Digging deeper into the issue list I decided I would try my hand at a problem that was still unsolved: how do we override the default stream operator for a component?
Here the term override is used loosely since in C++ you can only override a virtual function, but our web components use a function template, which cannot be virtual.

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
*I had to be a little careful not get too carried away*

#### ReadoutPanel: Live Variables in the Limelight
As a counterpart to the configuration panel, Matthew suggested making a component that could display values live from a simulation.
While Empirical has a visualization component using [D3](https://d3js.org/), this component would serve the need for a lighter style of display for simulation statistics.

Here's its bio:
* Inheriting from the collapsible `Card` prefab component, the Readout Panel provides a simple way to animate a collection of live values.
* A user can specify a refresh rate the panel will attempt to update at without choking execution.
* A close cousin in style and spirit to the `ConfigPanel` by reusing components developed in the `ConfigPanel` refactor.

Along the way I also added a variadic method for adding values to the panel.
However, this required that I pass on r-value references correctly to all the way to a `Live` wrapper which required perfect forwarding.
The syntax for this is rather wild so for anyone curious about where the ellipses go, here's an example:
```cpp
OuterFunc(VALUE_TYPES && ... others) {
  InnerFunc(std::forward<VALUE_TYPES>(others)...);
}
```
The `...` is one component of a parameter pack expansion which allows the `forward` function to be applied to each argument individually. Again, pretty nifty stuff!

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
However, until recently we didn't have prefab components inheriting from other prefab components, everything was just one step in inheritance above a simple web component.
The ReadoutPanel's development was complicated by being the prefab component to be derived from another prefab component.
When I modified the `Card` class, I include an "on toggle" handler.
To keep this function around and modifiable it need to be on the `info` member, a shared pointer that holds information about the a `Card` instance.
This required that I make a custom class `CardInfo` that inherited from `DivInfo`.
However, when the `ReadoutPanel` needed to have its own custom members with an "on toggle" function and a list of divs to refresh.
However, there was no clear way to get both these properties attached to the panel without wiping out the existing `Card` structure as a side effect (and also possibly creating memory leaks).
We solved this problem and [here](https://github.com/devosoft/Empirical/tree/master/include/emp/prefab#inheritance) you can see a more detailed explanation of the problem and proposed pattern for inheritance for prefab components to fix it.

While this solution is nice, there are still some flaws since its somewhat unwieldy and unnatural to force all construction to be delegated to a single protected constructor, though it works for a number of the cases we have now.
Having components be both modular and allowing derived classes to inherit properly is necessary to prevent code duplication but a hard problem.
My solution will likely work in the short term, but I'm hoping whoever inherits this code will give it a good think too in case there's a better way.

#### You know... there's CSS for that
One of the projects I didn't get to this summer was adding something like a layout manager to the prefab project.
However, when I tried out ideas for a model, it became clear that CSS already has excellent methods for laying out components using [flexboxes](https://css-tricks.com/snippets/css/a-guide-to-flexbox/) and [grids](https://css-tricks.com/snippets/css/complete-guide-grid/).
Rather than creating a whole new prefab component, Empirical could simply provide some artfully crafted classes in the [default prefab styles](https://github.com/devosoft/Empirical/blob/master/include/emp/prefab/DefaultPrefabStyles.less) that users could place on their own divs.
In a similar way, `@media` queries are a great way to change layouts or hide/show components without the costs of altering component hierarchies programmatically, though are really most effective for overarching layout alternations.
In the end I've been pleasantly surprised with how many tricky programing problems can be avoided via artful CSS.


## Thoughts on the Future
Several challenges exist on the horizon for Empirical's prefabricated web tools.
First, upgrading past Bootstrap v4 to v5 seems to break a styling for a few components.
This is unfortunate since Bootstrap v5 has a lot of new components which could be very useful!
Second, there are plans to build the next version of Avida with some of these prefabricated web tools.
However, the web components are based on Bootstrap which is developed with mobile-first responsive design philosophy where as Avida has traditionally had desktop application look-and-feel.

## Acknowledgements
This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563).
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

I'd also like to thank my mentor, Matthew Andres Moreno, for his support and guidance on this project.
