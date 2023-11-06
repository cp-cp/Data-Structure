#include<iostream>
using std::max;
class AVL_Node{
    public:
        int data;
        int height;
        int balance;
        int left_size=0;
        int right_size=0;
        AVL_Node* left;
        AVL_Node* right;
        AVL_Node(int data):data(data){};
};
class AVL_Tree{
    public:
        AVL_Node* root;
        AVL_Node* Left_Rotate(AVL_Node* root);
        AVL_Node* Right_Rotate(AVL_Node* root);
        AVL_Node* Right_Left_Rotate(AVL_Node* root);
        AVL_Node* Left_Right_Rotate(AVL_Node* root);
        AVL_Node* Insert(AVL_Node* node,int data);
        AVL_Node* Delete(AVL_Node* node,int data);
        AVL_Node* Max_Node(AVL_Node* node);
        AVL_Node* Min_Node(AVL_Node* node);
        int Height(AVL_Node* root);
};
AVL_Node* AVL_Tree::Max_Node(AVL_Node* node)
{
    if(node->right=NULL)return node;
    else return node->right;
}
AVL_Node* AVL_Tree::Min_Node(AVL_Node* node)
{
    if(node->left==NULL)return node;
    else return node->left;
}
AVL_Node* AVL_Tree::Insert(AVL_Node* node,int value)
{
    // std::cout<<value<<std::endl;
    if(node==NULL)
    {
        node=new AVL_Node(value);
        node->height=1;
    }
    else if(node->data<value)
    {
        node->right=Insert(node->right,value);//右节点
        node->right_size++;
        // std::cout<<node->data<<" "<<Height(node->left)<<" "<<Height(node->right)<<std::endl;
        if(std::abs(Height(node->left)-Height(node->right))>1)//出现异常
        {
            // printf("ERROR: %d\n",node->data);
            if(value>node->right->data)
                node=Left_Rotate(node);
            else
                node=Right_Left_Rotate(node);
        }
        node->height=max(Height(node->left),Height(node->right))+1;
    }
    else
    {
        node->left=Insert(node->left,value);//左节点
        node->left_size++;
        if(std::abs(Height(node->left)-Height(node->right))>1)//出现异常
        {
            if(value<node->left->data)
                node=Right_Rotate(node);
            else
                node=Left_Right_Rotate(node);
        }       
        node->height=max(Height(node->left),Height(node->right))+1;
    }
    return node;
}
/*
分为三种情况：
1.叶节点：直接删除。
2.有唯一子树：直接替换。
3.具有左右子树：转化为情况1。
*/
AVL_Node* AVL_Tree::Delete(AVL_Node* node,int value)
{
    if(node==NULL)
    {
        std::cout<<"ERROR: NOT FIND"<<std::endl;
        return NULL;
    }
    // std::cout<<node->data<<" ";
    if(value==node->data)
    {
        if(node->left==NULL&&node->right==NULL)//情况1
            return NULL;
        if(node->left==NULL)//情况2:左子树为空，右子树不为空：直接替换
        {
            // node->right_size--;
            return node->right;
        }
        if(node->right==NULL)//情况2:右子树为空，左子树不为空：直接替换
        {
            // node->left_size--;
            return node->left;
        }
        if(1)//剩下的就是情况3:左右子树都不为空
        {
            if(Height(node->left)>Height(node->right))//如果左子树比右子树要高，贪心的用左子树的叶节点来替换。
            {
                AVL_Node* max_node=Max_Node(node->left);
                node->data=max_node->data;
                node->left_size--;
                node->left=Delete(node->left,max_node->data);
            }
            else//如果右子树比左子树要高，贪心的用右子树的叶节点来替换。
            {
                AVL_Node* min_node=Min_Node(node->left);
                node->right_size--;
                node->data=min_node->data;
                node->left=Delete(node->left,min_node->data);
            }
        }
    }
    else if(value>node->data)//删除右节点
    {
        node->right=Delete(node->right,value);
        node->right_size--;
        if(std::abs(Height(node->left)-Height(node->left))>1)//失衡的话，肯定是左子树比右子树更高了
        {
            /*
                   5
                  /  
                 3    
                  \
                   4
            */
            if(Height(node->left->right)>Height(node->left->left))
                node=Left_Right_Rotate(node);
            /*
                    5
                   /
                  4
                 /
                3
            */
            else
                node=Right_Rotate(node);
        }
    }
    else
    {
        node->left=Delete(node->left,value);
        node->left_size--;
        if(std::abs(Height(node->left)-Height(node->left))>1)//失衡的话，肯定是右子树比左子树更高了
        {
            if(Height(node->right->left)>Height(node->right->right))
                node=Right_Left_Rotate(node);
            else
                node=Left_Rotate(node);
        }
    }
    return node;
}
int AVL_Tree::Height(AVL_Node* root)
{
    if(root==NULL)return 0;
    else return root->height;
}
/*
 1
  \
   2
    \
     3
*/
AVL_Node* AVL_Tree::Left_Rotate(AVL_Node* root)
{
    AVL_Node* right=root->right;
    root->right=right->left;
    right->left=root;

    int tmp=right->left_size;

    right->left_size=root->left_size+right->left_size+1;
    root->right_size=tmp;

    root->height=max(Height(root->left),Height(root->right))+1;//注意先更新root
    right->height=max(Height(right->left),Height(right->right))+1;



    return right;//更新根节点
}
/*
         3
        /
       2            
      /
     1
*/
AVL_Node* AVL_Tree::Right_Rotate(AVL_Node* root)
{
    AVL_Node* left=root->left;
    root->left=left->right;
    left->right=root;

    int tmp=left->right_size;
    left->right_size=root->right_size+left->right_size+1;
    root->left_size=tmp;


    root->height=max(Height(root->left),Height(root->right))+1;//注意先更新root
    left->height=max(Height(left->left),Height(left->right))+1;
    return left;//更新根节点
}
/*
   6
    \
      7
     /
    8
*/
AVL_Node* AVL_Tree::Right_Left_Rotate(AVL_Node* root)
{
    root->right=Right_Rotate(root->right);
    root->height=max(Height(root->left),Height(root->right))+1;
    return Left_Rotate(root);
}
/*
     4
    /
   3
    \
     2
*/
AVL_Node* AVL_Tree::Left_Right_Rotate(AVL_Node* root)
{
    root->left=Left_Rotate(root->left);
    root->height=max(Height(root->left),Height(root->right))+1;
    return Right_Rotate(root);
}

void dfs(AVL_Node* node)
{
    if(node==NULL)return;
    std::cout<<node->data<<" "<<node->left_size<<" "<<node->right_size<<" "<<node->height<<std::endl;
    dfs(node->left);
    // std::cout<<node->data<<" "<<node->left_size<<" "<<node->right_size<<" "<<node->height<<std::endl;
    dfs(node->right);
}
int main()
{
    AVL_Tree* t=new AVL_Tree();
    t->root=t->Insert(t->root,1);
    t->root=t->Insert(t->root,2);
    t->root=t->Insert(t->root,3);
    t->root=t->Insert(t->root,4);
    t->root=t->Insert(t->root,5);
    t->root=t->Insert(t->root,6);
    t->root=t->Insert(t->root,7);
    dfs(t->root);
}