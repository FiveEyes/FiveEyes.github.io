---
layout: post
title: "Reinforcement Learning 5: Monte Carlo Methods"
date: 2018-05-25 23:43:00
categories: Learning
---

# 5 Monte Carlo Methods

do not assume complete knowledge of the environment

the model need only generate sample transitions, not the complete probability distributions of all possible transitions

## 5.1 Monte Carlo Prediction

**The first-visit MC method**

The every-visit MC method

Example 5.1: Blackjack

Example 5.2: Soap Bubble

[code](https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/rlbook/5_2_SoapBubble.ipynb)

## 5.2 Monte Carlo Estimation of Action Values

maintaining exploration -> exploring starts

## 5.3 Monte Carlo Control

**Monte Carlo with Exploring Starts**

Example 5.3 Solving Blackjack

## 5.4 Monte Carlo Control without Exploring Starts

on-policy methods and off-policy methods
$\epsilon$-greedy policy

For any $\epsilon$-soft policy, $\pi$, any $\epsilon$-greedy policy with respect to $q_\pi$ is guaranteed to be better than or equal to $\pi$.

**On-policy first-visit MC control (for $\epsilon$-soft policies)**

## 5.5 Off-policy Prediction via Importance Sampling

explore and learn

A more straightforward approach is to use two policies, one that is learned about and that becomes the optimal policy, and one that is more exploratory and is used to generate behavior.

The policy being learned about is called the *target policy*, and the policy used to generate behavior is called the *behavior policy*.

In this case we say that learning is from data "off" the target policy, and the overall process is termed *off-policy learning*.

*importance sampling*

*importance-sampling ratio*

*ordinary importance sampling*: unbiased, but variance could be large

*weighted importance sampling*: biased, but variance is small

**Example 5.4: Off-policy Estimation of a Blackjack State Value**

**Example 5.5: Infinite Variance**

## 5.6 Incremental Implementation

**Off-policy MC prediction**

## 5.7 Off-policy Monte Carlo Control

**Off-policy MC control** why not sample from policy $\pi$ directly?

**Exercise 5.8: Racetrack**

## 5.8 *Discounting-aware Importance Sampling
rewrite formula with discounting
## 5.9 *Per-reward Importance Sampling
rewrite formula with discounting
## 5.10 Summary
learning without a model
do not bootstrap

