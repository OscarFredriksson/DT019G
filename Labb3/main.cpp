#include "linked_list.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    linked_list list1;
    linked_list list2;
    for(int i = 0; i < 10; i++)
    {
      list1.push_back(list1.back() + rand() % 20);
      list2.push_back(list2.back() + rand() % 20);
    }
    /*if(list1[50] > list2[50])
    { 
        std::cout << "Elementet i lista 1 är störst." << std::endl;
        list1.remove(50);
    }
    else if(list1[50] < list2[50])
    {
        std::cout << "Elementet i lista 2 är störst." << std::endl;
        list2.remove(50);
    }
    else
        std::cout << "Elementen är lika stora." << std::endl;*/

    list1.print();
    std::cout << "storlek: " << list1.size() << std::endl;
    list1.insert(5, 2);
    list1.print();
    std::cout << "storlek: " << list1.size() << std::endl;


    /*list1.push_back(2);
    list1.push_back(3);
    std::cout << list1.pop_back() << std::endl;
    std::cout << list1.pop_back() << std::endl;
    list1.size();*/

    return 0;
}