#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using std::atan;
using std::cin;
using std::cout;
using std::vector;
using std::atan2;
using std::sort;

/*
如何确定顺序？
0-360？
*/


double Angle(double x, double y) {
    double angle = atan2(y, x);
    if (angle < 0) 
        angle+=2*M_PI;
    return angle;
}
class node
{
    public:
        double x;
        double y;
        int id=-1;
        double degree=0;
        node(double x,double y,int id=-1):x(x),y(y),id(id)
        {
            degree=Angle(x,y);
        };
        node(){};
        node(const node &p)
        {
            this->x=p.x;
            this->y=p.y;
            this->id=p.id;
            this->degree=p.degree;
        }
        void print()
        {
            cout<<x<<" "<<y<<" "<<degree<<"\n";
        };
};
class edge
{
    public:
        node *start;
        node *end;
        edge(node *start,node *end):start(start),end(end){};
        void print()
        {
            cout<<"相交的线段为:\n";
            start->print();
            end->print();
            // cout<<start->id<<" "<<end->id<<"\n";
        };
};
class graph
{
    public:
        vector<node>node_set;
        vector<edge>edge_set;
        graph(){};
        void push_node(node p);
        void print_node()
        {
            for(int i=0;i<node_set.size();i++)
            {
                node_set[i].print();
            }
        };
        void add_node(vector<node> nodes)
        {
            for(int i=0;i<nodes.size();i++)
            {
                node_set.push_back(nodes[i]);
            }
        };
};
class polygon
{
    int node_num=0;
    vector<node>node_set;//强制规定按~顺序插入！
    vector<edge>edge_set;
    public:
        node* max_node=NULL;
        node* min_node=NULL;
        polygon(){};
        void push_node(node p);
        void add_edge(node p1,node p2)
        {
            edge* tmp=new edge(&p1,&p2);
        };
        void set_edge()
        {
            for(int i=0;i<node_set.size();i++)
            {
                node* p1=&node_set[i];
                node* p2=&node_set[(i+1)%node_set.size()];
                edge* tmp=new edge(p1,p2);
                edge_set.push_back(*tmp);
            }
        };
        vector<node> get_node_set(){return this->node_set;};
        vector<edge> get_edge_set(){return this->edge_set;};
};
vector<node> Visible_Check(node* p,vector<polygon*> polygon_set)
{
    cout<<"hi\n";
    p->print();
    vector<node> vis_node;
    vector<node> all_node;
    vector<edge> all_edge;
    vector<edge> scan_line;
    // priority_queue<node> scan_line;
    for(int i=0;i<polygon_set.size();i++)
    {
        vector<node> tmp=polygon_set[i]->get_node_set();
        all_node.insert(all_node.end(),tmp.begin(),tmp.end());
        vector<edge> tmp_edge=polygon_set[i]->get_edge_set();
        all_edge.insert(all_edge.end(),tmp_edge.begin(),tmp_edge.end());
    }//获取所有点集和边集
    sort(all_node.begin(),all_node.end(),[p](const node& a,const node& b){return a.degree<b.degree;});//排序
    for(int i=0;i<all_edge.size();i++)
    {
        edge* tmp=&all_edge[i];
        node* node_1=tmp->start;
        node* node_2=tmp->end;
        double x1=node_1->x-p->x;
        double y1=node_1->y-p->y;
        double x2=node_2->x-p->x;
        double y2=node_2->y-p->y;
        if(y1*y2<0)
        {
            if((1.0*(x1-x2)/(y1-y2)*(-y2)+x2)>=0)
            {
                scan_line.push_back(*tmp);
            }
        }
        if(y1==0&&x1>=0)
        {
            scan_line.push_back(*tmp);
        }
        if(y2==0&&x2>=0)
        {
            scan_line.push_back(*tmp);
        }
    }
    for(int i=0;i<scan_line.size();i++)
    {
        scan_line[i].print();
    }



    return vis_node;
    // while(all_node[0].degree==0)
    // {
    //     node tmp=all_node[0];
    //     all_node.erase(all_node.begin());
    //     vis_node.push_back(tmp);
    //     //考虑如何由点确定边？
    // }
}
void Visible_Map(graph* g,vector<polygon*> polygon_set)
{
    vector<node> node_set=g->node_set;//获取所有节点
    for(int i=0;i<node_set.size();i++)
    {
        node* p=&node_set[i];
        vector<node> vis_node;//用来记录可见节点
        vis_node=Visible_Check(p,polygon_set);
    }
}
void polygon::push_node(node p)
{
    node* tmp=new node(p);
    this->node_set.push_back(*tmp);
    this->node_num++;
    if(max_node==NULL)max_node=tmp;
    if(min_node==NULL)min_node=tmp;
    if(max_node->degree-p.degree<0)max_node=tmp;
    if(min_node->degree-p.degree>0)min_node=tmp;
    if(this->node_num>1)
    this->add_edge(*tmp,(this->node_set[this->node_num-2]));
}
int main()
{
    //设计起点
    node* start_node=new node(0,0);
    polygon* polygon_1=new polygon();
    polygon_1->push_node({1,2,1});
    polygon_1->push_node({1,4,2});
    polygon_1->push_node({3,5,3});
    polygon_1->push_node({4,1,4});
    polygon_1->push_node({3,0,5});
    polygon_1->set_edge();

    polygon* polygon_2=new polygon();
    polygon_2->push_node({2,0,1});
    polygon_2->push_node({3,-1,2});
    polygon_2->push_node({5,1,3});
    polygon_2->push_node({4,-2,4});
    polygon_2->push_node({2,-4,5});
    polygon_2->push_node({1,-1,6});
    polygon_2->set_edge();


    graph* g=new graph();
    g->add_node(polygon_1->get_node_set());
    g->add_node(polygon_2->get_node_set());
    // cout<<g->node_set.size()<<"\n";

    vector<polygon*> polygon_set;
    polygon_set.push_back(polygon_1);
    polygon_set.push_back(polygon_2);

    // Visible_Map(g,polygon_set);
    node* p=new node(2,4);
    Visible_Check(p,polygon_set);
    // g->pr_node();
    // cout<<"hi\n";
}