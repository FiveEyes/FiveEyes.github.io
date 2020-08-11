---
layout: post
title: "笛卡尔积"
date: 2020-08-11 18:00:00
categories: Language
---

# 笛卡尔积

读Effective Java的Item 45和Item 47的时候,作者讨论了笛卡尔积和幂集的实现方式. 看完之后灵光一现,敲了一个结合两种实现方法的笛卡尔积集合.

## 笛卡尔积是什么

需要实现笛卡尔积的场景常见于枚举配置选项.比如我有一个函数,f(int numOfRequest, string serviceUrl, double timeout);

numOfRequest可以是{10, 20, 30}, serviceUrl可以是{"xx", "yy", "zz"}, timeout可以是{0.7, 0.8, 0.9}

如果我要测试所有的选项,那么一共有27种可能性. 这27种组合的数学名称就叫笛卡尔积.

$$
D_1 = \{ a_1, a_2, \dots \}, D_2 = \{ b_1, \dots \}, \dots, D_n = \{ c_1, \dots \} \\
D_1 \times D_2 \times \dots \times D_n = \{ (a, b, \dots, c) \mid a \in D_1, b \in D_2, \dots, c \in D_n \}
$$

如果有n个集合,那么最终的笛卡尔积的大小是n个集合大小的乘积.

从概念和具体实例上,笛卡尔积都简单易懂.但对于某些编程语言,却很难实现通用的用于生成笛卡尔积的函数.

先从一个很好实现笛卡尔积的编程语言入手,万金油Python

```
D_1 = {10, 20, 30}
D_2 = {"xx", "yy", "zz"}
D_3 = {0.7, 0.8, 0.9}

def prod(*args):
    if len(args) == 1:
        for i in args[0]:
            yield [i]
    else:
        for i in args[0]:
            for vs in prod(*args[1:]):
                yield [i] + vs

for v in prod(D_1, D_2, D_3):
    print(v)
```

Python很容易实现笛卡尔积有两点原因:
  - 动态类型,prod可以传任意数量和任意类型的set
  - 支持generator,就是yield语法.更正式一点,叫做协程(coroutine).
  
反观C++和Java,实现这个功能就有点难受了. 下面我们对比几种实现的方式.

## 几种实现的对比

对于静态类型的传统语言,仅考虑使用场景,prod应该如何实现呢? Item 45提供了两种思路:

### 最符合直觉的写法for-loop

```
for(n : nums)
  for(u : urls)
    for(t : timeout)
      test_f(n, u, t)
```

其实这种写法,从性能上来考虑是效率最高的.
  - 但如果配置的条目(维度)变大,就会出现嵌套for-loop过深的问题.
  - 其次代码不具有复用性,所有需要枚举配置组合的地方,都需要手动复制for-loop.

C++ Solution: 有个很邪恶的解决方法,就是用宏展开来压缩代码.

### Java 8提供的Stream接口

Java 8增加了Collection对Stream的支持,从某种意义上来讲,可以类比成python generator,但两者背后的出发点是完全不同的.

```
nums
  .flatMap(num -> urls.map(url -> [num, url]))
  .flatMap(list -> times.map(time -> list.append(time)))
  .forEach(list -> test_f(list[0], list[1], list[2]));
```

笛卡尔积某种程度上等价于flatMap,同时考虑到Java所有类型都可以擦除变为Object,可以使用flatMap防止缩进过深的现象.
至于效率嘛...就仁者见仁智者见智了,因为这段代码非常依赖于Stream的具体实现. 
对于不同的实现优化,一个很简单的问题都很难回答: 这段代码在执行最后一步forEach时,究竟在内存中维护了多少Tuple(num, url, time)实例?
  - 最简单的实现方式,执行完两次flatMap之后,会产生一个Size为27的Tuple List,然后在forEach每一个tuple.
  - 稍微复杂的实现方式,使用惰性计算,对每次forEach现场回溯生成Tuple,始终只维护一个Tuple实例

很明显,第一种实现方式是不可接受的,因为如果有32个boolean维度,那么将产生一个size为2^32的List.

## 结合Item 47的实现

Effective Java的Item 47讨论了如何隐式实现一个Set<T>的PowerSet.

```
PowerSet {
  Set<T> set;
  PowerSet(Set<T> _set) {
    set = _set;
  }
  int size() {
    return 1 << len(set);
  }
  Set<T> get(int k) {
    ret = {}
    for i in range(len(set)):
      if k % 2 == 1:
        ret.add(set[i])
      k /= 2
    return ret
  }
}

PowerSet powerSet(set);
for i in range(powerSet.size()):
  subset = powerSet.get(i)
  f(subset)
```

这个实现方法由PowerSet类来生成所有的subset,实时生成一个index i的subset,而不是将subsets枚举展开成为一个List.这样实现的好处显而易见:
  - 既避免了占有过多的内存,
  - 其次也保证了效率,
  - 最后没有嵌套多层for-loop.

结合C++17的新特性,和这个powerset的API接口,我们可以使用template实现一个类型安全的笛卡尔积集合,ProdSet.
  - 支持任意数量,任意类型的vector T1, ..., vector Tn 作为构造函数参数.
  - get(int index)支持使用index获取相对应的笛卡尔积元素,返回类型为Tuple<T1, ..., Tn>.
  - get(int index)现场生成对应的返回值.
  
```
struct ProdSet {
    ProdSet(vector<T1> D1, ..., vector<Tn> Dn);
    int size();
    Tuple<T1, ..., Tn> get(int i);
};
```

玩游戏去了,不写了,lol.

具体实现链接: [https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/cpp/prod.cpp](https://github.com/FiveEyes/FiveEyes.github.io/blob/master/assets/code/cpp/prod.cpp)


