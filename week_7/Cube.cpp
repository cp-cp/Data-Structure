#include<iostream>
#include<map>
#include<string>
using std::map;
using std::string;
/*
考虑生成一个魔方class，能够执行各种旋转。
前(F)后(B)左(L)右(R)上(U)下(D)
并且以顺时针旋转作为正向.

如何表示各个面？
采取最直观的3*3*6，面表示法。

F(2)B(3)L(4)R(5)U(0)D(1)


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
    void L();
    void R();
    void F();
    void B();
    void U();
    void D();
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
            {'R', '1', 'R'},
            {'4', 'R', '2'},
            {'R', '3', 'R'}
        };
        this->Polyhedral['U']=Up_Side;
        this->Polyhedral['D']=Down_Side;
        this->Polyhedral['F']=Front_Side;
        this->Polyhedral['B']=Back_Side;
        this->Polyhedral['L']=Left_Side;
        this->Polyhedral['R']=Right_Side;
        
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                std::cout<<this->Polyhedral['L'][i][j]<<' ';
            std::cout<<std::endl;
        }
    }
};
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
            Polyhedral['U'][i][0]=Polyhedral['B'][i][2];//U->B
        for(int i=0;i<3;i++)
            Polyhedral['B'][i][2]=Polyhedral['D'][i][2];//B->D
        for(int i=0;i<3;i++)
            Polyhedral['D'][i][2]=Polyhedral['F'][i][0];//D->F
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
}
int main()
{
    Cube* cube=new Cube();
    cube->L();
    // cube->R();
    cube->Show('U');
    cube->Show('F');
    cube->Show('D');
    cube->Show('B');
    // for(int i=0;i<3;i++)
    // {
    //     for(int j=0;j<3;j++)
    //         std::cout<<cube->Polyhedral['R'][i][j]<<' ';
    //     std::cout<<std::endl;
    // }
}