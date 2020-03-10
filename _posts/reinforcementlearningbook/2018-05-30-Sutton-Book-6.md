---
layout: post
title: "Reinforcement Learning 6: Temporal-Difference Learning"
date: 2018-05-30 18:10:00
categories: Learning
---

# 6 Temporal-Difference Learning

## 6.1 TD Prediction

**Tabular TD(0) for estimating $v_\pi$**

**Example 6.1: Driving Home**

## 6.2 Advantages of TD Prediction Methods

**Example 6.2 Random Walk**

## 6.3 Optimality of TD(0)

**Example 6.3: Random walk under batch updating**

**Example 6.4: You are the Predictor**

## 6.4 Sarsa: On-policy TD Control

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma Q(S_{t+1}, A_{t+1}) - Q(S_t, A_t)]
$$

**Sarsa (on-policy TD control) for estimating $Q \approx q*$**

**Example 6.5: Windy Gridworld**

## 6.5 Q-learning: Off-policy TD Control

**Q-learning (off-policy TD control) for estimating $\pi \approx \pi*$**

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma \max_a Q(S_{t+1}, A_{t+1}) - Q(S_t, A_t)]
$$

**Example 6.6: Cliff Walking**

## 6.6 Expected Sarsa

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma \mathbb{E}[Q(S_{t+1}, A_{t+1}) | S_{t+1}] - Q(S_t, A_t)]
$$


## 6.7 Maximization Bias and Double Learning

**Example 6.7: Maximization Bias Example**

**Double Q-learning**

## 6.8 Games, Afterstates, and Other Special Cases



## 6.9 Summary








