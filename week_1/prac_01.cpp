#include<iostream>
int main()
{
    int n=10;
    char(*c)[5];
    c=new char[n][5];
    for(int i=0;i<n;i++)
    {
        std::cout<<c[i]<<std::endl;
    }
}
/*
int rows = 3; // 二维数组的行数
int cols = 4; // 二维数组的列数

char** array2D = new char*[rows]; // 创建一个指向指针的指针

for (int i = 0; i < rows; i++) {
    array2D[i] = new char[cols]; // 为每一行分配内存
}

// 现在你可以使用 array2D[i][j] 访问元素

// 记得在使用完后释放内存
for (int i = 0; i < rows; i++) {
    delete[] array2D[i]; // 释放每一行的内存
}

delete[] array2D; // 释放指向指针的指针

*/