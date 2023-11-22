#include<iostream>
#include<algorithm>
#include"Disjoint_Set.h"
class Edge{
    public:
        int x;
        int y;
        int w;
        bool operator < (const Edge& e) const
        {
            return w<e.w;
        }
};
int main()
{
    int n,m;
    std::cin>>n>>m;
    Union_Find uf(n+1);
    Edge edge[m];
    for(int i=0;i<m;i++)
    {
        std::cin>>edge[i].x>>edge[i].y>>edge[i].w;
    }
    std::sort(edge,edge+m);//对边进行排序
    int sum=0;
    for(int i=0;i<m;i++)
    {
        // std::cout<<uf.Find(edge[i].x)<<" "<<uf.Find(edge[i].y)<<"\n";
        if(uf.Find(edge[i].x)!=uf.Find(edge[i].y))
        {
            uf.Union(edge[i].x,edge[i].y);
            sum+=edge[i].w;
            // std::cout<<edge[i].x<<" "<<edge[i].y<<" "<<edge[i].w<<"\n";
        }
    }
    std::cout<<sum;
}