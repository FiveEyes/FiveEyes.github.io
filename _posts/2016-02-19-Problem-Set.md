---
layout: post
title: "Problem Set"
date: 2016-02-19 16:16:00
categories: Zzz
---

Sample $$m$$ numbers $$\{x_1, \dots, x_m\}$$ without replacement from $$\{1, \dots, n+m\}$$. Let $$X = x_1 + \dots + x_m$$. Find $$\mathrm{E}(X)$$ and $$\mathrm{Var}(X)$$. 

$$\begin{eqnarray}
\mathrm{E}(X) &=& \frac{m}{n} \sum_{i=1}^{n+m} i \\
  &=& m(m+n+1)/2 \\
\mathrm{E}(X^2) &=& \frac{m}{n+m} \sum_{i=1}^{n+m} i^2 + \frac{m(m-1)}{(n+m)(n+m-1)} \sum_{i=1}^{n+m-1}\sum_{j=i+1}^{n+m} 2ij \\
\mathrm{Var}(X) &=& \mathrm{E}(X^2) - (\mathrm{E}(X))^2\\
  &=& nm(n+m+1)/12 \\
\end{eqnarray}$$

{% highlight wolfram %}
en := m/(n+m) * Sum[i, {i,1,n+m}]

ens := m/(n+m) * Sum[i^2, {i, 1, n+m}] + m(m-1)/((m+n)(n+m-1)) * Sum[Sum[2*i*j, {j, i+1, n+m}], {i,1,n+m-1}]

varn := Simplify[ens - en^2]

{% endhighlight %}

---

