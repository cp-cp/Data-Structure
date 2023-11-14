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
int main()
{
    Union_Find uf(10);
    uf.Union(1,2);
    uf.Union(3,4);
    uf.Union(5,6);
    uf.Union(7,8);
    uf.Union(7,9);
    uf.Union(2,8);
    uf.Union(0,5);
    uf.Union(1,9);
    /*
    1 2 7 8 9
    3 4
    0 5 6 
    */
    for(int i=0;i<10;i++)
    {
        std::cout<<uf.Find(i)<<" ";
    }
}