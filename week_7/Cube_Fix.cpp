#include"Cube.h"
#include<algorithm>
/*

      U U U
      U U U
      U U U
L L L F F F R R R B B B 
L L L F F F R R R B B B
L L L F F F R R R B B B
      D D D
      D D D
      D D D

            U   ?   *
           U/B  U   ?
            U  U/R  U
L   L   L   F   F   F   R    ?   *   *   ?   B   
L   L   L   F   F   F  R/U   R   ?   ?   B   U/B
L   L   L   F   F   F   R   R/B  R   B   B/R   B
            D   D   D
            D   D   D
            D   D   D

规定，魔方的方块用颜色来进行编号。
角块：URF,URB,ULF,ULB,DRF,DRB,DLF,DLB,
棱块：UF,UR,UB,UL,DF,DR,DB,DL,FR,FL,BR,BL，
中心块：U,F,R,B,L,D，


前提假设：
    中间块的颜色没有乱掉。
    假设魔方本身是可以还原到正常状态的（与你的理想状态完全一致）。

补充解释：但是会存在棱块的位置对换，以及棱块的方向对换，角块的方向对换。

在固定FLD面后，我发现：
1. 对于一个魔方，可以分成棱块和角块分别考虑，两者互不影响。
2. 凡是具有FLD面的角块是已被位置以及方向确定的，只有URB角块的方向不确定，共3种可能。(即上图*所表示的位置)
3. 对于具有FLD面的棱块，只有FU,FR,LU,LB,DR,DB的相对位置不能确定，即FU与FR、LU与LB、DR与DB可能位置对换，共2^3=8可能。(即上图"/"表示的位置)
4.对于与FLD面无关的棱块，只有UR,UB,RB的相对位置不确定,且自身方向也不确定，一共有2^3*3!=48种可能。(即上图"?"表示的位置)

综上，样本空间总数为:3*8*48=1152种可能。


OUTPUT:
见Cube_Fix.txt
最终的结论是：
共有172种魔方可以被复原
概率为:0.1493055555555556
*/
int main()
{
    freopen("Cube_Fix.txt","w",stdout);
    // int t=0;
        int t=1,fixed_num=0;
    char condition_1_color[3]={'U','B','R'};
    for(int j=0;j<3;j++)
    {
        Cube* cube=new Cube();
        cube->Polyhedral['U'][0][2]=condition_1_color[(1+j)%3];
        cube->Polyhedral['B'][0][0]=condition_1_color[(2+j)%3];
        cube->Polyhedral['R'][0][2]=condition_1_color[(3+j)%3];
        for(int b=0;b<8;b++)
        {
            if((b)&1)
                std::swap(cube->Polyhedral['U'][2][1],cube->Polyhedral['R'][1][0]);
            if((b>>1)&1)
                std::swap(cube->Polyhedral['U'][1][0],cube->Polyhedral['B'][1][2]);
            if((b>>2)&1)
                std::swap(cube->Polyhedral['B'][2][1],cube->Polyhedral['R'][2][1]);
            char condition_3_color_tmp[3][2]={{'U','R'},{'R','B'},{'B','U'}};
            int dic[3]={0,1,2};
            do
            {
                char condition_3_color[3][2];
                for(int k=0;k<3;k++)
                {
                    condition_3_color[k][0]=condition_3_color_tmp[dic[k]][0];
                    condition_3_color[k][1]=condition_3_color_tmp[dic[k]][1];
                }
                for(int i=0;i<8;i++)
                {   
                    if(i&1)
                        std::swap(condition_3_color[0][0],condition_3_color[0][1]);
                    if((i>>1)&1)
                        std::swap(condition_3_color[1][0],condition_3_color[1][1]);
                    if((i>>2)&1)
                        std::swap(condition_3_color[2][0],condition_3_color[2][1]);
                    cube->Polyhedral['U'][1][2]=condition_3_color[0][0];
                    cube->Polyhedral['R'][0][1]=condition_3_color[0][1];
                    cube->Polyhedral['R'][1][2]=condition_3_color[1][0];
                    cube->Polyhedral['B'][1][0]=condition_3_color[1][1];
                    cube->Polyhedral['B'][0][1]=condition_3_color[2][0];
                    cube->Polyhedral['U'][0][1]=condition_3_color[2][1];
                    std::cout<<"第"<<t<<"个魔方的形式："<<std::endl;
                    cube->Open_Show();
                    cube->fix_bottom_cross();
                    cube->fix_bottom_total();
                    cube->fix_middle();
                    // cube->Open_Show();
                    bool check_point=cube->fix_upper_cross();
                    // std::cout<<"test "<<check_point<<std::endl;
                    if(check_point)
                    {
                        // cube->Open_Show();
                        cube->fix_upper_total();
                        // cube->Open_Show();
                        cube->fix_final();
                        // cube->Open_Show();
                    }
                    if(cube->Check())
                        std::cout<<"魔方已被复原\n",fixed_num++;
                    else
                        std::cout<<"魔方不可被复原\n";
                    cube->Reset();
                    t++;
                    // std::cout<<t<<std::endl;
                }
                    // t++;
                    // std::cout<<t<<std::endl;
            }while(std::next_permutation(dic,dic+3));
        }

    }
    std::cout<<"共有"<<fixed_num<<"种魔方可以被复原"<<std::endl;
    return 0;
}