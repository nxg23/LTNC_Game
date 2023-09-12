#include<bits/stdc++.h>
using namespace std;

struct node
{
    int data ;
    node* next;
};

node* makeNode(int x)
{   
    node* newNode = new node();
    newNode->data = x;  
    newNode->next = NULL;
    return newNode;
}
void print(node *head)
{
    while(head != NULL){
        cout << head->data << " ";
        head = head->next;
    }
}

void push(node *&head, int val)
{
    node *newNode = new node{val, head};
    //head = newNode;
    head = newNode;  
}

void pushBack(node *&head, int val)
{
    node *newNode = new node{val, NULL};
    if(head == NULL)
    {
        head = newNode; return;
    }
    node* temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}
void erasehead(node *&head)
{
  node* temp = head;
  head = head->next;
  delete temp;
}

void eraseTail(node *&head)
{
    node *temp = head;
    while(temp->next->next != NULL)
    {
        temp = temp->next;
    }
    node *last = temp->next;
    delete last;
    temp->next = NULL;
}
void pushPos(node*&head, int val, int pos)
{
    int n = sizeof(head);
    node *newNode = new node{val, NULL};
    if(pos == 1) push(head, val);
    if(pos == n) pushBack(head, val);
    node *temp = head;
    for(int i = 1; i <= pos - 2; i++){
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void erasePos(node *&head, int pos)
{
    int n = sizeof(head);
    if(pos == n) eraseTail(head);
    if(pos == 1) erasehead(head);
    node *temp = head;
    for(int i = 1; i <= pos - 2; i++) {
      temp = temp->next;
    }
    node *posnode = temp->next;
    temp->next = temp->next->next;
    delete posnode;
}
int main()
{
    node *head = NULL;
    for(int i = 1; i <= 5; i++)
    {
        pushBack(head,i);
    }
    pushPos(head, 6, 3);
    //erasehead(head);
    //eraseTail(head);
    //erasePos(head, 4);
    print(head);
    return 0;
}
