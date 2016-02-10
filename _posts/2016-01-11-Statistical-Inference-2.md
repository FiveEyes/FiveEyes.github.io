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

**Lemma 5.2.5**: 

  $$\mathrm{E}(\sum_{i=1}^n g(X_i)) = n(\mathrm{E}g(X_1))$$

and

  $$\mathrm{Var}(\sum_{i=1}^n g(X_i)) = n(\mathrm{Var}g(X_1))$$

**Theorem 5.2.6**:

  * $$\mathrm{E}\bar{X} = \mu$$,
  * $$\mathrm{Var}\bar{X} = \sigma^2/n$$,
  * $$\mathrm{E}S^2 = \sigma^2$$.
  
**Theorem 5.2.7**:

  $$M_{\bar{X}}(t) = [M_X(t/n)]^n$$

**Example 5.2.8**:Let $$X_1, \dots, X_n$$ be a random sample from a $$n(\mu, \sigma^2)$$ population. Then the mgf of the sample mean is

$$\begin{eqnarray}
M_{\bar{X}}(t) &=& [\exp(\mu t / n + \sigma^2(t/n)^2/2)]^n \\
&=&\exp(\mu t + (\sigma^2/n)t^2/2)
\end{eqnarray}$$

Thus, $$\bar{X}$$ has a $$n(\mu, \sigma^2/n)$$ distribution.

Another simple example is given by a $$gamma(\alpha, \beta)$$ random sameple. Here, we can also easily derive the distribution of the sample mean. The mgf of the sample mean is

$$M_{\bar{X}}(t) = [(\frac{1}{1 - \beta(t/n)})^\alpha]^n = (\frac{1}{1-(\beta/n)t)})^{n\alpha}$$

which we recognize as the mgf of a $$gamma(n\alpha, \beta/n)$$, the distribution of $$\bar{X}$$.

## 5.3 Sampling from the Normal Distribution

### 5.3.1 Properties of the Sample Mean and Variance

**Theorem 5.3.1**: Let $$X_1, \dots, X_n$$ be a random sample from a $$n(\mu, \sigma^2)$$ distribution, and let $$\bar{X}$$ and $$S^2$$. Then
  
  * $$\bar{X}$$ and $$S^2$$ are independent random variables,
  * $$\bar{X}$$ has a $$n(\mu, \sigma^2/n)$$ distribution,
  * $$(n-1)S^2/\sigma^2$$ has a chi squared distribution with $$n - 1$$ degrees of freedom.

**Lemma 5.3.2**:

  * If $$Z$$ is a $$n(0,1)$$ random variable, then $$Z^2 \thicksim \chi_1^2$$.
  * If $$X_1, \dots, X_n$$ are independent and $$X_i \thicksim \chi_{p_i}^2$$, then $$X_1 + \dots + X_n \thicksim \chi_{p_1 + \dots + p_n}^2$$.  
  
## 5.4 Order Statistics

**Theorem 5.4.3**:

$$P(X_{(j)} \le x_i) = \sum_{k=j}^n \binom{n}{k} P_i^k(1-P_i)^{n-k}$$

and

$$P(X_{(j)} = x_i) = \sum_{k=j}^n \binom{n}{k} [P_i^k(1-P_i)^{n-k}-P_{i-1}^k(1-P_{i-1})^{n-k}]$$

**Theorem 5.4.4**:

$$f_{X_{(j)}}(x) = \frac{n!}{(j-1)!(n-j)!}f_X(X)[F_X(x)]^{j-1}[1-F_X(x)]^{n-j}$$

**Theorem 5.4.6**:

$$\begin{eqnarray}
f_{X_{(i)},X_{(j)}}(u,v) &=& \frac{n!}{(i-1)!(j-1-i)!(n-j)!}f_X(u)f_X(v)[F_X(u)]^{i-1} \\
&& \times [F_X(v) - F_X(u)]^{j-1-i}[1-F_X(v)]^{n-j}
\end{eqnarray}$$

## 5.5 Convergence Concepts

### 5.5.1 Convergence in Probability

**Definition 5.5.1**:

  $$\lim_{ n \rightarrow \infty } P(|X_n - X| \ge \epsilon) = 0$$

or,

  $$\lim_{ n \rightarrow \infty } P(|X_n - X| < \epsilon) = 1$$

**Theorem 5.5.2 (Weak Law of Large Numbers)**:
  
  $$\lim_{ n \rightarrow \infty } P(|\bar{X}_n - \mu| < \epsilon) = 1$$ 
  
### 5.5.2 Almost Sure Convergence

**Definition 5.5.6**:

  $$P(\lim_{ n \rightarrow \infty } |X_n - X| < \epsilon) = 1$$

**Theorem 5.5.9 (Strong Law of Large Numbers)**:
  
  $$P(\lim_{ n \rightarrow \infty } |\bar{X}_n - \mu| < \epsilon) = 1$$
  
### 5.5.3 Convergence in Distribution

**Definition 5.5.10**:

  $$\lim_{ n \rightarrow \infty } F_{X_n}(x) = F_X(x)$$

**Theorem 5.5.14 (Central Limit Theorem)**: Let $$X_1, X_2, \dots $$ be a sequence of iid random variables whose mgfs exist in neighborhood of 0 (that is , $$M_{X_i}(t)$$ exists for ```\(|t| < h\)```, for some positive $$h$$). Let $$\mathrm{E}X_i = \mu$$ and $$\mathrm{Var}X_i = \sigma^2 > 0$$. (Both $$\mu$$ and $$\sigma^2$$ are finite since the mgf exists.) Define $$\bar{X_n} = (1/n)\sum_{i=1}^n X_i$$. Let $$G_n(x)$$ denote the cdf of $$\sqrt{n}(\bar{X_n}-\mu)/\sigma$$. Then, for any $$x$$, $$-\infty < x < \infty$$,

$$\lim_{ n \rightarrow \infty} G_n(x) = \int_{-\infty}^x \frac{1}{\sqrt{2\pi}} e^{-y^2/2} dy$$


### 5.5.4 The Delta Method

## 5.6 Generating a Random Sample

### 5.6.1 Direct Methods

### 5.6.2 Indirect Methods

### 5.6.3 The Accept/Reject Algorithm

### 5.6.(4) The MCMC methods

**Gibbs Sampler**

**Metropolis Algorithm**

# 6 Principles of Data Reduction

## 6.1 Introduction

## 6.2 The Sufficiency Principles

### 6.2.1 Sufficient Statistics

### 6.2.2 Minimal Sufficient Statistics

## 6.3 The Likelihood Principles

## 6.4 The Equivariance Principles