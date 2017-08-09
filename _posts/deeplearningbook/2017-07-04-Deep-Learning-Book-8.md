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
  
### 8.2.3 Plateaus, Saddle Points and Other Flat Regions

### 8.2.4 Cliffs and Exploding Gradients

### 8.2.5 Long-Term Dependencies

### 8.2.6 Inexact Gradients

### 8.2.7 Poor Correspondence between Local and Global Structure

### 8.2.8 Theoretical Limits of Optimization

## 8.3 Basic Algorithms

### 8.3.1 Stochastic Gradient Descent

### 8.3.2 Momentum

### 8.3.3 Nesterov Momentum

## 8.4 Parameter Initialization Strategies

Unfortunately, these optimal criteria for initial weights often do not lead to optimal performance. Three different reasons:
  * wrong criteria
  * the properties may not persist after learning
  * the criteria might succeed at improving the speed of optimization but inadvertently increase generalization error.

There are a few situations where we may set some biases to nonzero values:
  * if a bias is for an output unit.
  * choose the bias to avoid causing too much saturation at initialization.
  * a control unit.

## 8.5 Algorithms with Adaptive Learning Rates

**delta-bar-delta**

### 8.5.1 AdaGrad

**Algorithm 8.4** The AdaGrad algorithm

### 8.5.2 RMSProp

**Algorithm 8.5** The RMSProp algorithm

 **Algorithm 8.6** RMSProp algorithm with Nesterov momentum

### 8.5.3 Adam ???

### 8.5.4 Choosing the Right Optimization Algorithm

hahaha: The choice of which algorithm to use, at this point, seems to depend largely on the user's familiarity with the algorithm(for ease of hyperparameter tuning).

## 8.6 Approximate Second-Order Methods

### 8.6.1 Newton's Method

### 8.6.2 Conjugate Gradients

Conjugate gradients is a method to efficiently avoid the calculation of the inverse Hessian by iteratively descending conjugate directions.

### 8.6.3 BFGS ???

## 8.7 Optimization Strategies and Meta-Algorithms

### 8.7.1 Batch Normalization

### 8.7.2 Coordinate Descent 

### 8.7.3 Polyak Averaging

When applying Polyak averaging to non-convex problems, it is typical to use an exponentially decaying running average:
$$
\hat{\theta}^{(t)} = \alpha \hat{\theta}^{(t-1)} + (1 - \alpha) \theta^{(t)}.
$$

### 8.7.4 Supervised Pretraining

greedy supervised pretraining

transfer learning

teacher student network

### 8.7.5 Designing Models to Aid Optimization

In practice, it is more important to choose a model family that is easy to optimize than to use a powerful optimization algorithm.

ReLU

linear paths or skip connections



### 8.7.6 Continuation Methods and Curriculum Learning

**Continuation methods**

Traditional continuation methods are usually based on smoothing the objective function.

**Curriculum learning**

















