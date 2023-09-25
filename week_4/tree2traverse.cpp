#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using std::vector;
using std::string;
using std::cin;
using std::cout;
class Node
{
    public:
        int id;
        vector<Node*>son;
        Node* father;
        Node(int id){this->id=id;}
};
void post_traverse(Node* f)
{
    // cout<<f->id<<" "<<f->son.size()<<std::endl;
    for(auto s:f->son)
        post_traverse(s);
    cout<<f->id<<" ";
}
void pre_traverse(Node* f)
{
    // cout<<f->id<<" "<<f->son.size()<<std::endl;
    cout<<f->id<<" ";
    for(auto s:f->son)
        pre_traverse(s);
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
        for(auto s:p->son)
           q.push(s);
    }
}
int main()
{
    string s;
    cin>>s;
    int len=s.size();
    int num=0;
    Node* head;
    Node* p=NULL;
    for(int i=0;i<len;i++)
    {
        if(s[i]<='9'&&s[i]>='0')
        {
            num=num*10+s[i]-'0';
        }
        else
        {
            if(num)
            {
                Node* a=new Node(num);
                if(p!=NULL)
                {
                    // cout<<p<<std::endl;;
                    a->father=p;
                    p->son.push_back(a);
                    // cout<<num<<" "<<p->id<<" "<<p<<" "<<a<<std::endl;
                    p=a;
                }
                else 
                {
                    head=a;
                    p=a;
                }
                num=0;//清空
            }
            if(s[i]==',')
            {
                Node tmp=*p;
                p=tmp.father;
            }
            if(s[i]==')')
            {
                Node tmp=*p;
                p=tmp.father;
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