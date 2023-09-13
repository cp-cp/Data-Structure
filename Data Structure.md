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

