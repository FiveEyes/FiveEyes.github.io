---
layout: post
title: "Deep Learning: Chapter 10"
date: 2017-09-16 12:30:00
categories: Learning
---

# 10 Sequence Modeling: Recurrent and Recursive Nets

## 10.1 Unfolding Computational Graphs

$$
h^{(t)} = f(h^{t-1},x^{t};\theta)
$$

## 10.2 Recurrent Neural Networks

back-propagation through time(BPTT)

### 10.2.1 Teacher Forcing and Networks with Output Recurrence

### 10.2.2 Computing the Gradient in Recurrent Neural Network

## 10.5 Deep Recurrent Network

Three blocks:
  * from the input to the hidden state,
  * from the previous hidden state to the next hidden state, and
  * from the hidden state to the output

## 10.6 Recursive Neural Networks

## 10.7 The Challenge of Long-Term Dependencies

vanish or explode

## 10.8 Echo State Networks

## 10.9 Leaky Units and Other Strategies for Multiple Time Scales

### 10.9.1 Adding Skip Connections through Time

### 10.9.2 Leaky Units and a Spectrum of Different Time Scales

### 10.9.3 Removing Connections

## 10.10 The Long Short-Term Memory and Other Gated RNNs

### 10.10.1 LSTM

### 10.10.2 Other Gated RNNs

## 10.11 Optimization for Long-Term Dependencies

### 10.11.1 Clipping Gradients

### 10.11.2 Regularizing to Encourage Information Flow

### 10.12 Explicit Memory

working memory

memory network

neural Turing machine [https://arxiv.org/abs/1410.5401](https://arxiv.org/abs/1410.5401)

It is difficult to optimize functions that produce exact, integer addresses. To alleviate this problem, NTMs actually read to or write from many memory cells simultaneously. To read, they take a weighted of many cells. To write, they modify multiple cells by different amounts. The coefficients for these operations are chosen to be focused on a small number of cells.

These memory cells are typically augmented to contain a vector. There are two reasons,
  * increasing cost of accessing a memory cell.
  * allow for content-based addressing.













