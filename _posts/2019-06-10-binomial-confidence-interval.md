---
layout: post
title: "Binomial confidence interval"
date: 2019-06-10 19:30:00
categories: Statistics Algo
---

# Binomial confidence interval with shortest length

## Problem description

The problem is pretty simple. Suppose we have a coin, toss it $n$ times, and observe $x$ number of heads. Now, we want to estimate the possibility $p$ of head. The best estimator is $\frac{x}{n}$. But we are also interested in providing a confidence interval(CI) of $p$, $[L(x), R(x)]$.

Suppose that the confidence level is $c$. And a CI of confidence level $c$ is that ```$\forall p \in [0, 1], P(p \in [L(x), R(x)] | p) \ge c$```.

## Solution

Unfortunately, there is no exact solution for this problem. [https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval](https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval)

The main issue is that binomial distribution is a discrete distribution. Generally, probnlems in discrete field are more difficult than the similiar problems with continuous setting. For this problem, if we give an appropriate target for this problem, we can use computer to coimput an optimal solution.

The first step is transfering the orignal problem to an optimazation problem. Given $n$ and $c$, we want to minimze the maximum length of CI, $\min \max(R(x) - L(x))$, which satisfies ```$\forall p \in [0, 1], P(p \in [L(x), R(x)] | p) \ge c$```.

To solve this optimal problem, the high level idea is binary searching $t = \max(R(x) - L(x))$. And we also can assume that $\forall x \in \\{ 0, \dots, n \\}, R(x) - L(x) = t$. Now, the sub-problem is to decide if $L(x)$ exists for a given $t$.

Suppose $L(x)$ is known for all $x \le k$, we want to compute $L(k+1)$. The optimal $L(k+1)$ is the first $p'$ such that ```$P(p' \in [L(x), R(x)] | p') = c$```, and for all $p > p'$, ```$P(p \in [L(x), R(x)] | p) < c$```. Clearly, it can be done by binary search.

## Code

[Jupyter Notebook](https://github.com/FiveEyes/ml-notebook/blob/master/statistical_inference/binomial_confidence_interval_v2.ipynb)

Example: 

n = 20, confidence level = 90%

minimum interval length = 0.347

```
n: 20 , confidence: 0.9 , interval: 0.34707111480793
0 [0.0, 0.34707111480793] 0.0
1 [0.0052541740694689865, 0.352325288877399] 0.05
2 [0.026914132614011044, 0.37398524742194106] 0.1
3 [0.05641789624311604, 0.40348901105104606] 0.15
4 [0.09021345530747042, 0.43728457011540045] 0.2
5 [0.1269260599358087, 0.4739971747437387] 0.25
6 [0.16587238278892374, 0.5129434975968538] 0.3
7 [0.20666403328284658, 0.5537351480907766] 0.35
8 [0.2490648213798084, 0.5961359361877384] 0.4
9 [0.29292888519207044, 0.6400000000000005] 0.45
10 [0.33817090338965594, 0.685242018197586] 0.5
11 [0.3811895005158469, 0.728260615323777] 0.55
12 [0.4271718075480454, 0.7742429223559755] 0.6
13 [0.4739972939527387, 0.8210684087606688] 0.65
14 [0.5129436168058538, 0.8600147316137838] 0.7
15 [0.5537352672997766, 0.9008063821077066] 0.75
16 [0.5961360553967384, 0.9432071702046685] 0.8
17 [0.6720098441544733, 1.0] 0.85
18 [0.728260734532777, 1.0] 0.9
19 [0.79683990144431, 1.0] 0.95
20 [0.874186048296206, 1.0] 1.0
```
