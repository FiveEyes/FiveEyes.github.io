---
layout: post
title: "Reinforcement Learning: Chapter 9"
date: 2018-10-25 07:00:00
categories: Learning
---

# 9 On-policy Prediction with Approximation

## 9.1 Value-function Approximation

## 9.2 The Prediction Objective

$$
VE(w) = \sum_{s \in S} \mu(s)[v_\pi(s) - \hat{v}(s,w)]^2
$$
Often $\mu(s)$ is chosen to be the fraction of time spent in $s$.

**The on-policy distribution in episodic tasks**

## 9.3 Stochastic-gradient and Semi-gradient Methods

$w \leftarrow w + \alpha [G_t - \hat{v}(S_t, w)] \nabla \hat{v}(S_t, w)$

If $G_t$ is unbiased estimate, it'sStochastic-gradient method. If $G_t$ is biased estimate, it's Semi-gradient method.

**Example 9.1: State Aggregation on the 1000-state Random Walk**

## 9.4 Linear Methods

## 9.5 Feature Construction for Linear Methods

### 9.5.1 Polynomials

### 9.5.2 Fourier Basis

### 9.5.3 Coarse Coding

### 9.5.4 Tile Coding

### 9.5.5 Radial Basis Functions

## 9.6 Nonlinear Function Approximation: ANNs

## 9.7 Least-Squares TD

**LSTD for estimating $\hat{v} \approx v_{\pi}$ ($O(d^2)$ version)**

## 9.8 Memory-based Function Approximation

## 9.9 Kernel-based Function Approximation

## 9.10 Kernel-based Function Approximation

## 9.11 Looking Deeper at On-policy Learning: Interest and Emphasis

## 9.12 Summary





