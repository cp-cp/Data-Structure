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
        void push(T t);
        void pop();
        // int length();
        T top();
        int display();
};
template<class T>
void Stack<T>::push(T t)
{
    //this.
    list.Insert(0,t);
}
template<class T>
int Stack<T>::display()
{
    return list.Display();
}
template<class T>
T Stack<T>::top()
{
    return list.Show(0);
}
template<class T>
void Stack<T>::pop()
{
    list.Delete(0);
}