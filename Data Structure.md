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

## 树

### homework

1. 给定特地的树，输出遍历。
2. 给定两种遍历，形成特定的树（括号表示）。

### 线索二叉树

![image-20230927144014754](Data Structure.assets/image-20230927144014754.png)



#### 前序遍历

无法处理6和3号节点，即为父亲右节点且有左节点存在的数据。

需要用堆栈辅助。

#### 后序遍历

无法处理$3\Rightarrow 4$.

需要堆栈辅助，一般来说只需要：堆入14.



### 哈夫曼树



## 堆Heap

形式上数组，意义上树。
$$
left child=2i+1\\

right child=2i+2\\

father=\lfloor\frac{i-1}{2}\rfloor\\
$$


删除：去除根节点，用最后一个元素代替根节点，往下交换传递，变为正确的顺序。

添加：放在底部，一步步向上传播。

N个节点的树，以上时间复杂度为O(NlogN)  



### 斐波那契堆

[算法 - 优先队列 - 斐波那契堆 | Earth Guardian (redspider110.github.io)](https://redspider110.github.io/2018/09/25/0105-algorithms-fibonacci-heap/)

## 二叉搜索树

左小右大

动态有序



AVL树

B树

### 红黑树

#### 性质约定

1. 节点是红色或黑色。
2. **根是黑色**。
3. 所有**叶子都是黑色**（叶子是**NIL**节点）。
4. **不存在**两个相邻的红色节点
5. 从任一节点到其每个叶子的所有简单路径都包含**相同数目的黑色节点。**



![An example of a red-black tree](https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Red-black_tree_example.svg/450px-Red-black_tree_example.svg.png)



#### 动态调整

$Case\_1$

![情形3示意图](https://upload.wikimedia.org/wikipedia/commons/c/c8/Red-black_tree_insert_case_3.png)

直接将父亲与叔叔染成黑色。

$Case\_2$

![情形4示意图](https://upload.wikimedia.org/wikipedia/commons/5/56/Red-black_tree_insert_case_4.png)

先进行左旋

![情形5示意图](https://upload.wikimedia.org/wikipedia/commons/6/66/Red-black_tree_insert_case_5.png)

再进行右旋
