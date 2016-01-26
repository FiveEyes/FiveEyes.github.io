---
layout: post
title: "Statistical Inference 5~8"
date: 2016-01-11 11:51:00
categories: Math
---

# Statistical Inference 5~8

# 5 Properties of a Random Sample

## 5.1 Basic Concepts of Random Samples

## 5.2 Sums of Random Variables from a Random Sample

## 5.3 Sampling from the Normal Distribution

## 5.4 Order Statistics

**Theorem 5.4.3**:

$$P(X_{(j)} \le x_i) = \sum_{k=j}^n \binom{n}{k} P_i^k(1-P_i)^{n-k}$$

and

$$P(X_{(j)} = x_i) = \sum_{k=j}^n \binom{n}{k} [P_i^k(1-P_i)^{n-k}-P_{i-1}^k(1-P_{i-1})^{n-k}]$$

**Theorem 5.4.4**:

$$f_{X_{(j)}}(x) = \frac{n!}{(j-1)!(n-j)!}f_X(X)[F_X(x)]^{j-1}[1-F_X(x)]^{n-j}$$

**Theorem 5.4.6**:

$$
\begin{eqnarray}
f_{X_{(i)},X_{(j)}}(u,v) &=& \frac{n!}{(i-1)!(j-1-i)!(n-j)!}f_X(u)f_X(v)[F_X(u)]^{i-1} \\
&& \times [F_X(v) - F_X(u)]^{j-1-i}[1-F_X(v)]^{n-j}
\end{eqnarray}$$

## 5.5 Convergence Concepts

### 5.5.1 Convergence in Probability

### 5.5.2 Almost Sure Convergence

### 5.5.3 Convergence in Distribution

### 5.5.4 The Delta Method

## 5.6 Generating a Random Sample

### 5.6.1 Direct Methods

### 5.6.2 Indirect Methods

### 5.6.3 The Accept/Reject Algorithm

### 5.6.(4) The MCMC methods

**Gibbs Sampler**

**Metropolis Algorithm**
