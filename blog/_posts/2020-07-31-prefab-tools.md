---
layout: post
title: "Prefabricated Web Tools"
date: 2020-07-31
author: Sara Boyd
---

Phylogeny, convergent evolution, the genetic code. 
What is this? DNA, genome, fitness function. 
Okay, these are sounding slightly more familiar. 
Pointers, (OOP) inheritance, responsive web design. 
Whew, finally topics that are in my comfort zone.

A neat aspect of working in the Digital Evolution Lab is the wide range of topics that you can explore, from biological evolution to application development tools. 
For me, creating font-end web tools was the most intriguing. 
I’ve worked on web applications before, but I was interested to see how to implement them with [Empirical](https://github.com/devosoft/Empirical), a C++ based “library of tools for scientific software development”[^1].

# Goals
The goal of this project was to provide an easy way for developers to add an interactive and dynamic configuration panel to their web app.
By allowing the user to change configuration settings we aim to provide a better overall user experience.

Before this summer, there was a tool in Empirical that would read through a configuration file abstract data, and create a form to display in a web application. One application using this config panel is Emily Dolson’s [Model of cancer evolution along an oxygen gradient](https://emilydolson.github.io/memic_model/web/memic_model.html)[^2].

![Model of cancer evolution along an oxygen gradient]({{ site.baseurl }}/assets/kayakingCellist/original_config_panel.png)


<table>
  <tr>
    <td><b>Features we like:</b></td>
    <td><b>New Features:</b></td>
  </tr>
  <tr>
    <td>
      <ul>
        <li>Slider for numerical input</li>
        <li>Output updates when slider is changed</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>Ability to type numerical input</li>
        <li>Mobile responsive</li>
        <li>Add description for each setting</li>
      </ul>
    </td>
  </tr>
</table>

# Revamping the Configuration Panel
The first step in creating the new config panel was to create a mockup.
This provided a handy framework to base our Empirical web tool off of.
The mockup was also useful for sending out polls to ask for feedback and recomendations on design decisions.

For the mockup, I set aside Empirical and focused on creating a visually appealing and responsive layout with what I know best, HTML, CSS, and JavaScript. 
Thanks to Bootstrap, this was not too challenging. 

:bulb: **New feature idea:** Show the input slider in a dropdown box on mobile devices so the panel will look less crowded.

Because of the power of GitHub web hosting, I was able to create web pages with multiple design options.
Then, I sent out links to these web pages to get feedback from WAVES other workshop particpiants.
Huge thanks to them! 
These polls helped decide which [glyphs](https://kayakingcellist.github.io/ControlPanelDemo/toggle_options.html) to add to the ConfigPanel and the most intuitive way to indicate that a [Bootstrap card](https://kayakingcellist.github.io/ControlPanelDemo/card_demo.html) is collapsible.

**New Configuration Panel**
![New Configuration Panel]({{ site.baseurl }}/assets/kayakingCellist/new_config_panel.png)


# Adding Config Panel to Empirical
Once we had a design we were happy with, the next step was to recreate it in Empirical. 
Using the existing config panel class as a base, I set out to add the styling from the mockup. 
Luckily, there were already web tools in Empirical to customize and add web elements to the config panel such as Divs and Input types. 

One feature that was tricky to implement was synchronizing the three inputs for a config setting: slider that appears in the desktop version, slider that appears in the mobile version, and the input box to typing the number. 
The key was ensuring the callback function for the changed input “notified” the other inputs of the change. 

:bulb: **New feature idea:** Provide a CSS style guide for the config panel.

Empirical provides functions that allow developers to set CSS styles and classes. 
If I wanted to be a frustrating programmer, I would nest the styling within the ConfigPanel class. 
Then others would have to sift through the class to change a style they don’t like. :smirk:
But, I guess that wouldn’t be very nice ...

Instead, by placing default style settings in a separate CSS file, app developers can simply create their own CSS file that overrides the default styles. 
We use [jsDelivr](https://www.jsdelivr.com/?docs=gh), a content delivery network to provide an easy way to link to our default style guide.

:bulb: **New feature idea:** Breakdown the ConfigPanel into reusable components.

While developing the ConfigPanel, it became clear many features could be reused in other applications for different purposes.
As a result, we broadened our project goals to include developing new prefabricated web tools.
Many of them provide an interface for other libraries such as [Bootstrap](https://getbootstrap.com/), [FontAwesome](https://fontawesome.com/v4.7.0/), and [HighlightJS](https://highlightjs.org/).

In designing and developing these prefab elements, we decided we wanted them to function as similarly to the existing web tools as possible. 
This way, developers who are familiar with web tools can easily use prefab tools too. 
For example, prefab elements can be streamed into other web elements with the `<<` operator and add styling with `SetAttr()` and `SetCSS()`.

# Additions to the Empirial Library

While developing the ConfigPanel and other prefabricated tools, I encountered cases where I found it would have been nice to have some new functionality. 

:heavy_check_mark: Allow the user to add multiple attribute values to a web component

- Before, if you set an attribute using `SetAttr()` twice, the second call would override the value set in the first call.
- Now, you can update an attribute’s value with `AddAttr()` which appends the new value to the existing ones. 
This is handy if you want to add multiple classes to a web element.

:heavy_check_mark: Allow the user to print special characters (&lt; , &gt; , &quot; , &apos; , &amp;) on a web page

- Before, these characters would render as special HTML characters on a web page, not string literals.
- Now, the `to_web_safe_string()` method replaces special HTML characters with a character entity so the symbol will appear as expected.
- More detailed explination of special HTML characters [here](https://www.w3schools.com/html/html_symbols.asp)
    
# Testing New Prefabricated Web Tools
I often hear developers complain about testing. 
It’s too tedious. 
It’s slowing down progress. 
I’m guilty of this too. 
Though, after working on Empirical, I think these statements are true and false. 
Is this even possible?

When I was developing unit tests for the prefab elements, it definitely felt tedious enumerating exactly how the HTML for each element should be laid out. 
I spent the last several weeks of the summer mainly focusing on writing tests. 
At times, it felt frustrating because we had more ideas for new prefab tools, but I couldn’t work on implementing those because I had to write the tests.

On the flip side, as I was writing tests, I realized some major flaws in my code. 
Who knows how long they would have lasted if I had chosen to skip testing. 
Being able to patch up these issues now, counts as progress in my book. 

Additionally, [TravisCI](https://travis-ci.com) (continuous integration) tests were set up for Empirical before I came to the project. 
These tests run automatically when we push new code to GitHub. 
They check that the new code added doesn't break or conflict with the existing code. 
I can imagine the tests took some time to set up. 
However, they have helped me on numerous occasions to quickly identify and locate a bug I unintentionally added to Empirical.

I suppose the benefits of testing are most appreciated in the long term, but they can prove meaningful during the testing process as well. 


# Conclusion
Perhaps the best part of building these prefabricated tools is knowing that this is not the end for the project. 
Since the idea behind prefab tools is that they are built using basic Empirical web tools, there’s really no end to the possible tools that will come in the future. 
A list of some ideas we could think of at the moment are listed in [issue 334](https://github.com/devosoft/Empirical/issues/334).
If the issue has been closed by the time you click the link, hopefully they have been added already.
Yay! :tada: :tada: :tada:

Now that the summer is over, I am sad to leave the program and everyone at MSU. 
I want to say a huge thanks to my mentor, Matthew Andres Moreno, who has helped me every step of the way.

# Prefab Tools Demo
Congradulations! You made it to the end!
You can see all the new prefabricated tools in action [**here**](https://devosoft.github.io/empirical-prefab-demo/empirical-prefab-demo).

## Sources
[^1]: [Empirical GitHub](https://github.com/devosoft/Empirical)
[^2]: [Model of cancer evolution along an oxygen gradient](https://emilydolson.github.io/memic_model/web/memic_model.html)