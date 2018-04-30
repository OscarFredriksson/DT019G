#include <iostream>
#include <cstddef>

class linked_list 
{
public:

    //Default constructor
    linked_list() = default;
    
    //Kopierings constructor?
    //linked_list(const linked_list & src);
    
    //Destructor
    //~linked_list();

    /*
    //Överlagra tilldelningsoperatorn
    linked_list & operator =(const linked_list & rhs);
    
    //Överlagra += operatorn.
    linked_list & operator +=(const linked_list & rhs);
    
    //Lägga till element
    void insert(double value, size_t pos);  //Lägg till ett element på en specifik position
    */void push_front(double value);          //Lägg till ett element längst fram
    void push_back(double value);           //Lägg till ett element längst bak
    /*
    
    //Nå element
    */double front() const;                  //Returnerar elementet längst fram
    double back() const;                   //Returnerar elementet längst bak
    double at (size_t pos) const;          //Returnerar elementet på en specifik position
    /*double & operator[](size_t pos) const;   //Returnerar elementet på en specifik position   

    

    void remove (size_t pos);   //Tar bort element på en specifik position
    
    //remove and access
    */double pop_front(); //Tar bort elementet längst fram i listan och returnerar det
    /*double pop_back();  //Tar bort elementet längst bak i listan och returnerar det
    
    //informational
    */size_t size() const;    //Returnerar listans storlek
    /*bool is_empty() const;  //returnerar om listan är tom eller inte
    
    //output
    void print() const;         //Skriver ut listan
    void print_reverse() const; //Skriver ut listan omvänt*/
        
private:
    struct node_t   //En nod i listan
    {
        node_t(double value , node_t * next = 0, node_t * prev = 0)
            :value(value), next(next), prev(prev)
		    {};   //Constructor
        
        double value;   //Nodens data
        node_t * next;  //Nästa element i listan?
        node_t * prev;  //Föregående element i listan?
    };

    node_t * head = 0;  //Första positionen i listan
    node_t * tail = 0;  //Sista positionen i listan
};