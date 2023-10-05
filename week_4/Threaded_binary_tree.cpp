#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
using std::string;
using std::stack;
using std::queue;
/*
INPUT:
1(2,3(4,5(6,7)))

OUTPUT:
forward head:2
reverse head:7
size of tree:7
1 l:2 r:3
2 r:1
3 l:4 r:5
4 l:1 r:3
5 l:6 r:7
6 l:3 r:5
7 l:5 
2 1 4 3 6 5 7
7 5 6 3 4 1 2

*/
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
        std::cout << root->data <<" ";
       if(root->left!=NULL)
            std::cout<<"l:"<<root->left->data<<" ";
        if(root->right!=NULL)
            std::cout<<"r:"<<root->right->data<<" ";
        std::cout<<"\n";
        if(root->if_left)
            printTree(root->left);
        if(root->if_right)
            printTree(root->right);
    }
}
void forward(Threaded_Node* head,int n)
{
    for(int i=1;i<=n;i++)
    {
        std::cout<<head->data<<" ";
        if(head->if_right)
        {
            head=head->right;
            while(head->if_left)
            {
                head=head->left;
            }
        }
        else
        {  
            head=head->right;
        }
    }
    printf("\n");
}
void reverse(Threaded_Node* head,int n)
{
    for(int i=1;i<=n;i++)
    {
        std::cout<<head->data<<" ";
        if(head->if_left)
        {
            head=head->left;
            while(head->if_right)
            {
                head=head->right;
            }
        }
        else
        {  
            head=head->left;
        }
    }
}
void createThread(Threaded_Node* p,Threaded_Node*& pre,Threaded_Node*& forward_head)//对pre取址的原因是，保持全局性
{
	if(p==NULL)return;
    // if(p!=NULL&&pre!=NULL)
    //     std::cout<<p->data<<" "<<pre->data<<std::endl;
    createThread(p->left,pre,forward_head); 
	if (p->left==NULL)
	{
		p->left=pre;
		// p->if_left=1;
	}
	if (pre!=NULL&&pre->right==NULL)
	{
		pre->right=p;
		// pre->if_right=1;
	}
    if(pre==NULL)forward_head=p;
	pre=p;
    // std::cout<<p->data<<std::endl;
	createThread(p->right,pre,forward_head);
}
int main()
{
    int n=0;
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
                    n++;
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
                    n++;
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
                        n++;
                    }
                    nodeStack.pop();
                    if(!nodeStack.empty())
                    {
                        p=nodeStack.top();
                    }
                }
            }
        }
    }//通过读入括号序列循环建树
    Threaded_Node* pre=NULL;
    Threaded_Node* forward_head=NULL;
    Threaded_Node* reverse_head=NULL;
    createThread(head,pre,forward_head);
    reverse_head=pre;
    std::cout<<"forward head:"<<forward_head->data<<std::endl;
    std::cout<<"reverse head:"<<reverse_head->data<<std::endl;
    std::cout<<"size of tree:"<<n<<std::endl;
    printTree(head);
    forward(forward_head,n);
    reverse(reverse_head,n);
}