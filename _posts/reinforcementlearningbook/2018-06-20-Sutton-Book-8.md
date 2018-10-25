---
layout: post
title: "Reinforcement Learning: Chapter 8"
date: 2018-06-20 22:22:00
categories: Learning
---

# 8 Planning and Learning with Tabular Methods
model-based: planning
model-free: learning
## 8.1 Models and Planning
distribution models
sample models
Two distinct approaches to planning
  * state-space planning
  * plan-space planning
**Random-sample one-step tabular Q-planning**
## 8.2 Dyna: Integrating Planning, Acting and Learning
**Tabular Dyna-Q**
**Example 8.1: Dyna Maze**
## 8.3 When the Model Is Wrong
**Example 8.2: Blocking Maze**
**Example 8.3: Shortcut Maze**
  * Dyna-Q+: the transition has not been tried in $\tau$ time steps, then planning updates are done as if that transition produced a reward of $r + k\sqrt{\tau}$
**Exercise 8.4**

## 8.4 Prioritized Sweeping
Only work back from any state whose value has changed.
**Prioritized sweeping for a deterministic environment**
**Example 8.4: Prioritized Sweeping on Mazes**
**Example 8.5: Rod Maneuvering**
## 8.5 Expected vs. Sample Updates
1. state values or action values
2. estimate the value for optimal policy or for an arbitrary given policy
3. expected updates sample updates
## 8.6 Trajectory Sampling
## 8.7 Real-time Dynamic Programming
**Example 8.6: RTDP on the Racetrack**
## 8.8 Planning at Decision Time
background planning: to use planning to gradually improve a policy or value function
decision-time planning: to select an action for the current state
## 8.9 Heuristic Search
## 8.10 Rollout Algorithms
## 8.11 Monte Carlo Tree Search
1. Selection
2. Expansion
3. Simulation
4. Backup
My implementation of MCTS + ResNet for Gomoku: [GomokuZero](https://github.com/FiveEyes/GomokuZero)
# 8.12 Summary of the Chapter
