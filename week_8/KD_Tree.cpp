#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using std::vector;
using std::cin;
using std::cout;
using std::sort;
/*
5 2
1 0
2 1
3 2
4 3
5 4

2 5

OUTPUT:
4 3
*/
class KD_Tree{
    int Dim;
    class Node{
        public:
            vector<int>data;
            int split;
            Node *left=NULL;
            Node *right=NULL;
            Node(vector<int>data,int split):data(data),split(split){};
            void Print(){
                cout<<"»®·ÖÎ¬¶È"<<split<<" ";
                for(int i=0;i<data.size();i++)
                    cout<<data[i]<<" ";
                cout<<"\n";
            }
    };
    Node* Build(vector<vector<int>> &vertex,int split);
    public:
        Node *root=NULL;
        KD_Tree(int d):Dim(d),root(nullptr){};
        KD_Tree(vector<vector<int>> &vertex, int d);
        void dfs(Node* root);
        vector<int> Find_Nearest_Neighbor(vector<int> node);
        Node* Find_Nearest(vector<int> node,Node* root);
        double Distance(vector<int>a,vector<int>b);
};
double KD_Tree::Distance(vector<int> a,vector<int> b)
{
    double value=0;
    for(int i=0;i<this->Dim;i++)
    {
        value+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return std::sqrt(value);
}
bool cmp(const vector<int> &a, const vector<int> &b, int split)
{
    return a[split] < b[split];
}
KD_Tree::Node* KD_Tree::Find_Nearest(vector<int>node,KD_Tree::Node* root)
{
    if(root->left==NULL&&root->right==NULL)
    {
        return root;
    }
    if(root->left!=NULL&&root->right!=NULL)
    {
        int split=root->split;
        if(node[split]<root->data[split])
        {
            Node* tmp=Find_Nearest(node,root->left);
            double dis_1=Distance(tmp->data,node);
            if(dis_1>std::abs(node[split]-root->data[split]))
            {
                Node* tmp_tmp=Find_Nearest(node,root->right);
                double dis_2=Distance(tmp_tmp->data,node);
                if(dis_1<dis_2)return tmp;
                else return tmp_tmp; 
            }
        }
        else
        {
            Node* tmp=Find_Nearest(node,root->right);
            double dis_1=Distance(tmp->data,node);
            if(dis_1>std::abs(node[split]-root->data[split]))
            {
                Node* tmp_tmp=Find_Nearest(node,root->left);
                double dis_2=Distance(tmp_tmp->data,node);
                if(dis_1<dis_2)return tmp;
                else return tmp_tmp; 
            }
        }
    }
    if(root->left!=NULL)return Find_Nearest(node,root->left);
    else return Find_Nearest(node,root->right);
}
vector<int> KD_Tree::Find_Nearest_Neighbor(vector<int> node)
{
    Node* ans=Find_Nearest(node,root);
    return ans->data;
}
KD_Tree::Node* KD_Tree::Build(vector<vector<int>> &vertex, int split)
{
    int len=vertex.size();
    if(len==1)
    {
        Node* root=new Node(vertex[0],split);
        return root;
    }
    sort(vertex.begin(), vertex.end(), [split](const vector<int>& a, const vector<int>& b){return cmp(a, b, split);});
    int split_id=len/2;
    Node* root=new Node(vertex[split_id],split);
    int next_spilt=(split+1)%this->Dim;
    vector<vector<int>> ver_lf;
    ver_lf.insert(ver_lf.begin(),vertex.begin(),vertex.begin()+std::max(split_id,1));
    root->left=Build(ver_lf,next_spilt);
    vector<vector<int>> ver_rt;
    if(split!=(len-1))
    {
        ver_rt.insert(ver_rt.begin(),vertex.begin()+std::max(split_id,1)+1,vertex.end());
        root->right=Build(ver_rt,next_spilt);
    }
    return root;
}
KD_Tree::KD_Tree(vector<vector<int>> &vertex, int d)
{
    this->Dim=d;
    this->root=Build(vertex,0);
}
void KD_Tree::dfs(Node* root)
{
    if(root==NULL)return;
    root->Print();
    dfs(root->left);
    dfs(root->right);
}
int main()
{
    int n,d;
    cin>>n>>d;
    vector<vector<int>>vertex;
    for(int i=0;i<n;i++)
    {
        vector<int>temp;
        for(int j=0;j<d;j++)
        {
            int x;
            cin>>x;
            temp.push_back(x);
        }
        vertex.push_back(temp);
    }
    KD_Tree* tree=new KD_Tree(vertex,d);
    tree->dfs(tree->root);
    vector<int>v;
    for(int i=0;i<d;i++)
    {
        int tmp;
        cin>>tmp;
        v.push_back(tmp);
    }
    vector<int>ans=tree->Find_Nearest_Neighbor(v);
    for(int i=0;i<d;i++)
        cout<<ans[i]<<" ";
}