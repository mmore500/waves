---
layout: post
title: "Prefabricated Web Tools"
date: 2020-06-03
author: Sara Boyd
---

[Empirical](https://github.com/devosoft/Empirical) is "a library of tools for scientific software development" [^1].
This library can be used to develop web applications.
Since C++ code will be compiled to JavaScript with Emscripten, web tools are a great way to allow developers to design web pages in C++ without needing to learn much HTML and CSS.

# Goals
The goal of this project was to provide an easy way for developers to add an interactive and dynamic configuration panel to their web app.
By allowing the user to change configuration settings we aim to provide a better overall user experience.

- Look at config panel in existing app
    - ![Model of cancer evolution along an oxygen gradient]({{ site.baseurl }}/assets/kayakingCellist/original_config_panel.png)
    - [Live Demo](https://emilydolson.github.io/memic_model/web/memic_model.html)[^2]
    - Features to keep:
        - Slider for numerical input
        - Output updates when slider is changed
    - Features to add:
        - Ability to type numerical input
        - Mobile responsive
        - Add description for each setting

# Revamping the Configuration Panel
The first step in creating the new config panel was to create a mockup.
This provided a handy framework to base our Empirical web tool off of.
The mockup was also useful for sending out polls to ask for feedback and recomendations on design decisions.

- HTML, CSS, JavaScript Mockup
    - ![First Mockup]({{ site.baseurl }}/assets/kayakingCellist/first_mockup.png)
    - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/allSettings.html)
    - Used Bootstrap classes to implement components:
        - Card for each setting category
        - Toggle option for card elements and description box
    - Synchronize inputs to reflect changes in slider value (desktop and mobile) and number input field
- Poll Participants for UI Design Decisions
    - ![Glyph options]({{ site.baseurl }}/assets/kayakingCellist/glyphs.png)
    - Description box collapse glyphs 
        - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/toggle_options.html)
    - Card collapse highlighting
        - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/card_demo.html)
    - Final config panel design
        - _Add live demo (or link)_

# Adding Config Panel to Empirical
Once we had a design we were happy with, the next step was to use existing Empirical web tools to construct the config panel.

- Convert Mockup to a ConfigPanel Prefabricated Component
    - Became familiar with Empirical's web components (Div, Element, Input, ...)
    - Implement form synchronization to with input's callback function
        - Future improvement: Abilbity to sync more than three inputs
    - Create a default CSS for the Config Panel
        - Hosted on Empirical [source/prefab/DefaultConfigPanelSytle.css](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/DefaultConfigPanelStyle.css)
        - Link to HTML files using [jsDelivr CDN](https://www.jsdelivr.com/?docs=gh)
            - `<link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/gh/devosoft/Empirical@prefab/source/prefab/DefaultConfigPanelStyle.css">`
        - Can override style with a local CSS file linked below default CSS

While developing the config panel, it became clear that aspects of the config panel could be resued in other applications for other purposes.
As a result, we broadened our project goals to include developing new prefabricated web tools.
Many of them provide an interface for other libraries such as Bootstrap, FontAwesome, and HighlightJS.

- Breakdown ConfigPanel into reusable components
    - [CommentBox](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/CommentBox.h), [Card](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/Card.h), [Collapse](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/Collapse.h), [FontAwesomeIcon](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/FontAwesomeIcon.h)
    - Design Decisions:
        - Make prefab components a web widget
        - Make prefab components a class similar to ConfigPanel which is composed of web components
            - Instances are created and updated and deleted when they go out of scope
        - Make prefab components inherit from a web component
            - Can use widget methods such as SetAttr and SetCSS
            - Can use the overloaded << operator to stream component into other web components

- Additions to Empirical:
    - Allow user to add multiple attribute values to a web component
        - Before, if you set an attribute using SetAttr twice, the second call would override the value given in the first call
        - Now, you can use AddAttr method to append more values to an attribute
    - Allow user to print special characters (<, >, ", ', &) on screen
        - Before, these characters would render as special HTML characters, not string literals
        - After, replace the special characters with a character entity
        - More detailed explination of special HTML characters [here](https://www.w3schools.com/html/html_symbols.asp)
    
# Testing New Prefabricated Web Tools
Throughout the development process, it was important that any changes we made to Empirical did not jeopardize the library.
To help us out, TravisCI (continuous integration) was already set up, so whenever we pushed to GitHub, our code was tested.

We also wrote our own unit tests with Mocha and Chai to test that our new web tools were layed out in HTML and behaved as expected.
- Testing:
    - Set up a docker image and can run test in the a docker container
    - Karma test runner
    - Mocha for unit testing JavaScript
    - Chai assertion library

# Conclusion
I want to say a huge thanks to my mentor, Matthew Andres Moreno, who has helped me every step of the way.

Congradulations! You made it to the end!
You can see all the new prefabricated tools in action [here](https://devosoft.github.io/empirical-prefab-demo/empirical-prefab-demo).

## Sources
[^1]: [Empirical GitHub](https://github.com/devosoft/Empirical)
[^2]: [Model of cancer evolution along an oxygen gradient](https://emilydolson.github.io/memic_model/web/memic_model.html)