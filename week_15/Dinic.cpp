#include<iostream>
#include<cstring>
#include<queue>
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using std::min;
/*

实现了求最大流的DINIC算法。



INPUT:
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30
OUPUT:
50
*/
const int N=2e6+10;
struct edge
{
    int to,nxt,w;
}e[N];
int n,m,s,t;
int head[N],cnt=0,dis[N];
void addEdge(int u,int v,int w)
{
    e[++cnt].w=w;
    e[cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
bool bfs()//构建层次图
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        // cout<<u<<" : ";
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            // cout<<v<<" ";
            
                // cout<<v<<"&"<<e[v].w<<"&"<<dis[v]<<" ";
            if(dis[v]==0x3f3f3f3f&&e[i].w>0)
            {
                // cout<<v<<" ";
                q.push(v);
                dis[v]=dis[u]+1;
            }
        }
        // cout<<endl;
    }
    if(dis[t]==0x3f3f3f3f)return false;
    else return true;
}
int dfs(int x,int fl)//寻找阻塞流,x代表当前节点，fl代表水流量
{
    // cout<<x<<" "<<t<<" "<<fl<<" "<<endl;
    if(x==t) return fl;
    int f=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(dis[v]==dis[x]+1&&e[i].w>0)
        {
            int x=dfs(v,min(e[i].w,fl));
            e[i].w-=x;//u->v减小
            e[i+1].w+=x;//v->u增大
            fl-=x;
            f+=x;
        }
    }
    return f;
}
int main()
{
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,0);
    }
    int ans=0;
    while(bfs())
    {
        // for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
        // cout<<endl;
        ans+=dfs(s,0x3f3f3f3f);
    }
    cout<<ans;
}