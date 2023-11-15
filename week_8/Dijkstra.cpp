#include<bits/stdc++.h>
using namespace std;
/*
有向边的Dijkstra算法
INPUT:
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
OUTPUT:
0 2 4 3
*/
const int N=1e6+9;
int u,vv,w,n,m,s,head[N],v[N],dis[N],cur;
struct node{int w,to,next;}e[N<<1];
void add(int u,int v,int w){e[++cur].to=v,e[cur].w=w,e[cur].next=head[u],head[u]=cur;}
void dij(int x)
{
	priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > >q;
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int p=q.top().second;
		q.pop();
		if(v[p])continue;
		v[p]=1;
		for(int i=head[p];i;i=e[i].next)
		{
			int dx=e[i].to,dw=e[i].w;
			if(dis[dx]>dis[p]+dw)
			{
				dis[dx]=dis[p]+dw;
				q.push(make_pair(dis[dx],dx));
			}
		}
	}
}
int main()
{
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>vv>>w;
		add(u,vv,w);
	}
	memset(dis,0x3f,sizeof(dis));
	dij(s);
	for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
 } 