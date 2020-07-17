---
layout: default
---

<div>
{% for post in site.categories.tutorials reversed %}
  {% capture href %}{{ site.baseurl }}{{ post.url }}{% endcapture %}
    <div class="lessons_list">
      {% increment counter %}. » <a href="{{ href }}">{{ post.title }}</a>
    </div>
  <ul style="list-style-type:none; margin-bottom:0;">
  <li>
  {% include toc.html baseurl=href html=post.content %}
  </li>
  </ul>
{% endfor %}
</div>
