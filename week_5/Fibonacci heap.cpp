#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::queue;
class FibonacciHeap
{
    public:
        class FibonacciHeapNode{
            public:
                int key;
                int degree=0;
                FibonacciHeapNode *left=NULL;
                FibonacciHeapNode *right=NULL;
                FibonacciHeapNode *parent=NULL;
                FibonacciHeapNode *child=NULL;
                bool mark=false;
                FibonacciHeapNode(int x):key(x){};
        };
        int num=0;//堆内节点数量
        FibonacciHeapNode* min=NULL;
        // vector<FibonacciHeapNode*>list;//储存堆内的最小堆序树
        void Insert(int x);
        int Min(){return min->key;};
        int Extract_Min();
        void Consolidating();
        //void Merge(FibonacciHeap fib);
};
void FibonacciHeap::Insert(int x)
{
    FibonacciHeapNode* fib_node=new FibonacciHeapNode(x);    
    if(min==NULL)
    {
        min=fib_node;
        fib_node->left=fib_node;
        fib_node->right=fib_node;
    }
    else
    {
        /*
         min->  <-fid_node-> <- min_right
        */
        fib_node->left=min;
        fib_node->right=min->right;
        min->right->left=fib_node;
        min->right=fib_node;
        if(fib_node->key<min->key)
        {
            min=fib_node;
        }
    }
    num++;
}
int FibonacciHeap::Extract_Min()
{
    if(min!=NULL)
    {
        int min_tmp=min->key;
        FibonacciHeapNode* fib_node=min->child;
        // cout<<"min:"<<min->key<<"\n";
        if(min->child!=NULL)
        {
            /* 
            min -> <- fib_node  .....  fid_node_left ->  <-mid_right
            */
            // cout<<fib_node->right->key<<" "<<fib_node->left->key<<"\n";
            min->right->left=fib_node->left;
            fib_node->left=min;
            fib_node->left->right=min->right;
            min->right=fib_node;
            min->child=NULL;
        }
        if(min->left==min)
        {
            min=NULL;
        }
        else
        {
            // FibonacciHeapNode* tmp=min->left;
            min->left->right=min->right;
            min->right->left=min->left;
            min=min->right;
            Consolidating();
        }
        num--;
        return min_tmp;
    }
    return NULL;
}
void FibonacciHeap::Consolidating()
{
    FibonacciHeapNode* a[20];
    for(int i=0;i<20;i++)a[i]=NULL;
    queue<FibonacciHeapNode*>q;
    FibonacciHeap::FibonacciHeapNode* tmp=min;
    do
    {
        q.push(tmp);
        tmp=tmp->right;
    }while(tmp!=min);
    // cout<<"size:"<<q.size()<<"\n";
    while(!q.empty())
    {
        FibonacciHeapNode* x=q.front();
        q.pop();
        int d=x->degree;
        // cout<<x<<" "<<x->key<<" "<<std::endl;
        while(a[d]!=NULL)
        {
            FibonacciHeapNode* y=a[d];
            if(x->key>y->key)swap(x,y);//把y转到x的儿子
            x->degree++;
            y->left->right=y->right;
            y->right->left=y->left;//删除y
            y->parent=x;
            if(x->child==NULL)
            {
                x->child=y;
                y->left=y;
                y->right=y;
            }
            else
            {
                /*
                child -> <-y  <-child_right
                */
                y->left=x->child;
                y->right=x->child->right;
                x->child->right->left=y;
                x->child->right=y;
                // cout<<"test:"<<x->child->key<<" "<<x->child->left->key<<" "<<x->child->right->key<<"\n";
            }
            y->mark=false;
            a[d]=NULL;
            d++;
        }
        // cout<<x->key<<" "<<x->degree<<std::endl;
        a[d]=x;
    }
    min=NULL;
    // cout<<"list:";
    for(int i=0;i<20;i++)
    {
        if(a[i]!=NULL)
        {
            // cout<<i<<" ";
            FibonacciHeapNode* fib_node=a[i];
            if(min==NULL)
            {
                min=fib_node;
                fib_node->left=fib_node;
                fib_node->right=fib_node;
            }
            else
            {
                /*
                min->  <-fid_node-> <- min_right
                */
                fib_node->left=min;
                fib_node->right=min->right;
                min->right->left=fib_node;
                min->right=fib_node;
                if(fib_node->key<min->key)
                {
                    min=fib_node;
                }
            }            
        }
    }
    // cout<<"\n";
}
int main()
{
    FibonacciHeap fib;
    fib.Insert(1);
    fib.Insert(2);
    fib.Insert(3);
    fib.Insert(4);
    fib.Insert(4);
    cout<<fib.Extract_Min()<<" ";
    cout<<fib.Extract_Min()<<" ";
    cout<<fib.Extract_Min()<<" ";
    cout<<fib.Extract_Min()<<" ";
    cout<<fib.Extract_Min()<<" ";
    // FibonacciHeap::FibonacciHeapNode* tmp=fib.min;
    // do
    // {
    //     cout<<tmp->key<<std::endl;
    //     tmp=tmp->right;
    // }while(tmp!=fib.min);
}