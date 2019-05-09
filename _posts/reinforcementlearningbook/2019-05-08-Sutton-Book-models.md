---
layout: post
title: "Reinforcement Learning: Models"
date: 2019-05-08 20:20:00
categories: Learning
---

# Chapter 6

## TD(0)

state-value function

on-policy

$$
V(S_t) \leftarrow V(S_t) + \alpha [R_{t+1} + \gamma V(S_{t+1}) - V(S_t)]
$$

## Sarsa

action-value funcation

on-policy

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma Q(S_{t+1}, A_{t+1}) - Q(S_t, A_t)]
$$

## Q-learning

off-policy

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma \max_a Q(S_{t+1}, a) - Q(S_t, A_t)]
$$

## Expected Sarsa

$$
Q(S_t, A_t) \leftarrow Q(S_t, A_t) + \alpha [R_{t+1} + \gamma E[Q(S_{t+1}, a) | S_{t+1}] - Q(S_t, A_t)]
$$

## Double Q-learning

With 0.5 probability:

$$
Q_1 (S_t, A_t) \leftarrow Q_1 (S_t, A_t) + \alpha [ R_{t+1} + \gamma Q_2(S_{t+1}, \arg \max_a Q_1(S_{t+1}, a))- Q_1(S_t, A_t)]
$$

or

$$
Q_2 (S_t, A_t) \leftarrow Q_2 (S_t, A_t) + \alpha [ R_{t+1} + \gamma Q_1(S_{t+1}, \arg \max_a Q_2(S_{t+1}, a))- Q_2(S_t, A_t)]
$$
