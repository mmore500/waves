---
layout: post
title: "More Prefabricated Web Tools!"
date: 2021-08-20
author: Tait Weicht
---

I had no idea that people actually did web development in C++ prior to learning of [Empirical](https://github.com/devosoft/Empirical), a library of tools for developing efficient, reliable, and accessible scientific software.
Thanks to [emscripten](https://emscripten.org/), it _is_ possible turn your C++ into WebAssembly to run quickly in the browser.
With this framework, it becomes simple to compile a C++ command line tool into web application.
Running scientific software on the web has enormous potential to expand reach and engage the public since literally anyone can replicate your results and play with experimental conditions.
However, just because something can run on the web does not make it a _web application_.
Developing a graphical user interface is a lot more work than making a command line interface.

To expedite porting from command line to browser, Empirical provides C++ wrappers for simple components like divs (for <em>div</em>iding up web content), spans (for placing and styling text) and buttons.
To meet more the specific needs of researchers, Empirical also includes higher level components like a configuration panel for managing settings.
Since these components are created and managed in C++ they can provide an graphical user interface to manage the execution of preexisting code.
We call these components "prefabricated web tools" and they use the open source front-end toolkit, [Bootstrap](https://getbootstrap.com/docs/5.1/getting-started/introduction/) to help with styling and user interfaces.
My WAVES predecessor Sarah Boyd developed a large number of components which you can read about [here]({{ site.baseurl }}/blog/prefab-tools.html).
I took up the torch this summer to add to this previous work!

## Goals
My goal this summer was to enhance existing prefabricated components and to create new ones.
In addition, some prefabricated components had issues which needed to be addressed (:bug:) or challenges (:lemon:).
[Empirical issue #334](https://github.com/devosoft/Empirical/issues/334) listed some components to develop and along the way we thought up some more (:bulb:)! [Empirical issue #444](https://github.com/devosoft/Empirical/issues/444) contains the most current list of project ideas for prefab components.

#### "It will be simple," they said, "a button", they said
Thinking it would be a relatively simple thing to start with, I began work adding a reload button to the `ConfigPanel` as one of my first tasks.
Reloading the page allows us to restart the web app with a query string in the URL.
Empirical's `ArgManager` class formats the key-value pairs from the query string so that it can interpret them exactly like it does command line flags.
It should have been easy to just create an hyperlink with the appropriate values plucked from the `ConfigPanel`.

However, this task almost immediately stalled on discovery of a bug!

:bug: __Bug__: In an attempt to make `Config` objects flexible, `std::stringstream` was being used to extract `double`s, `float`s and `int`s from text entered by the user.
This worked fine until you tried it with `std::string`s.
The `std::stringstream` method resulted in only the first word being copied!

:butterfly: __Solution__: Keeping a templated interface was necessary for efficiency and clarity. However, we needed different behavior for a specific type. Luckily since C++17 we have `if constexpr` and type traits. Using
```c++
  if constexpr(std::is_same<MY_TYPE, std::>::value) {
    // do something ...
  }
```
inside a function template, we can do a compile time type check as to whether it should generate the code inside the `if`.
Pretty nifty! Knowing this pattern means that in the future if new types become supported in config files there's already a good example of how to handle their parsing smartly.

However, this was not the only fix necessary.
In a URL query string both `%20` and `+` encode a space character (`' '`) and the HTML5 standard for percent encoding does not differentiate between them.
However, Empirical's `ArgumentManager` class supports multiple values for a key which meant that strings with whitespace were being processes as a sequence of words assigned to a key rather than a single string object.
By assigning `+` the role of a value separator it became possible to have support for keys with multiple values and support whitespace _in_ string values.

So in the end while not a lot changed in the graphical user interface, Empirical now has a more robust argument and configuration management system.
To see the updated component you can find a demo [here](https://devosoft.github.io/empirical-prefab-demo/empirical-prefab-demo.html).

#### How _Card_ could it be?
Digging deeper into the issue list I decided I would try my hand at a problem that was still unsolved: how do we override the default stream operator for a component?
Here the term override is used loosely since in C++ you can only override a [virtual function](https://en.cppreference.com/w/cpp/language/virtual), but our web components use a function template, which cannot be virtual.

:lemon: __Problem__: A number of methods had been tried to get streaming into a `Card` to place components into the `Card`'s body element but all led to the cryptic runtime error `too much recursion`.

:tropical_drink: __Solution__: The root of the problem was that `Card` itself needed sub-components (it has a header div and a body div).
To get these components in place `Card` uses, you guessed it, the stream operator.
So replacing the stream operator for `Card` had the effect that when the constructor tried to add the body div, it tried to put the body div inside _itself_.

![A gif of zooming in on cup with a small table next to it with a cup with a small table next to it with...]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-droste.gif){:style="width: 100%"}
*TOO MUCH RECURSION!!!*

Using `static_cast<Div>(*this)` prevents infinite recursion by using `Div`'s default method of streaming components.

#### The Config Panel Conundrum
The next issue we tackled was a strange bug with the `ConfigPanel`.

:bug: __Bug__: A `ConfigPanel` only works if it is a global object.

This indicated that something was going wrong with our memory management.
The problem was a rather subtle one, while the `ConfigPanel` _was_ a div, it also _had_ a div.
Like Dr. Jekyll and Mr. Hyde caught mid transformation the `ConfigPanel` was caught trying to be two things at once, a class to setup a div (:hammer_and_wrench:) and a div with some extra frills (:ribbon:).
The result was that when time came to add the component to the document object model (DOM), the inner shell member div was properly placed and the outer shell destructed, but the inner shell kept references to the outer.

:exclamation: And since the outer shell didn't exist at that point things were seriously borked. :exclamation:

This state of affairs worked when the component was global because the outer shell existed past the end of `main` so the component could still function.
Once the problem was identified it wasn't to hard to fix its identity crisis.

:butterfly: __Solution__:

To align its behavior with other components, I eliminated the internal div and made sure users have to stream the entire component into the document.
I also made sure that lambda expressions capture by  value any components they need to keep around.
Since Empirical web components are really just interfaces around a protected shared pointer this keeps access to the shared pointer with little overhead and prevents dangling references inside the lambda which can occur when capturing by reference.
In addition, the alterations provided the opportunity to break the component into some smaller reusable pieces.

![A "refactor all the things" meme]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-refactor.png){:style="width: 100%"}
*I had to be a little careful not get too carried away*

I also wrote a reload button that refreshes the page and injects any settings the user has supplied through the config panel.
This allows the user to easily restart an application, much like rerunning a program on the command-line.
An added bonus is that you can then copy and distribute the URL which will contain your simulation settings.
This of course has lead to more ideas for config panel buttons/features.

:bulb: __Save button__: a button to save configuration settings as a `.cfg` file.

:bulb: __Clipboard button__: a button to copy the URL to this simulation w/ settings to the clipboard.

:bulb: __Apply settings__: a way to initiate file selection for a `.cfg` file with settings to load.

All the ideas for prefab components which we didn't have time to develop can be found in [Empirical issue 444](https://github.com/devosoft/Empirical/issues/444) on GitHub!

#### ReadoutPanel: Live Variables in the Limelight
As a counterpart to the configuration panel, Matthew suggested making a component that could display values live from a simulation.
While Empirical has a graphical visualization component using [D3](https://d3js.org/), this component would serve the need for a lightweight display for simulation statistics.

![Gollum eating a fish]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-raw.png){:style="width: 50%"}
*If you like your numbers like Gollum likes his fish, the `ReadoutPanel` might be for you*

Here's its bio:
* Inheriting from the collapsible `Card` prefab component, the Readout Panel provides a simple way to animate a collection of live values.
* A user can specify a refresh rate for live values in the panel.
* The readout panel will attempt to update without choking execution; it will gracefully skip redraws if getting the values is taking longer than the refresh rate.
* A close cousin in style and spirit to the `ConfigPanel` by reusing components developed in the `ConfigPanel` refactor.

Along the way I also added a variadic method for adding values to the panel.
However, this required that I pass on [r-value references](https://en.cppreference.com/w/cpp/language/reference) correctly to all the way to a `Live` wrapper which required perfect forwarding.
The syntax for this is rather wild so for anyone curious about where the ellipses go, here's an example:
```cpp
OuterFunc(VALUE_TYPES && ... others) {
  InnerFunc(std::forward<VALUE_TYPES>(others)...);
}
```
The ellipses (`...`) in the inner function indicates a parameter pack expansion which allows the `forward` function to be applied to each argument individually. Pretty nifty stuff!

## Some Takeaways
Having worked on projects from fixing small bugs to writing entire components, I've been able to see a good portion of Empirical's web framework.
I'm really excited for where things are going and want to leave things in a good state for the next person to work on this code base.
As such, here are some ideas and principles I've come across or come up with when working on this project.

#### Modularity is King, Specialization is Queen
The real power of prefabricated components is __modularity__.
Empirical's web tools become exponentially more versatile as new components are added since there become more and more ways of combining lower level components into higher level ones.
When refactoring and debugging the `ConfigPanel`, the large size of the component made tracking down the root cause much trickier.

![The Titanic sinking]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-titanic.png){:style="width: 100%"}
*The bigger they are, the harder they fall*

In the refactor, I created a sub-component called a `ValueBox` and a number of derived classes that added or specialized features (i.e. `ValueDisplay`, `ValueControl`, `NumericValueControl`, etc).
While these components are not much use on their own to an Empirical user, they were instrumental in creating the `ReadoutPanel` and keeping its style and structure aligned with that of the `ConfigPanel`.

In addition, it was helpful to realize that not only are we making components for end users, but we can also make them for ourselves as developers to make the job easier.
Modularity also helps with testing since breaking into smaller components that could be individually tested eliminated redundancies in the `ConfigPanel`'s unit tests.

However, building components out of others isn't enough because sometimes we just need a souped up version of a component (:racing_car:) with new features that we can't get by just adding other components (:car:).
However, until recently we didn't have prefab components inheriting from other prefab components; everything was just one step in inheritance above a simple web component.
The `ReadoutPanel`'s development was complicated by being derived from `Card`, another prefab component.

Empirical web components are really just interfaces around a protected shared pointer `info` that holds all the information about that component.
When components are streamed into the global `Document` instance, they are registered which will keep the `info` pointer from being destructed.
To keep the "on toggle" function around and modifiable it need to be on the `info` member, a shared pointer that holds information about the a `Card` instance.
This required that I make a custom class `CardInfo` derived from `DivInfo`.
The `ReadoutPanel` also needed to have its own custom members with an "on toggle" function and a list of divs to refresh.

However, there was no clear way to attach both these properties to the panel without wiping out the existing `Card` structure as a side effect (and also possibly creating memory leaks).
To fix the problem, we had to come up with a model for inheritance and construction when you've got an interface wrapped around a shared pointer.
At its core the ideas is that every web component has a protected constructor accepting a raw `info` pointer and which may call a [derived constructor](https://en.cppreference.com/w/cpp/language/derived_class) if it is inheriting from another component.
Public interfaces use [delegated construction](https://en.cppreference.com/w/cpp/language/constructor) to tap into this protected pipeline with the correct type of pointer.
Using delegation prevents users from having to manage pointers explicitly.

![A model for construction and inheritance]({{ site.baseurl }}/assets/lemniscate8/more-prefab-tools-pipeline.png){:style="width: 100%"}

Since this is an important issue and likely to come up again in the future I created a README for the prefab components and documented the method I used [here](https://github.com/devosoft/Empirical/tree/master/include/emp/prefab#inheritance).

This solution is effective, but there are still some flaws.
While it works for the current set of prefabricated tools, it's somewhat unwieldy to force all construction to be delegated to a single protected constructor.
Making components that are modular and support inheritance is necessary to prevent code duplication but a hard problem.
My solution will likely work in the short term, but I'm hoping whoever inherits this code will give it a good think too in case there's a better way.

#### You know... there's CSS for that
One of the projects I didn't get to this summer was adding something like a layout manager to the prefab project.
However, when I tried out ideas for a model, it became clear that CSS already has excellent methods for laying out components using [flexboxes](https://css-tricks.com/snippets/css/a-guide-to-flexbox/) and [grids](https://css-tricks.com/snippets/css/complete-guide-grid/).
Rather than creating a whole new prefab component, Empirical could simply provide some artfully crafted classes in the [default prefab styles](https://github.com/devosoft/Empirical/blob/master/include/emp/prefab/DefaultPrefabStyles.less) that users could place on their own divs.
In a similar way, `@media` queries are a great way to make dramatic changes a page's main layout or hide/show components without the costs of altering component hierarchies programmatically.
In the end I've been pleasantly surprised with how many tricky programing problems can be avoided via artful CSS.

:bulb: __Layout classes__: make some CSS classes for standard responsive layouts.

:bulb: __Grid guides__: make Bootstrap's grid classes more accessible through some [sort of interface](https://github.com/devosoft/Empirical/issues/441).

## Thoughts on the Future
Several challenges exist on the horizon for Empirical's prefabricated web tools.

First, upgrading Bootstrap from v4 to v5 seems to break styling for a few components.
This is unfortunate since Bootstrap v5 levelizes button and input groups, making them easier to construct and adds new components such as [offcanvas](https://getbootstrap.com/docs/5.1/components/offcanvas/) which is a fantastic place to put items when there is limited space on the page (i.e. on a mobile device).

Second, there are plans to build the next version of Avida-ED with some of these prefabricated web tools.
The web components are based on Bootstrap, which is developed with mobile-first responsive design philosophy, where as Avida-ED has traditionally had desktop application look-and-feel.
Since nowadays the majority of people expect a web page to function on their mobile device and we are already using Bootstrap, it would be valuable to consider what opportunities might be afforded by developing future tools with mobile viewport in mind.
In addition, a modernized style would likely be appealing to younger generations which would benefit outreach using the next generation of Avida-ED.

## Acknowledgements
I'd like to thank my mentor, Matthew Andres Moreno, for his support and guidance on this project.
He's also done a great job leading the whole program!
:clap: :clap: :clap:

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563).
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.
