---
layout: post
title: "Quick Notes"
date: 2016-02-17 15:24:00
categories: Zzz
---

# Quick Notes

The expectation times of sampling to get a number twice from a discrete uniform distribution $$U(1,n)$$.

$$\begin{eqnarray}
E_n &=& 0 \\
E_{n-1} &=& \frac{1}{n}(1 + E_n) \\
E_{n-2} &=& \frac{2}{n}(1 + E_{n-1}) \\
E_{i} &=& \frac{n-i}{n}(1 + E_{i+1}) \\
E_{0} &=& \frac{n}{n}(1 + E_{1}) \\
\end{eqnarray}$$

$$\begin{eqnarray}
E_0 + 1 &=& \frac{\sum_{i=0}^{n} \frac{n!}{(n-i)!}n^{n-i}}{n^n} \\
  &=& e^n n^{-n}\Gamma(n+1,n)
\end{eqnarray}$$

{% highlight wolfram %}

Function[{n}, (e/n)^n * Gamma[n+1,n]][100]

{% endhighlight %}




