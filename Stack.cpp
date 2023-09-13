#include"Stack.h"
int main()
{
    Stack<int> s;
    printf("%d\n",s.Empty());
    s.Push(10);
    s.Push(20);
    s.Push(30);
    s.Display();
    s.Pop();
    s.Display();
    printf("%d\n",s.Empty());
    printf("%d",s.Top());
}