---
layout: default
title: People
description: Workshop folks
---

<style>
.img-holder {
  width: 20%;
  position: relative;
  min-width:100px;
  max-width:150px;
  padding: 10px;
}
.img-holder img {
  top: 0;
  left: 0;
}
</style>

{% assign mentors = site.data.people | where:'role', 'mentor' | sort: "nick" %}
{% assign participants = site.data.people | where:'role', 'participant' | sort: "nick" %}
{% assign friends = site.data.people | where:'role', 'other'  | sort: "nick" %}
{% assign shuffle = site.data.people | sample: 100 %}


<div style="display: flex; justify-content: center; flex-wrap: wrap; width: 100vw; margin-left: -50vw; left: 50%; position: relative;">
{% for person in shuffle %}

  <div class="img-holder">
    <a href="#{{person.github}}">
      <img src="{{ site.baseurl }}/assets/headshots/square-{{ person.github }}.png">
    </a>
  </div>
{% endfor %}
</div>

# Participants

![clouds]({{ site.baseurl }}/assets/gifcities-clouds.gif){:width="100%"}

{% for person in participants %}

  {% include person.html %}

{% endfor %}

# Mentors

![twisting]({{ site.baseurl }}/assets/gifcities-twist.gif){:width="100%"}

{% for person in mentors %}

  {% include person.html %}

{% endfor %}

# Friends

![sheep]({{ site.baseurl }}/assets/gifcities-sheep.gif){:width="100%"}

{% for person in friends %}

  {% include person.html %}

{% endfor %}
