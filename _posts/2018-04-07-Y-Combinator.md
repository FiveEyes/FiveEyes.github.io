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

这里纯粹从技术的角度来讲解如何实现Y Combinator.

## 介绍Y Combinator

遵循Y Combinator的惯例,我们使用fact来做演示. 首先写一个最简单版本,既然不允许调用,那么就把自己作为参数传进去.
{% highlight Racket %}
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
{% highlight Racket %}
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
也就是说fact其实是fact1的不动点,接下来的问题是如何从fact1转换成fact.那么完成这个任务的函数就叫做Y Combinator.
```
fact = Y fact1
```

## 实现Y Combinator
Y Combinator如何实现,从解题的角度来讲,如果我们可以实现了```fact0```,那么```fact = fact0 fact0```. 

我们观察一下fact0的特点.
  * 首先, fact0是一个函数到函数的映射.
  * 其次, 至始至终, 他永远只用到了```fact0 -> fact```这一对映射.

换句话讲,我们可以实现一个假的```fact0```,只需要让他满足```fact0 -> fact```这个映射就可以了.现在我们称这个函数叫```helper```,我们的目标是实现```fact = helper helper```.

接下来的工作就简单了,
```helper```的参数是```helper```, 他需要返回```fact```, 而刚好```fact = helper helper```. 然后我们得到了```helper self = self self```. 这个是错的, 因为这个相当于```f x = f x```.

这时候我们发现题目里还有一个叫```fact1```的没有用到, 而刚好```fact = fact1 (helper helper)```. 这次终于对了,其实是我用玄学凑出来的,2333.

所以,最终答案是:
```
helper self = fact1 (self self)
```
这个函数满足了```fact = helper helper```的需求,如果仔细观察,会发现这一步其实讲递归嵌套了进去,所以这里需要lazy evaluation才可以正常运行. 否则```(self self)```会无限递归

那么接下来最简单的一步
```
fact = helper helper
```

最终代码:
{% highlight Racket %}
#lang lazy
; Reminder: Here requires lazy evalution.
;(define (U f) (f f))
;(define (Y f)
;  (U (lambda (helper) (f (U helper)))))

(define (fact1 self)
  (lambda (x)
    (if (= x 1)
        1
        (* x (self (- x 1))))))

(define (Y f)
  (define (helper self) (f (self self)))
  (helper helper))

(define fact (Y fact1))
(fact 3)
{% endhighlight %}

## 停机问题

明白了如何实现Y Combinator,稍微讲一下它和停机问题的关系. 因为哥德尔不完备定理和停机问题是等价的,所以就不区别讲.

图灵机$M$和输入$x$. $M(x)$有可能终止,也有可能永远运行. 对于一对<M,x>是否可以终止,是不可判定的(undecidable). 换句话讲不存在图灵机$H$,对输入$<M,x>$,可以判定$M(x)$是否halt.

证明的核心想法很简单
{% highlight C %} 
void f() {
  if(f() run forever) return;
  else run forever;
}
{% endhighlight %}
这里可以看到$f()$既不可以终止,也不可以永远运行.

证明的思路是采用反证法,我们假设存在$H$,然后使用$H$构造出这个函数$f()$,产生矛盾.

我们首先定义一个图灵机$G(<M, x>)$,这个函数相当于前文的fact1.
```
G(<M,x>) {
  if M(x) halts {
    run forever;
  }
}
```

接着定义一个$Helper$,直接拷贝过来
```
Helper(M) {
  G(<M,M>)
}
```
最终得到我们的目标F
```
F = Helper(Helper)
```
可以看到$<Helper, Helper>$是不可判定的.
如果$Helper(Helper)$ halts, 则说明$G(<helper,helper>)$ halts, 然后说明$Helper(helper)$ runs forever, 矛盾.

这里的证明的重点是用来讲解Y Combinator与停机问题的关系. 我们还可以将G和Helper合并在一起,获得更简洁的证明.
