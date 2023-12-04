#include<iostream>
#include<list>
#include<vector>
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*
    封装了一个无权有向图。
    V代表图的节点数。
    addEdge进行加边。
    component查询以某一个点作为代表元素的联通分支组成。
*/
class Graph
{
    public:
        int V;// index 0;
        list<int>* adj;
        Graph(int V)
        {
            this->V=V;
            adj=new list<int>[V];
        }
        void addEdge(int v,int w)
        {
            adj[v].push_back(w);
        }
        void component(int p)
        {
            int *vis=new int[V];
            vis[p]=1;
            dfs(p,vis);
            cout<<endl;
        }
        void dfs(int p,int *vis)
        {
            cout<<p<<" ";
            for(list<int>::iterator it=adj[p].begin();it!=adj[p].end();++it)
            {
                if(!vis[*it])
                {
                    vis[*it]=1;
                    dfs(*it,vis);
                }
            }
        }
};