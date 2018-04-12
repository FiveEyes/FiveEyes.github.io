---
layout: post
title: "FractalNet"
date: 2018-04-11 21:13:00
categories: Learning
---

# FractalNet: Ultra-Deep Neural Networks without Residuals

## Fractal architrecture

[https://arxiv.org/abs/1605.07648](https://arxiv.org/abs/1605.07648)

$$
f_1(z) = conv(z) \\
f_{C+1}(z) = [(f_C \circ f_C)(z)] \oplus [conv(z)]
$$

$\oplus$ can be concatenation and addition.

![Overview]({{ site.url }}/assets/img/FractalNet-overview.png)

## Drop-path

![Drop-path]({{ site.url }}/assets/img/FractalNet-droppath.png)
