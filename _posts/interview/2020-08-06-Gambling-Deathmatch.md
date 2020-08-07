---
layout: post
title: "投币 X 死斗"
date: 2020-08-06 22:50:00
categories: Interview
---

# 投币 X 死斗

很多涉及到概率和状态的题目,可以抽象成Markov Chain模型,问题一般是求某个状态的期望值.比如赌博中当前状态的胜率.
  - 可以通过设未知量解方程,来求出所有状态的期望值,也就是整个系统的平衡态.
  - 也可以随机初始化,然后反复迭代趋近平衡态.
  - 最后还可以蒙特卡罗模拟,也就是知名的MCMC.

## St. Petersburg Lottery

先放一道自己不会做的题目祭天: [St. Petersburg Lottery](https://projecteuler.net/problem=499)

这个题目的难点在于状态的数目是无限的,而三种方法都会失效... 先不说这道题目,等有空再展开,有兴趣点链接读一下...

顺便一提,Project Euler上面题目难度从1-100,这道题目好像是难度100...

## 投币 X 死斗

### 题目描述

两人A和B,分别有X和Y元,两人对赌,每局赌1块钱,一直赌到其中一方清零为止,已知A每局的胜率固定是P,问A最终获胜的概率是多少?

### 题解

假设A现在持有i元,把每局游戏有P的概率转移到i+1, (1-P)的概率转移到i-1. 0元时胜率是0, n=X+Y元时胜率是1.

$$x_0 = 0, x_n = 1 \\ x_i = P x_{i+1} + (1-P) x_{i-1}, 0 < i < n$$

解方程就得到答案了.

### 优化

接下来是优化方法:
  - 如果注意到$x_i$只和相邻两项有关的话,那么解方程的时间复杂度可以从$O(n^3)$降低到$O(n)$.
  - 再接下来...如果发现这个等式其实和斐波那契数列一致,还可以继续优化到$O(\log(n))$.

我们重写一下等式

$$x_{i+1} = 1/P x_i + (P-1)/P x_{i-1}$$

可以很清楚的看到这个等式是一个加权的斐波那契数列. 但对于斐波那契数列,我们已知前两项,可以任意顺推第i项的值.而对于现在的问题,我们只知道第一项和最后一项.

不过没有关系,我们依然可以使用斐波那契数列$O(\log(n))$的技巧来求解这道题.

$$ A = \begin{bmatrix} 0 & 1 \\ (P-1)/P & 1/P\end{bmatrix} \\ A^n \begin{bmatrix} x_0 \\ x_1 \end{bmatrix} = \begin{bmatrix} x_n \\ x_{n+1} \end{bmatrix}$$

我们可以在$O(\log(n))$时间内求出$A^n$,然后再求出$x_1$,这样就有了数列的前两项,从而$O(\log(n))$时间内求任意一项的值.

代码实现: [gambling_deathmatch.ipynb](https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/gambling_deathmatch.ipynb)
