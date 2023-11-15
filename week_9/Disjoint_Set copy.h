#include<iostream>
/*
    实现并查集代码，包括按秩合并、查找。    
    根据id进行索引
*/
class Union_Find
{
    public:
        Union_Find(int n)
        {
            f=new int[n];
            rank=new int[n];
            for(int i=0;i<n;i++)
            {
                f[i]=i;
                rank[i]=0;
            }
        };
        ~Union_Find()
        {
            delete [] f;
            delete [] rank;
        };
        int Find(int p)
        {
            while(p!=f[p])
            {
                f[p]=f[f[p]];//路径压缩
                p=f[p];
            }
            return p;
        };
        void Union(int p,int q)
        {
            int i=Find(p);
            int j=Find(q);
            if(i==j)
                return;
            if(rank[i]<rank[j])
                f[i]=j;
            else if(rank[i]>rank[j])
                f[j]=i;
            else
            {
                f[j]=i;
                rank[i]++;
            }
        };
    private:
        int* f;
        int* rank;
};