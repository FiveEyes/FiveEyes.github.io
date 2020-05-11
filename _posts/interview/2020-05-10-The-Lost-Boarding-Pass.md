---
layout: post
title: "丢失的登机牌(The Lost Boarding Pass)"
date: 2020-05-10 23:30:00
categories: Interview
---

# The Lost Boarding Pass

[LeetCode 1227](https://leetcode.com/problems/airplane-seat-assignment-probability/)

[Solution](https://arxiv.org/abs/1910.02515)

## 问题描述

N个人依次登机,只有第一个人忘记了自己的座位号,他随便找了个位置坐下,随后的人按以下规则入座:
  - 如果自己的座位没被占,坐自己的位置,
  - 如果自己的位置被占了,随便找个位置坐下.

问题:
  - 原题,最后一个人能坐到自己位置的概率是多少?
  - 扩展,第K个人能坐到自己位置的概率是多少?

# 解答

**Solution给出的两个完全靠想的答案**:
  - 因为最终只可能剩下第一个位置和最后一个位置,而且具有对称性,所以最后一个人坐到自己的位置的可能性是50%.
  - 当第K个人登机时, 第$2, \dots, K-1$个位置都是坐着人的, 其余$N-K+2$个位置中有i一个被占,而且概率相等,所以第K个人的座位被占的概率是$1/(N-K+2)$.

**自己的答案**
很久之前做过这道题...当时应该是爆推公式,现在已经忘记了...又推了一遍,但感觉没以前那个版本复杂...

现在设$F(n,k)$是N个人登机,第K个人座位被占的概率,可得

$$
F(n,k) = \frac{1}{n} + \frac{1}{n} F(n-1,k-1) + \frac{1}{n} F(n-2, k-2) + \dots + \frac{1}{n} F(n-k+2,2)
$$

化简得到

$$F(n,k) = \frac{1}{n} (1 + \sum_{i=1}^{k-2} F(n-i,k-2))$$

设$S(n,k) = F(n,k) + F(n-1,k-1) + \dots + F(n-k+2,2)$, 带入上式得到

$$F(n,k) = \frac{1}{n} (1 + S(n-1,k-1)))$$

化简得到

$$S(n,k) = (n+1)F(n,k) - 1$$

已知$F(n,k) = S(n,k) - S(n-1,k-1)$, 得到 

$$F(n,k) = (n+1)F(n,k) - 1 - n F(n-1,k-1) + 1$$

化简得到

$$
F(n,k) = F(n-1,k-1)
$$

最终得到答案

$$
F(n,k) = F(n-1,k-1) = \dots = F(n-k+2, 2) = \frac{1}{n-k+2}
$$



