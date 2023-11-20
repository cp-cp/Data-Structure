#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
/*
INPUT:
5 5
2 3
3 4
4 5
5 1
1 3
OUTPUT:
start_node:2
Exist Euler Path:
2 3 4 5 1 3

INPUT:
5 4
2 3
3 4
5 1
1 3
OUTPUT:
start_node:2
No Euler Path


*/


vector<int>degree;
vector<vector<std::pair<int, int>>> edge;
vector<int>vis;
queue<int>ans;
int n,m;
bool dfs(int u,int v,vector<int>copiedVis)//需要找的是v，当前节点是u。
{
    // cout<<u<<" ";
    if(u==v)
        return true;
    for(int i=0;i<edge[u].size();i++)
    {
        if(copiedVis[edge[u][i].second]==0)
        {
            copiedVis[edge[u][i].second]=1;
            if(dfs(edge[u][i].first,v,copiedVis))
                return true;
        }
    }
    return false;
}
bool is_bridge(int u,int j)//判断u节点的第j条边是否是桥
{
    
    std::vector<int> copiedVis(vis);
    copiedVis[edge[u][j].second]=1;//标记这条边
    // cout<<u<<" "<<edge[u][j].first<<"\n";
    if(dfs(u,edge[u][j].first,copiedVis))return false;
    else return true;
}
void Fleury(int p)
{
    // cout<<p<<" ";
    ans.push(p);
    int ex=-1;
    for(int i=0;i<edge[p].size();i++)
    {
        if(vis[edge[p][i].second]==0)//这条边没有被访问过
        {
            ex=i;
            if(!is_bridge(p,i))//这条边不是桥
            {
                vis[edge[p][i].second]=1;
                Fleury(edge[p][i].first);
                return ;//返回
            }
        }
    }
    if(ex!=-1)
    {
        vis[edge[p][ex].second]=1;
        Fleury(edge[p][ex].first);
    }
}
int main()
{
    cin>>n>>m;//n个节点，m条边
    degree.resize(n+1, 0);
    edge.resize(n+1);
    vis.resize(m+1,0);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        // cout<<edge[u].size()<<std::endl;
        edge[u].push_back(std::make_pair(v,i));//i为边的索引
        edge[v].push_back(std::make_pair(u,i));
        // cout<<"hi";
        degree[u]++;
        degree[v]++;
    }
    int start_node;
    for(int i=1;i<=n;i++)
    {
        if(degree[i]%2==1)
        {
            start_node=i;
            break;
        }
    }
    cout<<"start_node:"<<start_node<<endl;
    Fleury(start_node);
    if(ans.size()==(m+1))//如果是一个欧拉路径
    {
        cout<<"Exist Euler Path:"<<endl;;
        while(!ans.empty())
        {
            cout<<ans.front()<<" ";
            ans.pop();
        }
    }
    else
    {
        cout<<"No Euler Path";
    }
}