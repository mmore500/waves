---
layout: default
---

# Workshop Blog

<ul class="posts">
  {% for post in site.categories.blog %}
    <li>{{post.author}} » <a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>
