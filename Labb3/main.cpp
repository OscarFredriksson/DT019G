#include "linked_list.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    linked_list list1;
    linked_list list2;
    for(int i = 0; i < 100; i++)
    {
      list1.push_back(list1.back() + rand() % 20);
      list2.push_back(list1.back() + rand() % 20);
    }
    list1.print();
    list2.print();




    return 0; 
}