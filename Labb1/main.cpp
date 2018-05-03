#include "person.h"
#include "misc.h"

int main()
{
    std::string filename = "names.txt";
    std::vector<person> persons = read_file(filename);
    
    if(persons.size() == 0) //Om det inte finns några kontakter, avsluta programmet
    {
        std::cout << "Kunde inte läsa in några personer, avslutar programmet." << std::endl;
        return -1;
    }

    bool exit = false;  
    while(!exit)    //Loopa sålänge användaren inte ber om att avsluta programmet
    {
        printMenu();

        std::string temp;
        std::getline(std::cin, temp);   //Tar in inmatning i en temporär variabel
        int val = stoi(temp);   //Gör strängen till en int

        switch(val)
        {
            case 1: //Söka efter en person
            {
                std::string searchterm = getInput();    //Tar in sökterm
                
                std::cout << "Hittade " << find_in_names(persons, searchterm) 
                          << " personer med söktermen \"" << searchterm << "\"." << std::endl;  //Skriver ut antalet hittade personer
                
                getEnter(); //Ber användaren om en entertryckning
                break;
            }
            case 2: //Söka städer
            {
                std::string searchterm = getInput();    //tar in sökterm
                
                std::vector<person> matches = find_person_from_city(persons, searchterm);   //Sparar samtliga träffar
                
                std::cout << std::endl << "Hittade " << matches.size();  //Skriver ut antalet träffar
                
                if(matches.size() == 0)         std::cout << " personer." << std::endl;
                else if(matches.size() == 1)    std::cout << " person:" << std::endl; 
                else                            std::cout << " personer:" << std::endl;
                
                for(int i = 0; i < matches.size();i++)  //Skriver ut samtliga träffar
                    std::cout << matches[i].name << ", " << matches[i].adress.city << std::endl; 
                
                getEnter(); //Ber användaren om en entertryckning
                break;
            }
            case 3: //Avsluta programmet
                exit = true;    //Gå ur loopen
                break;
            default:
                std::cout << "Felinmatning, prova igen." << std::endl;
                getEnter(); //Ber användaren om en entertryckning
                break;
        }
    }
    return 0;
}



