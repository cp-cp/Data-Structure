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
            {'1', 'U', '2'},
            {'U', 'U', 'U'},
            {'3', 'U', '4'}
        };
        char (*Down_Side)[3] = new char[3][3]{
            {'1', 'D', '2'},
            {'D', 'D', 'D'},
            {'3', 'D', '4'}
        };
        char (*Front_Side)[3] = new char[3][3]{
            {'1', 'F', '2'},
            {'F', 'F', 'F'},
            {'3', 'F', '4'}
        };
        char (*Back_Side)[3] = new char[3][3]{
            {'1', 'B', '2'},
            {'B', 'B', 'B'},
            {'3', 'B', '4'}
        };
        char (*Left_Side)[3] = new char[3][3]{
            {'1', 'L', '2'},
            {'L', 'L', 'L'},
            {'3', 'L', '4'}
        };
        char (*Right_Side)[3] = new char[3][3]{
            {'1', 'R', '2'},
            {'R', 'R', 'R'},
            {'3', 'R', '4'}
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
int main()
{
    Cube* cube=new Cube();
    // cube->L();//FIX
    // cube->R();//FIX
    // cube->F();//FIX
    // cube->B();//FIX
    // cube->U();
    // cube->D();
    cube->Show('U');
    cube->Show('F');
    cube->Show('L');
    cube->Show('R');
    cube->Show('D');
    cube->Show('B');
    // for(int i=0;i<3;i++)
    // {
    //     for(int j=0;j<3;j++)
    //         std::cout<<cube->Polyhedral['R'][i][j]<<' ';
    //     std::cout<<std::endl;
    // }
}