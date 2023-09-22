#include<iostream>
struct Fun
{
    int x=10;
    void operator()(int x)
    {
        std::cout << x << std::endl;
    }
};
int main()
{
    Fun fun;
    fun(111);//形成一个函数的形式。
}
// 迭代器如何实现？