---
layout: post
title: "Copernican Principle"
date: 2016-02-01 12:50:00
categories: Math
---

# Copernican principle

## Problem

Sampling $$m$$ numbers $$X = \{x_1, \dots, x_m\}$$from a discrete uniform distribution $$U(1,N)$$ where $$N$$ is unknown. Let $$k$$ be the largest number of the $$m$$ samples. The problem is estimating $$N$$.

## Solution under the Copernican principle

### Basic idea

To explain the basic idea, let $$m = 1$$, then $$k = x_1$$. Because $$P(n/4 < k < 3n/4) = 1/2$$, we will get $$P(4k/3 < n < 4k) = 1/2$$. 

An another example, $$P(0 < k < n/2) = 1/2$$, then $$P(n > 2k) = 1/2$$.

### Generalize the idea

The probability of all samples are not greater than $$kn/y$$,

$$P(X \le kn/y) = P(k/y)^m = (k/y)^m = P(k \le kn/y)$$

where $$k$$ is the largest number in $$X$$, and $$y$$ is an arbitrary number greater than $$k$$. Then,

$$P(N \ge y) = (k/y)^m$$

Also, $$P(n = y) = P(n \ge y) - P(n \ge y + 1)$$, then,

$$P(n = y | m, k) = (k/y)^m - (k/(y+1))^m, \quad y \ge k$$

$$\begin{eqnarray}
\mathrm{E}(n | m, k) &=& \sum_{i=k}^{\infty} i((\frac{k}{i})^m - (\frac{k}{i+1})^m) \\
  &=& k^m\zeta(m, k) + k-1 \\
\mathrm{Var}(n | m, k) &=& \mathrm{E}(n^2 | m, k) - \mathrm{E}(n | m, k)^2 \\
  &=& k^2 + 2k^m\zeta(m-1,k+1) - k^m\zeta(m, k+1) - \mathrm{E}(n | m, k)^2
\end{eqnarray}$$

Examples of expectations and variances:

$$\begin{eqnarray}
\mathrm{E}(n | 2, 100) \approx 199.502 &\quad& \mathrm{Var}(n | 2, 100) = \infty \\
\mathrm{E}(n | 3, 100) \approx 149.502 &\quad& \mathrm{Var}(n | 3, 100) \approx 7499.833 \\
\mathrm{E}(n | 6, 100) \approx 119.505 &\quad& \mathrm{Var}(n | 6, 100) \approx 599.883 \\
\mathrm{E}(n | 9, 100) \approx 112.007 &\quad& \mathrm{Var}(n | 9, 100) \approx 200.789 \\
\mathrm{E}(n | 100, 100) \approx 100.592 &\quad& \mathrm{Var}(n | 100, 100) \approx 0.960 \\
\end{eqnarray}$$

The wolfram code to calculate the expectation and the variance.

{% highlight wolfram %}

Function[{m, k}, N[Sum[i((k/i)^m-(k/(i+1))^m), {i, k, Infinity}], 50]][3, 100]
Function[{m, k}, N[k^m * Sum[1/i^m, {i, k, Infinity} + k - 1], 50]][6, 100]
Function[{m, k}, N[k^m * Zeta[m,k] + k - 1, 50]][9, 100]

en1[m_, k_] := Sum[i((k/i)^m-(k/(i+1))^m), {i, k, Infinity}]

ent1[m_, k_] := Sum[(i^2) * ((k/i)^m-(k/(i+1))^m), {i, k, Infinity}]

varn1[m_, k_] := ent1[m,k] - en1[m,k]^2

varn2[m_, k_] := Sum[((i - en[m, k])^2) * ((k/i)^m-(k/(i+1))^m), {i, k, Infinity}]

en[m_, k_] := k^m * Zeta[m, k] + k - 1

ent[m_, k_] := k^2 + k^m * (-Zeta[m, k+1] + 2 * Zeta[m-1, k+1])

varn[m_, k_] := ent[m,k] - en[m,k]^2

N[en[2, 100], 100]
N[en[3, 100], 100]
N[en[6, 100], 100]
N[en[9, 100], 100]

N[varn[2, 100], 100]
N[varn[3, 100], 100]
N[varn[6, 100], 100]
N[varn[9, 100], 100]

{% endhighlight %}





