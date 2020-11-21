---
layout: post
title: "笛卡尔积 2: 从Generator到Iterator"
date: 2020-11-19 22:10:00
categories: Language
---

# 笛卡尔积 2: 从Generator到Iterator

## 背景简述

笛卡尔积是什么,以及为何实现困难,还有黑科技CPP实现,请见第一篇blog: 
  - [笛卡尔积](https://freopen.com/language/2020/08/11/Cartesian-Product.html)
  - [代码实现](https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/cpp/prod.cpp)

第一篇的重点侧重于讲解如何使用CPP的新特性,来实现这个不确定参数数量和类型的笛卡尔积迭代器ProdIter和笛卡尔积集合ProdSet.

如果使用Python, ProdIter会很方便实现. 这是因为:
  - 1, python是动态类型;
  - 2, python有Generator.

其实第一篇最后的代码,同时解决了这两个问题:
  - 实现了对任意类型和任意数量的参数,实现了类型安全的ProdIter和ProdSet;
  - 实现了一个笛卡尔积迭代器, ProdIter. 使用效果和Generator一致.
  
但由于这两个问题的解决方法相辅相成,所以不容易单独分离出这两个问题的解决方案. 并且,对于每个问题都有更好的解决方法,但因为第一篇要同时解决这两个问题,导致选择解决方案上也受到了限制.

所以这一篇仅从Generator到Iterator这个角度切入,来说明对于CPP这样没有Generator的语言,在某些特定场景下,非常需要Generator这一特性,如何将其转化成Iterator.

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

第一篇非常具有针对性的实现这个Cartesian Product Iterator. 方法是在ProdIter中维护一个current output, 然后考虑如何推导出next output.

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
    ProdIter(const vector<unsigned int>& _sz) : sz(_sz), N(_sz.size()), cur(N) {
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
    vector<unsigned int> dimSize({2,3,4});
    ProdIter iter(dimSize);
    vector<int> output(dimSize.size());
    while(iter.next(output)) {
        print(output);
    }
    return 0;
}
```

## 更通用的解决方案

回顾一下刚刚的ProdIter,首先是有悖直觉的组合顺序: 前面的数字每次都在变化,后面的数组更稳定,
```
0 0
1 0
0 1
1 1
```
而不是更自然的
```
0 0
0 1
1 0
1 1
```
这是因为第一篇还需要同时兼顾类型问题,而在使用template解决类型问题时,第一种顺序更方便实现.

对于第二种更加自然的顺序,我们参考一下使用python的generator实现方式:
```
def prod_iter(s):
    if len(s) == 0:
        yield []
    else:
        for x in range(s[0]):
            for xs in prod_iter(s[1:]):
                yield [x] + xs
                
for x in prod_iter([2,3]):
    print(x)
```

同时通过这段代码,可以明细看出为什么这个Generator难以转化成Iterator.
  - 这是一个递归式的Generator.
  - Iterator没办法递归实现.

既然Iterator没办法递归实现,那么一个通用的解决方案呼之欲出: 提前使用递归函数,将所有的组合,即整个笛卡尔积预先存入链表,Iterator只需要遍历链表即可.

但这个方法太简单了...而且浪费了很多内存,假装内存很重要...我们如何实现类似Generator一样即时生成呢.

其实也是一个古老的方式,我们都知道调用函数的基础是函数栈...那么我们只需要手动模拟函数栈,既可实现.

如果想使用CPP实现协程,那会很麻烦:
  - 每个协程都有自己的函数栈.
  - yield和resume的时候需要切换现场,切换函数栈和寄存器.
  
C++20貌似已经提供协程,我一度认为C++没办法实现...主要理由是C++的函数栈是hardcoded的,没办法做到切换函数栈,看了一下新特性的简要,切换函数栈可以直接复制替换...

这也让我重新思考了一下这个问题,想了几种思路,最终定稿了一版,正在尝试使用宏来避免手动添加lable和跳转.
  - 最初的思路是完整的模拟函数栈,参数,返回值,局部变量和程序计数器PC,全部都push入函数栈.
  - 后来发现没必要,我们依然可以尽可能多的利用宿主语言的语法,来减少模拟.
  - 我们对定义一个Generator class,局部变量定义在class里,存在堆上,函数调用依然可以基于CPP自身的栈.
  - 因为每个Generator都有自己的局部变量,所以调用Generator时,相当于切换了栈空间.

这段代码的本质依然是栈模拟,虽然可能看不出来...

这段实现的依然需要我们手动设置代码里的labels,有一点写汇编的感觉,小窍门就是把label设成行号就好了.
  - 有可能通过宏来实现自动label和jump,正在思考怎么实现...

```
// clang -std=c++17 -lstdc++ prod.cpp -o prod && ./prod

#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <vector>

using namespace std;

template<typename S>
class Source;

template<typename S>
class Source : public std::enable_shared_from_this<Source<S>> {
public:
	virtual ~Source() {}
    virtual bool operator()(S& output) = 0;
    bool next(S& output) {
        return (*this)(output);
    }
    shared_ptr<Source<S>> getPtr() { return this->shared_from_this(); }
};

/*
L: def prod_iter(s):
0:   if len(s) == 0:
1:     yield []
2:   else:
3:     x = 0
4:     while true:
5:       xs = []
6:       iter = generator.create(prod_iter(s[1:]))
7:       while true:
8:         xs, isAlive = iter.resume()
9:         if !isAlive:
10           break
11         yield [x] + xs
12       x += 1
13       if x >= s[0]:
14         break
-1   return
*/
class ProdGen : public Source<vector<int> > {
public:
    int state;
    vector<unsigned int> s;
    int x;
    shared_ptr<Source<vector<int> > > iter;
    ProdGen(const vector<unsigned int>& _s) : s(_s), state(0) {}
    bool operator()(vector<int>& output) {
        while(1) {
            switch(state) {
            case 0: {
                if(s.size() == 0) {
                    output.clear();
                    state = -1;
                    return true;
                } else {
                    x = 0;
                    state = 5;
                    break;
                }
            }
            case 5: {
                vector<unsigned int> ss(s.begin() + 1, s.end());
                iter = make_shared<ProdGen>(ss);
                state = 7;
                break;
            }
            case 7: {
                vector<int> xs;
                bool isLive = iter->next(xs);
                if(isLive) {
                    output.clear();
                    output.push_back(x);
                    output.insert(output.end(), xs.begin(), xs.end());
                    state = 7;
                    return true;
                } else {
                    state = 12;
                    break;
                }
            }
            case 12: {
                x += 1;
                if(x >= s[0]) {
                    state = -1;
                    break;
                } else {
                    state = 5;
                    break;
                }
            }
            case -1: {
                return false;
            }
            }
        }
    }
};

template<typename T>
void print(vector<T>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<unsigned int> dimSize({2,3,4});
    vector<int> output(dimSize.size());Sure
    ProdGen prodGen(dimSize);
    while(prodGen(output)) {
        print(output);
    }
    return 0;
}
```

再来一个汉诺塔来练习一下
```
/*
def hanoi(n, a, b, c):
    if n == 1:
        s = str(a) +  ' --> ' + str(c)
        yield s
    else:
        for s in hanoi(n - 1, a, c, b):
            yield s
        for s in hanoi(1    , a, b, c):
            yield s
        for s in hanoi(n - 1, b, a, c):
            yield s
*/
#define YIELD_BEGIN while(1) { switch(state) {
#define YIELD_END }}
#define YIELD_GOTO(x) {state=(x); break;}
#define YIELD_LAST() {state=-1; return true;}
class MacroHanoiGen : public Source<string> {
public:
    int state;
    int n;
    string a, b, c;
    shared_ptr<Source<string> > iter;
    MacroHanoiGen(int _n, string _a, string _b, string _c) : n(_n), a(_a), b(_b), c(_c), state(0) {}
    bool operator()(string& output) {
    YIELD_BEGIN
    case 0: {
        if(n == 1) {
            output = a + " --> " + c;
            YIELD_LAST();
        } else {
            iter = make_shared<MacroHanoiGen>(n - 1, a, c, b);
            YIELD_GOTO(2);
        }
    }
    case 2: {
        bool isLive = iter->next(output);
        if(isLive) {
            return true;
        } else {
            iter = make_shared<MacroHanoiGen>(1, a, b, c);
            YIELD_GOTO(4);
        }
    }
    case 4: {
        bool isLive = iter->next(output);
        if(isLive) {
            return true;
        } else {
            iter = make_shared<MacroHanoiGen>(n - 1, b, a, c);
            YIELD_GOTO(6);
        }
    }
    case 6: {
        bool isLive = iter->next(output);
        if(isLive) {
            return true;
        } else {
            YIELD_GOTO(-1);
        }  
    }        
    case -1: {
        return false;
    }
    YIELD_END
    }
};


int main() {
    MacroHanoiGen hanoiGen(3, "A", "B", "C");
    while(hanoiGen(s)) {
        cout << s << endl;
    }
    return 0;
}
```

宏已经写好了,这篇太长了,另开一篇.

