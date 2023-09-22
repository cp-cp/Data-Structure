#include"../week_2/Stack.h"
bool next_permutation(int* array_begin,int* array_end)
{
    int n=(array_end-array_begin);//计算长度
    // printf("%d\n",n);
    // for (int* it = array_begin; it != array_end; ++it) {
    //     std::cout << *it << " ";
    // }
    Stack<int>s;//开辟一个栈空间，储存末尾单调上升的序列
    s.Push(*(array_end-1));//放入最后一个元素

    for(int* r_p=array_end-2;r_p>=array_begin;r_p--)
    {
        if(*r_p>*(r_p+1))
        {
            s.Push(*r_p);
        }
        else
        {
            break;
        }
    }//把倒序上升序列找到并全部压栈
    // printf("Length: %d\n",s.Length());
    if(s.Length()==n)
        return false;//判断是否是最后一个排列。
    else
    {
        int len=s.Length();
        int * end_p=array_end-1;
        while(!s.Empty())
        {
            // printf("%d %d\n",*end_p,s.Top());
            *end_p=s.Top();
            s.Pop();
            end_p--;
        }//倒序出栈，使倒序上升序列反转
        for(int* it=end_p+1;it!=array_end;it++)
        {
            if(*it>*end_p)
            {
                int c=*it;
                *it=*end_p;
                *end_p=c;
                return true;
            }
        }//寻找第一个大于下一个元素的数字，并交换。
    }
}
int main()
{
    int n,a[100];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)a[i]=i;
    do
    {
        for(int i=1;i<=n;i++)printf("%d ",a[i]);
        printf("\n");
    }while(next_permutation(a+1,a+1+n));
}   