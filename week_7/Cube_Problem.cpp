#include"Cube.h"
/*
如何复原魔方？
首先复原底面！
*/
void fix_bottom(Cube* cube)
{
    map<int,char>map_color_tmp={{0,'L'},{2,'R'},{3,'F'},{1,'B'}};
    for(int i=0;i<4;i++)
    {
        char tmp_color=map_color_tmp[i];
        char tmp_color_op=map_color_tmp[(2+i)%4];
        std::cout<<"tmp_color:"<<tmp_color<<std::endl;
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
            // if(egdes.first==NULL)
            // {
            //     cube->Open_Show();
            //     // std::cout<<tmp_color<<std::endl;
            //     std::pair<char,char>egdes2=cube->Find_Color('B','D');
            //     // std::cout<<"notice!!!!!!:    "<<egdes2.first<<" "<<egdes2.second<<std::endl;
            // }
            // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
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
            std::cout<<"tmp_color_right:"<<tmp_color_right<<std::endl;
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color);
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color_right);
            cube->performSingleMove(tmp_color_right);
        }
        cube->Open_Show();
    }
}
int main()
{
    Cube* cube=new Cube();
    string moves="D2 L' F' L2 U2 B2 D2 B U2 L2 D2 R2 B' L' D L2 D2 F2 U' F2";
    cube->performMoves(moves);
    cube->Open_Show();
    fix_bottom(cube);
    // cube->Open_Show();
    // std::pair<char,char>egdes=cube->Find_Color('R','F');
    // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
}