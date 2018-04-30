#include "linked_list.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    linked_list list;
    for(int i = 0; i < 20; i++)
    {
      list.push_back(rand() % 100 + 1);
    }
    //std::cout << list.size() << std::endl;

    for(int i = 0; i < list.size(); i++)
        std::cout << list.at(i) << " ";
    
    std::cout << std::endl;
        
    list.push_front(5);
    list.print();
    list.push_back(2);
    list.print();
    std::cout << list.size() << std::endl;

    return 0; 
}