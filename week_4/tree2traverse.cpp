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
using std::stack;
class Node
{
    public:
        int id;
        Node* left=NULL;
        Node* right=NULL;
        Node* father;
        Node(int id){this->id=id;}
};
void post_traverse(Node* f)
{
    // cout<<f->id<<" "<<f->son.size()<<std::endl;
    if(f)
    {
        post_traverse(f->left);
        post_traverse(f->right);
        cout<<f->id<<" ";
    }
}
void pre_traverse(Node* f)
{
    if(f)
    {
        cout<<f->id<<" ";
        pre_traverse(f->left);
        pre_traverse(f->right);
    }
}
void deep_traverse(Node* f)
{
    std::queue<Node*>q;
    q.push(f);
    while(!q.empty())
    {
        Node *p=q.front();
        q.pop();
        cout<<p->id<<" ";
        if(p->left)
            q.push(p->left);
        if(p->right)
            q.push(p->right);
    }
}
int main()
{
    string s;
    std::cin>>s;
    int len=s.size();
    int num=0;
    Node* head=NULL;
    Node* p=NULL;
    stack<Node*> nodeStack;
    for(int i=0;i<len;i++)
    {
        if(s[i]<='9'&&s[i]>='0')
        {
            num=num*10+s[i]-'0';
        }
        else
        {
            if(s[i]=='(')
            {
                if(num)
                {
                    Node* a=new Node(num);
                    if(p==NULL)
                    {
                        head=a;
                    }
                    else
                    {
                        if(p->left)
                        {
                            p->right=a;
                        }
                        else
                        {
                            p->left=a;
                        }
                    }
                    nodeStack.push(a);
                    p=a;
                    num=0;
                }
            }
            else if(s[i]==',')
            {
                if(num)
                {
                    Node* a=new Node(num);
                    p->left=a;
                    num=0;
                }
            }else if(s[i]==')')
            {
                if(!nodeStack.empty())
                {
                    if(num)
                    {
                        Node* a=new Node(num);
                        p=nodeStack.top();
                        p->right=a;
                        num=0;
                    }
                    nodeStack.pop();
                    if(!nodeStack.empty())
                    {
                        p=nodeStack.top();
                    }
                }
            }
        }
    }
    cout<<"后序遍历: ";
    post_traverse(p);//后序遍历
    cout<<"\n";
    cout<<"先序遍历: ";
    pre_traverse(p);//先序遍历
    cout<<"\n层次遍历: ";
    deep_traverse(p);
}