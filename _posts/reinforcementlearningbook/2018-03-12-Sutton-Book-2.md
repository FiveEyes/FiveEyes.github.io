---
layout: post
title: "Reinforcement Learning 2: Multi-armed Bandits"
date: 2018-03-12 15:25:00
categories: Learning
---

# Part I: Tabular Solution Methods

the state and action spaces are small enough for the approximate value functions to be represented as arrays, or tables.

In this case, the methods can often find the exact solutions, that is, they can often find exactly the optimal value function and the optimal policy.

Chapter 2 describes solution methods for the special case of the reinforcement learning problem in which there is only a single state, called bandit problems.

Chapter 3~5 describe three fundamental classes of methods for solving finite Markov decision problems: dynamic programming, Monte Carlo methods, and temporal-difference learning.

Chapter 6 describe how the strengths of Monte Carlo methods can be combined with the strengths of temporal-difference methods via the use of eligibility traces.

Chapter 7 describe how temporal-difference learning methods can be combined with model learning and planning methods for a complete and unified solution the the tabular reinforcement learning problem.

# 2 Multi-armed Bandits

## 2.1 A $k$-armed Bandit Problem

Is it the same with The Multiplicative Weights Update Method?

Exploitation or Exploration

## 2.2 Action-value Methods

$\epsilon$-greedy method: with small probability $\epsilon$, we select ramdomly from among all the actions with equal probability.

## 2.3 The 10-armed Testbed

## 2.4 Incremental Implementation

$$
Q_{n+1} = Q_n + \frac{1}{n}[R_n - Q_n]
$$

$$
NewEstimate \leftarrow OldEstimate + StepSize \times [Target - OldEstimate]
$$

## 2.5 Tracking a Nonstationary Problem

exponential recency-weighted average

$$
Q_{n+1} = Q_n + \alpha [R_n - Q_n]
$$


The choice $\alpha_n(a) = \frac{1}{n}$ results in the sample-average method, which is guaranteed to converge to the true action values by the law of large numbers.

But of course cnvergence is not guaranteed for all choices of the sequence $\{ \alpha_n(a) \}$. A well-known result in stochastic approximation theory gives us the conditions required to assure convergence with

$\sum_{n=1}^{\infty} \alpha_n(a) = \infty$ and $\sum_{n=1}^{\infty} \alpha_n^2(a) < \infty$

## 2.6 Optimistic Initial Values

## 2.7 Upper-Confidence-Bound Action Selection

It would be better to select among the non-greedy actions according to their potential for actually being opptimal

$$
A_t = \arg_a \max [ Q_t(a) + c \sqrt{\frac{\ln t}{N_t(a)}} ]
$$

the number $c > 0$ controls the degree of exploration.

The idea of this UCB action selection is that the square-root term is a measure of the uncertainy or variance in the estimate of a's value.

## 2.8 Gradient Bandit Algorithms

we consider learning a numerical preference for each action $a$, which we denote $H_t(a)$.

$$
Pr\{ A_t = a \} = \frac{e^{H_t(a)}}{\sum_{b=1}^{k} e^{H_t(b)}} = \pi_t(a)
$$

Update rule:

$$
H_{t+1}(A_t) = H_t(A_t) + \alpha (R_t - \bar R_t)(1 - \pi_t(A_t)), \\
H_{t+1}(a) = H_t(a) - \alpha (R_t - \bar R_t) \pi_t(a), \quad \forall a \neq A_t \\
$$

### The Bandit Gradient Algorithm as Stochastic Gradient Ascent

Interesting!

## 2.9 Associative Search

## 2.10 Summary


