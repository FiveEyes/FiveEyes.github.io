---
layout: post
title: "Deep Learning: Chapter 9"
date: 2017-08-09 14:15:00
categories: Learning
---

# 9 Convolutional Networks

## 9.1 The Convolution Operation

## 9.2 Motivation

Three important ideas:
  * sparse interactions
  * parameter sharing
  * equivariant representations


## 9.3 Pooling

## 9.4 Convolution and Pooling as an Infinitely Strong Prior

One key insight is that ...

Another key insight is that ...

## 9.5 Variants of the Basic Convolution Function

**stride**

**padding**
  * valid
  * same
  * full 

locally connected layer(unshared convolution)

Tiled convolution

There three operations - convolution, backprop from output to weight, and backprop from output to inputs - are sufficient to compute all the gradients needed to train any depth of feedforward convolutional network.

## 9.6 Structured Outputs



## 9.7 Data Types



## 9.8 Efficient Convolution Algorithms


## 9.9 Random or Unsupervised Features

There are three basic strategies for obtaining convolution kernels without supervised training.
  * initialize them randomly
  * unsupervised learning approach
  * intermediate approach

## 9.10 The Neuroscientifice Basis for Convolutional Networks

## 9.11 Convolutional Networks and the History of Deep Learning