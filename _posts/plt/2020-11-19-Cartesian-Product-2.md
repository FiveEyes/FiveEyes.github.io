---
layout: post
title: 笛卡尔积 2: 从Generator到Iterator
date: 2020-11-19 22:10:00
categories: Language
---

# 笛卡尔积 2: 从Generator到Iterator

## 背景简述

笛卡尔积是什么,以及为何实现困难,还有黑科技CPP实现,请见第一篇blog: 
  - [笛卡尔积](https://freopen.com/language/2020/08/11/Cartesian-Product.html)
  - [代码实现](https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/cpp/prod.cpp)

第一篇的重点侧重于讲解,如何使用CPP的新特性,来实现这个不确定参数数量和类型的笛卡尔积迭代器ProdIter和笛卡尔积集合ProdSet.

第一篇也提到,如果使用Python会很方便实现. 原因在于: 一是动态类型; 二是Generator.

其实第一篇最后的代码,同时解决了这两个问题:
  - 实现了对任意类型和任意数量的参数,实现了类型安全的ProdIter和ProdSet;
  - 实现了一个笛卡尔积迭代器, ProdIter. 使用效果和Generator一致.
  
但两部分的解决方式杂糅在一起,不容易把看出如何分别解决了这两个问题. 其次,虽然这两个问题都有更好的解决方法,但因为第一篇要同时解决这两个问题,导致选择解决方案时上也受到了限制.

所以这一篇从仅从Generator到Iterator这个角度切入,来说明对于CPP这样没有Generator的语言,在某些特定场景下,非常需要Generator这一特性,如何将其转化成Iterator.

## 简化问题

首先把类型相关的部分剔除.问题简化为,实现一个ProdIter:
  - ProdIter(int dimSize[]), 构造器传入每一个dim的size数组
  - bool next(int output[]), 如果hasNext,返回true,并填充output数组,ooutput[i]代表第i个dim的choice.

```
// 第一维有3种可能{0,1,2}, 第二维有2种可能{0,1}
ProdIter({3,2})

// next()会依次返回6种组合.
while(next(output)) print(output);
// 0 0
// 1 0
// 2 0
// 0 1
// 1 1
// 2 1
```

## ProdIter的实现方式

首先是,针对性的实现这个Cartesian Product Iterator. 方法是在ProdIter中维护一个Current output, 然后考虑如何推导出next output.

比如

```
size = {2,3,4};
cur = {0, 0, 0}, next = {1, 0, 0};
cur = {1, 0, 0}, next = {0, 1, 0};
// ...
cur = {1, 2, 0}, next = {0, 0, 1};
```

仔细观察可知,这是很简单的加法进制,即如果前i位choice都已经是其维度的最后一个item,那么前i位归零,第i+1位加一.

下面就把这段逻辑从原始的代码实现中抽离出来.
```
// clang -std=c++17 -lstdc++ prod.cpp -o prod && ./prod

#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <utility>

using namespace std;

template<typename T>
void print(vector<T>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

struct ProdIter {
    unsigned int N = 0;
    vector<int> cur;
    vector<unsigned int> sz;
    ProdIter(vector<unsigned int>& _sz) : sz(_sz), N(_sz.size()), cur(N) {
        reset();
    }
    ProdIter(vector<unsigned int> _sz) : sz(_sz), N(_sz.size()), cur(N) {
        reset();
    }
    bool next(vector<int>& output) {
        int i = 0;
        while(i < N && sz[i] <= cur[i] + 1) cur[i++] = 0;
        if(i >= N) {
            return false;
        }
        cur[i]++;
        for(int i = 0; i < N; ++i) {
            output[i] = cur[i];
        }
        return true;
    }
    void reset() {
        for(int i = 0; i < N; ++i) cur[i] = sz[i] - 1;
        cur[N-1] = -1;
    }
};

int main() {
    ProdIter iter(vector<unsigned int>({3,4,5}));
    vector<int> output({0,0,0});
    print(output);
    while(iter.next(output)) {
        print(output);
    }
    return 0;
}
```

## 更通用的解决方案

回顾一下刚刚的ProdIter,首先有悖直觉的是生成的组合顺序,是前面的数字每次都在变化,后面的数组更稳定
```
0 0
1 0
0 1
0 1
```
而不是更自然的
```
0 0
0 1
1 0
1 1
```
原因在于,第一篇还有同时兼顾类型问题,使用template时,第一种顺序更方便实现.


为什么第二种顺序更加自然,我们参考一下python的generator实现方式:

```
def prod_iter(s):
    if len(s) == 0:
        yield []
    else :
        for i in range(s[0]):
            for xs in prod_iter(s[1:]):
                yield [i] + xs
                
for x in prod_iter([2,3]):
    print(x)
```

同时借这段代码,来思考一下为什么这个Generator难以转化成Iterator.
  - 这是一个递归式的Generator.
  - Iterator是没办法递归实现.

既然Iterator没办法递归实现,那么一个通用的解决方案呼之欲出: 提前使用递归函数,将所有的组合,即整个笛卡尔积预先存入链表,Iterator只需要遍历链表即可.

但这个方法太简单了...而且浪费了很多内存,假装内存很重要...我们如何实现类似Generator一样generate data on the fly呢.

其实也是一个古老的方式,我们都知道调用函数的基础是函数栈...那么我们只需要手动模拟函数栈,既可实现.

要睡了,打工人还要打工,未完待续!



