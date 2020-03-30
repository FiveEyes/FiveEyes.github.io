---
layout: post
title: "Metropolis-Hastings Algorithm"
date: 2020-03-30 02:48:00
categories: Math, Statistics
---

# Metropolis-Hastings Algorithm

[https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm](https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm)

已知一个连续pdf, $P(x)$, 如何从中取样?

最直接的方法是求出cdf, $F(x)$, 然后使用$F^{-1}(U)$来取样, U是一个取自$Unifrom(0,1)$的随机变量.

如果cdf不太好求,一种方式是通过rejection sampling来在pdf上直接取样,这种方法可能出现的问题是拒绝率太高,导致取样速度很慢.

Metropolis algorithm是使用Markov Chain Monte Carlo(MCMC)想法来取样.取样速度很快,但也有他自身的问题:
  - 需要一个burn-in的预热过程.
  - 连续样本直接是相互依赖的,仅保证最终sample set是符合目标分布的.

Metropolis把pdf的support set想象成随机过程中的状态集,$P(x)$就是每个状态被访问的概率,那么状态转移概率为$P(x_{i+1}|x_i)$.

如果我们已经知道了$P(x_{i+1}|x_i)$,那么可以很容易的使用使用MCMC来取样$P(x)$.

```
Initialize $x_0$
For $i = 1, \dots, n$
  $x_i \sim P(x_{i} | x_{i-1})$
```

构造$P(x'|x)$只需要满足以下条件的:

$$
\frac{P(x'|x)}{P(x|x')} = \frac{P(x')}{P(x)}
$$

假设我们可从分布$g(x'|x)$中取样,那么我们添加转移成功率$A(x', x)$来修正$g(x'|x)$.

$$
P(x'|x) = g(x'|x) A(x',x)
$$

那么，

$$
\frac{A(x',x)}{A(x,x')} = \frac{P(x')}{P(x)} \frac{g(x|x')}{g(x'|x)}
$$

现在我们构造$A(x',x)$, Metropolis的方式是,让大的那个等于1, $\max(A(x',x),A(x,x'))= 1$.

最后得到

$$
A(x',x) = \min(1,\frac{A(x',x)}{A(x,x')} = \frac{P(x')}{P(x)} \frac{g(x|x')}{g(x'|x)})
$$

算法:

```
Initialize $x_0$
For $i = 1, \dots, n$
  $x_i \sim g(x_i|x_{i-1})$
  $p_i = \min(1,\frac{P(x')}{P(x)} \frac{g(x|x')}{g(x'|x)})$
  $u_i \sim Uniform(0,1)$
  If $u_i > p_i$
    $x_i = x_{i-1}$
```

如果我们取g(x'|x)为以x为均值的正态分布, 即$g(x'|x) = Normal(x,1)$, 那么$g(x'|x) = g(x|x')$, 得到

$$
x_i \sim Normal(x,1) \\
p_i = \min(1,\frac{P(x')}{P(x)})$
$$
