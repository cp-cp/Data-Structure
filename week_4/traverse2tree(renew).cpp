#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
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

按照mid_order的顺序入队，结点按照先序遍历的顺序建立，如果当前节点与队首元素一致，出队，下次的操作通过新的队首元素是否为其父亲或是否未被访问过，来进行判断。
若为其父亲，则继续出队，下一个继续判断。
若未被访问过，则为其右儿子。

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
    int mid_que[100];
    int vis[100];
    memset(vis,0,sizeof(vis));
    memset(mid_que,0,sizeof(mid_que));
    for(int i=1;i<=n;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        pre_que.push(tmp);
    }//读入先序遍历
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&mid_que[i]);
    }//读入中序遍历
    int* p_mid_que=mid_que+1;//指向第一个元素
    Node* head=new Node(pre_que.front());
    pre_que.pop();
    Node* p=head;
    // cout<<*(p_mid_que+1)<<std::endl;
    while(!pre_que.empty())//以先序遍历为蓝本,建立树的形式
    {
        int num=pre_que.front();
        pre_que.pop();
        Node* th=new Node(num);
        cout<<num<<" "<<p->id<<" "<<*p_mid_que<<std::endl;
        if(p->id==*p_mid_que)
        {
            while(p!=head&&((*(p_mid_que+1))==p->father->id||p->right_son!=NULL))
            {
                p=p->father;
                p_mid_que++;
            }
            cout<<num<<" "<<p->id<<std::endl;
            p->right_son=th;
            th->father=p;
            p=th;
            p_mid_que++;
        }
        else
        {
            p->left_son=th;
            th->father=p;
            p=th;
        }
    }
    std::queue<Node*>q;
    q.push(head);
    string s;
    while(!q.empty())
    {
        Node* th_p=q.front();
        s.append(std::to_string(th_p->id));
        q.pop();
        if(th_p->left_son!=NULL)
            q.push(th_p->left_son);
        if(th_p->right_son!=NULL)
            q.push(th_p->right_son);
        if(th_p->left_son!=NULL||th_p->right_son!=NULL)
        {
            s.append("(");
        }
        else
        {
            s.append(",");
        }
    }
    cout<<s<<"\n";
    dfs(head);
}