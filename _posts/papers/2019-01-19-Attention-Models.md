---
layout: post
title: "Attention Models"
date: 2019-01-19 22:22:00
categories: Learning
---

# Attention Models

## Papers

Neural Machine Translation [https://arxiv.org/abs/1409.0473](https://arxiv.org/abs/1409.0473)

Effective Approaches to Attention-based Neural Machine Translation [https://arxiv.org/abs/1508.04025](https://arxiv.org/abs/1508.04025)

Convolutional Sequence to Sequence Learning [https://arxiv.org/abs/1705.03122](https://arxiv.org/abs/1705.03122)

Attention Is All You Need [https://arxiv.org/abs/1706.03762](https://arxiv.org/abs/1706.03762)

## Neural Machine Translation

总结下要点...首先,研究的问题是Seq2Seq. ```$X = \{ x_1, \dots, x_n \}, Y = \{ y_1, \dots, y_m \}$```. 
  1. Attention机制在生成每个$y_i$的时候,对于每个$y_i$都会有自己独自的一个上下文向量(context vector) $c_i$, ```$p(y_i | X) = g(y_{i-1}, s_i, c_i)$```. $s_i$是生成Y时RNN的hidden state vector.
  2. $c_i$是通过计算attention,然后直接将RNN中间状态按attention的比例累加得到的, $c_i = \sum_j \alpha_{ij} h_j$. 这里的$h_j$是在X上的用bi-RNN生成出来的.
  3. $\alpha_{ij} = \frac{\exp(e_{ij})}{\sum_k \exp(e_{ik})}, e_{ij} = score(s_{i-1}, h_j)$. 最后的$score$是一个神经网络.

## Effective Approaches to Attention-based Neural Machine Translation

这篇就是对上篇的小改进, 讲了两个, global attention和local attention. 第一个区别是不再区分两种不同的hidden state, s和h, 因为他把X和Y整合成一个字符串$X<eos>Y$. 走X的时候没有输出, 遇到$<eos>$开始输出预测的$y_1, \dots, y_m$.

global attention就是模型上的魔改...
1. ```$p(y_t | X) = softmax(W_s \hat{h}_t)$```, 这里$y_t$是来自一个被attention修正过的hidden state.
2. $\hat{h}_t = tanh(W_c[c_t;h_t])$, 这里的$h_t$是来自RNN的原始hidden state, $c_t$是上文context vector,但是求法不同.
3. $\alpha_{ij} = \frac{\exp(e_{ij})}{\sum_k \exp(e_{ik})}, e_{ij} = score(h_i, h_j)$.
4. score函数,作者实验了三种:
  * $h_t^T h_s$
  * $h_t^T W_a h_s$
  * $v_a^T tanh(W_a[h_t; h_s])$

local attention就是对gloabl attention的魔改. 整个大流程是一样的,区别就是求$\alpha_{ij}$的时候,$j$的范围不再是$[1,n]$,而是$[p_t-D,p_t+D]$.$D$是超参, $p_t$可以硬设置,也可以丢进去学习,计算函数是,$p_t = S \times sigmoid(v_p^T tanh(W_p h_t))$.

## ConvS2S

## Transformer
