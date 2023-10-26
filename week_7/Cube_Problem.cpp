#include"Cube.h"
/*
打乱指令生成：https://cstimer.net/
魔方与群论：https://cstimer.net/
*/
void fix_bottom_cross(Cube* cube)
{
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
        // cube->Open_Show();
    }
}
void fix_bottom_total(Cube* cube)
{
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
void fix_middle(Cube* cube)
{
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
void fix_upper_cross(Cube* cube)
{
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
    cube->Open_Show();
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
    if(times!=4) return;//判断是否完成
    cube->Open_Show();
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
}
void fix_upper_total(Cube* cube)
{
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
void fix_final(Cube* cube)
{
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
int main()
{
    Cube* cube=new Cube();
    // std::cout<<""
    string moves="D2 L' F' L2 U2 B2 D2 B U2 L2 D2 R2 B' L' D L2 D2 F2 U' F2";
    // string moves="B2 L2 D F2 R2 B2 R2 U F2 D U2 R U F' R' F' D2 B' D2 U'";
    // string moves="B' L2 F' D2 B2 D2 U2 L2 B' U2 L' F2 R' B' D L2 D2 U' R U'";
    // string moves="B2 L2 B L B' L F2 D L2 U2 F B D2 R2 B R2 L2 D'";
    std::cout<<"打乱前的魔方："<<std::endl;
    cube->Open_Show();
    cube->performMoves(moves);
    std::cout<<"被打乱的魔方："<<std::endl;
    cube->Open_Show();
    std::cout<<"步骤一：拼个底面十字"<<std::endl;
    fix_bottom_cross(cube);
    cube->Open_Show();
    // std::tuple<char,char,char>sharps=cube->Find_Color_Sharp('D','L','F');
    // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
    // sharps=cube->Find_Color_Sharp('L','D','F');
    // std::cout<<std::get<0>(sharps)<<" "<<std::get<1>(sharps)<<" "<<std::get<2>(sharps)<<std::endl;
    std::cout<<"步骤二：拼完底面"<<std::endl;
    fix_bottom_total(cube);
    cube->Open_Show();
    std::cout<<"步骤三：拼中间层"<<std::endl;
    fix_middle(cube);
    cube->Open_Show();
    std::cout<<"步骤四：拼顶面十字并对齐"<<std::endl;
    fix_upper_cross(cube);
    cube->Open_Show();
    std::cout<<"步骤五：拼顶面"<<std::endl;
    fix_upper_total(cube);
    cube->Open_Show();
    std::cout<<"步骤六：顶面棱角对齐"<<std::endl;
    fix_final(cube);
    cube->Open_Show();
    if(cube->Check())
    {
        std::cout<<"魔方已被复原\n";
    }
    else
    {
        std::cout<<"魔方不可被复原\n";
    }
    // std::pair<char,char>egdes=cube->Find_Color('R','F');
    // std::cout<<egdes.first<<" "<<egdes.second<<std::endl;
}