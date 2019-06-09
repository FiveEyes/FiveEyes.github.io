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
$$
\mathrm{E}(\sum_{i=1}^n g(X_i)) = n(\mathrm{E}g(X_1))
$$
and
$$
\mathrm{Var}(\sum_{i=1}^n g(X_i)) = n(\mathrm{Var}g(X_1))
$$

**Theorem 5.2.6**:

  * $\mathrm{E}\bar{X} = \mu$,
  * $\mathrm{Var}\bar{X} = \sigma^2/n$,
  * $\mathrm{E}S^2 = \sigma^2$.

**Theorem 5.2.7**:
$$
M_{\bar{X}}(t) = [M_X(t/n)]^n
$$

**Example 5.2.8**:Let $X_1, \dots, X_n$ be a random sample from a $n(\mu, \sigma^2)$ population. Then the mgf of the sample mean is

$$
\begin{eqnarray}
M_{\bar{X}}(t) &=& [\exp(\mu t / n + \sigma^2(t/n)^2/2)]^n \\
&=&\exp(\mu t + (\sigma^2/n)t^2/2)
\end{eqnarray}
$$

Thus, $\bar{X}$ has a $n(\mu, \sigma^2/n)$ distribution.

Another simple example is given by a $gamma(\alpha, \beta)$ random sameple. Here, we can also easily derive the distribution of the sample mean. The mgf of the sample mean is

$$
M_{\bar{X}}(t) = [(\frac{1}{1 - \beta(t/n)})^\alpha]^n = (\frac{1}{1-(\beta/n)t)})^{n\alpha}
$$

which we recognize as the mgf of a $gamma(n\alpha, \beta/n)$, the distribution of $\bar{X}$.

**Theorem 5.2.9** If $X$ and $Y$ are independent continuous random variables with pdfs $f_X(x)$ and $f_Y(y)$, then the pdf of $Z = X + Y$ is

$$
f_Z(z) = \int_{-\infty}^{\infty} f_X(w) f_Y(z-w) dw
$$

**Example 5.2.10 (Sum of Cauchy random variables)**

**Theorem 5.2.11** Suppose $X_1, \dots, X_n$ is a random sample from a pdf or pmf ```\(f(x|\theta)\)```, where

