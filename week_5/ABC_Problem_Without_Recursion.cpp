#include<iostream>
#include<stack>
#include<string>
using std::stack;
using std::string;
using std::cout;
char dic[27][3];
bool vis[27];
int ans=0;
string ss;
/*

OUTPUT:
27 AAABAACABBABCACBACCBBBCBCCCAA
*/
int main()
{
    int cur=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                dic[cur][0]=i+'A';
                dic[cur][1]=j+'A';
                dic[cur][2]=k+'A';
                cur++;
            }
        }
    }
    struct node{
        char* last_arr;//上一层的字符串
        int num;//层深度
        string s;//累积字符串
        int v;//当前层的循环位置
    };
    stack<node>sta;
    vis[0]=true;
    string s;
    s=s+dic[0][0]+dic[0][1]+dic[0][2];
    // cout<<s;
    sta.push({dic[0],1,s,1});
    while(!sta.empty())
    {
        node a=sta.top();
        sta.pop();
        // if(a.v==2)
            // std::cout<<a.num<<" "<<a.v<<" "<<vis[a.v]<<" "<<dic[a.v][0]<<dic[a.v][1]<<dic[a.v][2]<<" "<<a.s<<"\n";
        if(a.v<27)//该层未完
        {
            int i=a.v;
            sta.push({a.last_arr,a.num,a.s,a.v+1});
            if(!vis[i])//未被访问
            {
                // std::cout<<a.last_arr[0]<<a.last_arr[1]<<a.last_arr[2]<<"\n";
                if(dic[i][0]==a.last_arr[1]&&dic[i][1]==a.last_arr[2])//匹配
                {
                    // printf("in\n");
                    vis[i]=true;//标记访问
                    sta.push({a.last_arr,a.num,a.s,a.v});//递归返回位置
                    string s_pri=a.s+dic[i][2];//更新累计字符串
                    sta.push({dic[i],a.num+1,s_pri,1});//递归
                }
            } 
        }
        else
        {
            ans=std::max(ans,a.num);//更新
            if(a.num==27)//剪枝
            {
                ss=a.s;
                break;
            }
            // cout<<ans<<" ";
            if(sta.empty())break;
            a=sta.top();
            sta.pop();//返回递归位置
            int i=a.v;
            vis[i]=false;//返还标记
        }
    }
    std::cout<<ans<<" "<<ss;
}