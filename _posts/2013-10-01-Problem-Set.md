---
layout: post
title: "Problem Set"
date: 2013-10-01 16:16:00
categories: Zzz
---

### Problem 2

How many time do we need to toss to estimate the fairness of a coin?

[Estimation of A Biased Coin](https://www.youtube.com/watch?v=2_S9ytglwM4)



### Problem 1

The expectation times of sampling to get a number twice from a discrete uniform distribution $$U(1,n)$$.

$$\begin{eqnarray}
P(X = x | n) &=& \frac{x}{n} \frac{\prod_{i=0}^{x-1} (n-i)}{n^x}, \quad x = 1, 2, \dots, n \\
P(X = x | n) &=& \frac{x}{n} \frac{n-x+1}{x-1} P(x - 1 | n) \\
\end{eqnarray}$$


$$P(X = x)$$ denotes the probability that $$S = \{s_1, ..., s_x\}$$ are distinct numbers, and $$s_{x+1} \in S$$.

### Solution

**Expectation**:

$$\begin{eqnarray}
E_n &=& 0 \\
E_{n-1} &=& \frac{1}{n}(1 + E_n) \\
E_{n-2} &=& \frac{2}{n}(1 + E_{n-1}) \\
E_{i} &=& \frac{n-i}{n}(1 + E_{i+1}) \\
E(X) = E_{0} &=& \frac{n}{n}(1 + E_{1}) \\
\end{eqnarray}$$

$$\begin{eqnarray}
E(X) + 1 &=& \frac{\sum_{i=0}^{n} \frac{n!}{i!}n^i}{n^n} \\
  &=& e^n n^{-n}\Gamma(n+1,n) \\
\end{eqnarray}$$

where

$$\begin{eqnarray}
\Gamma(s,x) &=& \int_x^\infty t^{s-1}e^{-t} dt \\
  &=& (s-1)!e^{-x}\sum_{k=0}^{s-1} \frac{x^k}{k!} \\
\end{eqnarray}$$

**Variance**:

$$\mathrm{Var}(X) = \mathrm{E}(X^2) - (\mathrm{E}X)^2$$

I don't find a good way to calculate it yet.

$$\begin{eqnarray}
\mathrm{E}(10) = 3.660215680,& \quad &\mathrm{Var}(10) = 2.942605496\\
\mathrm{E}(100) = 12.20996063,& \quad &\mathrm{Var}(100) = 38.70690078\\
\mathrm{E}(200) = 17.39844386,& \quad &\mathrm{Var}(200) = 79.89570756\\
\mathrm{E}(10000) = 124.9991219,& \quad &\mathrm{Var}(10000) = 4250.220410\\
\end{eqnarray}$$

$$\begin{eqnarray}
P(X \le 94 | N = 1000) &>& 0.99 \\
P(X \le 302 | N = 10000) &>& 0.99 \\
\end{eqnarray}$$

{% highlight wolfram %}

pr[x_,n_] := x * Product[(n-i), {i, 0, x - 1}] / n^(x+1)

en1[n_] := Sum[i * pr[i, n], {i, 1, n}]

ens1[n_] := Sum[i * i * pr[i, n], {i, 1, n}]


prlist[n_] := NestList[{#[[1]] + 1, (#[[1]] + 1) / n * (n - #[[1]]) / #[[1]] * #[[2]]} &, {1, 1/n}, n - 1]

en2[n_] := Total[Apply[Times, prlist[n], {1}]]

ens2[n_] := Total[Apply[Function[{a,b}, a*a*b], prlist[n], {1}]]


en[n_] := (E/n)^n * Gamma[n+1,n] - 1

varn[n_] := ens2[n] - en[n]^2

N[en[10], 10]

N[en[100], 10]

N[en[200], 10]

N[varn[10], 10]

N[varn[100], 10]

N[varn[200], 10]

cdf[n_,p_] := 
  Catch[
    Fold[
      Function[{s, x}, Print[{x[[1]],N[x[[2]] + s]}];
        If[x[[2]] + s >= p, 
           Throw[x[[1]]], 
           s + x[[2]]]], 
      0, prlist[n]]]
           
cdf[1000, 0.99]
{% endhighlight %}

---

### Problem 0

Sample $$m$$ numbers $$\{x_1, \dots, x_m\}$$ without replacement from $$\{1, \dots, n+m\}$$. Let $$X = x_1 + \dots + x_m$$. Find $$\mathrm{E}(X)$$ and $$\mathrm{Var}(X)$$. 

### Solution

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