$$
f(x|\theta = h(x)c(\theta)\exp{(\sum_{i=1}^k w_i(\theta) t_i(x))}
$$

is a member of an exponential family. Define statistics $T_1, \dots, T_k$ by

$$
T_i(X_1, \dots, X_n) = \sum_{j=1}^n t_i(X_j), \quad i = 1, \dots, k.
$$

If the set $\{(w_1(\theta), w_2(\theta), \dots, w_k(\theta))\}$ contains an open subset of $R^k$, then the distribution of $(T_1, \dots, T_k)$ is an exponential family of the form

$$
d_T(u_1, \dots, u_k|\theta) = H(u_1, \dots, u_k)[c(\theta)]^n \exp{(\sum_{i=1}^k w_i(\theta) u_i)}
$$

**Example 5.2.12 (Sum of Bernoulli random variables)**

## 5.3 Sampling from the Normal Distribution

### 5.3.1 Properties of the Sample Mean and Variance

**Theorem 5.3.1**: Let $X_1, \dots, X_n$ be a random sample from a $n(\mu, \sigma^2)$ distribution, and let $\bar{X}$ and $S^2$. Then

  * $\bar{X}$ and $S^2$ are independent random variables,
  * $\bar{X}$ has a $n(\mu, \sigma^2/n)$ distribution,
  * $(n-1)S^2/\sigma^2$ has a chi squared distribution with $n - 1$ degrees of freedom.

**Lemma 5.3.2**:

  * If $Z$ is a $n(0,1)$ random variable, then $Z^2 \thicksim \chi_1^2$.
  * If $X_1, \dots, X_n$ are independent and $X_i \thicksim \chi_{p_i}^2$, then $X_1 + \dots + X_n \thicksim \chi_{p_1 + \dots + p_n}^2$.  

## 5.4 Order Statistics

**Theorem 5.4.3**:

$$
P(X_{(j)} \le x_i) = \sum_{k=j}^n \binom{n}{k} P_i^k(1-P_i)^{n-k}
$$

and

$$
P(X_{(j)} = x_i) = \sum_{k=j}^n \binom{n}{k} [P_i^k(1-P_i)^{n-k}-P_{i-1}^k(1-P_{i-1})^{n-k}]
$$

**Theorem 5.4.4**:

$$
f_{X_{(j)}}(x) = \frac{n!}{(j-1)!(n-j)!}f_X(X)[F_X(x)]^{j-1}[1-F_X(x)]^{n-j}
$$

**Theorem 5.4.6**:

$$
\begin{eqnarray}
f_{X_{(i)},X_{(j)}}(u,v) &=& \frac{n!}{(i-1)!(j-1-i)!(n-j)!}f_X(u)f_X(v)[F_X(u)]^{i-1} \\
&& \times [F_X(v) - F_X(u)]^{j-1-i}[1-F_X(v)]^{n-j}
\end{eqnarray}
$$

## 5.5 Convergence Concepts

### 5.5.1 Convergence in Probability

**Definition 5.5.1**:

$$
\lim_{ n \rightarrow \infty } P(|X_n - X| \ge \epsilon) = 0
$$

or,

$$
\lim_{ n \rightarrow \infty } P(|X_n - X| < \epsilon) = 1
$$

**Theorem 5.5.2 (Weak Law of Large Numbers)**:

$$
\lim_{ n \rightarrow \infty } P(|\bar{X}_n - \mu| < \epsilon) = 1
$$

### 5.5.2 Almost Sure Convergence

**Definition 5.5.6**:

$$
P(\lim_{ n \rightarrow \infty } |X_n - X| < \epsilon) = 1
$$

**Theorem 5.5.9 (Strong Law of Large Numbers)**:

$$
P(\lim_{ n \rightarrow \infty } |\bar{X}_n - \mu| < \epsilon) = 1
$$

### 5.5.3 Convergence in Distribution

**Definition 5.5.10**:

$$
\lim_{ n \rightarrow \infty } F_{X_n}(x) = F_X(x)
$$

**Theorem 5.5.14 (Central Limit Theorem)**: Let $X_1, X_2, \dots $ be a sequence of iid random variables whose mgfs exist in neighborhood of 0 (that is , $M_{X_i}(t)$ exists for ```\(|t| < h\)```, for some positive $h$). Let $\mathrm{E}X_i = \mu$ and $\mathrm{Var}X_i = \sigma^2 > 0$. (Both $\mu$ and $\sigma^2$ are finite since the mgf exists.) Define $\bar{X_n} = (1/n)\sum_{i=1}^n X_i$. Let $G_n(x)$ denote the cdf of $\sqrt{n}(\bar{X_n}-\mu)/\sigma$. Then, for any $x$, $-\infty < x < \infty$,

$$
\lim_{ n \rightarrow \infty} G_n(x) = \int_{-\infty}^x \frac{1}{\sqrt{2\pi}} e^{-y^2/2} dy
$$


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

Three principles of data reduction:

  * The Sufficiency Principle
  * The Likelihood Principle
  * The Equivariance Principle

## 6.2 The Sufficiency Principle

### 6.2.1 Sufficient Statistics

**Definition 6.2.1**: A statistic $T(X)$ is a sufficient statistic of $\theta$ if the conditional distribution of the sample $X$ given the value of $T(X)$ does not depend on $\theta$.

**Theorem 6.2.2**: If ```\(p(x | \theta)\)``` is the joint pdf or pmf of $X$ and ```\(q(t | \theta)\)``` is the pdf or pmf of $T(X)$, then $T(X)$ is a sufficient statistic for $\theta$ if, for every $x$ in the sample space, the ratio ```\(p(x | \theta)/q(T(X) | \theta)\)``` is constant as a function of $\theta

**Theorem 6.2.6 (Factorization Theorem)**: Let ```\(f(x | \theta)\)``` denote the joint pdf or pmf of a sample $X$. A statistic $T(X)$ is a sufficient statistic for $\theta$ if and only if there exist functions ```\(g(x | \theta)\)``` and $h(x)$ such that, for all sample points $x$ and all parameter points $\theta$,

$$
f(x|\theta) = g(T(x)|\theta)h(x)
$$

### 6.2.2 Minimal Sufficient Statistics


### 6.2.3 Ancillary Statistics

**Definition 6.2.16**: A statistic $S(X)$ whose distribution does not depend on the parameter $\theta$ is called an ancillary statistic.

### 6.2.4 Sufficient, Ancillary, and Complete Statistics

**Example 6.2.20 (Ancillary precision)**

**Theorem 6.2.24 (Basu's Theorem)**: If T(X) is a complete and minimal sufficient statistic is independent of every ancillary statistic.

**Theorem 6.2.25 (Complete statistic in the exponential family)**: Let $X_1, \dots, X_n$ be iid observations from an exponential family with pdf or pmf of the form

$$
f(x|\theta) = h(x)c(\theta)\exp(\sum_{j=1}^k w(\theta_j)t_j(x))
$$

where $\theta = (\theta_1, \dots, \theta_k)$. Then the statistic

$$
T(X) = (\sum_{i=1}^n t_1(X_i), \dots, \sum_{i=1}^n t_k(X_i))
$$

is complete as long as the parameter space $\Theta$ contains an open set in $R^k$.


## 6.3 The Likelihood Principle

## 6.4 The Equivariance Principle


# 7 Point Estimation

## 7.1 Introduction

This chapter is divided into two parts. The first part deals with methods for finding estimators, and the second part deals with evaluating these estimators.

**Definition 7.1.1** A point estimator is any function $W(X_1, \dots, X_x)$ of a sample; that is, any statistic is a point estimator.

## 7.2 Methods of Finding Estimators

### 7.2.1 Method of Moments

### 7.2.2 Maximum Likelihood Estimators

### 7.2.3 Bayes Estimators

### 7.2.4 The EM Algorithm

## 7.3 Methos of Evaluating Estimators

### 7.3.1 Mean Squared Error

**Definition 7.3.1** The mean squared error of an estimator $W$ of a parameter $\theta$ is the function of $\theta$ defined by $\mathrm{E}_\theta(W - \theta)^2$.

$$
\mathrm{E}_\theta(W - \theta)^2 = \mathrm{Var}_\theta W + (\mathrm{Bias}_\theta W)^2
$$

### 7.3.2 Best Unbiased Estimators

**Definition 7.3.7** An estimator ```$W^*$``` is a best unbiased estimator of $\tau(\theta)$ if it satisfies ```$E_\theta W^* = \tau(\theta)$``` for all $\theta$ and, for any other estimator $W$ with $E_\theta W = \tau(\theta)$, we have ```$\mathrm{Var}_\theta W^* \le \mathrm{Var}_\theta W$``` for all $\theta$. ```$W^*$``` is also called a uniform minimum variance unbiased estimator (UMVUE) of $\tau(\theta)$.

**Theorem 7.3.9 (Cramer-Rao Inequality)**: Let $X_1, \dots, X_n$ be a sample with pdf ```$f(x | \theta)$```, and let $W(X) = W(X_1, \dots, X_n)$ be any estimator satisfying

$$
\frac{d}{d\theta} E_{\theta}W(X) = \int_{\chi} \frac{\partial}{\partial \theta} [W(x) f(x|\theta)] dx
$$

and

$$
\mathrm{Var}_\theta W(X) < \infty
$$

Then

$$
\mathrm{Var}_\theta (W(X)) \ge \frac{(\frac{d}{d\theta} \mathrm{E}_\theta W(X))^2}{\mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2)}
$$

**Corollary 7.3.10 (Cramer-Rao Inequality, iid case)** If the assumptions of Theorem 7.3.9 are satisfied and, additionally, if $X_1, \dots, X_n$ are iid with pdf ```\(f(x|\theta)\)```, then

$$
\mathrm{Var}_\theta W(X) \ge \frac{(\frac{d}{d\theta} \mathrm{E}_{\theta}W(X))^2}{n \mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2)}
$$

