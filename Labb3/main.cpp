#include "linked_list.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    linked_list list;
    for(int i = 0; i < 20; i++)
    {
      list.push_front(rand() % 100);
      std::cout << list.at(i) << " ";
    }
    std::cout << std::endl << list.size() << std::endl;
    
    
    /*list.push_front(5);
    std::cout << list.front() << " " << list.size() << std::endl;
    list.push_back(3);
    std::cout << list.size() << std::endl;*/

    return 0; 
}