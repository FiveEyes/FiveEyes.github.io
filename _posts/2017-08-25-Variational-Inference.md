[http://blog.huajh7.com/2013/03/06/variational-bayes/](http://blog.huajh7.com/2013/03/06/variational-bayes/)

PRML Chapter 10

MLAPP Chapter 21

## 背景知识

**熵**

$$
H[p] = - \int p(x) \ln{p(x)} dx
$$

**相对熵, KL散度**

$$
KL(q || p) = - \int q(x) \ln{\frac{q(x)}{p(x)}} dx
$$

## 问题
已知数据模型和数据集 $ X = \\{ x_1, \dots, x_n \\} $, 模型的参数 $Z = \\{ z_1, \dots, z_m \\} $ 未知, 我们希望使用后验分布$p(Z|X)$.
  * 一是$p(Z|X)$可能非常难求,而且不好做后续的处理. 
  * 二是$p(Z,X)$可能会很好求.

## 解决方案
求解一个近似p(Z|X)的分布q(Z), q(Z)取自一个方便处理的分布家族,比如指数家族.使用q(Z)代替p(Z|X).

**两点问题**:
  * 如何比较两个分布是否相近. 相对熵.
  * 如何从分布家族中选取一个接近p(Z|X). 取相对熵最小的分布,转化成最优解问题.
$$
\min_{Z}{KL(q(Z)||p(Z|X))}
$$

## 最优化问题

先对目标函数做一些转换,这个转换把最优化问题从$p(Z|X)$转换到$p(Z,X)$上.

$$
\begin{eqnarray}
KL(q(Z)||p(Z|X)) &=& \int q(Z) \ln \frac{q(Z)}{p(Z|X)} dZ \\
&=& \int q(Z) \ln \frac{q(Z)p(X)}{p(Z,X)} dZ \\
&=& \int q(Z) \ln \frac{q(Z)}{p(Z,X)} dZ + \int q(Z) \ln p(X) dZ \\
&=& \int q(Z) \ln \frac{q(Z)}{p(Z,X)} dZ + \ln p(X) \\
\end{eqnarray}
$$

让 $L(q) = \int q(Z) \ln \frac{p(Z,X)}{q(Z)} dZ$, 通过上面的式子我们可以得到

$$
\ln p(X) = KL(q(Z)||p(Z|X)) + L(q)
$$

因为 $\ln p(X)$ 是常数, 所以$\min KL(q(Z)||p(Z|X))$,可以转化成$\max L(q)$.

## 分解q(Z)

这里做一个假定, 假定q分布是对于Z可分解的, 即
$$
q(Z) = \prod_{i=1}^{M} q_i(z_i)
$$
这里每个$q_i$都可以是不同形式的函数.

然后这里的做法是, 对每个$i$, 固定住其他变量, 对$q_i$求最优值. 然后循环到收敛.

先来看一下分解之后的$L(q)$, 这里用q_j表示q_j(z_j)
$$
\begin{eqnarray}
L(q) &=& \int q(Z) \ln \frac{p(Z,X)}{q(Z)} dZ \\
&=& \int \prod_{j=1}^{M} q_j \ln \frac{p(Z,X)}{\prod_{j=1}^{M} q_j} dZ \\
&=& \int \prod_{j=1}^{M} q_j ( \ln p(Z,X) - \sum_{k=1}^{M} \ln q_k) dZ \\
\end{eqnarray}
$$
到了这里之后,我们开始只考虑单个$q_j$对$L(q)$的影响,即把非$q_j$项都先积分,最后留下$q_j$.
$$
\begin{eqnarray}
L(q) &=& \int \prod_{j=1}^{M} q_j ( \ln p(Z,X) - \sum_{k=1}^{M} \ln q_k) dZ \\
&=& \int q_j \{ \int \prod_{i \neq j} q_i ( \ln p(Z,X) - \sum_{k=1}^{M} \ln q_k ) dz_i \} dz_j\\
&=& \int q_j \{ \int \prod_{i \neq j} q_i \ln p(Z,X) dz_i \} dz_j\\
&& - \int \prod_i q_i \sum_k \ln q_k dz_i \\
\end{eqnarray}
$$
我们先定义一个新分布 $p_j(z_j)$, 满足
$$
\begin{eqnarray}
\ln p_j(z_j) &=& \int \prod_{i \neq j} q_i \ln p(Z,X) dz_i + const \\
&=& \mathrm{E}_{i \neq j} [\ln p(Z, X)] + const
\end{eqnarray}
$$
这里的const主要为了把$\int p_j dz_j$凑成1,是normalization,不需要显式考虑.

其次注意到 $\int q_i dz_i = 1$, 可以得到
$$
\int \prod_i q_i \ln q_j dZ = \int q_j \ln q_j dz_j
$$ 
代入原式得到
$$
\begin{eqnarray}
L(q) &=& \int q_j \ln p_j dz_j - \sum_i \int q_i \ln q_i dz_i \\
&=& \int q_j \ln p_j dz_j - \int q_j \ln q_j dz_j + \sum_{i \neq j} \int q_i \ln q_i dz_i \\
&=& \int q_j \ln p_j dz_j - \int q_j \ln q_j dz_j + const \\
&=& \int q_j (\ln p_j - \ln q_j) dz_j + const \\
&=& \int q_j \ln \frac{p_j}{q_j} dz_j + const \\
&=& -KL(q_j || p_j) + const \\
\end{eqnarray}
$$
分解分布之后,$\sum_{i \neq j} \int q_i \ln q_i dz_i$这一项相对于z_j是const.

## 最大化$L(q)$
我们成功得到 $L(q) = -KL(q_j || p_j) + const$, 那么最大化$L(q)$就等于最小化$KL(q_j || p_j)$. 我们直接让$q_j = p_j$使得$KL(q_j || p_j)$取到最小值$0$.
$$
\ln q_j(z_j) = \mathrm{E}_{i \neq j} [\ln p(Z, X)] + const
$$




