**Lemma 7.3.11** If ```\(f(x|\theta)\)``` satisfies

$$
\frac{d}{d\theta} \mathrm{E}_\theta (\frac{\partial}{\partial \theta} \log{f(X|\theta)}) = \int \frac{\partial}{\partial \theta} [(\frac{\partial}{\partial \theta} \log{f(x|\theta)})] dx
$$

(true for an exponential family), then

$$
\mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2) = - \mathrm{E}_\theta(\frac{\partial^2}{\partial \theta^2}\log{f(X|\theta)}).
$$

**Corollary 7.3.15 (Attainment Let $X_1, \dots, X_n$ be iid ```\(f(x|\theta)\)```, where ```\(f(x|theta)\)``` satisfies the conditions of Cramer-Rao Theorem. Let ```\(L(\theta|X)=\prod_{i=1}^n f(x_i|\theta)\)```

### 7.3.3 Sufficiency and Unbiasedness

**Theorem 7.3.17 (Rao-Blackwell)** Let W be any unbiased estimator of $\tau(\theta)$, and let T be a sufficient statistic for $\theta$. Define ```\(\phi(T) = \mathrm{E}(W|T)\)```. Then ```$\mathrm{E}_\theta \phi(T) = \tau(\theta)$``` and ```$\mathrm{Var}_\theta \phi(T) \le \mathrm{Var}_\theta W$``` for all $\theta$; that is, $\phi(T)$ is a uniformly better estimator of $\tau(\theta)$.

**Theorem 7.3.19** If W is a best unbiased estimator of $\tau(\theta)$, then W is unique.

**Theorem 7.3.20** If $\mathrm{E}_\theta W = \tau(\theta)$, W is the best unbiased estimator of $\tau(\theta)$ if and only if W is uncorrelated with all unbiased estimators of 0.

**Theorem 7.3.23** Let T be a complete sufficient statistic for a parameter $\theta$, and let $\phi(T)$ be any estimator based only on T. Then $\phi(T)$ is the unique best unbiased estimator of its expected value.

### 7.3.4 Loss Function Optimality

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
$$
\mathrm{E}(\sum_{i=1}^n g(X_i)) = n(\mathrm{E}g(X_1))
$$
and
$$
\mathrm{Var}(\sum_{i=1}^n g(X_i)) = n(\mathrm{Var}g(X_1))
$$

**Theorem 5.2.6**:
  * $\mathrm{E}\bar{X} = \mu$,
  * $\mathrm{Var}\bar{X} = \sigma^2/n$,
  * $\mathrm{E}S^2 = \sigma^2$.

**Theorem 5.2.7**:

$$
M_{\bar{X}}(t) = [M_X(t/n)]^n
$$

**Example 5.2.8**:Let $X_1, \dots, X_n$ be a random sample from a $n(\mu, \sigma^2)$ population. Then the mgf of the sample mean is

$$
\begin{eqnarray}
M_{\bar{X}}(t) &=& [\exp(\mu t / n + \sigma^2(t/n)^2/2)]^n \\
&=&\exp(\mu t + (\sigma^2/n)t^2/2)
\end{eqnarray}
$$

Thus, $\bar{X}$ has a $n(\mu, \sigma^2/n)$ distribution.

Another simple example is given by a $gamma(\alpha, \beta)$ random sameple. Here, we can also easily derive the distribution of the sample mean. The mgf of the sample mean is

$$
M_{\bar{X}}(t) = [(\frac{1}{1 - \beta(t/n)})^\alpha]^n = (\frac{1}{1-(\beta/n)t)})^{n\alpha}
$$

