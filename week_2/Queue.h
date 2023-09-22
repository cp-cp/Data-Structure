#include"List.h"
template<class T>
class Queue
{
    private:
        Linked_List<T> list;
    public:
        T Front()const;
        T Back()const;
        void Push(T t);
        void Push_Back(T t);
        bool Empty()const;
        int Size()const;
        void Pop();
        void Deque();
        void Display() const;
};
template<class T>
T Queue<T>::Front()const
{
    return list.Show(0);   
}
template<class T>
T Queue<T>::Back()const
{
    return list.Show(list.Length()-1);   
}
template<class T>
void Queue<T>::Push_Back(T t)
{
    return list.Insert(0,t);   
}
template<class T>
void Queue<T>::Push(T t)
{
    return list.Insert(list.Length(),t);   
}
template<class T>
bool Queue<T>::Empty()const
{
    return !list.Length();
}
template<class T>
int Queue<T>::Size()const
{
    return list.Length();
}
template<class T>
void Queue<T>::Pop()
{
    list.Delete(0);
}
template<class T>
void Queue<T>::Deque()
{
    list.Delete(list.Length()-1);
}
template<class T>
void Queue<T>::Display() const
{
    list.Display();
}