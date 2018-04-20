#include <iostream>
#include <cstdint> 
#include <vector>
#include <math.h>

#ifdef WIN32    //Om systemet är windows
    #define clr_str "CLS"   
#else
    #define clr_str "clear"
#endif

struct Gibibyte //En datatyp som är en gibibyte stor ....
{
    int8_t gibibyte[1073741824] = {0};  //Skapar en array som är 1024^3 bytes (alltså en gibibyte) stor. 
};

struct Kibibyte //En datatyp som är en kibibyte stor
{
    int8_t kibibyte[1024] = {0};    //Skapar en array som är 1024 bytes (alltså en kibibyte) stor.
};

int main()
{
    std::vector<Gibibyte*> gibibytes;   //Skapar en vektor med pekare som pekar på minnesplatser för datatypen Gibibyte
    std::vector<Kibibyte*> kibibytes;   //Skapar en vektor med pekare som pekar på minnesplatser för datatypen Kibibyte
    
    bool exit = false;  
    while(!exit)    //Kör sålänge användaren inte ber om att avsluta programmet
    {
        system(clr_str);    //Rensar skärmen
        std::cout << "Har allokerat: " << gibibytes.size() << "GiB och " << kibibytes.size() << "KiB." << std::endl;    //Skriver ut hur mycket minne användaren har allokerat
       
        //Skriver ut menyn
        std::cout << "Vad vill du göra? Skriv en siffra för att välja." << std::endl;
        std::cout << "1. Allokera 1 GiB." << std::endl;
        std::cout << "2. Allokera 1 KiB." << std::endl;
        std::cout << "3. Avsluta programmet och frigöra minne." << std::endl;
        
        int menu;
        std::cin >> menu;    //Tar in menyval

        switch(menu)
        {
            case 1:
            {
                try
                {
                    gibibytes.push_back(new Gibibyte);  //Försök allokera en Gibibyte minne
                }
                catch(std::bad_alloc e )    //Om det misslyckades
                {
                    std::cerr << "Nått gick fel: " << e.what() << std::endl;    //Informera användaren
                    std::cin.ignore();  //Ignorerar överbklivet whitespace efter cin.
                    std::cin.get(); //Tar in en entertryckning
                }
                break;
            }
            case 2:
            {
                try
                {
                    kibibytes.push_back(new Kibibyte);  //Försök allokera en Kibibyte
                }
                catch( std::bad_alloc e )   //Om det misslyckades
                {
                    std::cerr << "Nått gick fel: " << e.what() << std::endl;    //Informera användaren
                    std::cin.ignore();  //Ignorerar överblivet whitespace efter cin.
                    std::cin.get(); //Tar in en entertryckning
                }
                break;
            }
            case 3:
                exit = true;    //Avsluta loopen
                break;
            default:
                std::cout << "Felinmatning." << std::endl;
                break;
        }
        
    }

    for(int i = 0; i < gibibytes.size(); i++)   //Ta bort allt minne allokerat av datatypen Gibibyte
        delete gibibytes[i];

    for(int i = 0; i < kibibytes.size(); i++)   //Ta bort allt minne allokerat av dataypen Kibibyte
        delete kibibytes[i];
        
    return 0;
}
