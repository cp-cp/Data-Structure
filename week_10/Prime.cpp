#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
// #include<pair>
using std::pair;
using std::priority_queue;
using std::memset;
using std::vector;
using std::greater;
/*
Prime算法实现最小生成树
*/
struct edge
{
    int v;
    int w;
    edge* next=NULL;
    edge(int v,int w,edge* next):v(v),w(w),next(next){};
};
edge* head[1000];
int dis[1000];
int vis[1000];
void add_edge(int u,int v,int w)
{
    edge* e=new edge(v,w,head[u]);
    head[u]=e;
}
int prim(int n)
{
    int sum=0;
    dis[1]=0;//从1号点开始
    // vis[1]=1;//访问标记
	priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > >q;
    //考虑储存什么？储存的应该是距离以及点的编号。默认是按照第一个元素进行排序的。
    q.push(std::make_pair(0,1));
    int cnt=0;
    while(!q.empty()&&cnt<n)//保证有边并且没有访问完所有的点
    {
        // std::cout<<q.top().second<<"\n";
        pair<int,int> p=q.top();
        q.pop();
        int u=p.second;
        if(vis[u])
            continue;
        vis[u]=1;
        // std::cout<<u<<" "<<dis[u]<<" "<<"\n";
        sum+=dis[u];
        cnt++;
        for(edge* e=head[u];e!=NULL;e=e->next)
        {
            int v=e->v;
            int w=e->w;
            if(dis[v]>w)
            {
                dis[v]=w;
                q.push(std::make_pair(dis[v],v));
            }
        }
    }
    if(cnt==n)
        return sum;
    else
        return -1;
}
int main()
{
    memset(dis,0x3f,sizeof(dis));
    int n,m;
    std::cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        std::cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    int  sum=prim(n);
    if(sum==-1)
        std::cout<<"给的图不联通";
    else
        std::cout<<sum;
}