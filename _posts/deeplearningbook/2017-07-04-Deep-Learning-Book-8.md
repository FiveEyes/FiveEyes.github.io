---
layout: post
title: "Deep Learning: Chapter 8"
date: 2017-07-04 02:36:00
categories: Learning
---

# 8 Optimization for Training Deep Models

This chapter focuses on one particular case of optimization: finding the parameters $\theta$ of a neural network that significantly reduce a cost function $J(\theta)$, which typically includes a performance measure evaluated on the entire training set as well as additional regularization terms.

## 8.1 How Learning Differs from Pure Optimization

### 8.1.1 Empirical Risk Minimization

### 8.1.2 Surrogate Loss Functions and Early Stopping

### 8.1.3 Batch and Minibatch Algorithms

standard error of the mean: $\sigma / \sqrt{n}$

large numbers of examples that all make very similar contributions to the gradient

Minibatch sizes are generally driven by the following factors:
  * Larger bathces provide a more accurate estimate of the gradient, but with less than linear return.
  * Multicore architectures are usually underutilized by extremely small batches.
  * Parallel processing
  * Specific sizes of arrays
  * Small batches can offer a regularizing effect.

Some algorithms are more sensitive to sampling error than others:
  * either because they use information that is difficult to estimate accurately with few sampels.
  * or because they use information in ways that amplify sampling errors more.

It is also crucial that the minibatches be selected randomly.
  * shuffle the order of the dataset once and then store itin shuffled fashion.




## 8.2 Challenges in Neural Network Optimization

### 8.2.1 Ill-Conditioning

### 8.2.2 Local Minima

**model identifiability**
  * weight space symmetry
  









