#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#include <unordered_map>
using std::pair;
using std::atan;
using std::cin;
using std::cout;
using std::vector;
using std::atan2;
using std::sort;
using std::priority_queue;
using std::map;
/*
如何确定顺序？
0-360

规定：
点、平行于视线的边无法阻挡视线。

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
        double dis=0;
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
            this->dis=p.dis;
        }
        void  print() const
        {
            cout<<x<<" "<<y<<"\n";// "<<degree<<" "<<dis<<"\n";
        };
        void update(node* p)
        {
            double tmp_x=x-p->x;
            double tmp_y=y-p->y;
            dis=std::sqrt(tmp_x*tmp_x+tmp_y*tmp_y);
            // cout<<"更新后:"<<this->dis<<"\n";
            degree=Angle(tmp_x,tmp_y);
        };
        bool operator==(const node & rec) const
        {
            return x==rec.x&&y==rec.y;
        }
};

struct NodeHash 
{
    std::size_t operator()(const node& p) const 
    {
        return std::hash<double>()(p.x) ^ std::hash<double>()(p.y);
    }
};
class edge
{
    public:
        node *start=NULL;
        node *end=NULL;
        edge(node *start,node *end):start(start),end(end){};
        edge(node start,node end){
            node* tmp=new node(start.x,start.y);
            this->start=tmp;
            tmp=new node(end.x,end.y);
            this->end=tmp;
        };
        void print()
        {
            cout<<"线段端点为:\n";
            start->print();
            end->print();
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
        void add_edge(vector<edge> edges)
        {
            for(int i=0;i<edges.size();i++)
            {
                edge_set.push_back(edges[i]);
            }
        };
        void add_edge(edge* tmp)
        {
            new edge(*tmp);
            edge_set.push_back(*tmp);
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

double get_x(edge e,node* p)
{
    double x1=e.start->x-p->x;
    double y1=e.start->y-p->y;
    double x2=e.end->x-p->x;
    double y2=e.end->y-p->y;
    if(y1*y2<0)
    {
        return (1.0*(x1-x2)/(y1-y2)*(-y2)+x2);
    }
    else if(y1==0)
    {
        return x1;
    }
    else if(y2==0)
    {
        return x2;
    }
    else return -1;
};
bool cmp(const node& a,const node& b)
{
    if(a.degree!=b.degree)
        return a.degree<b.degree;
    return a.dis<b.dis;
};

bool Visible_Node(const edge e,const node p,const node o)
{
    double x_1=o.x;
    double y_1=o.y;
    double x_2=e.start->x;
    double y_2=e.start->y;
    double x_3=e.end->x;
    double y_3=e.end->y;
    double tmp_1=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;
    x_1=p.x;
    y_1=p.y;
    double tmp_2=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;
    // cout<<"tmp_1:"<<tmp_1<<"\n";
    // cout<<"tmp_2:"<<tmp_2<<"\n";
    if(tmp_1*tmp_2<0)
    {
        return false;
    }
    else return true;
};

vector<node> Visible_Check(node* p,vector<polygon*> polygon_set)
{
    // cout<<"hi\n";
    // p->print();
    vector<node> vis_node;
    vector<node> all_node;
    vector<edge> all_edge;
    std::unordered_map<node,pair<edge,edge>,NodeHash> node_to_edge;

    std::unordered_map<node,int,NodeHash>node_to_polygon;
    // priority_queue<edge,vector<edge>,decltype(customCompare)>scan_line(customCompare);

    vector<edge>scan_line;

    for(int i=0;i<polygon_set.size();i++)
    {
        vector<node> tmp=polygon_set[i]->get_node_set();
        all_node.insert(all_node.end(),tmp.begin(),tmp.end());//获取所有点集
        vector<edge> tmp_edge=polygon_set[i]->get_edge_set();
        all_edge.insert(all_edge.end(),tmp_edge.begin(),tmp_edge.end());//获取所有边集
        for(int j=0;j<tmp.size();j++)
        {
            node* tmp_node=&tmp[j];
            edge* tmp_edge_1=&tmp_edge[j];
            edge* tmp_edge_2=&tmp_edge[(j-1+tmp.size())%tmp.size()];
            node_to_edge.insert({*tmp_node,std::make_pair(*tmp_edge_1,*tmp_edge_2)});
            node_to_polygon.insert({*tmp_node,i});
        }//建立node到edge的映射
    }
    // }
    for(int i=0;i<all_node.size();i++)
    {
        node* tmp=&all_node[i];
        tmp->update(p);
    }//更新所有点的距离和角度

    sort(all_node.begin(),all_node.end(),cmp);


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
        // if(y1==0&&x1>=0)
        // {
        //     scan_line.push_back(*tmp);
        // }
        // if(y2==0&&x2>=0)
        // {
        //     scan_line.push_back(*tmp);
        // }
    }//初始化0°扫描线

    for(int i=0;i<all_node.size();i++)
    {
        node tmp_node=all_node[i];//取出一个点
        // cout<<"当前点:";
        // tmp_node.print();
        //判断是否可见
        int index=0;
        // top.print();
        // cout<<node_to_polygon.at(*p)<<" "<<node_to_polygon.at(tmp_node)<<"\n";
        if(node_to_polygon.at(*p)==node_to_polygon.at(tmp_node))
        {
            // cout<<tmp_node.x<<" "<<tmp_node.y<<"\n";
            index=0;
        }
        else //if(!scan_line.empty())
        {
            // cout<<scan_line.size()<<"\n";
            if(scan_line.empty())
            {
                vis_node.push_back(tmp_node);
            }
            else
            {
                //cout<<"hihihihi\n";            
                edge top=scan_line[0];
                // cout<<"扫描线:";
                // top.print();
                if(Visible_Node(top,tmp_node,*p))
                {
                    // printf("可见\n");
                    vis_node.push_back(tmp_node);
                    index=0;   
                }
                else
                {
                    index=1;
                    while(index<scan_line.size()&&!Visible_Node(scan_line[index],tmp_node,*p))
                    {
                        index++;
                    }
                }
            }
        }

        // cout<<"hihihihihihih\n";

        // tmp_node.print();
        // cout<<"len: "<<scan_line.size()<<"\n";
        // cout<<"index:"<<index<<"\n";
        //更新扫描线
        edge tmp_edge_1=node_to_edge.at(tmp_node).first;
        edge tmp_edge_2=node_to_edge.at(tmp_node).second;

        //保证当前结点在start上
        if(tmp_edge_1.start->id!=tmp_node.id)
            std::swap(tmp_edge_1.start,tmp_edge_1.end);
        if(tmp_edge_2.start->id!=tmp_node.id)
            std::swap(tmp_edge_2.start,tmp_edge_2.end);
        
        //判断左右:ToLeft算法
        double x_1=p->x;
        double y_1=p->y;
        double x_2=tmp_node.x;
        double y_2=tmp_node.y;
        double x_3=tmp_edge_1.end->x;
        double y_3=tmp_edge_1.end->y;
        // cout<<x_1<<" "<<y_1<<" "<<x_2<<" "<<y_2<<" "<<x_3<<" "<<y_3<<"\n"; 
        double test_edge_1=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;

        x_3=tmp_edge_2.end->x;
        y_3=tmp_edge_2.end->y;
        double test_edge_2=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;

        x_1=tmp_edge_1.end->x;
        y_1=tmp_edge_1.end->y;
        double test_order=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;

        // cout<<"test_edge_1:"<<test_edge_1<<"\n";
        // cout<<"test_edge_2:"<<test_edge_2<<"\n";
        // cout<<"test_order:"<<test_order<<"\n";


        if(test_edge_1>0&&test_edge_2>0)
        {
            if(test_order>0)
            {
                scan_line.insert(scan_line.begin()+index,tmp_edge_2);
                scan_line.insert(scan_line.begin()+index,tmp_edge_1);
            }
            else
            {
                scan_line.insert(scan_line.begin()+index,tmp_edge_1);
                scan_line.insert(scan_line.begin()+index,tmp_edge_2);
            }
        }
        else
        {
            if(test_edge_1<0)
            {
                for(int j=index;j<scan_line.size();j++)
                {
                    if((scan_line[j].start->x==tmp_edge_1.start->x&&scan_line[j].start->y==tmp_edge_1.start->y)||(scan_line[j].end->x==tmp_edge_1.start->x&&scan_line[j].end->y==tmp_edge_1.start->y))
                    {
                        scan_line.erase(scan_line.begin()+j);
                        break;
                    }
                }
            }
            if(test_edge_2<0)
            {
                for(int j=index;j<scan_line.size();j++)
                {
                    if((scan_line[j].start->x==tmp_edge_2.start->x&&scan_line[j].start->y==tmp_edge_2.start->y)||(scan_line[j].end->x==tmp_edge_2.start->x&&scan_line[j].end->y==tmp_edge_2.start->y))
                    {
                        scan_line.erase(scan_line.begin()+j);
                        break;
                    }
                }
            }
            if(test_edge_1>0)
            {
                scan_line.insert(scan_line.begin()+index,tmp_edge_1);
            }
            if(test_edge_2>0)
            {
                scan_line.insert(scan_line.begin()+index,tmp_edge_2);
            }
        }
    }
    return vis_node;
}
void Visible_Map(graph* g,vector<polygon*> polygon_set)
{
    vector<node> node_set=g->node_set;//获取所有节点
    for(int i=0;i<node_set.size();i++)
    {
        node* p=&node_set[i];
        vector<node> vis_node;//用来记录可见节点
        // cout<<"当前点:";
        // p->print();
        vis_node=Visible_Check(p,polygon_set);
        for(int j=0;j<vis_node.size();j++)
        {
            // node* tmp=new node(vis_node[j].x,vis_node[j].y);
            edge* tmp_edge=new edge(*p,vis_node[j]);
            g->add_edge(tmp_edge);
            // cout<<"可见点:\n";
            // cout<<vis_node[j].x<<" "<<vis_node[j].y<<"\n";
        }
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

    g->add_edge(polygon_1->get_edge_set());
    g->add_edge(polygon_2->get_edge_set());
    // cout<<g->node_set.size()<<"\n";

    vector<polygon*> polygon_set;
    polygon_set.push_back(polygon_1);
    polygon_set.push_back(polygon_2);

    Visible_Map(g,polygon_set);
    for(int i=0;i<g->edge_set.size();i++)
    {
        g->edge_set[i].print();
    }
}