#include<iostream>
int gcd(int a,int b)
{
    while(b)
    {
        printf("a:%d b:%d\n",a,b);
        int tmp=a;
        a=b;
        b=tmp%b;
    }
    printf("a:%d b:%d",a,b);
    return b;
}
void exgcd(int a,int b)
{
    int b_tmp=b;
    int m[2][2]={{1,0},
                 {0,1}};//单位矩阵
    while(b)
    {
        int m_tmp[2][2]={{0,0},{0,0}};
        int m_th[2][2]={{0,1},
                         {1,-a/b}};//当前循环的还原矩阵

        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    m_tmp[i][j]+=m[i][k]*m_th[k][j];//计算累乘矩阵
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                m[i][j]=m_tmp[i][j];//替换
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
                printf("%d ",m[i][j]);
            printf("\n");
        }//输出目前的累乘矩阵
        printf("a:%d b:%d\n",a,b);
        int tmp=a;
        a=b;
        b=tmp%b;
    }
    printf("x=%d,y=%d",m[0][0],m[1][0]);//因为最终取x=1，y=0，所以答案就是第一列的数。
    // int x=m[0][0];
    // x = ((x+b_tmp) % b_tmp ) % b_tmp;
    // printf("%d",x);
}
int main()
{
    int a,b;
    printf("a:");
    scanf("%d",&a);
    printf("b:");
    scanf("%d",&b);
    exgcd(a,b);
}