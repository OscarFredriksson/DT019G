#include "linked_list.h"
#include <time.h>

int main()
{
    srand(time(0));
    linked_list ll;
    ll.push_back(ll.back() + rand()% 20);

    

    return 0; 
}