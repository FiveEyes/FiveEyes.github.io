---
layout: post
title: "Copernican Principle"
date: 2016-02-01 12:50:00
categories: Math
---

# Copernican principle

## Problem

Sampling $$m$$ numbers $$X = \{x_1, \dots, x_m\}$$from a discrete $$Uniform(1,N)$$ where $$N$$ is unknown. Let $$k$$ be the largest number of the $$m$$ samples. The problem is estimating $$N$$.

## Solution under the Copernican principle

### Basic idea

To explain the basic idea, let $$m = 1$$, then $$k = x_1$$. Because $$P(n/4 < k < 3n/4) = 1/2$$, Then we will get $$P(4k/3 < n < 4k) = 1/2$$. The another example, $$P(0 < k < n/2) = 1/2$$, then $$P(n > 2k) = 1/2$$.

### Generalize the idea

The probability of all $$m$$ numbers are not greater than $$kn/y$$, 

$$P(X \le kn/y) = P(k/y)^m = (k/y)^m = P(k \le kn/y)$$

Then,

$$P(N \ge y) = (k/y)^m$$

Also, $$P(n = y) = P(n \ge y) - P(n \ge y + 1)$$, then,

$$P(n = y | m, k) = (k/y)^m - (k/(y+1))^m, \quad y \ge k$$

$$\begin{eqnarray}
\mathrm{E}(n | m, k) &=& \sum_{i=k}^{\infty} i((\frac{k}{i})^m - (\frac{k}{i+1})^m) \\
 &=& k^m\zeta(m) - \sum_{i=1}^{k-1} (\frac{k}{i})^m + k-1
\end{eqnarray}$$

$$\mathrm{E}(n | 2, 100) \approx 199.502$$

$$\mathrm{E}(n | 3, 100) \approx 149.502$$

$$\mathrm{E}(n | 6, 100) \approx 119.505$$

$$\mathrm{E}(n | 9, 100) \approx 112.007$$

{% highlight wolfram %}

Function[{m, k}, N[Sum[i((k/i)^m-(k/(i+1))^m), {i, k, Infinity}], 50]][3, 100]
Function[{m, k}, N[k^m * Sum[1/i^m, {i, k, Infinity} + k - 1], 50]][6, 100]
Function[{m, k}, N[k^m * Zeta[m,k] + k - 1, 50]][9, 100]

en := Function[{m, k}, k^m * Zeta[m, k] + k - 1]

ent[m_, k_] := Sum[(i^2) * ((k/i)^m-(k/(i+1))^m), {i, k, Infinity}]

varn[m_, k_] := Sum[((i - en[m, k])^2) * ((k/i)^m-(k/(i+1))^m), {i, k, Infinity}]

varn1[m_, k_] := ent[m,k] - en[m,k]^2

varn2[m_, k_] := k^2 + k^m * (-Zeta[m, k+1] + 2 * Zeta[m-1, k+1]) - en[m,k]^2

{% endhighlight %}





