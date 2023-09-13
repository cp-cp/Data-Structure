#include"List.h"
template<class T>
class Stack
{
    private:
        Linked_List<T> list;
    public:
        Stack()
        {
        }
        void Push(T t);
        void Pop();
        // int length();
        bool Empty()const;
        T Top()const;
        int Display()const;
};
template<class T>
void Stack<T>::Push(T t)
{
    //this.
    list.Insert(0,t);
}
template<class T>
bool Stack<T>::Empty()const
{
    return !list.Length();
}
template<class T>
int Stack<T>::Display() const
{
    return list.Display();
}
template<class T>
T Stack<T>::Top()const
{
    return list.Show(0);
}
template<class T>
void Stack<T>::Pop()
{
    list.Delete(0);
}