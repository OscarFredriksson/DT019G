#include "linked_list.h"
#include <cstdlib>
#include <ctime>

linked_list merge(linked_list list1, linked_list list2);

int main()
{
    srand(time(NULL));
    
    linked_list list1;
    linked_list list2;
    
    for(int i = 0; i < 100; i++)
    {
        if(!i)  
        {
            list1.push_back(rand() % 20);
            list2.push_back(rand() % 20);
        }
        else
        {
            list1.push_back(list1.back() + rand() % 20);
            list2.push_back(list2.back() + rand() % 20);
        }
    }

    if(list1[49] > list2[49])
    { 
        std::cout << "Elementet i lista 1 är störst, tar bort det." << std::endl;
        list1.remove(49);
    }
    else if(list1[49] < list2[49])
    {
        std::cout << "Elementet i lista 2 är störst, tar bort det." << std::endl;
        list2.remove(49);
    }
    else
        std::cout << "Elementen är lika stora." << std::endl;
    
    linked_list list3 = list1;

    for(int i = 0; i < 50; i++)
    {
        list3.pop_back();
        list3.push_front(list3.pop_front());
    }
    
    list3.print();
    list3.print_reverse();

    return 0;
}