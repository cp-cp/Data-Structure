#include<iostream>

template <class T> class Linked_List
{  
    private:
        class Node
        {
            public:
                T data;
                Node* next=NULL;
                Node(T x)
                {
                    this->data=x;
                }
        };  
        Node* head;
    public:
        Linked_List(){
            head = NULL;
        };
        Linked_List(T A[],int n);
        ~Linked_List();
        int Display()const;//返回列表长度
        void Insert(int index, T x);
        void Delete(int index);
        int Length()const;
        T Show(int index)const;
};
template<class T>
Linked_List<T>::Linked_List(T A[],int n)
{
    Node* last,*t;
    head=new Node(A[0]);
    // head->data=A[0];
    // head->next=NULL;
    last=head;
    for(int i=1;i<n;i++)
    {
        t=new Node(A[i]);
        // t->data=A[i];
        // t->next=NULL;
        last->next=t;
        last=t;
    }
}
template<class T>
Linked_List<T>::~Linked_List(){
    Node* p = head;
    while(head){
        head = head->next;
        delete p;
        p = head;
    }
}
template <class T>
int Linked_List<T>::Display()const
{
    int lenth;
    Node* p=head;
    while(p)
    {
        lenth++;
        std::cout<<p->data<<" ";
        p=p->next;       
    }
    std::cout<<"\n";
    return lenth;
}
template <class T>
void Linked_List<T>::Insert(int index,T x)
{
    Node* t=new Node(x);
    Node* p=head;
    if(index < 0 || index > Length())
        return;
    if(index==0)
    {
        t->next=head;
        head=t;
    }
    else
    {
        for(int i=0; i<index-1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}
template <class T>
T Linked_List<T>::Show(int index)const
{
    Node* p=head;
    if(index < 0 || index >= Length())
        return NULL;
    if(index==0)
    {
        // t->next=head;
        return head->data;
        // head=t;
    }
    else
    {
        for(int i=0; i<index-1; i++)
            p = p->next;
        return p->next->data;
        // t->next = p->next;
        // p->next = t;
    }
}
template <class T>
void Linked_List<T>::Delete(int index)
{
    Node* p=head;
    Node* q=head;
    if(index < 0 || index >= Length())
        return;
    if(index==0)
    {
        head=head->next;
    }
    else
    {
        for(int i=0; i<index; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        delete p;
    }
}
template <class T>
int Linked_List<T>::Length() const
{
    int length=0;
    Node* p=head;
    while(p)
    {
        p=p->next;
        length++;
    }
    return length;
}