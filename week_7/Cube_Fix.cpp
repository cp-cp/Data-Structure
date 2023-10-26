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

�涨��ħ���ķ�������ɫ�����б�š�
�ǿ飺URF,URB,ULF,ULB,DRF,DRB,DLF,DLB,
��飺UF,UR,UB,UL,DF,DR,DB,DL,FR,FL,BR,BL��
���Ŀ飺U,F,R,B,L,D��


ǰ����裺
    �м�����ɫû���ҵ���
    ����ħ�������ǿ��Ի�ԭ������״̬�ģ����������״̬��ȫһ�£���

������ͣ����ǻ��������λ�öԻ����Լ����ķ���Ի����ǿ�ķ���Ի���

�ڹ̶�FLD����ҷ��֣�
1. ����һ��ħ�������Էֳ����ͽǿ�ֱ��ǣ����߻���Ӱ�졣
2. ���Ǿ���FLD��Ľǿ����ѱ�λ���Լ�����ȷ���ģ�ֻ��URB�ǿ�ķ���ȷ������3�ֿ��ܡ�(����ͼ*����ʾ��λ��)
3. ���ھ���FLD�����飬ֻ��FU,FR,LU,LB,DR,DB�����λ�ò���ȷ������FU��FR��LU��LB��DR��DB����λ�öԻ�����2^3=8���ܡ�(����ͼ"/"��ʾ��λ��)
4.������FLD���޹ص���飬ֻ��UR,UB,RB�����λ�ò�ȷ��,��������Ҳ��ȷ����һ����2^3*3!=48�ֿ��ܡ�(����ͼ"?"��ʾ��λ��)

���ϣ������ռ�����Ϊ:3*8*48=1152�ֿ��ܡ�


OUTPUT:
��Cube_Fix.txt
���յĽ����ǣ�
����172��ħ�����Ա���ԭ
����Ϊ:0.1493055555555556
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
                    std::cout<<"��"<<t<<"��ħ������ʽ��"<<std::endl;
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
                        std::cout<<"ħ���ѱ���ԭ\n",fixed_num++;
                    else
                        std::cout<<"ħ�����ɱ���ԭ\n";
                    cube->Reset();
                    t++;
                    // std::cout<<t<<std::endl;
                }
                    // t++;
                    // std::cout<<t<<std::endl;
            }while(std::next_permutation(dic,dic+3));
        }

    }
    std::cout<<"����"<<fixed_num<<"��ħ�����Ա���ԭ"<<std::endl;
    return 0;
}