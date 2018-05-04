#include "linked_list.h"
#include <cstdlib>
#include <ctime>
#include <vector>

linked_list merge(linked_list list1, linked_list list2);

bool isSorted(linked_list list);

void print_list(linked_list list)
{
    list.print();
}

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
    std::cout << "Lista 1:" << std::endl;
    list1.print();

    std::cout << std::endl << "Lista 2:" << std::endl;
    list2.print();
    
    std::cout << std::endl;

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
    else    std::cout << "Elementen är lika stora, tar inte bort något." << std::endl;
    
    linked_list list3;
    list3 = list1;  //Skapa en ny lista och tilldela lista 1 till denna

    for(int i = 1; i < list3.size(); i++) //Ta bort varannat element i lista 3
    {
        list3.pop_back();
        list3.push_front(list3.pop_back());
    }

    //Skriver ut lista 3
    std::cout << std::endl << "Lista 3:" << std::endl;  
    print_list(list3);
    
    linked_list list4 = merge(list1, list2);    //Slår ihop lista 1 och 2 till lista 4

    //Skriver ut lista 4
    std::cout << std::endl << "Lista 4:" << std::endl;
    list4.print();

    //Skriver ut om lista 4 är sorterad eller inte
    std::cout << "Lista 4 är ";
    if(!isSorted(list4))    std::cout << "inte ";
    std::cout << "sorterad." << std::endl;

    return 0;
}

linked_list merge(linked_list list1, linked_list list2)
{
    linked_list list;   //Skapa en ny lista
    int iter1 = 0;  //Iterator för lista 1 
    int iter2 = 0;  //Iterator för lista 2

    while (iter1 < list1.size() && iter2 < list2.size())    //Så länge det finns element kvar i båda listorna
    {
        //Jämför elementen
        if(list1.at(iter1) > list2.at(iter2))
        {
            list.push_back(list2.at(iter2));    //Lägg till det större i listan
            iter2++;    //Öka dess iterator
        }
        else if(list1.at(iter1) < list2.at(iter2))
        {
            list.push_back(list1.at(iter1));    //Lägg till det större i listan
            iter1++;    //Öka dess iterator
        }
        else    //Om elementen är lika stora
        {
            list.push_back(list1.at(iter1));    //Lägg till båda elementen i listan
            list.push_back(list2.at(iter2));    
            iter1++;    //Öka bådas iteratorer
            iter2++;
        }   
    }
    
    /*
     * Om det finns element kvar i någon av listorna, 
     * lägg till dessa i den nya listan.
     */
    while(iter1 < list1.size())
    {
        list.push_back(list1.at(iter1));    
        iter1++;
    }

    while(iter2 < list2.size())
    {
        list.push_back(list2.at(iter2));
        iter2++;
    }

    return list;    //Returnera den nya listan
}

bool isSorted(linked_list list)
{
    for(int i = 1; i < list.size()-1;i++)   //Gå igenom samtliga element i listan
        if(list[i] < list[i-1]) //Om elementet är mindre än föregående element  
            return false;   //Returnera att listan inte är sorterade

    return true;    //Om listan tar sig igenom hela loopen, returnera att listan är sorterad
}