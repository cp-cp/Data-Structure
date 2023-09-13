#include<iostream>
void swap(int A[],int l,int r)
{
    int a=A[l];
    A[l]=A[r];
    A[r]=a;
}
void QuickSort(int A[],int l,int r)
{
    // int length = sizeof(A)/sizeof(A[0]);
    for(int i=0;i<5;i++)
    {
        std::cout<<A[i]<<" ";
    }
    std::cout<<":"<<l<<" "<<r<<"\n";
    if(l>=r)return;
    int lp=l;
    int rp=r;
    int p=l+1;
    for(int i=l+1;i<=r;i++)
    {
        if(A[i]<A[l])
        {
            swap(A,i,p);
            p++;
        }
    } 
    swap(A,l,p-1);
    QuickSort(A,l,p-1);
    QuickSort(A,p,r);
}
int main()
{
    int A[]={5,4,3,2,1};
    QuickSort(A,0,4);
    for(int i=0;i<5;i++)
    {
        std::cout<<A[i]<<" ";
    }
    std::cout<<"\n";
}