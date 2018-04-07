---
layout: post
title: "Y Combinator"
date: 2018-04-07 01:41:00
categories: Math
---


# Y Combinator

## 起因

在学Theory of Computation, 前面讲对角线证明, 然后想到停机问题和哥德尔不完备性定理的证明,其实是构造了一个递归函数... 如果允许使用递归结构的构造,这个函数其实特别简单.
{% highlight C %} 
boolean f() {
  if (f()) return false;
  else return true;
}

void f() {
  if(f() run forever) return;
  else run forever;
}
{% endhighlight %}

然而这个问题一个技术核心就是,不能使用递归结构来构造函数,简单讲就是一个函数必须先定义再调用,不能在定义内部调用自身. 那么Y Combinator就是用来解决这个问题的技术.

因为对哲学兴趣不大,所以纯粹从技术的角度来讲解如何实现Y Combinator.

## 介绍Y Combinator

遵循Y Combinator的惯例,我们使用fact来做演示. 首先写一个最简单版本,既然不允许调用,那么就把自己作为参数传进去.
{% highlight lisp %}
; fact self x = if x == 1 then 1 else fact (x - 1)
; fact0 self x = if x == 1 then 1 else self self (x - 1)
; fact = fact0 fact0
#lang lazy
(define (fact0 self)
  (lambda (x)
    (if (= x 1)
        1
        (* x ((self self) (- x 1))))))

; fix = (f f)
(define fact (fact0 fact0))
(fact 3)
{% endhighlight %}
这个版本倒没什么问题,但我们希望把最后一行的((self self) (- x 1))变成(self (- x 1)). 也就是说我们希望传进来的self是fact而非fact0
{% highlight lisp %}
; fact1 self x = if x == 1 then 1 else self (x - 1)
; fact = fact1 fact
(define (fact1 self)
  (lambda (x)
    (if (= x 1)
        1
        (* x (self (- x 1))))))
{% endhighlight %}

这样做有什么好处呢? 我们看一下这样修改之后的效果
```
fact = fact1 fact
```
换句话说
```
x = f x
```
也就是说fact其实是fact1的不动点,接下来的问题是如何从fact1转换成fact.那么完成这个任务的函数就叫做Y Combintor.
```
fact = Y fact1
```
{% highlight lisp %}
; fix = (fact1 fix)
(define fact2 (fact1 (fact0 fact0)))
(fact2 3)
{% endhighlight %}

## 实现Y Combintor
Y Combintor如何实现,从解题的角度来讲,如果我们可以实现了fact0,那么fact = fact0 fact0. 

我们观察一下fact0的特点.
  * 首先fact0是一个函数到函数的映射.
  * 其次至始至终,他永远只用到了fact0 -> fact这一对映射.

换句话讲,我们可以实现一个假的fact0,只需要让他满足fact0 -> fact这个映射就可以了.现在我们称这个函数叫helper,我们的目标是实现fact = helper helper.

接下来的工作就简单了,
helper的参数是helper, 他需要返回fact, 而刚好fact = helper helper. 然后我们得到了```helper self = self self```. 这个是错的, 因为这个相当于f x = f x.
这时候我们想到了还没用到的fact1, 而刚好fact = fact1 (helper helper). 这次就对了. 其实是我用玄学凑出来的.
所以,最终答案是:
```
helper self = fact1 (self self)
```
这个函数满足了 fact = helper helper的需求,如果仔细观察,会发现这一步其实讲递归嵌套了进去,所以这里需要lazy evaluation才可以正常运行. 否则(self self)会无限递归

那么接下来最简单的一步
```
fact = helper helper
```
{% highlight lisp %}

; Reminder: Here requires lazy evalution.
(define (U f) (f f))
(define (Y f)
  (U (lambda (helper) (f (U helper)))))

(define fact4 (Y fact1))
(fact4 3)

{% endhighlight %}






