#include "linked_list.h"
#include <cstdlib>
#include <ctime>

linked_list merge(linked_list list1, linked_list list2);

int main()
{
    srand(time(NULL));  //Initiera slumpgeneratorn
    
    //Skapa två nya listor
    linked_list list1;  
    linked_list list2;

    for(int i = 0; i < 100; i++)    //Tilldela 100 nya elemenet i båda listorna
    {
        if(!i)  //Om det är loopens första varv
        {   //Lägg till ett slumpat värde mellan 0 och 19 i båda listorna
            list1.push_back(rand() % 20);
            list2.push_back(rand() % 20);
        }
        else    
        {   //Lägg till ett slumpat värde mellan 0 och 19 + listans sista elements värde till 
            list1.push_back(list1.back() + rand() % 20);
            list2.push_back(list2.back() + rand() % 20);
        }
    }

    /*
     * Jämför listornas 50e element, ta bort det större elementet
     * Om elementen är lika stora tas inget element bort
     */
    if(list1[49] > list2[49])   
    { 
        std::cout << "Elementet i lista 1 är störst, tar bort det." << std::endl;
        list1.remove(49);   //Ta bort det större elementet
    }
    else if(list1[49] < list2[49])  
    {
        std::cout << "Elementet i lista 2 är störst, tar bort det." << std::endl;
        list2.remove(49);   //Ta bort det större elementet
    }
    else    std::cout << "Elementen är lika stora." << std::endl;
    
    linked_list list3 = list1;  //Skapa en ny lista och tilldela lista 1 till denna

    for(int i = 1; i < list3.size(); i++) //Ta bort varannat element i lista 3
    {
        list3.pop_back();
        list3.push_front(list3.pop_back());
    }
    
    list3.print();

    linked_list list4 = merge(list1, list2);

    return 0;
}

linked_list merge(linked_list list1, linked_list list2)
{
    linked_list list;
    
    double value1 = list1.pop_front();
    double value2 = list2.pop_front();
    
    while(!list1.is_empty() && !list2.is_empty())
    {
        if(value1 < value2)
        {
            list.push_back(value1);
            value1 = list1.pop_front();
        }
        else
        {
            list.push_back(value2);
            value2 = list2.pop_front();
        }
    }

    list.push_back(value1);
    list.push_back(value2);

    while(!list1.is_empty())  
        list.push_back(list1.pop_front());
    
    while(!list2.is_empty())        
        list.push_back(list2.pop_front());

    return list;
}