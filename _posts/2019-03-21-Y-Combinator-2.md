---
layout: post
title: "Y Combinator 精简版"
date: 2019-03-21 22:00:00
categories: Math
---


# Y Combinator

回头看了一下去年写的Y Combinator,太罗嗦了(基友看不懂),更像是解题思路讲解.重新写个抓重点的精简(民科)版.

## 问题描述

我们要解决的问题很简单: 定义函数的时候不能在函数体内调用自己,在这种情况下如何实现递归函数. 比如我们要实现一个递归版的阶乘函数fact(n) = n!.

## 解决方案1

很直接的一个思路,既然不让调用自己,那就函数的参数再加一项--函数自己--需要调用自身的时候,就调用传进来的函数.这个实现我们就叫fact0.
```
fact(n) = fact0(fact0,n)
```
## 问题描述2

刚刚这个解决方案太简单粗暴了,而且没有哲理性.我们为了更有哲理(难度),设想我们实现了这么一个函数fact1.它满足以下的性质:
```
fact(n) = fact1(fact,n)
```
fact1和fact0的不同之处在于,fact0的参数是fact0自身,而fact1的参数是fact--而fact的定义需要用到fact1.所以对fact1来讲,依然有这一层递归引用的关系.

那么如何用fact1实现fact,实现这个过程的函数就叫Y Combinator:
```
fact = Y(fact1)
```
搞这么复杂的哲理性体现在哪里呢,如果我们考虑到Partial application,那么
```
fact = fact1(fact)
```
所以fact是fact1的不动点,Y含义是求解fact1不动点的函数.

讲了这么多,最后的问题还是如何实现这个Y Combinator.

## 解决方案2

实现Y Combinator的思路很简单,就是使用fact1构造出fact0,然后fact = fact0(fact0),大功告成.

实现方法,具体想法细节参见第一篇,以及这里需要lazy evaluation.

```
fact0(f0) = fact1(f0(f0))
```

最终Y的实现:

```
Y(fact1) =
  def fact0(f0) = fact1(f0(f0))
  return fact0(fact0)
```

搞定.
