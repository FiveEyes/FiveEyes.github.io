---
layout: post
title: "Deep Learning: Chapter 5"
date: 2017-03-15 01:59:00
categories: Learning
---

# 5 Machine Learning Basics

## 5.1 Learning Algorithms

### 5.1.1 The Task, $T$
  * Classification
  * Classification with missing inputs
  * Regression
  * Transcription
  * Machine translation
  * Structured output
  * Anomaly detection
  * Sythesis and sampling
  * Imputation of missing values
  * Denoising
  * Density estimation or probability mass function estimation

### 5.1.2 The Performance Measure, $P$

### 5.1.3 The Experience, $E$

### 5.1.4 Example: Linear Regression

## 5.2 Capacity, Overfitting and Underfitting

The error incurred by an oracle making predictions from the true distribution p(x, y) is called the Bayes error.

### 5.2.1 The No Free Lunch Theorem

### 5.2.2 Regularization

Regularization is any modification we make to a learning algorithm that is intended to reduce its generalization error but not its training error.

## 5.3 Hyperparameters and Validation Sets

### 5.3.1 Cross-Validation

## 5.4 Estimators, Bias and Variance

### 5.4.1 Point Estimation

### 5.4.2 Bias

### 5.4.3 Variance and Standard Error

### 5.4.4 Trading Off Bias and Variance to Minimize Mean Squared Error

### 5.4.5 Consistency



## 5.5 Maximum Likelihood Estimation

### 5.5.1 Conditional Log-Likelihood and Mean Squared Error

**Example: Linear Regression as Maximum Likelihood**

We now revisit linear regression from the point of view of maximum likelihood estimation.

### 5.5.2 Properties of Maximum Likelihood

**Statistic efficiency**

## 5.6 Bayesian Statistics

**Example: Bayesian Linear Regression**

### 5.6.1 Maximum A Posteriori (MAP) Estimation

## 5.7 Supervised Learning Algorithms

### 5.7.1 Probabilistic Supervised Learning

**logistic regression**

### 5.7.2 Support Vector Machines

**kernel trick**

**radial basis function**

### 5.7.3 Other Simple Supervised Learning Algorithms

**k-nearest neighbors**

**decision tree**

## 5.8 Unsupervised Learning Algorithms

There are multiple ways of defining a simpler representation. Three of the most common include lower-dimensional representations, sparse representations, and independent representations.

### 5.8.1 Principal Components Analysis

### 5.8.2 k-means Clustering

## 5.9 Stochastic Gradient Descent

The insignht of SGD is tha the gradient is an expectation. The expectation may be approximately estimated using a small set of samples. Specifically, on each step of the algorithm, we can sample a minibatch of examples $B = \{ x^1, \dots, x^{m'} \}$ drawn uniformly from the training set. The minibatch size $m'$ is typeically chosen to be a relatively small number of examples, rangning from one to a few hundred.

## 5.10 Building a Machine Learning Algorithm

A fairly simple recipe: combine a specification of a dataset, a cost function, an optimization procedure and a model.

## 5.11 Challenges Motivating Deep Learning

### 5.11.1 The Curse of Dimensionality

### 5.11.2 Local Constancy and Smoothness Regularization

### 5.11.3 Manifold Learning












