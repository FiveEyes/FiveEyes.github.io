---
layout: post
title: "Reinforcement Learning: Chapter 3"
date: 2018-03-14 02:42:00
categories: Learning
---

# 3 Finite Markov Decision Processes

"we introduce the formal problem of finite MDPs which we try to solve in the rest of the book" What???

trade-off between immediate and delayed reward


## 3.1 The Agent-Environment Interface

## 3.2 Goals and Rewards

## 3.3 Returns and Episodes

## 3.4 Unified Notation for Episodic and Continuing Tasks

## 3.5 Policies and Value Functions

policy: ```$\pi(a|s)$``` is the probability that $A_t = a$ if $S_t = s$.

value function for policy $\pi$: $v_{\pi}(s)$

action-value function for policy $\pi$: $q_{\pi}(s,a)$, the value of taking action $a$ in state $s$ under a policy $\pi$.

The value functions $v_{\pi}$ and $q_{\pi}$ can be estimated from experience, Monte Carlo methods.

$$
v_{\pi}(s) = \sum_a \pi(a | s) \sum_{s', r} p(s', r | s, a)][r + \gamma v_{\pi}(s')]
$$

**Example 3.6 Gridworld**

**Example 3.7 Golf**

## 3.6 Optimal Policies and Optimal Value Functions

optimal policies $\pi_*$

optimal state-value function $v_*(s) = \max_\pi v_\pi(s)$

optimal action-value function $q_*(s,a) = \max_{\pi} q_\pi(s,a)$

> because optimal policies is greedy, so is it possible to learn by EM?
> for current value function, learn the optimal policy.
> for current policy, update value function.

## 3.7 Optimality and Approximation

## 3.8 Summary
