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
        void print()
        {
            cout<<"线段端点为:";
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
    double x_1=e.start->x;
    double y_1=e.start->y;
    double x_2=e.end->x;
    double y_2=e.end->y;
    double x_3=p.x;
    double y_3=p.y;
    double x_4=o.x;
    double y_4=o.y;
    double tmp_1=x_1*y_2+x_2*y_3+x_3*y_1-x_1*y_3-x_2*y_1-x_3*y_2;
    double tmp_2=x_1*y_2+x_2*y_4+x_4*y_1-x_1*y_4-x_2*y_1-x_4*y_2;
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
    auto customCompare = [&p](const edge& a, const edge& b) {
        double a_x=get_x(a,p);
        double b_x=get_x(b,p);
        return a_x>b_x;
    };
    // priority_queue<edge,vector<edge>,decltype(customCompare)>scan_line(customCompare);

    vector<edge>scan_line;

    for(int i=0;i<polygon_set.size();i++)
    {
        vector<node> tmp=polygon_set[i]->get_node_set();
        all_node.insert(all_node.end(),tmp.begin(),tmp.end());//获取所有点集
        vector<edge> tmp_edge=polygon_set[i]->get_edge_set();
        all_edge.insert(all_edge.end(),tmp_edge.begin(),tmp_edge.end());//获取所有边集
        for(int i=0;i<tmp.size();i++)
        {
            node* tmp_node=&tmp[i];
            edge* tmp_edge_1=&tmp_edge[i];
            edge* tmp_edge_2=&tmp_edge[(i-1+tmp.size())%tmp.size()];

            node_to_edge.insert({*tmp_node,std::make_pair(*tmp_edge_1,*tmp_edge_2)});
        }//建立node到edge的映射
    }

    // for(auto it=node_to_edge.begin();it!=node_to_edge.end();it++)
    // {
    //     node tmp_node=it->first;
    //     cout<<"node:\n";tmp_node.print();
    //     pair<edge,edge> tmp_edge=it->second;
    //     cout<<"edge:\n";tmp_edge.first.print();tmp_edge.second.print();
    //     cout<<"\n";
    // }
    for(int i=0;i<all_node.size();i++)
    {
        node* tmp=&all_node[i];
        tmp->update(p);
    }//更新所有点的距离和角度

    // cout<<"更新后:\n";
    // for(int i=0;i<all_node.size();i++)
    // {
    //     all_node[i].print();
    // }//打印所有点

    sort(all_node.begin(),all_node.end(),cmp);

    // sort(all_node.begin(),all_node.end(),[](const node& a,const node& b){
    //         if(a.degree==b.degree)
    //             return a.dis<b.dis;
    //         else  
    //             return a.degree<b.degree;
    //     });//排序

    // cout<<"排序后:\n";
    // for(int i=0;i<all_node.size();i++)
    // {
    //     all_node[i].print();
    // }//打印所有点

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
        // cout<<i<<":";tmp_node.print();
        //判断是否可见
        edge top=scan_line[0];
        int index=0;
        if(Visible_Node(top,tmp_node,*p))
        {
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
        // tmp_node.print();
        // cout<<"index:"<<index<<"\n";
        //更新扫描线
        /*
            考虑如何由点确定边？
            已知一个点一定对应于两条边。
            考虑下面这些方案：
            方案1:在边集中找到这两条边，单次查询O(N)
            方案2:用map建立,点到pair<edge,edge>的关系，单次查询O(logN)
            那么这里采用方案2.
            是否有更好的处理方式？？？
        */
        // cout<<vis_node.size();
        // node * tmp_o=new node(0,0);
        // tmp_node.update(tmp_o);

        // tmp_node.print();

        edge tmp_edge_1=node_to_edge.at(tmp_node).first;
        
        cout<<"点"<<tmp_node.x<<" "<<tmp_node.y<<"\n";
        // tmp_edge_1.print();


        node* tmp_node_1_1=tmp_edge_1.start;
        node* tmp_node_1_2=tmp_edge_1.end;
        if(tmp_node_1_1->degree>tmp_node_1_2->degree)
        {
            node* tmp=tmp_node_1_1;
            tmp_node_1_1=tmp_node_1_2;
            tmp_node_1_2=tmp;
        }//保证tmp_node_1_1的degree小于tmp_node_1_2
        if(tmp_node.degree<tmp_node_1_2->degree)//如果是较小的那个
        {
            scan_line.insert(scan_line.begin()+index,tmp_edge_1);
        }

        
        edge tmp_edge_2=node_to_edge.at(tmp_node).second;


        node* tmp_node_2_1=tmp_edge_2.start;
        node* tmp_node_2_2=tmp_edge_2.end;
        if(tmp_node_2_1->degree>tmp_node_2_2->degree)
        {
            node* tmp=tmp_node_2_1;
            tmp_node_2_1=tmp_node_2_2;
            tmp_node_2_2=tmp;
        }//保证tmp_node_2_1的degree小于tmp_node_2_2
        if(tmp_node.degree<tmp_node_2_2->degree)//如果是较小的那个
        {
            // cout<<"--------\n";
            scan_line.insert(scan_line.begin()+index,tmp_edge_2);
        }
        cout<<"扫描线:"<<scan_line.size()<<"\n";
        edge tmp_eddge=scan_line[0];
        tmp_eddge.print();
    }
    
    // cout<<"可见点:\n";
    // for(int i=0;i<vis_node.size();i++)
    // {
    //     vis_node[i].print();
    // }//打印可见点

    return vis_node;
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
    node* p=new node(0,0);
    Visible_Check(p,polygon_set);
    // g->pr_node();
    cout<<"hi\n";
}