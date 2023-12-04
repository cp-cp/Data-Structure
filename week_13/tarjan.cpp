#include<iostream>
#include<stack>
#include"Graph.h"
using std::stack;
using std::min;
using std::pair;
stack<int>s;
int tmp=0;
/*
1. 时间戳index[x]:节点x第一次被访问的顺序
2. 追溯值low_link[x]:从节点x出发，所能访问到的最早时间戳
3. 栈stack[]，存储还没有处理完的强连通分量中的节点。

1.处理v时，标记时间戳并将v入栈
2.枚举v的邻点p，可能会出现三种情况：
    1.邻点没有被标记过时间戳。对邻点进行深搜并用low_link[v]更新low_link[u]。
    2.邻点被标记过时间戳且在栈内。说明(u,v)是返祖边或者横叉边，用dfn[v]更新low[u]
    3.邻点被标记过时间戳且不在栈内，说明邻点v所在的强连通分量已经被处理完毕，此时不需要执行任何操作。
3.离开u时，如果u是强连通分量的根（dfn[u] == low[u），记录SCC。只有遍历完一个SCC（s[top] == u）,才可以出栈。
  这里也体现出了更新low[u]的意义：避免SCC中的节点提前出栈。


5 5
2 3
3 4
4 0
0 1
0 3
*/
vector<pair<int,int> >edge;
void tarjan(int v,int f,int *low_link,int *index,int *vis,Graph* g)
{
    low_link[v]=index[v]=tmp++;
    vis[v]=1;
    // s.push(v);
    for(list<int>::iterator it=g->adj[v].begin();it!=g->adj[v].end();++it)
    {
        int p=*it;
        if(p==f)continue;
        if(!index[p])
        {
            vis[p]=1;
            tarjan(p,v,low_link,index,vis,g);
            low_link[v]=min(low_link[v],index[p]);
            // cout<<p<<" "<<low_link[p]<<" "<<index[p]<<" "<<v<<" "<<low_link[v]<<" "<<index[v]<<endl;
            if(low_link[p]>index[v])
            {
                // cout<<"hihi"<<endl;
                edge.push_back(std::make_pair(v,p));
            }
        }
        else if(vis[v])//返祖边
        {
            low_link[v]=min(low_link[v],index[p]);
        }
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    Graph* g=new Graph(n);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        g->addEdge(x,y);
        g->addEdge(y,x);
    }
    int *low_link=new int[n];
    int *index=new int[n];
    int *vis=new int[n];
    // for(int i=0;i<n;i++)
    {
        tarjan(2,-1,low_link,index,vis,g);
    }
    for(int i=0;i<edge.size();i++)
    {
        cout<<edge[i].first<<" "<<edge[i].second<<endl;
    }
}