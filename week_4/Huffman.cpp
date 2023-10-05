#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using std::vector;
using std::map;
using std::queue;
using std::string;
/*
    输入一段文字(仅包含26个英文字母)，统计出数字并且获取哈夫曼编码。
INPUT:
in computer science and information theory, a huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. the process of finding or using such a code is huffman coding, an algorithm developed by david a. huffman while he was a sc.d. student at mit, and published in the 1952 paper "a method for the construction of minimum-redundancy codes".

OUTPUT:
char :"a";times:25
char :"b";times:2
char :"c";times:17
char :"d";times:20
char :"e";times:27
char :"f";times:14
char :"g";times:4
char :"h";times:14
char :"i";times:24
char :"l";times:9
char :"m";times:15
char :"n";times:23
char :"o";times:27
char :"p";times:11
char :"r";times:15
char :"s";times:21
char :"t";times:20
char :"u";times:13
char :"v";times:2
char :"w";times:2
char :"x";times:1
char :"y";times:5
word: u;times 13;code: 0000
word: f;times 14;code: 0001
word: h;times 14;code: 0010
word: m;times 15;code: 0011
word: r;times 15;code: 0100
word: c;times 17;code: 0110
word: t;times 20;code: 0111
word: d;times 20;code: 1001
word: s;times 21;code: 1010
word: n;times 23;code: 1011
word: i;times 24;code: 1100
word: a;times 25;code: 1101
word: e;times 27;code: 1110
word: o;times 27;code: 1111
word: l;times 9;code: 01011
word: p;times 11;code: 10001
word: g;times 4;code: 010101
word: y;times 5;code: 100001
word: x;times 1;code: 0101000
word: b;times 2;code: 0101001
word: w;times 2;code: 1000000
word: v;times 2;code: 1000001
*/
class Huffman
{
    public:
        class huffman_node
        {
            public:
                char c;//代表的字符
                int weight;//权重
                string huffman_code;//当前节点的代表代码
                huffman_node *left;
                huffman_node *right;
        };
        void Huffman_Build(map<char,int>word);
        void Print();    
        void GenerateHuffmanCodes(huffman_node *node, string code);
    private:
        huffman_node* root=NULL;
        static bool sort_by_weight(huffman_node *a, huffman_node *b)
        {
            return a->weight < b->weight;
        }
};
void Huffman::Huffman_Build(map<char,int>words)
{
    vector<huffman_node *> huffman_tree_node;
    for(auto word:words)
    {
        // huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
        huffman_node *node = new huffman_node();
        node->c=word.first;
        node->weight=word.second;
        node->left=NULL;
        node->right=NULL;
        huffman_tree_node.push_back(node);
    }//为每一个节点申请地址并且放到vector中。
    while (huffman_tree_node.size()>0)
    {
        std::sort(huffman_tree_node.begin(), huffman_tree_node.end(), sort_by_weight);
        // 取出前两个节点
        if (huffman_tree_node.size() == 1)
        {
                root = huffman_tree_node[0];
                huffman_tree_node.erase(huffman_tree_node.begin());
        }
        else
        {
                huffman_node *node_1 = huffman_tree_node[0];
                huffman_node *node_2 = huffman_tree_node[1];
                huffman_tree_node.erase(huffman_tree_node.begin());
                huffman_tree_node.erase(huffman_tree_node.begin());
                // huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
                huffman_node *node = new huffman_node();
                node->weight = node_1->weight + node_2->weight;
                if(node_1->weight<node_2->weight)
                {
                    node->left=node_1;
                    node->right=node_2;
                }
                else 
                {
                    node->left=node_2;
                    node->right=node_1;
                }//左小右大
                huffman_tree_node.push_back(node);//继续放入
        }
    }
    GenerateHuffmanCodes(root, "");
}
void Huffman::GenerateHuffmanCodes(huffman_node *node, string code)
{
    // printf("hi");
    if (node)
    {
        if (node->left)
        {
            node->left->huffman_code= code+"0";
            GenerateHuffmanCodes(node->left, node->left->huffman_code);
        }

        if (node->right)
        {
            node->right->huffman_code=code+"1";
            GenerateHuffmanCodes(node->right, node->right->huffman_code);
        }
    }
}
void Huffman::Print()
{
    queue<huffman_node*>q;
    // printf("111");
    // if(root!=NULL)
    //     root->huffman_code="0";
    // printf("222");
    q.push(root);
    while(!q.empty())
    {
        huffman_node* p=q.front();
        q.pop();
        if(p->right!=NULL)
        {
            q.push(p->left);
            q.push(p->right);
        }
        else
        {
            // printf("%c\n",p->c);
            std::cout<<"word: "<<p->c<<";times "<<p->weight<<";code: "<<p->huffman_code<<std::endl;
        }
    }
}
int main()
{
    string s;
    // std::cin>>s;
    getline(std::cin,s);
    map<char, int> words;
    for(char c='a';c<='z';c++)
    {
        int num=std::count(s.begin(),s.end(),c);
        if(num)
        {
            printf("char :\"%c\";times:%d\n",c,num);
            words[c]=num;
        }
    }

    // words['a'] = 5;
    // words['b'] = 9;
    // words['c'] = 12;

    Huffman huffmanTree;
    huffmanTree.Huffman_Build(words);
    huffmanTree.Print();
    return 0;
}