#include "linked_list.h"

linked_list::linked_list()
{

};

linked_list::linked_list(const linked_list & src)
{

};

linked_list::~linked_list()
{

};

linked_list& linked_list::operator=(const linked_list& rhc)
{

};

linked_list& linked_list::operator+=(const linked_list& rhc)
{

};

void linked_list::insert(double value, size_t pos)
{

};

void linked_list::push_front(double value)
{
    auto node = new linked_list::node_t(value, head, nullptr);
    head->prev = node;
    node->next = head;
    head = node;
};

void linked_list::push_back(double value)
{
    auto node = new linked_list::node_t(value, nullptr, tail);
    tail->next = node;
    node->prev = tail;
    tail = node;
};

double linked_list::front() const
{
    return head->value;
};

double linked_list::back() const
{
    return tail->value;
};

double linked_list::at(size_t pos) const
{
    
};

double linked_list::operator[](size_t pos) const
{
    return at(pos);
};

void linked_list::remove(size_t pos)
{

};

double linked_list::pop_front()
{

};

double linked_list::pop_back()
{
    double value = tail->value;
    if(tail == head)
    {
        delete tail;
        tail = nullptr;
        delete head;
        head = nullptr;
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
    while(current != nullptr)
    {
        size++;
        current = current->next;
    }

    return size;
};

bool linked_list::is_empty() const
{

};

void linked_list::print() const
{

};

void linked_list::print_reverse() const
{

};
