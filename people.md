---
layout: default
title: People
description: Workshop folks
---

{% assign mentors2021 = site.data.people | where:'role', 'mentor' | where:'year', '2021' | sort: "nick" %}
{% assign participants2021 = site.data.people | where:'role', 'participant' | where:'year', '2021' | sort: "nick" %}
{% assign friends2021 = site.data.people | where:'role', 'other' | where:'year', '2021' | sort: "nick" %}

{% assign mentors2020 = site.data.people | where:'role', 'mentor' | where:'year', '2020' | sort: "nick" %}
{% assign participants2020 = site.data.people | where:'role', 'participant' | where:'year', '2020' | sort: "nick" %}
{% assign friends2020 = site.data.people | where:'role', 'other' | where:'year', '2020' | sort: "nick" %}

{% assign shuffled_grouped = site.data.people | reverse | group_by:"github" | sample: 100 %}


<div style="display: flex; justify-content: center; flex-wrap: wrap; width: 100vw; margin-left: -50vw; left: 50%; position: relative;">
{% for by_github_username in shuffled_grouped %}
  {% assign person = by_github_username.items | first %}

  <div class="img-holder">
    <a href="#{{ person.github | replace: "-", "_" }}{{ person.year }}">
      <img
        src="{{ site.baseurl }}/assets/headshots/square-{{ person.github }}.png"
        alt="{{ person.first }} {{ person.last }}"
      >
    </a>
  </div>
{% endfor %}
</div>

# Participants 2021

![clouds]({{ site.baseurl }}/assets/gifcities-clouds.gif){:style="width:100%;"}

{% for person in participants2021 %}

  {% include person.html %}

{% endfor %}

# Mentors 2021

![twisting]({{ site.baseurl }}/assets/gifcities-twist.gif){:style="width:100%;"}

{% for person in mentors2021 %}

  {% include person.html %}

{% endfor %}

# Friends 2021

![sheep]({{ site.baseurl }}/assets/gifcities-sheep.gif){:style="width:100%;"}

{% for person in friends2021 %}

  {% include person.html %}

{% endfor %}

# Participants 2020

![clouds]({{ site.baseurl }}/assets/gifcities-clouds.gif){:style="width:100%;"}

{% for person in participants2020 %}

  {% include person.html %}

{% endfor %}

# Mentors 2020

![twisting]({{ site.baseurl }}/assets/gifcities-twist.gif){:style="width:100%;"}

{% for person in mentors2020 %}

  {% include person.html %}

{% endfor %}

# Friends 2020

![sheep]({{ site.baseurl }}/assets/gifcities-sheep.gif){:style="width:100%;"}

{% for person in friends2020 %}

  {% include person.html %}

{% endfor %}
