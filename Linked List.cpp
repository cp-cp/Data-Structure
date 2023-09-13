#include<iostream>

class Node {
    public:
        int data;
        Node* next;
};

class Linked_List{
    private:
        Node* head;
    public:
        Linked_List(){
            head = NULL;
        }
        Linked_List(int A[], int n);
        ~Linked_List();
        void Display() const;
        void Insert(int index, int x);
        int Delete(int index);
        int Length();
};
int Linked_List::Length(){
    Node* p = head;
    int len = 0;
    while(p){
        len++;
        p = p->next;
    }
    return len;
}
Linked_List::Linked_List(int A[], int n){
    Node* last, *t;
    head = new Node;
    head->data = A[0];
    head->next = NULL;
    last = head;
    for(int i=1; i<n; i++){
        t = new Node;
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}
Linked_List::~Linked_List(){
    Node* p = head;
    while(head){
        head = head->next;
        delete p;
        p = head;
    }
}
void Linked_List::Display() const{//const 保证内参不会改变
    Node* p = head;
    while(p){
        std::cout<<p->data<<" ";
        p = p->next;
    }
    std::cout<<std::endl;
}
void Linked_List::Insert(int index, int x){
    Node* t, *p = head;
    if(index < 0 || index > Length())
        return;
    t = new Node;
    t->data = x;
    t->next = NULL;
    if(index == 0){
        t->next = head;
        head = t;
    }
    else{
        for(int i=0; i<index-1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}
int Linked_List::Delete(int index){
    Node* p, *q = NULL;
    int x = -1;
    if(index < 1 || index > Length())
        return -1;
    if(index == 1){
        p = head;
        head = head->next;
        x = p->data;
        delete p;
    }
    else{
        p = head;
        for(int i=0; i<index-1; i++){
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        delete p;
    }
    return x;
}
int main(){
    int A[] = {1, 2, 3, 4, 5};
    Linked_List l(A, 5);
    l.Display();
    l.Insert(3, 10);
    l.Display();
    std::cout<<l.Delete(3)<<std::endl;
    l.Display();
    return 0;
}