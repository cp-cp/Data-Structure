#include"Stack.h"
int main()
{
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    s.pop();
    s.display();
    printf("%d",s.top());
}