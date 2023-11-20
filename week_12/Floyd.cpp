#include<iostream>
using std::cin;
using std::cout;
int mapp[100][100];
/*
Floyd算法求传递闭包。
INPUT:
5
A F
B D
C E
F D
D E
OUTPUT:
A->D
A->E
A->F
B->D
B->E
C->E
D->E
F->D
F->E

输入的可视化如下：
A -> F
     |
     V
B -> D
     |
     V
C -> E
*/
int main()
{
    int m;
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        char x,y;
        cin>>x>>y;
        mapp[x-'A'][y-'A']=1;
    }//初始建图
    for(int k=0;k<26;k++)
    {
        for(int i=0;i<26;i++)
        {
            for(int j=0;j<26;j++)
            {
                if(mapp[i][k]&&mapp[k][j])
                    mapp[i][j]=1;
            }
        }
    }//动态规划
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<26;j++)
        {
            if(mapp[i][j])
                cout<<(char)(i+'A')<<"->"<<(char)(j+'A')<<"\n";
        }
    }
}