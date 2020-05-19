---
layout: default
---

<ol class="posts" start="0">
  {% for post in site.categories.tutorials reversed %}
    {% capture href %}{{ site.baseurl }}{{ post.url }}{% endcapture %}
      <li class="lessons_list"> » <a href="{{ href }}">{{ post.title }}</a></li>
    <div>
    {% include toc.html baseurl=href html=post.content %}
    </div>
  {% endfor %}
</ol>
