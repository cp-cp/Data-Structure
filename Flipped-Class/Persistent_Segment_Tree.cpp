#include<iostream>
const int N=2e6+10;
class Persistent_Segment_Tree
{
    public:
        static const int MAXN=2000010;
        struct Node
        {
            int l,r,sum;
        }node[MAXN];
        int A[MAXN],root[MAXN],cnt=1,n;
        Persistent_Segment_Tree(int A[],int n)
        {
            // std::cout<<"Persistent_Segment_Tree Build"<<std::endl;
            this->n=n;
            root[0]=0;
            for(int i=1;i<=n;i++)
                this->A[i]=A[i-1];
            // for(int i=1;i<=n;i++)
            //     std::cout<<this->A[i]<<" ";
            build(0,1,n);
        }
        void build(int p,int l,int r)
        {
            // std::cout<<"build:"<<p<<" "<<l<<" "<<r<<std::endl;
            if(l==r)
            {
                // std::cout<<"build:"<<l<<" "<<A[l]<<std::endl;
                node[p].sum=A[l];
                return;
            }
            int mid=(l+r)>>1;
            node[p].l=cnt++;
            build(node[p].l,l,mid);
            node[p].r=cnt++;
            build(node[p].r,mid+1,r);
        }
        //p是上一个版本的根节点，q是本版本的节点，pos是要修改的位置，val是修改后的值
        void update(int p,int q,int l,int r,int pos,int val)
        {
            if(l==r)
            {
                node[q].sum=val;
                return;
            }
            else
            {
                //复制上一个版本的节点
                node[q].l=node[p].l;
                node[q].r=node[p].r;
                int mid=(l+r)>>1;
                //修改左子树或右子树
                if(pos<=mid)
                {
                    node[q].l=cnt++;
                    update(node[p].l,node[q].l,l,mid,pos,val);
                }
                else
                {
                    node[q].r=cnt++;
                    update(node[p].r,node[q].r,mid+1,r,pos,val);
                }
            }
        }
        //最初的p是版本号，l和r是区间，pos是要查询的位置
        int query(int p,int l,int r,int pos)
        {
            if(l==r)
            {
                // std::cout<<"query:"<<l<<" "<<p<<" "<<node[p].sum<<std::endl;
                return node[p].sum;
            }
            else
            {
                int mid=(l+r)>>1;
                if(pos<=mid)
                    return query(node[p].l,l,mid,pos);
                else
                    return query(node[p].r,mid+1,r,pos);
            }
        }
        //查询第p个版本的pos位置的值
        int query_version(int p,int pos)
        {
            // std::cout<<"query_version:"<<p<<" "<<pos<<std::endl;
            return query(root[p],1,n,pos);
        }
        //在第p个版本的基础上，修改pos位置的值为val
        void update_version(int p,int q,int pos,int val)
        {
            root[q]=cnt++;
            update(root[p],root[q],1,n,pos,val);
        }
        //复制第p个版本到第q个版本
        void copy_version(int p,int q)
        {
            root[q]=root[p];
        }
};
int main()
{   
    // int a[4]={0,1,2,3};
    // Persistent_Segment_Tree pst(a,4);
    // std::cout<<pst.query_version(0,1)<<std::endl;
    // std::cout<<pst.query_version(0,2)<<std::endl;
    // std::cout<<pst.query_version(0,3)<<std::endl;
    // std::cout<<pst.query_version(0,4)<<std::endl;
    // pst.update_version(0,1,2,4);
    // std::cout<<pst.query_version(1,1)<<std::endl;
    // std::cout<<pst.query_version(1,2)<<std::endl;
    // std::cout<<pst.query_version(1,3)<<std::endl;
    // std::cout<<pst.query_version(1,4)<<std::endl;


    int n,m;
    std::cin>>n>>m;
    int a[N];
    for(int i=0;i<n;i++)
    {
        std::cin>>a[i];
    }
    Persistent_Segment_Tree pst(a,n);
    // std::cout<<pst.query_version(0,1)<<std::endl;
    // std::cout<<pst.query_version(0,2)<<std::endl;
    // std::cout<<pst.query_version(0,3)<<std::endl;
    // std::cout<<pst.query_version(0,4)<<std::endl;
    // std::cout<<pst.query_version(0,5)<<std::endl;

    for(int i=1;i<=m;i++)
    {
        int v,o;
        std::cin>>v>>o;
        if(o==1)
        {
            int x,y;
            std::cin>>x>>y;
            pst.update_version(v,i,x,y);
        }
        else
        {
            int k;
            std::cin>>k;
            pst.copy_version(v,i);
            std::cout<<pst.query_version(v,k)<<std::endl;
        }
    }
    return 0;
}