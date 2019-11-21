---
layout: default
title: Discussion Materials
description: Class discussion materials
---

{% for post in site.categories.discussion reversed %}
# [{{ post.title }}]({{ site.baseurl }}{{ post.url }})
{{ post.content }}
{% endfor %}
