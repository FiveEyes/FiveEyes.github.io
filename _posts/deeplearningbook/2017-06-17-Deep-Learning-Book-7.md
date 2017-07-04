---
layout: post
title: "Deep Learning: Chapter 7"
date: 2017-06-17 03:01:00
categories: Learning
---

# 7 Regularization for Deep Learning

to reduce the test error, at the expense of increased training error.

There are many regularization strategies.
  * put extra constraints on a machine learning model.
  * add extra terms in the objective function
  * encode specific kinds of prior knowledge
  * to express a generic preference for a simpler model class in order to promote generalization.
  * to make an underdetermined problem determined.
  * ensemble methods, combine multiple hypotheses that explain the training data.

In the context of deep learning, most regularization strategies are based on regularizing estimators. Regularization of an estimator works by trading increased bias for reduced variance.

## 7.1 Parameter Norm Penalties

$$
\tilde{J}(\theta; X, y) = J(\theta; X, y) + \alpha \Omega(\theta),
$$

where $\alpha \in [0,\infty]$.

penalizes pnly the weights and leaves thje biases unregularized.


### 7.1.1 $L^2$ Parameter Regularization

$$
w \leftarrow (1 - \epsilon \alpha) w - \epsilon J(w; X, y)
$$

### 7.1.2 $L^1$ Regularization



## 7.2 Norm Penalties as Constrained Optimization

Sometimes we may wish to use explicit constraints rather than penalties.
  * This can be useful if we have an idea of what value of k is appropriate and do not want to spend time searching for the value of \alpha that corresponds to this k.
  * penalities can cause nonconvex optimization.
  * impose some stability on the optimization procedure.

## 7.3 Regularization and Under-Constrained Problems

regluarization correspond to inverting $X^T X + \alpha I$, and is guaranteed to be invertible.

## 7.4 Dataset Augmentation

Create new fake data
  * this approach is easiest for classification.
  * difficult to generate new fake data for a density estimation.

It is a effecirve technique for object recognition.
  * translating the training images a few pixels
  * translation invariant: convolution and pooling
  * rotating and scaling

Horizontal flips and 180 degree rotations may be not appropriate ways.
  * "b" and "d"
  * "6" and "9"

What we would like but that are not easy to perform
  * out-of-plane rotation

Speech recognition:
  * injecting noise

Neural networks prove not to be very robust to noise.

## 7.5 Noise Robustness

Noise injection can be much more powerful than simply shrinking the parameters, especially when the noise is added to the hidden units.

Another way: adding noise to the weights.
  * Encourage the parameters to go to regions of parameter space where small perturbations of the weights have a relatively small influence onethe output.

### 7.5.1 Injecting Noise at the Output Targets
$0,1 \rightarrow \frac{\epsilon}{k-1}, 1-\epsilon$
  * prevent softmax classifier 


## 7.6 Semi-Supervised Learning

Share parameters

The generative criterion then expresses a particular form of prior belief about the solution.(Lasserre et al., 2006)

## 7.7 Multitask Learning

Multitask learning
  * Task-specific parameters
  * Generic parameters


## 7.8 Early Stopping

One way to think of early stopping is as a very efficient hyperparameter selection algorithm.

act as a regularizer

## 7.9 Parameter Tying and Parameter Sharing

dependencies between the model parameters

parameter sharing

### 7.9.1 Convolutional Neural Networks

## 7.10 Sparse Representations

to place a penalty on the activations of the units

Representational regularization

## 7.11 Bagging and Other Ensemble Methods

Bagging

general strategy: model averaging

The reason that model works
  * independent error

Boosting


## 7.12 Dropout

Dropout can be thought of as a method of making bagging practical for ensembles of very many large neural networks.

geometric mean

weight scaling inference rule


## 7.13 Adversarial Training

Semi-supervised learning
  * virtual adversarial examples

## 7.14 Tangent Distance, Tangent Prop and Manifold Tangent Classifier

to overcome the curse of dimensionality
  * assuming that data lies near a low-dimensional manifold.

tangent distance algorithm
  * local invariance is achieved by requiring $\nabla_x f(x)$ to be orthogonal to the known manifold tangent vectors $v^{(i)}$ at $x$. ($f(x)$ is invariant for transformations).

Two major drawbacks
  * it only regularizes the model to resist infinitesimal perturbation. Explicit dataset augementation confers resistance to larger perturbations.
  * the infinitesimal approach poses difficulties for models based on rectified linear units. Dataset augmentation works well with RLU.

Tangent propagation is also related to
  * double backprop
  * adversarial training

Dataset augmentation is the non-infinitesimal version of tangent propagation, adversarial training is the non-infinitesimal version of double backprop.

---

The manifold tangent classifier eliminates the need to know the tangent vectors a priori.
  * Autoencoders can estimate the manifold tangent vectors.

The algorithm:
  * use an autoencoder to learn the manifold struicture by unsupervised learning.
  * use these tangents to regularize a neural net classifier as in tangent prop.
