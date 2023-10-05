#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
using std::vector;
using std::string;
using std::cin;
using std::cout;
/*
  1
 / \
2   3       
   / \
  4   5
     / \
    6   7
pre_order traverse: 1 2 3 4 5 6 7
mid_order traverse: 2 1 4 3 6 5 7

考虑pre_order traverse与mid_order traverse.
pre_order traverse能够让根节点与子节点分离。
mid_order traverse让根节点间隔开子节点，确定左右节点的顺序。

以mid_que作为跳转指针，用vis统计队首元素是否在pre_que出现，如果mid_que队首元素已经出现过,则跳到这个点，其左子树不可能再加东西。

如何形成格式？
目前感觉与前序、后序不太相同，只能靠实际建立出树的形式才能再生成括号序列。

TEST_1:
7
1 2 3 4 5 6 7
2 1 4 3 6 5 7

OUT_1:
1(2,3(4,5(6,7)))

TEST_2:
7 
1 2 3 4 5 6 7
2 1 5 4 6 3 7

OUT_2:
1(2,3(4(5,6),7))
*/
class Node
{
    public:
        int id;
        Node* left_son=NULL;
        Node* right_son=NULL;
        Node* father=NULL;
        Node(int id)
        {
            this->id=id;
        };
        Node(){};
};
void dfs(Node* p)
{
    if(p->left_son!=NULL)
        dfs(p->left_son);
    cout<<p->id<<std::endl;
    if(p->right_son!=NULL)
        dfs(p->right_son);}
int main()
{
    int n;
    scanf("%d",&n);
    std::queue<int>pre_que;
    std::queue<int>mid_que;
    int vis[100];//给mid traverse的
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        pre_que.push(tmp);
    }//读入先序遍历
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        mid_que.push(tmp);
    }//读入中序遍历
    Node* head=new Node(pre_que.front());
    vis[pre_que.front()]=1;
    Node* p=head;
    pre_que.pop();
    while(!pre_que.empty())
    {
        Node* th=new Node(pre_que.front());
        pre_que.pop();
        // cout<<th->id<<std::endl;
        if(vis[mid_que.front()])
        {
            while(vis[mid_que.front()])
            {
                while(p->id!=mid_que.front())
                    p=p->father;
                mid_que.pop();
            }       
            cout<<th->id<<" "<<p->id<<std::endl;
            p->right_son=th;
            th->father=p; 
            p=th;
        }
        else
        {
            p->left_son=th;
            th->father=p;
            p=th;
        }
        vis[th->id]=1;
    }
    int t=0;
    std::stack<Node*>q;
    q.push(head);
    string s;
    while(!q.empty())
    {
        Node* th_p=q.top();
        s.append(std::to_string(th_p->id));
        q.pop();
        if(th_p->right_son!=NULL)
            q.push(th_p->right_son);
        if(th_p->left_son!=NULL)
            q.push(th_p->left_son);
        if(th_p->left_son!=NULL||th_p->right_son!=NULL)
        {
            s.append("(");
            t++;
        }
        else
        {
            if(th_p->father->right_son==th_p)
                s.append("),"),t--;
            else
                s.append(",");
        }
    }
    if(t){s[s.length()-1]=')',t--;}
    while(t--)s.append(")");
    cout<<s<<"\n";
}