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


# Chapter 7

## n-step TD

$$
G_{t:t+n} = R_{t+1} + \gamma R_{t+2} + \dots + \gamma^{n-1} R_{t+n} + \gamma^n V_{t+n-1}(S_{t+n})
$$

$$
V_{t+n}(S_t) = V_{t+n-1}(S_t) + \alpha[G_{t:t+n} - V_{t+n-1}(S_t)]
$$


## n-step Sarsa

$$
G_{t:t+n} = R_{t+1} + \gamma R_{t+2} + \dots + \gamma^{n-1} R_{t+n} + \gamma^n Q_{t+n-1}(S_{t+n}, A_{t+n})
$$

$$
Q_{t+n}(S_t, A_t) = Q_{t+n-1}(S_t, A_t) + \alpha [G_{t:t+n} - Q_{t+n-1}(S_t, A_t)]
$$


## n-step Off-policy Learning by Importance Sampling

$$
\rho_{t:h} = \prod_{k=t}^{h} \frac{\pi(A_k | S_k)}{b(A_k | S_k)}
$$

$$
V_{t+n}(S_t) = V_{t+n-1}(S_t) + \alpha \rho_{t:t+n-1} [G_{t:t+n} - V_{t+n-1}(S_t)]
$$


## n-step Tree Backup Algorithm

$$
G_{t:t+n} = R_{t+1} + \gamma [\sum_{a \neq A_{t+1}} \pi(a|S_{t+1}) Q_t(S_{t+1}, a) + \pi(A_{t+1} | S_{t+1}) G_{t+1:t+n} ]
$$

$$
Q_{t+n}(S_t, A_t) = Q_{t+n-1}(S_t, A_t) + \alpha [G_{t:t+n} - Q_{t+n-1}(S_t, A_t)]
$$

