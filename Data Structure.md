## Linked List

> 思考题：如何判断一个链表错误的产生自环？

node要在list的作用域内，是链表下属的一个概念。脱离链表，结点丧失意义。





**1.用Map储存所有的地址**

**2.快慢指针：**

​	一旦相逢就说明有环。

​	但步长的差可能会失效。

​	扩展:**裴蜀定理**

​	假设初始两个指针的位置是$a,b$，步长是$p,q$。

​	环的长度为$$L$$

​	求解$k$，满足条件：
$$
a+k\times q=b+k\times p \notag
$$
​	整理后，可转化为：
$$
a-b\equiv k\times(p-q) \tag{mod L}\\

a-b=k\times(p-q)+t\times(L)\\
$$
​	由裴蜀定理$ax+by\equiv gcd(a,b)$一定有解可知，$$k$$有解的条件为：
$$
gcd(p-q,L)|(a-b)
$$


<img src="Data Structure.assets/59e5e8cd2511eba724ceefc16a4d3280.png" alt="img" style="zoom:50%;" />

在一些函数之后，加上const，以防止变量被修改。



```c++
void visit(...,fun)
{
	for(...p...)
		fun(*p)
}
```

使用户可以自定义操作函数



## 分治

**分(split)治(recursively)合(merge)**

为什么**”治“**是1？

* [ ] QuickSort//递推版本
* [ ] MergeSort



第K大元素，可以借助快排的思想进行。





## Abstract Data Type

## 扩展欧几里得

![image-20230924163155836](Data Structure.assets/image-20230924163155836.png)

## 汉诺塔

$$
F(n)=2\times F(n-1)+1
$$

第$n$问题变为$n-1$问题的过程，发生了规模变化（-1）、顺序改变。

目标n个盘子1->3

P:(n-1)个盘子1->2

I:第n个盘子 1->3

Q:(n-1)个盘子 2->3

对于lowbit前的每一个数对应于一个(p或者q)操作。

[汉诺塔杂谈（三）——非递归算法 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/36085324)



## 排列

1234

1243

1324

1342

...

先找到从末尾开始的反向最长上升子序列，翻转。

之后将前一个与子序列大于他的第一个数字交换位置。

