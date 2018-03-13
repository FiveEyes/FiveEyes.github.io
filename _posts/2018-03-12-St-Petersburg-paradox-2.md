---
layout: post
title: "圣彼得堡悖论 II"
date: 2018-03-12 23:55:00
categories: Math
---

# St. Petersburg Paradox II

终于开始写后续了... 强化学习开头讲了个老虎机问题,又把这个陈年老题给想起来...

## 先简单回顾下问题

圣彼得堡悖论: 掷硬币,若第一次掷出正面,你就赚2元.若第一次掷出反面,那就要再掷一次,若第二次掷的是正面,你便赚4元.若第二次掷出反面,那就要掷第三次,若第三次掷的是正面,你便赚8元,如此类推,即可能掷一次游戏便结束,也可能反复掷没完没了.问题是:你最多肯付多少钱参加这个游戏?

## Solution

$$ 
\begin{eqnarray*} 
E_{now}(1) &=& 2 \\
E_{now}(N) &=& E_{now}(N-1) + 1 \\ 
E_{win}(1) &=& 1 \\
E_{win}(N) &=& E_{now}(N-1)/2 + E_{win}(N-1) + 1/2 \\
\end{eqnarray*} 
$$

解得:

$$ 
\begin{eqnarray*} E_{now}(N) &=& n + 1 \\
E_{win}(N) &=& (n - 1)(n + 4) / 4 + 1 \\
\end{eqnarray*} 
$$

## Updates

上一篇post已经解出了投n次硬币之后获益的期望,假设每开一局需要消耗c,那么我们要解$\arg_x \min E_{win}(x) > c(x+1)/2$,获得最少的投掷次数已使获利期望为正.

可惜之后写了个模拟程序,发现大多数情况下,投掷x次获益为负.这是因为整个获益的分布方差太大导致的.理论上来讲,这时候只需要求一下中位数就好了,这样50%的概率获利.

然而递推公式并不能求得中位数,目前想到的方法依然需要把整个分布展开.也就是需要2^n项全部计算.

既然不能计算median,那么另一个方案是计算几何平均,对获益取log,然后算数平均,然后再exp回来.但是递推依然不支持,所以还没有验证.

还有一个是算方差,然后套Chebyshev's Inequality, $P(|X-E(X)| \ge b) \le \frac{Var(X)}{b^2}$. 但我怀疑这个界十分松散,根本不管用,毕竟Var(X)轻松彪上十几位数字.

纯理论上的方法既然不管用,那就来点工程暴力学了. 下面一个简单的思路是,通过某种方式把极大的获利在统计时去掉. 

比如我要投掷100次,那么一百次全为反面,会导致当前收益为$2^100$,虽然平均之后他只为平均值贡献了1...坑爹...

如何截断统计100次全为反面的统计,比较简单的一个方法方式就是,规定这一百次投掷中,第50次投掷强制是正面,这样就把51~100次连续反面的可能性全部截断了. 事实证明这个方式非常有效,直接将平均值减半了.

比如平均值是2000,那么截断之后平均值变成了1000.简单讲50%的概率1000,50%的概率3000.

### Implementation

注意到这个递推公式里面有两个常量 $E_{now}(1)$和$E_{win}(1)$. 其实我们可以把他们扩展变量用了从任意中间状态推导至$k$次投币之后. 改进之后的公式:

$$ 
\begin{eqnarray*} 
E_{now}(0) &=& n \ 
E_{now}(k) &=& E_{now}(k-1) + 1 \ 
E_{win}(0) &=& w \ 
E_{win}(k) &=& E_{now}(k-1)/2 + E_{win}(k-1) + 1/2 \ 
\end{eqnarray*} 
$$
解得:
$$ 
\begin{eqnarray*} E_{now}(k) &=& k + n \ 
E_{win}(k) &=& k(k + 1 + 2n) / 4 + w \ 
\end{eqnarray*} 
$$

这个扩展之后,我们不禁可以加入一个强制,而且可以加入任意多位置的强制
{% highlight python %} 
def solve(now, win, k):
    return k + now, win + k * (k + 1 + 2 * now) / 4

def solve1(now, win):
    return now + 1, win + (1 + now) / 2

def solveN(n):
    return solve(1, 0, n)

def win(now, win):
    return 2 * now, win

def lose(now, win):
    return 2, win + now + 1

def mustWinSeq(n, seq):
    Enow = 1.0
    Ewin = 0.0
    cur = 0
    for i in seq:
        if i - 1 > cur:
            Enow, Ewin = solve(Enow, Ewin, i - 1 - cur)
        Enow, Ewin = win(Enow, Ewin)
        cur = i
    Enow, Ewin = solve(Enow, Ewin, n - cur)
    return Enow, Ewin

def measureImprove(n, seq):
    retNow, retWin = solveN(n)
    retNow, retWin = lose(retNow, retWin)
    
    Enow, Ewin = mustWinSeq(n, seq)
    Enow, Ewin = lose(Enow, Ewin)
    print("solveN:", retWin)
    print("mustWinSeq:", Ewin)
    p = 0.5**len(seq)
    improve = retWin - (retWin - p*Ewin) / (1-p)
    retWin -= improve
    return retWin, improve, 1-p
    
measureImprove(1000,[500])
# solveN: 251752.0
# mustWinSeq: 376750.5
# (126753.5, 124998.5, 0.5)
{% endhighlight %}

可以看到投掷1000次,获益期望本来是251752, 现在是1/2的概率获益126753.5, 1/2的概率获益376750.5
