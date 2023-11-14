# Trie

## History

**检索retrieval**   引申到 **Trie**

## Deterministic finite automaton （确定有限状态自动机）



### 什么是自动机？



自动机是一种**有限状态机**（**FSM**）。

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a8/Fsm_parsing_word_nice.svg/400px-Fsm_parsing_word_nice.svg.png)





FSM是给定符号输入，依据转移函数“跳转”过一系列状态的一种机器。

逐个读取输入中的符号，直到被完全耗尽(把它当作有一个字写在其上的磁带，通过自动机的读磁头来读取它；磁头在磁带上前行移动，一次读一个符号)。一旦输入被耗尽，自动机被称为“停止”了。

依赖自动机停止时的状态，称呼这个自动机要么是“接受”要么“拒绝”这个输入。如果停止于“接受状态”，则自动机“接受”了这个字。在另一方面，如果它停止于“拒绝状态”，则这个字被“拒绝”。自动机接受的所有字的集合被称为“这个自动机接受的语言”。



自动机可以表示为五元组：
$$
\begin{align*}
(Q,\Sigma,\delta,q_0,F)
\end{align*}
$$
$Q$是状态的集合；

$\Sigma$是符号的有限集合，也就是自动机可接受的语言的字母表。

$\delta$是转移函数：$$\delta : Q \times \Sigma \rightarrow Q$$

$q_0$是开始状态，未处理输入时的状态，有$q_0\in Q$

$F$叫做终止状态，有$F\subseteq Q$



确定有限状态自动机：

对字母表中每个符号，自动机的状态都有且仅有一个转移。



### 来做个实验



#### 匹配 3 的倍数的正则表达式

```
^[0369]* (
  (
    [147][0369]*
  | [258][0369]*[258][0369]*
  ) ([147][0369]*[258][0369]*)* (
    [258][0369]*
 
  | [147][0369]*[147][0369]*
  )
| [258][0369]*[147][0369]* )* $
```



给你一个二进制数。

设计一个自动机，判断是否为3的倍数。

[匹配 3 的倍数的正则表达式 (quaxio.com)](https://www.quaxio.com/triple/)



给你一个十进制数。

设计一个自动机，判断是否为3的倍数。



![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9waWMyLnpoaW1nLmNvbS84MC9iODhjNGU3MWZmZTFiOTJlZTkyYWRiYzI1MzY1NGMzNF83MjB3LmpwZw?x-oss-process=image/format,png#pic_center)



[编译原理（四）——自动机与正则表达式_正则表达式与dfa之间的关系-CSDN博客](https://blog.csdn.net/weixin_43633784/article/details/108446358)



[Regex Golf (alf.nu)](https://alf.nu/RegexGolf?world=regex&level=r00)



## 应用

[Trie 树在路由匹配中应用的设计随想 - 掘金 (juejin.cn)](https://juejin.cn/post/7053663185638948895)
