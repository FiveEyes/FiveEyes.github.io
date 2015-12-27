---
layout: post
title: "Learning Asymptote"
date: 2015-11-30 00:44:00 -0800
categories: Tech
---

# Asymptote: the Vector Graphics Language

Just learning Asymptote, there is an example from the offical tutorial.

![Asy example]({{ site.url }}/assets/img/asy_example.jpg)

{% highlight cpp %}
size(4cm, 0);
pen colour1 = red;
pen colour2 = green;

pair z0 = (0,0);
pair z1 = (-1,0);
pair z2 = (1,0);

real r = 1.5;

path c1 = circle(z1,r);
path c2 = circle(z2,r);

fill(c1, colour1);
fill(c2, colour2);

picture intersection = new picture;
fill(intersection, c1, colour1+colour2);
clip(intersection, c2);

add(intersection);

draw(c1);
draw(c2);

label("$A$", z1);
label("$B$", z2);

pair z = (0, -2);
real m = 3;
margin BigMargin = Margin(0, m*dot(unit(z1-z),unit(z0-z)));

draw(Label("$A\cap B$",0),conj(z)--z0,Arrow,BigMargin);
draw(Label("$A\cup B$",0),z--z0,Arrow,BigMargin);
draw(z--z1,Arrow,Margin(0,m));
draw(z--z2,Arrow,Margin(0,m));

shipout(bbox(0.25cm));
{% endhighlight %}
