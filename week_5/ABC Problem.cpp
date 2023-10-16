#include<iostream>
using std::cout;
using std::string;
/*
ABC -> A
    -> B
    -> C


ANS=27

For Example:
AAACCCBCCACBBCBACABCAABBBABAA
or
AAABAACABBABCACBACCBBBCBCCCAA

*/
char dic[27][3];
bool vis[27];
int ans=0;
string ss;
void dfs(char* last_arr,int num,string s)
{
    for(int i=26;i>=0;i--)
    {
        if(!vis[i])
        {
            if(dic[i][0]==last_arr[1]&&dic[i][1]==last_arr[2])
            {
                vis[i]=true;
                string s_pri=s+dic[i][2];
                dfs(dic[i],num+1,s_pri);    
                vis[i]=false;
            }
        }
    }
    ans=std::max(ans,num);
    if(num==27)
    {
        ss=s;
    }
}
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
    vis[0]=true;
    string s;
    s=s+dic[0][0]+dic[0][1]+dic[0][2];
    // cout<<s;
    dfs(dic[0],1,s);
    cout<<ans<<"\n";
    cout<<ss;
}