which we recognize as the mgf of a $gamma(n\alpha, \beta/n)$, the distribution of $\bar{X}$.

**Theorem 5.2.9** If $X$ and $Y$ are independent continuous random variables with pdfs $f_X(x)$ and $f_Y(y)$, then the pdf of $Z = X + Y$ is

$$
f_Z(z) = \int_{-\infty}^{\infty} f_X(w) f_Y(z-w) dw
$$

**Example 5.2.10 (Sum of Cauchy random variables)**

**Theorem 5.2.11** Suppose $X_1, \dots, X_n$ is a random sample from a pdf or pmf ```\(f(x|\theta)\)```, where

$$
f(x|\theta = h(x)c(\theta)\exp{(\sum_{i=1}^k w_i(\theta) t_i(x))}
$$

is a member of an exponential family. Define statistics $T_1, \dots, T_k$ by

$$
T_i(X_1, \dots, X_n) = \sum_{j=1}^n t_i(X_j), \quad i = 1, \dots, k.
$$

If the set $\{(w_1(\theta), w_2(\theta), \dots, w_k(\theta))\}$ contains an open subset of $R^k$, then the distribution of $(T_1, \dots, T_k)$ is an exponential family of the form

$$
d_T(u_1, \dots, u_k|\theta) = H(u_1, \dots, u_k)[c(\theta)]^n \exp{(\sum_{i=1}^k w_i(\theta) u_i)}
$$

**Example 5.2.12 (Sum of Bernoulli random variables)**

## 5.3 Sampling from the Normal Distribution

### 5.3.1 Properties of the Sample Mean and Variance

**Theorem 5.3.1**: Let $X_1, \dots, X_n$ be a random sample from a $n(\mu, \sigma^2)$ distribution, and let $\bar{X}$ and $S^2$. Then

  * $\bar{X}$ and $S^2$ are independent random variables,
  * $\bar{X}$ has a $n(\mu, \sigma^2/n)$ distribution,
  * $(n-1)S^2/\sigma^2$ has a chi squared distribution with $n - 1$ degrees of freedom.

**Lemma 5.3.2**:

  * If $Z$ is a $n(0,1)$ random variable, then $Z^2 \thicksim \chi_1^2$.
  * If $X_1, \dots, X_n$ are independent and $X_i \thicksim \chi_{p_i}^2$, then $X_1 + \dots + X_n \thicksim \chi_{p_1 + \dots + p_n}^2$.  

## 5.4 Order Statistics

**Theorem 5.4.3**:

$$
P(X_{(j)} \le x_i) = \sum_{k=j}^n \binom{n}{k} P_i^k(1-P_i)^{n-k}
$$

and

$$
P(X_{(j)} = x_i) = \sum_{k=j}^n \binom{n}{k} [P_i^k(1-P_i)^{n-k}-P_{i-1}^k(1-P_{i-1})^{n-k}]
$$

**Theorem 5.4.4**:

$$
f_{X_{(j)}}(x) = \frac{n!}{(j-1)!(n-j)!}f_X(X)[F_X(x)]^{j-1}[1-F_X(x)]^{n-j}
$$

**Theorem 5.4.6**:

$$
\begin{eqnarray}
f_{X_{(i)},X_{(j)}}(u,v) &=& \frac{n!}{(i-1)!(j-1-i)!(n-j)!}f_X(u)f_X(v)[F_X(u)]^{i-1} \\
&& \times [F_X(v) - F_X(u)]^{j-1-i}[1-F_X(v)]^{n-j}
\end{eqnarray}
$$

## 5.5 Convergence Concepts

### 5.5.1 Convergence in Probability

**Definition 5.5.1**:

$$
\lim_{ n \rightarrow \infty } P(|X_n - X| \ge \epsilon) = 0
$$

or,

$$
\lim_{ n \rightarrow \infty } P(|X_n - X| < \epsilon) = 1
$$

**Theorem 5.5.2 (Weak Law of Large Numbers)**:

$$
\lim_{ n \rightarrow \infty } P(|\bar{X}_n - \mu| < \epsilon) = 1
$$

### 5.5.2 Almost Sure Convergence

**Definition 5.5.6**:

$$
P(\lim_{ n \rightarrow \infty } |X_n - X| < \epsilon) = 1
$$

**Theorem 5.5.9 (Strong Law of Large Numbers)**:

$$
P(\lim_{ n \rightarrow \infty } |\bar{X}_n - \mu| < \epsilon) = 1
$$

### 5.5.3 Convergence in Distribution

**Definition 5.5.10**:

$$
\lim_{ n \rightarrow \infty } F_{X_n}(x) = F_X(x)
$$

**Theorem 5.5.14 (Central Limit Theorem)**: Let $X_1, X_2, \dots $ be a sequence of iid random variables whose mgfs exist in neighborhood of 0 (that is , $M_{X_i}(t)$ exists for ```\(|t| < h\)```, for some positive $h$). Let $\mathrm{E}X_i = \mu$ and $\mathrm{Var}X_i = \sigma^2 > 0$. (Both $\mu$ and $\sigma^2$ are finite since the mgf exists.) Define $\bar{X_n} = (1/n)\sum_{i=1}^n X_i$. Let $G_n(x)$ denote the cdf of $\sqrt{n}(\bar{X_n}-\mu)/\sigma$. Then, for any $x$, $-\infty < x < \infty$,

$$
\lim_{ n \rightarrow \infty} G_n(x) = \int_{-\infty}^x \frac{1}{\sqrt{2\pi}} e^{-y^2/2} dy
$$


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

Three principles of data reduction:

  * The Sufficiency Principle
  * The Likelihood Principle
  * The Equivariance Principle

## 6.2 The Sufficiency Principle

### 6.2.1 Sufficient Statistics

**Definition 6.2.1**: A statistic $T(X)$ is a sufficient statistic of $\theta$ if the conditional distribution of the sample $X$ given the value of $T(X)$ does not depend on $\theta$.

**Theorem 6.2.2**: If ```\(p(x | \theta)\)``` is the joint pdf or pmf of $X$ and ```\(q(t | \theta)\)``` is the pdf or pmf of $T(X)$, then $T(X)$ is a sufficient statistic for $\theta$ if, for every $x$ in the sample space, the ratio ```\(p(x | \theta)/q(T(X) | \theta)\)``` is constant as a function of $\theta

**Theorem 6.2.6 (Factorization Theorem)**: Let ```\(f(x | \theta)\)``` denote the joint pdf or pmf of a sample $X$. A statistic $T(X)$ is a sufficient statistic for $\theta$ if and only if there exist functions ```\(g(x | \theta)\)``` and $h(x)$ such that, for all sample points $x$ and all parameter points $\theta$,

$$
f(x|\theta) = g(T(x)|\theta)h(x)
$$

### 6.2.2 Minimal Sufficient Statistics


### 6.2.3 Ancillary Statistics

**Definition 6.2.16**: A statistic $S(X)$ whose distribution does not depend on the parameter $\theta$ is called an ancillary statistic.

### 6.2.4 Sufficient, Ancillary, and Complete Statistics

**Example 6.2.20 (Ancillary precision)**

**Theorem 6.2.24 (Basu's Theorem)**: If T(X) is a complete and minimal sufficient statistic is independent of every ancillary statistic.

**Theorem 6.2.25 (Complete statistic in the exponential family)**: Let $X_1, \dots, X_n$ be iid observations from an exponential family with pdf or pmf of the form

$$
f(x|\theta) = h(x)c(\theta)\exp(\sum_{j=1}^k w(\theta_j)t_j(x))
$$

where $\theta = (\theta_1, \dots, \theta_k)$. Then the statistic

$$
T(X) = (\sum_{i=1}^n t_1(X_i), \dots, \sum_{i=1}^n t_k(X_i))
$$

is complete as long as the parameter space $\Theta$ contains an open set in $R^k$.


## 6.3 The Likelihood Principle

## 6.4 The Equivariance Principle


# 7 Point Estimation

## 7.1 Introduction

This chapter is divided into two parts. The first part deals with methods for finding estimators, and the second part deals with evaluating these estimators.

**Definition 7.1.1** A point estimator is any function $W(X_1, \dots, X_x)$ of a sample; that is, any statistic is a point estimator.

## 7.2 Methods of Finding Estimators

### 7.2.1 Method of Moments

### 7.2.2 Maximum Likelihood Estimators

### 7.2.3 Bayes Estimators

### 7.2.4 The EM Algorithm

## 7.3 Methos of Evaluating Estimators

### 7.3.1 Mean Squared Error

**Definition 7.3.1** The mean squared error of an estimator $W$ of a parameter $\theta$ is the function of $\theta$ defined by $\mathrm{E}_\theta(W - \theta)^2$.

$$
\mathrm{E}_\theta(W - \theta)^2 = \mathrm{Var}_\theta W + (\mathrm{Bias}_\theta W)^2
$$

### 7.3.2 Best Unbiased Estimators

**Definition 7.3.7** An estimator ```$W^*$``` is a best unbiased estimator of $\tau(\theta)$ if it satisfies ```$E_\theta W^* = \tau(\theta)$``` for all $\theta$ and, for any other estimator $W$ with $E_\theta W = \tau(\theta)$, we have ```$\mathrm{Var}_\theta W^* \le \mathrm{Var}_\theta W$``` for all $\theta$. ```$W^*$``` is also called a uniform minimum variance unbiased estimator (UMVUE) of $\tau(\theta)$.

**Theorem 7.3.9 (Cramer-Rao Inequality)**: Let $X_1, \dots, X_n$ be a sample with pdf ```$f(x | \theta)$```, and let $W(X) = W(X_1, \dots, X_n)$ be any estimator satisfying

$$
\frac{d}{d\theta} E_{\theta}W(X) = \int_{\chi} \frac{\partial}{\partial \theta} [W(x) f(x|\theta)] dx
$$

and

$$
\mathrm{Var}_\theta W(X) < \infty
$$

Then

$$
\mathrm{Var}_\theta (W(X)) \ge \frac{(\frac{d}{d\theta} \mathrm{E}_\theta W(X))^2}{\mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2)}
$$

**Corollary 7.3.10 (Cramer-Rao Inequality, iid case)** If the assumptions of Theorem 7.3.9 are satisfied and, additionally, if $X_1, \dots, X_n$ are iid with pdf ```\(f(x|\theta)\)```, then

$$
\mathrm{Var}_\theta W(X) \ge \frac{(\frac{d}{d\theta} \mathrm{E}_{\theta}W(X))^2}{n \mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2)}
$$

