---
layout: post
title: "Control Panel"
date: 2020-06-23
author: Sara Boyd
---
## Progress
- Look at config panel in existing app
    - ![Model of cancer evolution along an oxygen gradient]({{ site.baseurl }}/assets/kayakingCellist/original_config_panel.png)
    - [Live Demo](https://emilydolson.github.io/memic_model/web/memic_model.html)
    - Features to keep:
        - Slider for numerical input
        - Output updates when slider is changed
    - Features to add:
        - Ability to type numerical input
        - Mobile responsive
        - Add description for each setting

- HTML, CSS, JavaScript Mockup
    - ![First Mockup]({{ site.baseurl }}/assets/kayakingCellist/first_mockup.png)
    - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/allSettings.html)
    - Used Bootstrap classes to implement components:
        - Card for each setting category
        - Toggle option for card elements and description box
    - Synchronize inputs to reflect changes in slider value (desktop and mobile) and number input field

- Convert Mockup to a ConfigPanel Prefabricated Component
    - Became familiar with Empirical's web components (Div, Element, Input, ...)
    - Implement form synchronization to with input's callback function
        - Future improvement: Abilbity to sync more than three inputs
    - Create a default CSS for the Config Panel
        - Hosted on Empirical [source/prefab/DefaultConfigPanelSytle.css](https://github.com/devosoft/Empirical/blob/prefab/source/prefab/DefaultConfigPanelStyle.css)
        - Link to HTML files using [jsDelivr CDN](https://www.jsdelivr.com/?docs=gh)
            - `<link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/gh/devosoft/Empirical@prefab/source/prefab/DefaultConfigPanelStyle.css">`
        - Can override style with a local CSS file linked below default CSS
    
- Poll Participants for UI Design Decisions
    - ![Glyph options]({{ site.baseurl }}/assets/kayakingCellist/glyphs.png)
    - Description box collapse glyphs 
        - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/toggle_options.html)
    - Card collapse highlighting
        - [Live Demo](https://kayakingcellist.github.io/ControlPanelDemo/card_demo.html)
    - Card header btn vs btn-link
        - _Add live demo_

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
    - Allow user to add multiple classes to a web component
        - Before, if you set the class using SetAttr twice, the second call would override the class given in the first call
        - Now, you can use AddClass method to append more classes to previoulsy defined classes
    
- Bugs found:
    - When using the prefab comment box, I found that the order that it is streamed into the document affects the value update function for Inputs. [Issue here](https://github.com/devosoft/Empirical/issues/307)