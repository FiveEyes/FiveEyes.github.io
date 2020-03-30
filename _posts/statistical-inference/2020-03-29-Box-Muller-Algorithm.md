---
layout: post
title: "Box-Muller Algorithm"
date: 2020-03-29 05:28:00
categories: Math
---

# Box-Muller Algorithm

以前想过的一个很有意思的问题,如何从均匀分布生成正态分布.

## Description

$x_1$ and $x_2$ are two independent $uniform(0,1)$ random variables, and let

$$
r = \sqrt{-2 \log{x_1}}, \quad \theta = 2 \pi x_2
$$

Then

$$
z_1 = r \cos{\theta}, \quad z_2 = r \sin{\theta}
$$

are independent $normal(0,1)$ random variabls.

## Proof

首先,

$$
p(z_1,z_2) = \frac{1}{2\pi} e^{\frac{-(z_1^2 + z_2^2)}{2}}
$$

代入$r,\theta$得到

$$
f(r,\theta) = \frac{1}{2\pi} e^{\frac{-r^2}{2}}
$$

这里可以看到$f(r,\theta)$的取值只和$r$有关,所以对于相同的$r=R$,$\theta$的取值的概率相同,所以可知

$$
\theta = 2 \pi x_2.
$$

接下来我们求出$r$的pdf,$p(r)$和cdf,$F(r)$,然后用$F^{-1}(1-x_1)$来得到$r$.

对$\theta$求积分

$$
\int \int p(z_1,z_2) dz_1 dz_2 = \int \int rf(r,\theta) dr d\theta
$$

得到$r$的概率密度函数

$$
p(r) = r e^{\frac{-r^2}{2}}
$$

然后得到$r$的累积分布函数

$$
F(r) = 1 - e^{\frac{-r^2}{2}}
$$

同时

$$
F^{-1}(y) = \sqrt{-2\log(1-y)}
$$

因为$F^{-1}(1-U)$就可以把均匀分布变量转化为目标分布,得到

$$
r = \sqrt{-2\log(x_1)}
$$

## Polar form

原始的方法需要计算$sin(\theta)$和$cos(\theta)$, Polar form的改进可以直接取样出$sin(\theta)$,$cos(\theta)$.

方法: 在单位圆里均匀取样一个点$(x,y)$, 可得

$$
s = x^2 + y^2, sin(\theta) = y/\sqrt{s}, cos(\theta) = x/\sqrt{s}
$$

很容易验证,$r$符合均匀分布,最终我们得到

$$
r = \sqrt{-2 \log{s}} \\ z_1 = r y/\sqrt{s} \\ \quad z_2 = r x/\sqrt{s}
$$

如何在单位圆内均匀取样? Rejection sampling

```
do
  $x,y \sim U(0,1)$
while $x^2 + y^2 > 1$
```


