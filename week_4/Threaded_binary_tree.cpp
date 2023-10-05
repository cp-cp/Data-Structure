#include<iostream>
#include<cstring>
#include<stack>
using std::string;
using std::stack;
class Threaded_Node
{
    public:
        Threaded_Node* left=NULL;
        bool if_left=false;        
        Threaded_Node* right=NULL;
        bool if_right=false;
        int data;//以整型为例
        Threaded_Node(int num):data(num){}

};
void printTree(Threaded_Node* root) {
    if (root) {
        printTree(root->left);
        std::cout << root->data << " ";
        printTree(root->right);
    }
}
int main()
{
    string s;
    std::cin>>s;
    int len=s.size();
    int num=0;
    Threaded_Node* head=NULL;
    Threaded_Node* p=NULL;
    stack<Threaded_Node*> nodeStack;
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
                    Threaded_Node* a=new Threaded_Node(num);
                    if(p==NULL)
                    {
                        head=a;
                    }
                    else
                    {
                        if(p->if_left)
                        {
                            p->right=a;
                            p->if_right=true;
                        }
                        else
                        {
                            p->left=a;
                            p->if_left=true;
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
                    Threaded_Node* a=new Threaded_Node(num);
                    p->left=a;
                    p->if_left=true;
                    num=0;
                }
            }else if(s[i]==')')
            {
                if(!nodeStack.empty())
                {
                    if(num)
                    {
                        Threaded_Node* a=new Threaded_Node(num);
                        p=nodeStack.top();
                        p->right=a;
                        p->if_right=true;
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
    printTree(head);
}