**Lemma 7.3.11** If ```\(f(x|\theta)\)``` satisfies

$$
\frac{d}{d\theta} \mathrm{E}_\theta (\frac{\partial}{\partial \theta} \log{f(X|\theta)}) = \int \frac{\partial}{\partial \theta} [(\frac{\partial}{\partial \theta} \log{f(x|\theta)})] dx
$$

(true for an exponential family), then

$$
\mathrm{E}_\theta ((\frac{\partial}{\partial \theta} \log{f(X|\theta)})^2) = - \mathrm{E}_\theta(\frac{\partial^2}{\partial \theta^2}\log{f(X|\theta)}).
$$

**Corollary 7.3.15 (Attainment Let $X_1, \dots, X_n$ be iid ```\(f(x|\theta)\)```, where ```\(f(x|theta)\)``` satisfies the conditions of Cramer-Rao Theorem. Let ```\(L(\theta|X)=\prod_{i=1}^n f(x_i|\theta)\)```

### 7.3.3 Sufficiency and Unbiasedness

**Theorem 7.3.17 (Rao-Blackwell)** Let W be any unbiased estimator of $\tau(\theta)$, and let T be a sufficient statistic for $\theta$. Define ```\(\phi(T) = \mathrm{E}(W|T)\)```. Then ```$\mathrm{E}_\theta \phi(T) = \tau(\theta)$``` and ```$\mathrm{Var}_\theta \phi(T) \le \mathrm{Var}_\theta W$``` for all $\theta$; that is, $\phi(T)$ is a uniformly better estimator of $\tau(\theta)$.

**Theorem 7.3.19** If W is a best unbiased estimator of $\tau(\theta)$, then W is unique.

**Theorem 7.3.20** If $\mathrm{E}_\theta W = \tau(\theta)$, W is the best unbiased estimator of $\tau(\theta)$ if and only if W is uncorrelated with all unbiased estimators of 0.

**Theorem 7.3.23** Let T be a complete sufficient statistic for a parameter $\theta$, and let $\phi(T)$ be any estimator based only on T. Then $\phi(T)$ is the unique best unbiased estimator of its expected value.

### 7.3.4 Loss Function Optimality

# 8 Hypothesis Testing

## 8.1 Introduction

**Definition 8.1.1** A hypothesis is a statement about a population parameter.

**Definition 8.1.2** The two complementary hypotheses in a hypothesis testing problem are called null hypothesis and the alternative hypothesis. They are denoted by $H_0$ and $H_1$, respectively.

**Definition 8.1.3** A hypothesis testing procedure or hypothesis test is a rule that specifies:

  * For which sample values the decision is made to accept $H_0$ as true.
  * For which sample values $H_0$ is rejected and $H_1$ is accepted as true.

The subset of the sample space for which $H_0$ will be rejected is called the *rejection region* or *critical region*. The complement of the rejection region is called the *acceptance region*.

## 8.2 Methods of Finding Tests

### 8.2.1 Likelihood Ratio Tests

**Definition 8.2.1** The likelihood ratio test statistic for testing $H_0 : \theta \in \Theta_0$ versus $H_1 : \theta \in \Theta_0^c$ is

$$
\lambda(x) = \frac{\sup L(\theta | x)}{\sup L(\theta | x)}
$$

A likelihood ratio test (LRT) is any test that has a rejection region of the form $\{x: \lambda (x) \le c \}$, where $c$ is any number satisfying $0 \le c \le 1$.


**Example 8.2.2 (Normal LRT)** Let $X_1, \dots, X_n$ be a random sample from a $n(\theta, 1)$ population. Consider testing $H_0 : \theta = \theta_0$ versus $\theta \neq \theta_0$.

$$
\lambda(x) = exp[-n(\bar{x} - \theta_0)^2 / 2]
$$

### 8.2.2 Bayesian Tests

prior distribution -> posterior distribution

### 8.2.3 Union-Intersection and Intersection-Union Tests

**Example 8.2.9 (Acceptance sampling)**

## 8.3 Methods of Evaluating Tests

### 8.3.1 Error Probabilities and the Power Function

Type I Error and Type II 

| | Accept $H_0$ | Reject $H_1$ |
|:-------------:|:--------------:|:--------------:|
| Truth $H_0$ | Correct | Type I Error |
| Truth $H_1$ | Type II Error | Correct |

**Definition 8.3.1** The power function of a hypothesis test with rejection region $R$ is the functiuon of $\theta$ defined by $\beta(\theta) = P_\theta(X \in R)$.

**Example 8.3.3 (Normal power function)** Let $X_1, \dots, X_n$ be a random sample from a $n(\theta, \sigma^2)$ population, $\sigma^2$ known. An LRT of $H_0 : \theta \le \theta_0$ versus $H_1 : \theta > \theta_0$ is a test that rejects $H_0$ if $(\bar{X} - \theta_0) / (\sigma / \sqrt{n}) > c$. The constant $c$ can be any positive number. The power function of this test is

$$
\beta(\theta) = P(Z > c + \frac{\theta_0 - \theta}{\sigma / \sqrt{n}})
$$

**Example 8.3.4 (Coninuation of Example 8.3.3)**

Suppose that we want to have a maximum Type I Error probability of $0.1$, and a maximum Type II Error probability of $0.2$ if $\theta \ge \theta_0 + \sigma$. How to choose $c$ and $n$ to achieve these goals.

Goals: $\beta(\theta_0) = 0.1$ and $\beta(\theta_0 + \sigma) = 0.8$.
  * By choosing  $c = 1.28$, we achieve $\beta(\theta_0) = P(Z > 1.28) =  0.1$
  * By choosing $n=5$, we achieve $\beta(\theta_0 + \sigma) = P(Z > 1.28 - \sqrt{n}) = 0.8$

**Definition 8.3.5** size $\alpha$ test if $\sup_{\theta \in \Theta_0} \beta(\theta) = \alpha$
**Definition 8.3.6** level $\alpha$ test if $\sup_{\theta \in \Theta_0} \beta(\theta) \le \alpha$

**Definition 8.3.9** unbiased power function.

### 8.3.2 Most Powerful Tests

**Definition 8.3.11** uniformly most powerful class(UMP)

**Theorem 8.3.12 (Neyman-Pearson Lemma)** Consider testing $H_0 : \theta = \theta_0$ versus $H_1 : \theta = \theta_1$, where the pdf or pmf corresponding to $\theta_i$ is $f(x | \theta_i), i = 0, 1$, using a test with rejection region $R $that satisfies

$$
x \in R \text{ if } f(x | \theta_1) > k f(x | \theta_0)
$$

and

$$
x \in R^c\text{ if } f(x | \theta_1) < k f(x | \theta_0)
$$

for some $k \ge 0$, and
$$
\alpha = P_{\theta_0}(X \in R).
$$

Then,
  * (Sufficiency) Any test that satisifes these two inequalities is a UMP level $\alpha$ test.
  * (Necessity) If there exists a testing satisfying these two inequalities  with $k > 0$, then every UMP level $\alpha$ test is a size $\alpha$ test and every UMP level $\alpha$ test satisfies except perhpas on a set A satisifying $P_{\theta_0}(X \in A) = P_{\theta_1}(X \in A) = 0$.

**Example 8.3.14 (UMP binomial test)** Let $X \sim binmomial(2, \theta)$. We want to test $H_0 : \theta = \frac{1}{2}$ versus $H_1 : \theta = \frac{3}{4}$.

**Example 8.3.15 (UMP normal test)**

### 8.3.3 Sizes of Union-Intersection and Intersection-Union Tests

### 8.3.4 p-Values

**Definition 8.3.26** A p-value $p(X)$ is a test statistic satisfying $0 \le p(x) \le 1$ for every sample point $x$. Small values of $p(X)$ give evidence that $H_1$ is true. A p-value is valid if, for every $\theta \in \Theta_0$ and every $0 \le \alpha \le 1$,

$$
P_{\theta}(p(X) \le \alpha) \le \alpha
$$

### 8.3.5 Loss Function Optimality

