#include<iostream>
#include<queue>
#include<cstring>
/*
本程序是根据前序后序进行生成的，一开始考虑到多叉树不存在中序遍历，但之后发现并不可以唯一确定。
但是可以确定基本架构，仅链状结构无法确定，即：
1           1
 \   与    /
  2       2
无法区分。
更新后的程序请见"traverse2tree(rerenew).cpp"

  1
 / \
2   3       
   / \
  4   5
     / \
    6   7
pre_order traverse: 1 2 3 4 5 6 7
post_order traverse: 2 4 6 7 5 3 1


TEST_1:
7
1 2 3 4 5 6 7
2 4 6 7 5 3 1

OUT_1:
1(2,3(4,5(6,7)))

TEST_2:
7 
1 2 3 4 5 6 7
2 5 6 4 7 3 1

OUT_2:
1(2,3(4(5,6),7))
*/
int main()
{
    int n;
    scanf("%d",&n);
    std::queue<int>pre_que;
    std::queue<int>post_que;
    int vis[100];
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        pre_que.push(tmp);
    }//读入先序遍历
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        post_que.push(tmp);
    }//读入后序遍历
    std::string s;
    while(!pre_que.empty())//以先序遍历为蓝本
    {
        int th_p=pre_que.front();
        pre_que.pop();
        s.append(std::to_string(th_p));
        vis[th_p]=1;//判断是否已经加入输出输出序列
        if(post_que.front()==th_p)//通过后序遍历判断架构
            post_que.pop(),s.append(",");
        else
            s.append("(");
        while(vis[post_que.front()])
        {
            post_que.pop();
            s.insert(s.size()-1,")");
        }
    }
    s.erase(s.size()-1);//去除多余的,
    std::cout<<s;
}