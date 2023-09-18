#include"Queue.h"
int main()
{
    Queue<int>q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    // printf("%d\n",q.Front());
    // printf("%d\n",q.Back());
    q.Pop();
    q.Display();
    // printf("%d\n",q.Front());
    // printf("%d\n",q.Size());
    q.Deque();
    // printf("%d\n",q.Size());
    q.Display();
    // printf("%d\n",q.Front());
    // printf("%d\n",q.Back());
}