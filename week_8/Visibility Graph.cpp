#include<iostream>
#include<vector>
#include<cmath>
using std::atan;
using std::cin;
using std::cout;
using std::vector;

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
        int x;
        int y;
        int id=-1;
        double degree=0;
        node(int x,int y,int id=-1):x(x),y(y),id(id)
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
class polygon
{
    vector<node>node_set;//强制规定按顺序插入！
    int node_num=0;
    public:
        node* max_node=NULL;
        node* min_node=NULL;
        polygon(){};
        void push_node(node p);
};
void polygon::push_node(node p)
{
    node* tmp=new node(p);
    this->node_set.push_back(*tmp);
    this->node_num++;
    if(max_node==NULL)max_node=tmp;
    if(min_node==NULL)min_node=tmp;
    if(max_node->degree-p.degree<0)max_node=tmp;
    if(min_node->degree-p.degree>0)min_node=tmp;
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

    polygon* polygon_2=new polygon();
    polygon_2->push_node({2,0,1});
    polygon_2->push_node({3,-1,2});
    polygon_2->push_node({5,1,3});
    polygon_2->push_node({4,-2,4});
    polygon_2->push_node({2,-4,5});
    polygon_2->push_node({1,-1,6});

    
}