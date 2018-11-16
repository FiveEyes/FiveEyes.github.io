---
layout: post
title: "Capsule Network"
date: 2018-11-16 15:03:00
categories: Learning
---

# Capsule Network

## Paper

[Dynamic Routing Between Capsules](https://arxiv.org/abs/1710.09829)

### Ideas

The output of capsule is a vector, instead of a scaler. Vectors can carry more infomation, and each dimensions is interpretable.

The length of the vector represents the probablility.
  * squash function: short vectors get shrunk to almost zero length, and long vectors get shrunk to a length slightly below 1.

High level features computed by routing algorithm, instead of using max-pooling, because max-pooling loses information.

**Routing algorithm**
  * low layer vector times a parametric matrix to get next layer vector
  * the relations between two layer vectors are weighted.
  * similar to K-means to update the weight.
  * backward to update the matrix.

### Implementation

[CapsNet by pytorch](https://github.com/FiveEyes/ml-notebook/blob/master/capsnet/capsnet.py)

## Paper

[Matrix capsules with EM routing](https://openreview.net/pdf?id=HJWLfGWRb)

### Ideas


