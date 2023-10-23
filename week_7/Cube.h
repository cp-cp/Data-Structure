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
    void Open_Show();
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

    // Print the character with the selected color and reset to default color
    std::cout << color_code << c << "\033[0m ";
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
                // std::cout<<bias_i.first<<":"<<bias_i.second<<" ";
                // std::cout<<bias_j.first<<":"<<bias_j.second<<std::endl;
                // Show(id_face[i]);
                // std::cout<<Polyhedral[id_face[i]][1+bias_i.first][1+bias_i.second]<<" ";
                // std::cout<<Polyhedral[id_face[j]][1+bias_j.first][1+bias_j.second]<<std::endl;
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