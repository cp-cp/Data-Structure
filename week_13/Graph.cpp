#include<iostream>
#include<list>
#include<vector>
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
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
int main()
{
    Graph *g=new Graph(10);
    g->addEdge(0,1);
    g->addEdge(2,3);
    g->addEdge(3,4);
    g->addEdge(5,6);
    g->addEdge(6,7);
    g->addEdge(8,9);
    g->component(0);
    g->component(2);
    g->component(5);
    g->component(8);
}
