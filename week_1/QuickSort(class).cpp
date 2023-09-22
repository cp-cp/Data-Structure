#include<iostream>
template<class T,int N>
class MyTemplateClass//对于一个模板类
{
    public:
        T A[N];
        void sort(int l,int r);
    private:
        void swap(int l,int r);
};
template<class T,int N>
void MyTemplateClass<T,N>::swap(int l,int r)//交换
{
    T a=this->A[l];
    A[l]=A[r];
    A[r]=A[l];
}
template<class T,int N>
void MyTemplateClass<T,N>::sort(int l,int r)//排序
{
    T* A=this->A;
    if(l>=r)return;
    int lp=l;
    int rp=r;
    int p=l+1;
    for(int i=l+1;i<=r;i++)
    {
        if(A[i]<A[l])
        {
            swap(i,p);
            p++;
        }
    } //找出分割点p-1
    swap(l,p-1);
    sort(l,p-2);//左侧分治
    sort(p,r);//右侧分治
}
int main()
{
    class MyTemplateClass<int,10> a;
    for(int i=4;i>=0;i--)
        a.A[i]=i+1;
    a.sort(0,4);//内部排序
    for(int i=0;i<5;i++)
    {
        std::cout<<a.A[i]<<" ";
    }
    std::cout<<"\n";
}