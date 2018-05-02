#include "linked_list.h"

/*linked_list::linked_list(const linked_list & src)
{

};*/

linked_list::~linked_list()
{
    while(!is_empty())  pop_back(); //Ta bort samtliga element i listan
};


/*linked_list& linked_list::operator=(const linked_list& rhc)
{
    while(!is_empty()) pop_back();   //Töm listan
};*/

/*
linked_list& linked_list::operator+=(const linked_list& rhc)
{

};*/

void linked_list::insert(double value, size_t pos)
{
    if(size() < pos)    //Om positionen inte finns 
    {
        push_back(value);   //Lägg till elementet sist i listan
        return;
    }
    
    node_t * node = new node_t();   //Den nya noden som ska läggas till
    node->value = value; 

    node_t * node_pos = head;   //Positionen för den nya noden
    
    for(int i = 0; i <= pos; i++)
        node_pos = node_pos->next;
    
    node->next = node_pos;
    node->prev = node_pos->prev;

    node_pos->prev->next = node;
    node_pos->prev = node;
};

void linked_list::push_front(double value)
{
    node_t * node = new node_t(value,head, nullptr); //skapa en ny nod
    if(head)    
    {
        head->prev = node;  
        node->next = head;
    }
    if(size() == 1)     //Om listan bara innehåller ett element
        tail = head;    //Gör det gamla huvudet till svans    

    head = node;    //Gör den nya noden till huvud  
};

void linked_list::push_back(double value)
{
    node_t * node = new node_t(value, nullptr, tail);
    if(tail)    
    {
        tail->next = node;
        node->prev = tail;
    }
    if(!head)   head = node;    //Om det inte finns ett huvud
    tail = node;
};

double linked_list::front() const
{
    if(head)    return head->value;
    else        return -1;
};

double linked_list::back() const
{
    if(tail)    return tail->value;
    else        return -1;
};

double linked_list::at(size_t pos) const
{
    node_t * current = head;
    for(int i = 0; i != pos; i++)
        current = current->next;
    
    return current->value;
};

double linked_list::operator[](size_t pos) const
{
    return at(pos);
};

void linked_list::remove(size_t pos)
{
    node_t * rm = head;
    for(int i = 0; i < pos; i++)
        rm = rm->next;
    
    rm->prev->next = rm->next;
    rm->next->prev = rm->prev;
    
    rm->next = nullptr;
    rm->prev = nullptr;
    delete rm;
};

double linked_list::pop_front()
{
    double value = head->value;
    if(tail == head)
    {
        delete tail;
        tail = nullptr;
        delete head;
        head = nullptr;
    }
    else
    {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    return value;
};

double linked_list::pop_back()
{    
    double value = tail->value;

    if(tail == head)
    {
        tail = nullptr;
        head = nullptr;
        delete tail;
    }
    else
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
       
    return value;
};


size_t linked_list::size() const
{
    size_t size = 0;
    node_t * current = head;
    
    for(;current; size++)   
        current = current->next;
    
    return size;
};

bool linked_list::is_empty() const
{
    if(size() > 0)
        return false;
    else
        return true;
    //return size() == 0; //Returnerar om huvudet är nullptr eller inte
};

void linked_list::print() const
{
    for(int i = 0; i < size(); i++)
        std::cout << at(i) << " ";
    std::cout << std::endl;
};


void linked_list::print_reverse() const
{
    for(int i = size(); i > 0; i--)
        std::cout << at(i-1) << " ";
    std::cout << std::endl;
};
