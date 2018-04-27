#include "linked_list.h"
#include <time.h>

int main()
{
    srand(time(0));
    linked_list list;
    for(int i = 0; i < 20; i++)
        list.push_back(list.back() + rand()% 20);
    list.print();


    return 0; 
}