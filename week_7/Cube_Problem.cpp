#include"Cube.h"
/*
如何复原魔方？
底面十字
*/
void fix_bottom_cross(Cube* cube)
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
        cube->Open_Show();
    }
}
void fix_bottom_total(Cube* cube)
{
    map<int,char>map_color_tmp={{0,'L'},{1,'B'},{2,'R'},{3,'F'}};
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
        std::cout<<tmp_color<<"&"<<tmp_color_lf<<"&D:"<<std::endl;
        // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
        if((col_1==tmp_color&&col_2==tmp_color_lf)||(col_2==tmp_color&&col_3==tmp_color_lf)||(col_3==tmp_color&&col_1==tmp_color_lf))//位置正确
        {
            ;
        }
        else
        {
            if(col_1=='D'||col_2=='D'||col_3=='D')//如果说在底面
            {
                char tmp=col_1;
                if(tmp=='D')tmp=col_2;
                cube->performSingleMove(tmp);
                cube->performSingleMove('U');
                cube->performSingleMove(tmp);
                cube->performSingleMove(tmp);
                cube->performSingleMove(tmp);
                sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
                col_1=std::get<0>(sharps);
                col_2=std::get<1>(sharps);
                col_3=std::get<2>(sharps);
            }
            while((col_1!=tmp_color_lf||col_2!=tmp_color)&&(col_2!=tmp_color_lf||col_3!=tmp_color)&&(col_3!=tmp_color_lf||col_1!=tmp_color))//变为逆序
            {
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
            // cube->performSingleMove(tmp_color_lf);
            // cube->performSingleMove(tmp_color_lf);
            // cube->performSingleMove(tmp_color_lf);
            // cube->performSingleMove('U');
            // cube->performSingleMove('U');
            // cube->performSingleMove('U');
            // cube->performSingleMove(tmp_color_lf);
            // cube->performSingleMove(tmp_color_lf);
            // cube->performSingleMove(tmp_color_lf);
            sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
            col_1=std::get<0>(sharps);
            col_2=std::get<1>(sharps);
            col_3=std::get<2>(sharps);
            std::cout<<"process: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
        }
        sharps=cube->Find_Color_Sharp(tmp_color,tmp_color_lf,'D');
        col_1=std::get<0>(sharps);
        col_2=std::get<1>(sharps);
        col_3=std::get<2>(sharps);
        std::cout<<"targer: "<<tmp_color<<" "<<tmp_color_lf<<" "<<'D'<<std::endl;
        std::cout<<"final: "<<col_1<<" "<<col_2<<" "<<col_3<<std::endl;
    }
}
int main()
{
    Cube* cube=new Cube();
    string moves="D2 L' F' L2 U2 B2 D2 B U2 L2 D2 R2 B' L' D L2 D2 F2 U' F2";
    cube->performMoves(moves);
    cube->Open_Show();
    fix_bottom_cross(cube);
    // std::tuple<char,char,char>sharps=cube->Find_Color_Sharp('D','L','F');
    // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
    // sharps=cube->Find_Color_Sharp('L','D','F');
    // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
    fix_bottom_total(cube);
    cube->Open_Show();
    // std::pair<char,char>egdes=cube->Find_Color('R','F');
    // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
}