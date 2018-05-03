#include "linked_list.h"

linked_list::linked_list(const linked_list & src)
{
    *this = src;    //Ska göra samma som tilldelningsoperatorn
};

linked_list::~linked_list()
{
    while(!is_empty())  pop_back(); //Ta bort samtliga element i listan
};

linked_list& linked_list::operator=(const linked_list& rhs)
{
    while(!is_empty()) pop_back();   //Töm listan

    return *this += rhs;   //Tilldela den nya listan till denna lista
};

linked_list & linked_list::operator+=(const linked_list & rhs)
{
    node_t * current = rhs.head;    //Skapar en ny nod för att gå igenom inargumentslistan
    
    while(current)  //Så länge slutet av listan inte är nådd
    {
        push_back(current->value);  //Lägg till den nuvarande nodens värde till originallistan
        current = current->next;    //Gå vidare i listan
    }
    return *this;   //Returnera originallistan.
};

linked_list & linked_list::append(const linked_list & rhs)
{
    return *this += rhs;    //Ska göra samma som sammanfogningsoperatorn
};

void linked_list::insert(double value, size_t pos)
{
    if(size() < pos)    //Om positionen inte finns 
    {
        push_back(value);   //Lägg till elementet sist i listan
        return; //Gå ur funktionen
    }
    
    node_t * node_pos = head;   //Positionen för den nya noden
    
    for(int i = 0; i <= pos; i++)   //Loopa fram till positionen för den nya noden
        node_pos = node_pos->next;  //Gå till nästa nod i listan

    node_t * node = new node_t();   //Den nya noden som ska läggas till
    node->value = value;    //Tilldela värdet till den nya noden
    
    node->next = node_pos;  //Den nod som tidigare låg på den nya nodens position ska vara nästa nod i listan
    node->prev = node_pos->prev;    //Den nya noden ska peka på föregående nod i listan

    node_pos->prev->next = node;    //Den nod som var innan den nya nodens position ska peka på den nya noden som nästa nod i listan
    node_pos->prev = node;  //Den nod som nu är nästa nod ska peka på den nya noden som föregående nod i listan
};

void linked_list::push_front(double value)
{
    node_t * node = new node_t(value, head, nullptr); //Skapa en ny nod
    
    if(head)    head->prev = node;  //Om det finns ett huvud, tilldela dess prev-pekare till den nya noden

    head = node;    //Gör den nya noden till huvud  
    
    if(!tail)   tail = head;    //Om det nya huvudet är det enda elementet i listan, gör det även till svans    

};

void linked_list::push_back(double value)
{
    node_t * node = new node_t(value, nullptr, tail);   //Skapa en ny nod
    
    if(tail)    tail->next = node;  //Om det finns en svans, tilldela dess next-pekare till den nya noden

    tail = node;    //Gör den nya noden till svans

    if(!head)   head = node;    //Om det inte finns ett huvud
};

double linked_list::front() const
{  
    return head->value; //Returnera huvudets värde
};

double linked_list::back() const
{
    return tail->value; //Returnera svansens värde
};

double linked_list::at(size_t pos) const
{
    node_t * current = head;    //Ska efter loopen peka på den givna platsen i listan
    for(int i = 0; i != pos; i++)   //Loopa till den givna positionen
        current = current->next;    //Gå till nästa nod i listan
    
    return current->value;  //Returnera värdet för den givna noden
};

double linked_list::operator[](size_t pos) const
{
    return at(pos); //Ska göra samma som at(), returnera detta för den givna positionen.
};

void linked_list::remove(size_t pos)
{
    node_t * rm = head; //Ska efter loopen peka på den nod som ska tas bort
    for(int i = 0; i < pos; i++)    //Loopa till den givna positionen
        rm = rm->next;  //Gå till nästa nod i listan
    
    rm->prev->next = rm->next;  //Föregående nods next-pekare ska peka på efterföljande nod
    rm->next->prev = rm->prev;  //Efterföljande nods prev-pekare ska peka på föregående nod
    
    //Det borttagna elementets pekare ska inte peka på något
    rm->next = nullptr;  
    rm->prev = nullptr;
    delete rm;  //Frigör minnet
};

double linked_list::pop_front()
{
    double value = head->value; //Spara värdet för det första elementet i listan
    
    if(size() == 1) //Om det bara finns ett element i listan
    {
        delete head;    //Frigör minnet
        head = nullptr; //Ta bort head ur listan
        tail = nullptr; //Ta bort tail ur listan
    }
    else
    {
        head = head->next;  //Gör det tidigare elementet till head
        delete head->prev;  //Frigör minnet
        head->prev = nullptr;   //Ta bort det första elementet ur listan
    }

    return value;
};

double linked_list::pop_back()
{    
    double value = tail->value; //Spara värdet för det sista elementet i listan

    if(size() == 1) //Om det bara finns ett element i listan
    {
        delete tail;    //Frigör minnet
        tail = nullptr; //Ta bort tail ur listan
        head = nullptr; //Ta bort head ur listan
    }
    else   
    {
        tail = tail->prev;  //Gör det näst sista elementet till tail
        delete tail->next;  //Frigör minnet
        tail->next = nullptr;   //Ta bort det sista elementet ur listan
    }

    return value;   //Returnera värdet för det sista elementet i listan
};


size_t linked_list::size() const
{
    size_t size = 0;    //Listans storlek
    node_t * current = head;    //Skapar en ny pekare för att iterera igenom listan
    
    for(;current; size++)   //Loopa sålänge listans slut inte är nådd, öka på storleken varje varv
        current = current->next;    //Gå till nästa nod i listan
    
    return size;    //Returnera storleken
};

bool linked_list::is_empty() const
{
    return size() == 0; //Returnerar jämförelsen
};

void linked_list::print() const
{
    for(int i = 0; i < size(); i++) //Loopar igenom listan
        std::cout << at(i) << " ";  //Skriv ut elementet på aktuell position
    std::cout << std::endl; //Efter samtliga element, skriv ut en radbrytning
};


void linked_list::print_reverse() const
{
    for(int i = size()-1; i >= 0; i--)  //Loopa igenom listan omvänt
        std::cout << at(i) << " ";  //Skriv ut elementet på aktuell position
    std::cout << std::endl; //Efter samtliga element skriv ut en radbrytning
};
