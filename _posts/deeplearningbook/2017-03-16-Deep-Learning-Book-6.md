---
layout: post
title: "Deep Learning: Chapter 6"
date: 2017-03-16 04:15:00
categories: Learning
---

# 6 Deep Feedforward Networks

The question is then how to choose the mapping $\phi$
  * One option is use a very generic $\phi$, such as the infinite-dimensional $\phi$. RBF kernel.
  * Another option is to manually engineer $\phi$.
  * The strategy of deep learning is to learn $\phi$.

The same design decisions for a linear model:
  * Choosing the optimizer
  * the cost function
  * the form of the output units
Feedforward networks:
  * the activation functions
  * the architecture of the network

## 6.1 Example: Learning XOR
Treat this problem as a regression problem.
Using a mean squared error loss function.

## 6.2 Gradient-Based Learning

### 6.2.1 Cost Functions

#### 6.2.1.1 Learning Conditional Distributions with Maximum Likelihood

Most modern neural networks are trained using maximum likelihood. This means that the cost function is simply the negative log-likelihood, equivalently described as the cross-entropy between the training data and the model distribution. This cost function is given by
$$
  J(\theta) = - \mathbb{E}_{x,y \sim \hat{p}_{data}} \log{p_{model}(y|x)}.
$$

Functions that saturate (become very flat) undermine this objective because the activation functions used to produce the output of the hidden units or the output units saturate. The negative log-likelihood helps to avoid this problem for many models. Several output units involve an exp function that can saturate when its argument is very negative. The log function in the negative log-likelihood cost function undoes the exp of some outputs units.

#### 6.2.1.2 Learning Conditional Statistics

### 6.2.2 Output Units

#### 6.2.2.1 Linear Units for Gaussian Output Distributions

#### 6.2.2.2 Sigmoid Units for Bernoulli Output Distributions

This approach to predicting the probabilities in log space is natural to use with maximum likelihood learning.

#### 6.2.2.3 Softmax Units for Multinoulli Output Distributions

#### 6.2.2.4 Other Output Types

## 6.3 Hidden Units

### 6.3.1 Rectified Linear Units and Their Generalizations

### 6.3.2 Logistic Sigmoid and Hyperbolic Tangent

the hyperbolic tangent activation function
$$
  tanh(z) = 2\sigma(2z) - 1
$$

When a sigmoidal activation function must be used, the hyperbolic tangent activation function typically performs better than the logistic sigmoid.

### 6.3.3 Other Hidden Units

A few other reasonably common hidden unit types include
  * Radial basis function(RBF)
  * Softplus
  * Hard tanh

## 6.4 Architecture Design

the overall structure of the network:
  * how many units
  * how these units should be connected to each other

the depth of the network and the width of each layer.

### 6.4.1 Universal Approximation Properties and Depth

**Universal approximation theorem**: a feedforward network with a linear output layer and at least one hidden layer with any "squashing" activation function can approximate any Borel measurable function from one finite-dimensional space to another with any desired nonzero amount of error, provided that the network is given enough hidden units.

In the worst case, an exponential number of hidden units may be required.

### 6.4.2 Other Architectural Considerations

1) In general, the layers need not be connected in a chain, even though this is the most common practice.
  * Skip connections going from layer $i$ to layer $i+2$ or higher make it easier for the gradient to flow from output layers to layers nearer the input.

2) Another key consideration of architecture design is exactly how to connect a pair of layers to each other.
  * Each unit in the input layer is connected to only a small subset of units in the output layer, such as CNN.

## 6.5 Back-Propagation and Other Differentiation

forward propagation

back propagation

### 6.5.1 Computational Graphs

Here, we use each node in the graph to indicate a variable. The variable may be a scalar, vector, matrix, tensor, or even a variable of another type.

### 6.5.2 Chain Rule of Calculus

### 6.5.3 Recursively Applying the Chain Rule to Obtain Backprop

### 6.5.4 Back-Propagation Computation in Fully Connected MLP

### 6.5.5 Symbol-to-Symbol Derivatives

**Symbol-to-Number differentiation**: take a computational graph and a set of numerical values for the inputs to the graph, then return a set of numerical values describing the gradient at those input values.
  * Torch and Caffe.

**Symbol-to-Symbol**: Another approach is to take a computational graph and add additional nodes to the graph that provide a symbolic description of the desired derivatives.
  * Theano and Tensorflow.



### 6.5.6 General Back-Propagation

Each variable V is associated with the following subroutines:
  * get_operation(V)
  * get_consumers(V,G)
  * get_inputs(V,G)

Each operation op is also associated with a bprop operation.


### 6.5.7 Example: Back-Propagation for MLP Training

The memory cost is thus $O(mn_h)$, where $m$ is the number of examples in the minibatch and $n_h$ is the number of hidden units.

### 6.5.8 Complications

### 6.5.9 Differentiation outside the Deep Learning Community

**Automatic differentiation**

The back-propagation algorithm is only one approach to automatic differentiation.

It is a special case of a broader class of techniques called reverse mode accumulation.

Finding the optimal sequence of operations to compute the gradient is NP-complete.

### 6.5.10 Higher-Order Derivatives

**Krylov methods** ???

## 6.6 Historical Notes

mean squared error -> the cross-entropy family of loss functions.

sigmoid hidden units -> piecewise linear hidden units, such as rectified linear units.
  * For small datasets, using rectifying nonlinearities is even more important than learning the weights of hte hidden layers.
  * When more data is available, learning begins to extract enough useful knowledge to exceed the performance of randomly chosen parameters. learning is far easier in deep rectified linear networks than in deep networks that have curvature or two-sided saturation in their activation functions.

