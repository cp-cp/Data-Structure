#include<iostream>
using std::swap;
int lowbit(int x)
{
	return x & -x ;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<(1<<n);i++)//遍历操作，第一次为空操作
    {
        int l_b=lowbit(i);
        int origin_id=1,middle_id=2,target_id=3;
        int res=0;
        // printf("%d l_b:%d ",i,l_b);
        while(l_b)
        {
            l_b/=2;
            res++;
        }//获取最低位1的位置
        for(int j=n-1;j>=res;j--)
        {
            // printf("%d ",(1<<j)&i);
            if((1<<j)&i)
            {
                swap(middle_id,origin_id);
            }
            else
            {
                swap(middle_id,target_id);
            }
        }
        printf("plate_id:%d from tower(%d) to tower(%d)\n",res,origin_id,target_id);
    }
}