---
layout: default
title: People
description: Workshop folks
---

{% assign mentors = site.data.people | where:'role', 'mentor' | sort: "nick" %}
{% assign participants = site.data.people | where:'role', 'participant' | sort: "nick" %}
{% assign friends = site.data.people | where:'role', 'other'  | sort: "nick" %}
{% assign shuffle = site.data.people | sample: 100 %}


<div style="display: flex; justify-content: center; flex-wrap: wrap; width: 100vw; margin-left: -50vw; left: 50%; position: relative;">
{% for person in shuffle %}

  <div class="img-holder">
    <a href="#{{ person.github | replace: "-", "_" }}">
      <img
        src="{{ site.baseurl }}/assets/headshots/square-{{ person.github }}.png"
        alt="{{ person.first }} {{ person.last }}"
      >
    </a>
  </div>
{% endfor %}
</div>

# Participants

![clouds]({{ site.baseurl }}/assets/gifcities-clouds.gif){:style="width:100%;"}

{% for person in participants %}

  {% include person.html %}

{% endfor %}

# Mentors

![twisting]({{ site.baseurl }}/assets/gifcities-twist.gif){:style="width:100%;"}

{% for person in mentors %}

  {% include person.html %}

{% endfor %}

# Friends

![sheep]({{ site.baseurl }}/assets/gifcities-sheep.gif){:style="width:100%;"}

{% for person in friends %}

  {% include person.html %}

{% endfor %}
