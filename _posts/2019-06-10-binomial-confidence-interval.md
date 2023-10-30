---
layout: post
title: "The algorithm to compute the optimal binomial confidence interval"
date: 2019-06-10 19:30:00
categories: Statistics Algo
---

# Compute the optimal binomial confidence interval which has the shortest interval.

## Problem description

The problem is pretty simple. Suppose we have a coin, toss it $n$ times, and observe $x$ number of heads. Now, we want to estimate the possibility $p$ of head. The best estimator is $\frac{x}{n}$. But we are also interested in providing a confidence interval(CI) of $p$, $[L(x), R(x)]$.

Suppose that the confidence level is $c$. And a CI of confidence level $c$ is that $\forall p \in [0, 1], P(p \in [L(x), R(x)] | p) \ge c$.

## Background

I didn't find out a existing algorithm to compute out an optimal confidence interval yet. the optimal CI means that the the maximum length of all its intervals is the smallest one in all possible valid CIs. [https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval](https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval)

One possible reason I guess is that all the existing solutions are focusing on working out an analytical solution which is in the form of math expressions.

In this post, our target is to compute out a CI which is $\min_{R,L} \max_{x} (R(x) - L(x))$.

## Solution

### Main problem - binary search on the maximum length.

Let $t = \max_{x} R(x) - L(x)$, the high level idea is doing a binary search on $t$. The subproblem is that for a given $T$ and $N, C$, whether a valid $L(x)$ and $R(x)$ exists, where $\forall x \in \\{0, N\\}, R(x) - L(x) \ge T$ and $\forall p \in [0, 1], P(p \in [L(x), R(x)] | p) \ge C$.

And also, we can relax the problem by assuming that all $R(x)-L(x)$ are the same length, let $T = R(x) - L(x), \forall x \in \\{0, N\\}$. Now, we are ready to move to the subprobem.

### Sub problem - A proof by induction.

With this same length assumption, to solve the subproblem, we could construct $L(x)$ by induction. If the construction succeeds, then we get a valid CL with the length $T$, $L(x)$ by induction and $R(x) = L(x) + T, \forall x$. If the inductive construction fails, then it proves that no valid $L(x)$ exists for the given $T$.

the base case: $k = 0$, $L(k) = 0.0$ and $R(k) = T$.

the induction step: $L(k+1)$ is $p'$ such that 

$$\forall p \le p', \sum_{0 \le x \le k} 1(x) \times P(x | p') \ge C$$

and 

$$\forall p > p', \sum_{0 \le x \le k} 1(x) \times P(x | p') < C$$

where

$$1(x) = 1 \text{ if }  L(x) \le p' \le L(x) + T, \text{else }0$$

Clearly, this $p'$ could get found by binary search again, this inducative construction will give us the optimal candidate $L(x)$. To validate if it's a valid L(x), we can check if $L(N) + T \ge 1$ or not.

if $L(N) + T < 1$, then it proves that no valid solution exists.

if $L(N) + T \ge 1$, then it's a valid CI with length T.

### Summary

Now, we get an optimal binomial confidence interval, :) 
```
Input: N, C

binary_search(T, left=0.0, right=1.0)
  t = (left + right) / 2
  L = proof_by_induction(t,N,C)
  if L(N) + T < 1.0
    left = t
  else:
    right = t
return right
```

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
