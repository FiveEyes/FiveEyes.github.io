---
layout: post
title: "Airbnb经典论文: Real-time Personalization using Embeddings for Search Ranking at Airbnb"
date: 2020-09-08 17:15:00
categories: Learning
---

# Real-time Personalization using Embeddings for Search Ranking at Airbnb

本来4天长假,还想做点什么... 然而只读了半篇Paper,看了好几天电影和电视剧,韩剧恶之花还挺不错的...(大雾

这篇是Airbnb在KDD'18 Best Paper, 简单清晰, 适合阅读.

Link:
  - [KDD2018](https://www.kdd.org/kdd2018/accepted-papers/view/real-time-personalization-using-embeddings-for-search-ranking-at-airbnb)
  - [知乎讲解](https://zhuanlan.zhihu.com/p/56128664)

Airbnb的Embedding经典论文. 讲给定用户的点击序列,如果做listing(房源) embedding. 主要的想法对点击序列里面的listing做skip-gram word embedding.

这篇论文其实是分了两部分.
  - 前一部分,讨论了怎么做listing(房源) embedding. 
  - 后一部分,讨论了怎么做user's long-term intersets embedding. 貌似前半部分更有名一些.

# 3 Methodology

## 3.1 List Embeddings

对房源的embedding. 每个click session是一个listing sequence, click session可以分成两类:
  - booked sessions. 看了看订房了
  - exploratory sessions. 看了看就跑了

对于这个特定场景提出了一些改进:
  - Negative sampling: word embedding的基本操作, 取一些随机序列来作为负样本.
  - Booked Listing as Global Context: 对点击序列中的所有房间, 最终预订的房间,始终出现在他的context里面.
  - Adapting Training for Congregated Search: 如果Negative sampling是随机取样的话,可能会随机分散到不同的城市, 这样很容易从地理位置就区分正负样本,从而不能训练出有效的embedding. 改进方法是,在同一个城市随机生成负样本.
  - Cold start listing embeddings: 新上架的房间,需要一个初始化的embedding,方法是取几个地理位置靠近的,特征一致的几个房间,取平均.
  
 ## 3.2 User-type & Listing-type Embeddings
 
 3.1部分也可以理解成是user's short-term interests embedding,即当下in-session personalization. 长期而言,用户的行为是cross-market的,比如说,我去西雅图旅游之后,以后出去旅游很可能不会再去西雅图了.
 
 对用户的embedding,存在数据稀疏的问题:
   - 1 booked session占比例非常少.
   - 2 很多用户只订过一次房, 比如我...
   - 3 很多房间被订的次数少于5-10次...
   - 4 同一用户的相邻两次booked session,时间间隔太长,用户的喜好可能以及发生了偏移,比如用户更富了,选的房子价格更高了.
   
因此我们手工设计feature dims,把用户和房源映射到特征空间. 然后再将两个特征空间中的users和listings embed到同一个向量空间. 

一个直观的解释是, user type和listing type是两种不同语言,我们有一些这两种语言相似单词对(user/listing type pair from booked session), 和反义单词对(booked but rejected by host pair),然后我们要把这两种语言embed到一个同一个词义空间中,这样给定任意来自user type的单词可以翻译成listing type的单词,或者求listing type语言中词义相近的单词.

训练方法就是让相似的尽可能近,相反的尽可能远.

感觉这部分和word2vec没啥相似的...

# 4 Experiments

未完待续

## 4.1 Training Listing Embeddings

## 4.2 Offline Evaluation of Listing Embedding

## 4.3 Similar Listings using Embeddings

## 4.4 Real time personalization in Search Ranking using Embeddings
