#include<iostream>
#include<map>
#include <sstream>
#include<string>
#include<tuple>
using std::map;
using std::string;
/*

实现内容：
1.建立魔方模型。
2.LRUDFB六个面的旋转。
3.打印魔方展开图，并绘制颜色。


展开图与此网站的顺序一致https://rubiks-cube-solver.com/zh/

考虑生成一个魔方class，能够执行各种旋转。
前(F)后(B)左(L)右(R)上(U)下(D)
并且以顺时针旋转作为正向.

如何表示各个面？
采取最直观的3*3*6，面表示法。
规定魔方各面的顺序如下。
F:
    U
L       R
    D

R:
    U
F       B
    D

B:
    U
R       L
    D

L:
    U
B       F
    D

U:
    B
L       R
    F

D:
    B
R       L
    F
*/
class Cube
{
    public:
    map<char,char(*)[3]>Polyhedral;
    map<char,int>face_id={
        {'U',0},
        {'D',1},
        {'F',2},
        {'B',3},
        {'L',4},
        {'R',5}
    };
    map<int,char>id_face={
        {0,'U'},
        {1,'D'},
        {2,'F'},
        {3,'B'},
        {4,'L'},
        {5,'R'}
    };
    map<char, map<char,std::pair<int,int>>>face_map={
        {'F', {
            {'L', {0, -1}},
            {'U', {-1, 0}},
            {'R', {0, 1}},
            {'D', {1, 0}}
        }},
        {'R', {
            {'U', {-1, 0}},
            {'F', {0, -1}},
            {'D', {1, 0}},
            {'B', {0, 1}}
        }},
        {'B', {
            {'R', {0, -1}},
            {'U', {-1, 0}},
            {'L', {0, 1}},
            {'D', {1, 0}}
        }},
        {'L', {
            {'U', {-1, 0}},
            {'B', {0, -1}},
            {'D', {1, 0}},
            {'F', {0, 1}}
        }},
        {'U', {
            {'B', {-1, 0}},
            {'L', {0, -1}},
            {'R', {0, 1}},
            {'F', {1, 0}}
        }},
        {'D', {
            {'B', {-1, 0}},
            {'R', {0, -1}},
            {'L', {0, 1}},
            {'F', {1, 0}}
        }}
    };
    void performMoves(const string& moves);
    void performSingleMove(char face);
    void L();
    void R();
    void F();
    void B();
    void U();
    void D();
    //std::cout<<"步骤一：拼个底面十字"<<std::endl;
    void fix_bottom_cross();
    // std::cout<<"步骤二：拼完底面"<<std::endl;
    void fix_bottom_total();
    // std::cout<<"步骤三：拼中间层"<<std::endl;
    void fix_middle();
    // std::cout<<"步骤四：拼顶面十字并对齐"<<std::endl;
    bool fix_upper_cross();
    // std::cout<<"步骤五：拼顶面"<<std::endl;
    void fix_upper_total();
    // std::cout<<"步骤六：顶面棱角对齐"<<std::endl;
    void fix_final();
    void Open_Show();
    bool Check();
    void Reset();
    void print(char c);
    std::pair<char,char> Find_Color(char col_1,char col_2);
    std::tuple<char,char,char> Find_Color_Sharp(char col_1,char col_2,char col_3);
    std::pair<char,char> Get_Edge(char eg_1,char eg_2);
    void Show(char side){
        printf("Side %c:\n",side);
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                std::cout<<this->Polyhedral[side][i][j]<<' ';
            std::cout<<std::endl;
        }
    }
    Cube(){
        char (*Up_Side)[3] = new char[3][3]{
            {'U', 'U', 'U'},
            {'U', 'U', 'U'},
            {'U', 'U', 'U'}
        };
        char (*Down_Side)[3] = new char[3][3]{
            {'D', 'D', 'D'},
            {'D', 'D', 'D'},
            {'D', 'D', 'D'}
        };
        char (*Front_Side)[3] = new char[3][3]{
            {'F', 'F', 'F'},
            {'F', 'F', 'F'},
            {'F', 'F', 'F'}
        };
        char (*Back_Side)[3] = new char[3][3]{
            {'B', 'B', 'B'},
            {'B', 'B', 'B'},
            {'B', 'B', 'B'}
        };
        char (*Left_Side)[3] = new char[3][3]{
            {'L', 'L', 'L'},
            {'L', 'L', 'L'},
            {'L', 'L', 'L'}
        };
        char (*Right_Side)[3] = new char[3][3]{
            {'R', 'R', 'R'},
            {'R', 'R', 'R'},
            {'R', 'R', 'R'}
        };
        this->Polyhedral['U']=Up_Side;
        this->Polyhedral['D']=Down_Side;
        this->Polyhedral['F']=Front_Side;
        this->Polyhedral['B']=Back_Side;
        this->Polyhedral['L']=Left_Side;
        this->Polyhedral['R']=Right_Side;
    }
};
template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) {
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}
void Cube::Reset()
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                Polyhedral[id_face[i]][j][k]=id_face[i];
            }
        }
    }
}
bool Cube::Check()
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                if(Polyhedral[id_face[i]][j][k]!=id_face[i])
                    return false;
            }
        }
    }
    return true;
}
void Cube::performMoves(const std::string &moves) {
    std::istringstream iss(moves);
    std::string move;
    while (iss >> move) {
        char face = move[0];
        int count = 1;
        if (move.length() > 1) {
            char direction = move[1];
            if (direction == '\'') {
                count = 3; // Counter-clockwise (3 times)
            } else if (direction == '2') {
                count = 2; // 180 degrees (2 times)
            }
        }
        for (int i = 0; i < count; i++) {
            performSingleMove(face);
        }
    }
}
void Cube::performSingleMove(char face) {
    // std::cout << "Performing move: " << face << std::endl;
    switch (face) {
        case 'U':
            U();
            break;
        case 'D':
            D();
            break;
        case 'L':
            L();
            break;
        case 'R':
            R();
            break;
        case 'F':
            F();
            break;
        case 'B':
            B();
            break;
        default:
            std::cout << "Invalid move: " << face << std::endl;
    }
}
void Cube::L()
{
    if(1)//UFDB -> BUFD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['L'][0][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['L'][0][i]=Polyhedral['L'][i][0];//U->B
        for(int i=0;i<3;i++)
            Polyhedral['L'][i][0]=Polyhedral['L'][2][i];//B->D
        for(int i=0;i<3;i++)
            Polyhedral['L'][2][i]=Polyhedral['L'][2-i][2];//D->F
        for(int i=0;i<3;i++)
            Polyhedral['L'][i][2]=temp[i];//F->U
    }
    if(1)
    { 
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['U'][i][0];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['U'][i][0]=Polyhedral['B'][2-i][2];//U->B
        for(int i=0;i<3;i++)
            Polyhedral['B'][i][2]=Polyhedral['D'][i][2];//B->D
        for(int i=0;i<3;i++)
            Polyhedral['D'][i][2]=Polyhedral['F'][2-i][0];//D->F
        for(int i=0;i<3;i++)
            Polyhedral['F'][i][0]=temp[i];//F->U
    }
}
void Cube::R()
{
    if(1)//UBDF -> FUBD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['R'][0][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['R'][0][i]=Polyhedral['R'][i][0];//U->F
        for(int i=0;i<3;i++)
            Polyhedral['R'][i][0]=Polyhedral['R'][2][i];//L->D
        for(int i=0;i<3;i++)
            Polyhedral['R'][2][i]=Polyhedral['R'][2-i][2];//D->B
        for(int i=0;i<3;i++)
            Polyhedral['R'][i][2]=temp[i];//B->U
    }
    if(1)//UBDF -> FUBD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['U'][i][2];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['U'][i][2]=Polyhedral['F'][i][2];//U->F
        for(int i=0;i<3;i++)
            Polyhedral['F'][i][2]=Polyhedral['D'][2-i][0];//F->D
        for(int i=0;i<3;i++)
            Polyhedral['D'][i][0]=Polyhedral['B'][i][0];//D->B
        for(int i=0;i<3;i++)
            Polyhedral['B'][i][0]=temp[2-i];//B->U
    }
}
void Cube::F()
{
    if(1)//URDL -> LURD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['F'][0][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['F'][0][i]=Polyhedral['F'][i][0];//U->L
        for(int i=0;i<3;i++)
            Polyhedral['F'][i][0]=Polyhedral['F'][2][i];//L->D
        for(int i=0;i<3;i++)
            Polyhedral['F'][2][i]=Polyhedral['F'][2-i][2];//D->R
        for(int i=0;i<3;i++)
            Polyhedral['F'][i][2]=temp[i];//R->U
    }
    if(1)//URDL -> LURD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['U'][2][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['U'][2][i]=Polyhedral['L'][2-i][2];//U->L
        for(int i=0;i<3;i++)
            Polyhedral['L'][i][2]=Polyhedral['D'][2][2-i];//L->D
        for(int i=0;i<3;i++)
            Polyhedral['D'][2][2-i]=Polyhedral['R'][2-i][0];//D->R
        for(int i=0;i<3;i++)
            Polyhedral['R'][i][0]=temp[i];//R->U
    }
}
void Cube::B()
{
    if(1)//ULDR -> RULD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['B'][0][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['B'][0][2-i]=Polyhedral['B'][i][0];//U->R
        for(int i=0;i<3;i++)
            Polyhedral['B'][i][0]=Polyhedral['B'][2][i];//R->D
        for(int i=0;i<3;i++)
            Polyhedral['B'][2][i]=Polyhedral['B'][2-i][2];//D->L
        for(int i=0;i<3;i++)
            Polyhedral['B'][i][2]=temp[i];//L->U
    }
    if(1)//ULDR -> RULD
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['U'][0][i];// Save U
        for(int i=0;i<3;i++)
            Polyhedral['U'][0][i]=Polyhedral['R'][i][2];//U->R
        for(int i=0;i<3;i++)
            Polyhedral['R'][i][2]=Polyhedral['D'][0][i];//R->D
        for(int i=0;i<3;i++)
            Polyhedral['D'][0][i]=Polyhedral['L'][2-i][0];//D->L
        for(int i=0;i<3;i++)
            Polyhedral['L'][2-i][0]=temp[i];//L->U
    }
}
void Cube::U()
{
    if(1)//BRLF ->FBRL
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['U'][0][i];// Save B
        for(int i=0;i<3;i++)
            Polyhedral['U'][0][2-i]=Polyhedral['U'][i][0];//B->L
        for(int i=0;i<3;i++)
            Polyhedral['U'][i][0]=Polyhedral['U'][2][i];//L->F
        for(int i=0;i<3;i++)
            Polyhedral['U'][2][i]=Polyhedral['U'][2-i][2];//F->R
        for(int i=0;i<3;i++)
            Polyhedral['U'][i][2]=temp[i];//R->B
    }
    if(1)//BRLF->FBRL
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['B'][0][i];// Save B
        for(int i=0;i<3;i++)
            Polyhedral['B'][0][i]=Polyhedral['L'][0][i];//B->L
        for(int i=0;i<3;i++)
            Polyhedral['L'][0][i]=Polyhedral['F'][0][i];//L->F
        for(int i=0;i<3;i++)
            Polyhedral['F'][0][i]=Polyhedral['R'][0][i];//F->R
        for(int i=0;i<3;i++)
            Polyhedral['R'][0][i]=temp[i];//R->B
    }
}
void Cube::D()
{
    if(1)//BLFR->RBLF
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['D'][0][i];// Save B
        for(int i=0;i<3;i++)
            Polyhedral['D'][0][i]=Polyhedral['D'][i][0];//B->L
        for(int i=0;i<3;i++)
            Polyhedral['D'][i][0]=Polyhedral['D'][2][i];//L->F
        for(int i=0;i<3;i++)
            Polyhedral['D'][2][i]=Polyhedral['D'][2-i][2];//F->R
        for(int i=0;i<3;i++)
            Polyhedral['D'][i][2]=temp[i];//R->B
    }
    if(1)//BLFR->RBLF
    {
        char temp[3];
        for(int i=0;i<3;i++)
            temp[i]=Polyhedral['B'][2][i];// Save B
        for(int i=0;i<3;i++)
            Polyhedral['B'][2][i]=Polyhedral['R'][2][i];//B->L
        for(int i=0;i<3;i++)
            Polyhedral['R'][2][i]=Polyhedral['F'][2][i];//L->F
        for(int i=0;i<3;i++)
            Polyhedral['F'][2][i]=Polyhedral['L'][2][i];//F->R
        for(int i=0;i<3;i++)
            Polyhedral['L'][2][i]=temp[i];//R->B
    }
}
void Cube::print(char c) {
    std::string color_code;

    // Set color based on the character
    switch (c) {
        case 'U':
            color_code = "\033[1;37m"; // White
            break;
        case 'D':
            color_code = "\033[1;33m"; // Yellow
            break;
        case 'R':
            color_code = "\033[1;31m"; // Red
            break;
        case 'B':
            color_code = "\033[1;34m"; // Blue
            break;
        case 'F':
            color_code = "\033[1;32m"; // Green
            break;
        case 'L':
            color_code = "\033[1;35m"; // Magenta
            break;
        default:
            color_code = "\033[0m"; // Reset to default color
    }
    std::cout << color_code << c << "\033[0m ";
    // std::cout<<c<<" ";
}
void Cube::Open_Show() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            print(' ');
        }
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['U'][j][i]);
        }
        std::cout << "\n";
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['L'][j][i]);
        }
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['F'][j][i]);
        }
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['R'][j][i]);
        }
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['B'][j][i]);
        }
        std::cout << "\n";
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            print(' ');
        }
        for (int i = 0; i < 3; i++) {
            print(this->Polyhedral['D'][2 - j][2 - i]);
        }
        std::cout << "\n";
    }
}
std::pair<char,char> Cube::Find_Color(char col_1,char col_2)
{
    std::pair<char,char> result;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(face_map[id_face[i]].count(id_face[j]) > 0) 
            {
                // std::cout<<id_face[i]<<":"<<id_face[j]<<" ";
                std::pair<int,int>bias_i=face_map[id_face[i]][id_face[j]];
                std::pair<int,int>bias_j=face_map[id_face[j]][id_face[i]];
                if(Polyhedral[id_face[i]][1+bias_i.first][1+bias_i.second]==col_1&&Polyhedral[id_face[j]][1+bias_j.first][1+bias_j.second]==col_2)
                {
                    result.first=id_face[i];
                    result.second=id_face[j];
                    return result;
                }
            }
        }
    }
    return result;
}
std::tuple<char,char,char> Cube::Find_Color_Sharp(char col_1,char col_2,char col_3)
{
    std::tuple<char,char,char> result;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<6;k++)
            {
                if(face_map[id_face[i]].count(id_face[j])>0 && face_map[id_face[j]].count(id_face[k])>0 && face_map[id_face[k]].count(id_face[i])>0)
                {
                    std::pair<int,int>bias_i=face_map[id_face[i]][id_face[j]]+face_map[id_face[i]][id_face[k]];
                    std::pair<int,int>bias_j=face_map[id_face[j]][id_face[k]]+face_map[id_face[j]][id_face[i]];
                    std::pair<int,int>bias_k=face_map[id_face[k]][id_face[i]]+face_map[id_face[k]][id_face[j]];
                    if(Polyhedral[id_face[i]][1+bias_i.first][1+bias_i.second]==col_1&&Polyhedral[id_face[j]][1+bias_j.first][1+bias_j.second]==col_2&&Polyhedral[id_face[k]][1+bias_k.first][1+bias_k.second]==col_3)
                    {
                        result=std::make_tuple(id_face[i],id_face[j],id_face[k]);
                        return result;
                    }
                } 
            }
        }
    }
}
void Cube::fix_bottom_cross()
{
    Cube* cube=this;
    map<int,char>map_color_tmp={{0,'L'},{2,'R'},{3,'F'},{1,'B'}};
    for(int i=0;i<4;i++)
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_op=map_color_tmp[(2+i)%4];
        // std::cout<<"tmp_color:"<<tmp_color<<std::endl;
        // std::cout<<"tmp_color_op:"<<tmp_color_op<<std::endl;
        std::pair<char,char>egdes=cube->Find_Color(tmp_color,'D');
        // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
        if(egdes.first=='D')//
        {
            cube->performSingleMove(egdes.second);
            cube->performSingleMove(egdes.second);
            // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
        }
        if(egdes.second=='D')//如果已经在底面
        {
            cube->performSingleMove(egdes.first);
            cube->performSingleMove(egdes.first);
            // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
        }
        egdes=cube->Find_Color(tmp_color,'D');
        if(egdes.first==tmp_color_op||egdes.second==tmp_color_op)//如果在对面
        {
            // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
            int times=0;
            while(egdes.first!='U'&&egdes.second!='U')//转到顶面
            {
                times++;
                cube->performSingleMove(tmp_color_op);
                egdes=cube->Find_Color(tmp_color,'D');
                // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
            }
            cube->performMoves("U2");
            times=((4-times)%4+4)%4;
            while(times>0)//还原转动
            {
                times--;
                cube->performSingleMove(tmp_color_op);
            }
            egdes=cube->Find_Color(tmp_color,'D');
        }
        // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
        if(egdes.first=='U'||egdes.second=='U')//如果在顶面
        {
            while(egdes.first!=tmp_color&&egdes.second!=tmp_color)
            {
                cube->performMoves("U");
                egdes=cube->Find_Color(tmp_color,'D');
            }
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
        }
        while(egdes.first!='D'&&egdes.second!='D')
        {
            cube->performSingleMove(tmp_color);
            egdes=cube->Find_Color(tmp_color,'D');
        }
        if(egdes.first=='D'&&egdes.second==tmp_color)
        {
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            char tmp_color_right=map_color_tmp[(i+1)%4];
            // std::cout<<"tmp_color_right:"<<tmp_color_right<<std::endl;
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color_right);
        }
        // return true;
        // cube->Open_Show();
    }
}
void Cube::fix_bottom_total()
{
    Cube* cube=this;
    map<int,char>map_color_tmp={{0,'L'},{1,'B'},{2,'R'},{3,'F'}};
    map<char,int>map_id_tmp={{'L',0},{'R',2},{'F',3},{'B',1}};
    for(int i=0;i<4;i++)//每次处理tmp_color与tmp_color_lf
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_lf=map_color_tmp[(1+i)%4];
        char tmp_color_op=map_color_tmp[(2+i)%4];
        char tmp_color_rt=map_color_tmp[(3+i)%4];
        std::tuple<char,char,char>sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
        char col_1=std::get<0>(sharps);
        char col_2=std::get<1>(sharps);
        char col_3=std::get<2>(sharps);
        // std::cout<<tmp_color<<"&"<<tmp_color_lf<<"&D:"<<std::endl;
        // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
        if((col_1==tmp_color&&col_2==tmp_color_lf)||(col_2==tmp_color&&col_3==tmp_color_lf)||(col_3==tmp_color&&col_1==tmp_color_lf))//位置正确
        {
            ;
        }
        else
        {
            if(col_1=='D'||col_2=='D'||col_3=='D')//如果说在底面
            {
                char tmp_1=col_1,tmp_2=col_2;
                if(tmp_1=='D')tmp_1=col_3;
                if(tmp_2=='D')tmp_2=col_3;
                if(map_id_tmp[tmp_1]<map_id_tmp[tmp_2])std::swap(tmp_1,tmp_2);
                if(map_id_tmp[tmp_1]==3&&map_id_tmp[tmp_2]==0)std::swap(tmp_1,tmp_2);
                // std::cout<<"tmp_1:"<<tmp_1<<" tmp_2:"<<tmp_2<<std::endl;
                cube->performSingleMove(tmp_2);
                cube->performSingleMove('U');
                cube->performSingleMove(tmp_2);
                cube->performSingleMove(tmp_2);
                cube->performSingleMove(tmp_2);
                sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
                col_1=std::get<0>(sharps);
                col_2=std::get<1>(sharps);
                col_3=std::get<2>(sharps);
            }
            while((col_1!=tmp_color_lf||col_2!=tmp_color)&&(col_2!=tmp_color_lf||col_3!=tmp_color)&&(col_3!=tmp_color_lf||col_1!=tmp_color))//变为逆序
            {
                // std::cout<<"before: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
                cube->performSingleMove('U');
                sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
                col_1=std::get<0>(sharps);
                col_2=std::get<1>(sharps);
                col_3=std::get<2>(sharps);
            }
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
            col_1=std::get<0>(sharps);
            col_2=std::get<1>(sharps);
            col_3=std::get<2>(sharps);
        }
        // std::cout<<"before: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
        while(col_1=='D'||col_2=='D')//变为顺序
        {
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
            col_1=std::get<0>(sharps);
            col_2=std::get<1>(sharps);
            col_3=std::get<2>(sharps);
            // std::cout<<"process: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
        }
        sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
        col_1=std::get<0>(sharps);
        col_2=std::get<1>(sharps);
        col_3=std::get<2>(sharps);
        // std::cout<<"targer: "<<tmp_color<<" "<<tmp_color_lf<<" "<<'D'<<std::endl;
        // std::cout<<"final: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
        // cube->Open_Show();
    }
}
void Cube::fix_middle()
{
    Cube* cube=this;
    map<int,char>map_color_tmp={{0,'L'},{2,'R'},{3,'F'},{1,'B'}};
    map<char,int>map_id_tmp={{'L',0},{'R',2},{'F',3},{'B',1}};
    for(int i=0;i<4;i++)
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_lf=map_color_tmp[(1+i)%4];
        // std::cout<<"tmp_color:"<<tmp_color<<std::endl;
        // std::cout<<"tmp_color_lf:"<<tmp_color_lf<<std::endl;
        std::pair<char,char>egdes=cube->Find_Color(tmp_color,tmp_color_lf);
        // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
        if((egdes.first!=tmp_color||egdes.second!=tmp_color_lf)&&(egdes.first!=tmp_color_lf||egdes.second!=tmp_color))
        {
            if(egdes.first!='U'&&egdes.second!='U')//到顶层
            {
                int max_id=map_id_tmp[egdes.first];
                int min_id=map_id_tmp[egdes.second];
                if(max_id<min_id)std::swap(max_id,min_id);
                if(min_id==0&&max_id==3)std::swap(max_id,min_id);
                // std::cout<<"right:"<<map_color_tmp[min_id]<<" left:"<<map_color_tmp[max_id]<<std::endl;
                cube->performSingleMove(map_color_tmp[min_id]);
                cube->performSingleMove('U');
                cube->performSingleMove('U');
                cube->performSingleMove('U');
                cube->performSingleMove(map_color_tmp[min_id]);
                cube->performSingleMove(map_color_tmp[min_id]);
                cube->performSingleMove(map_color_tmp[min_id]);
                cube->performSingleMove('U');
                cube->performSingleMove('U');
                cube->performSingleMove('U');
                cube->performSingleMove(map_color_tmp[max_id]);
                cube->performSingleMove(map_color_tmp[max_id]);
                cube->performSingleMove(map_color_tmp[max_id]);
                cube->performSingleMove('U');
                cube->performSingleMove(map_color_tmp[max_id]);
                egdes=cube->Find_Color(tmp_color,tmp_color_lf);
                // std::cout<<"why?"<<egdes.first<<" "<<egdes.second<<std::endl;
            }
            while(egdes.first!=tmp_color&&egdes.second!=tmp_color)//到底层
            {
                // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
                cube->performSingleMove('U');
                egdes=cube->Find_Color(tmp_color,tmp_color_lf);
            }
                // std::cout<<"fi "<<egdes.first<<" "<<egdes.second<<std::endl;
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            egdes=cube->Find_Color(tmp_color,tmp_color_lf);
        }
        if(egdes.first!=tmp_color&&egdes.second!=tmp_color_lf)
        {
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove(tmp_color_lf);
            cube->performSingleMove('U');
            cube->performSingleMove(tmp_color_lf);
        }
        // cube->Open_Show();
    }
}
bool Cube::fix_upper_cross()
{
    Cube* cube=this;
    int bias[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    map<int,char>map_color_tmp={{0,'L'},{2,'R'},{3,'F'},{1,'B'}};
    map<char,int>map_id_tmp={{'L',0},{'R',2},{'F',3},{'B',1}};
    int times=0,flag=0;
    for(int i=0;i<4;i++)
        if(cube->Polyhedral['U'][1+bias[i][0]][1+bias[i][1]]=='U')
        {
            times++;
            flag+=i;
        }
    // std::cout<<times<<" "<<flag<<std::endl;
    if(times==1)
    {
        cube->performSingleMove('F');
        cube->performSingleMove('R');
        cube->performSingleMove('U');
        cube->performSingleMove('R');
        cube->performSingleMove('R');
        cube->performSingleMove('R');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('F');
        cube->performSingleMove('F');
        cube->performSingleMove('F');
    }
    times=0,flag=0;
    for(int i=0;i<4;i++)
        if(cube->Polyhedral['U'][1+bias[i][0]][1+bias[i][1]]=='U')
        {
            times++;
            flag+=i;
        }
    // std::cout<<times<<" "<<flag<<std::endl;
    // cube->Open_Show();
    if(times==2)
    {
        if(flag%2)
        {
            while(cube->Polyhedral['U'][0][1]!='U'||cube->Polyhedral['U'][1][0]!='U')
                cube->performSingleMove('U');
            cube->performSingleMove('F');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('F');
            cube->performSingleMove('F');
            cube->performSingleMove('F');
        }
        else
        {
            while(cube->Polyhedral['U'][1][2]!='U'||cube->Polyhedral['U'][1][0]!='U')
                cube->performSingleMove('U');
            cube->performSingleMove('F');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('F');
            cube->performSingleMove('F');
            cube->performSingleMove('F');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('L');
            cube->performSingleMove('U');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
        }
        times=0,flag=0;
        for(int i=0;i<4;i++)
            if(cube->Polyhedral['U'][1+bias[i][0]][1+bias[i][1]]=='U')
            {
                times++;
                flag+=i;
            }
    }
    if(times!=4) return false;//判断是否完成
    // cube->Open_Show();
    times=0,flag=0;
    char min_id;
    for(int i=0;i<4;i++)
    {
        char target_col=map_color_tmp[i];
        std::pair<int,int>bias=cube->face_map[target_col]['U'];
        if(cube->Polyhedral[target_col][1+bias.first][1+bias.second]==target_col)
        {
            times++;
            flag+=i;
        }
    }
    while(times<2)
    {
        cube->performSingleMove('U');
        times=0;
        for(int i=0;i<4;i++)
        {
            char target_col=map_color_tmp[i];
            std::pair<int,int>bias=cube->face_map[target_col]['U'];
            if(cube->Polyhedral[target_col][1+bias.first][1+bias.second]==target_col)
                times++,min_id=target_col;
        }
    }
    // std::cout<<" "<<times<<" "<<flag<<std::endl;
    if(times==2)
    {
        if(!(flag%2))
        {
            int flag_tmp=0;
            if(cube->Polyhedral['F'][0][1]=='F')
                cube->performSingleMove('U'),flag_tmp++;
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');

            cube->performSingleMove('B');
            cube->performSingleMove('U');
            cube->performSingleMove('B');
            cube->performSingleMove('B');
            cube->performSingleMove('B');
            cube->performSingleMove('U');
            cube->performSingleMove('B');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('B');
            cube->performSingleMove('B');
            cube->performSingleMove('B');
            if(!flag_tmp)
                cube->performSingleMove('U');
        }
        else
        {
            int tmp_num=(map_id_tmp[cube->Polyhedral['R'][0][1]]-map_id_tmp[cube->Polyhedral['B'][0][1]]+4)%4;
            while(tmp_num!=1)
            {
                cube->performSingleMove('U');
                // std::cout<<tmp_num<<std::endl;
                tmp_num=(map_id_tmp[cube->Polyhedral['R'][0][1]]-map_id_tmp[cube->Polyhedral['B'][0][1]]+4)%4;
            }
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
        }
        while(cube->Polyhedral['F'][0][1]!='F')
            cube->performSingleMove('U');
    }
    return true;
}
void Cube::fix_upper_total()
{
    Cube* cube=this;
    map<int,char>map_color_tmp={{0,'L'},{2,'R'},{3,'F'},{1,'B'}};//(6-i)%4
    map<char,int>map_id_tmp={{'L',0},{'R',2},{'F',3},{'B',1}};
    int times=0,flag=0;
    for(int i=0;i<4;i++)
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_lf=map_color_tmp[(1+i)%4];
        std::tuple<char,char,char>sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'U');
        char col_1=std::get<0>(sharps);
        char col_2=std::get<1>(sharps);
        char col_3=std::get<2>(sharps);
        if((col_1==tmp_color&&col_2==tmp_color_lf)||(col_2==tmp_color&&col_3==tmp_color_lf)||(col_3==tmp_color&&col_1==tmp_color_lf))
            times++,flag=i;
    }
    if(times==4)
        return;
    // std::cout<<"hi:"<<times<<"\n";
    if(times==0)
    {
        cube->performSingleMove('U');
        cube->performSingleMove('R');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('L');
        cube->performSingleMove('L');
        cube->performSingleMove('L');
        cube->performSingleMove('U');
        cube->performSingleMove('R');
        cube->performSingleMove('R');
        cube->performSingleMove('R');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('U');
        cube->performSingleMove('L');
    }
    times=0;
    for(int i=0;i<4;i++)
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_lf=map_color_tmp[(1+i)%4];
        std::tuple<char,char,char>sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'U');
        char col_1=std::get<0>(sharps);
        char col_2=std::get<1>(sharps);
        char col_3=std::get<2>(sharps);
        if((col_1==tmp_color&&col_2==tmp_color_lf)||(col_2==tmp_color&&col_3==tmp_color_lf)||(col_3==tmp_color&&col_1==tmp_color_lf))
            times++,flag=i;
    }
    // std::cout<<"hi:"<<times<<" "<<flag<<"\n";
    // cube->Open_Show();
    if(times==1)
    {
        do
        {
            int cnt=(6-flag)%4;
            for(int j=0;j<cnt;j++)
                cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
            cube->performSingleMove('L');
            cube->performSingleMove('U');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('U');
            cube->performSingleMove('L');
            cnt=(4-cnt)%4;
            for(int j=0;j<cnt;j++)
                cube->performSingleMove('U');
            times=0;
            // printf("%d\n",cnt);
            for(int i=0;i<4;i++)
            {
                char tmp_color=map_color_tmp[i];
                char tmp_color_lf=map_color_tmp[(1+i)%4];
                std::tuple<char,char,char>sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'U');
                char col_1=std::get<0>(sharps);
                char col_2=std::get<1>(sharps);
                char col_3=std::get<2>(sharps);
                if((col_1==tmp_color&&col_2==tmp_color_lf)||(col_2==tmp_color&&col_3==tmp_color_lf)||(col_3==tmp_color&&col_1==tmp_color_lf))
                    times++,flag=i;
            }
            // cube->Open_Show();
        }while(times==1);
    }
}
void Cube::fix_final()
{
    Cube* cube=this;
    int t=0;
    while(t<4)
    {
        while(cube->Polyhedral['U'][2][2]!='U')
        {
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('R');
            cube->performSingleMove('D');
            cube->performSingleMove('D');
            cube->performSingleMove('D');
            cube->performSingleMove('R');
            cube->performSingleMove('D');
        }
        t++;
        cube->performSingleMove('U');
    }
}
// int main()
// {
//     Cube* cube=new Cube();
//     // cube->L();//FIX
//     // cube->R();//FIX
//     // cube->Open_Show();
//     // cube->F();//FIX
//     // cube->R();//FIX
//     // cube->R();//FIX
//     // cube->U();//FIX
//     // cube->U();//FIX
//     // cube->U();//FIX
//     // cube->B();//FIX
//     // cube->U();
//     // cube->D();
//     // cube->Show('U');
//     // cube->Show('F');
//     // cube->Show('L');
//     // cube->Show('R');
//     // cube->Show('D');
//     // cube->Show('B');
//     string moves="D2 L' F' L2 U2 B2 D2 B U2 L2 D2 R2 B' L' D L2 D2 F2 U' F2";
//     cube->performMoves(moves);
//     cube->Open_Show();
//     // for(int i=0;i<3;i++)
//     // {
//     //     for(int j=0;j<3;j++)
//     //         std::cout<<cube->Polyhedral['R'][i][j]<<' ';
//     //     std::cout<<std::endl;
//     // }
// }