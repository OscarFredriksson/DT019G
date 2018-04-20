#include "misc.h"

//Rensar skärmen och skriver sedan ut menytexten.
void printMenu()    
{
        system(clr_str);    //Rensar skärmen
        std::cout << "Vad vill du göra? Skriv en siffra för att välja." << std::endl;
        std::cout << "1. Sök del av personnamn" << std::endl;
        std::cout << "2. Sök städer" << std::endl;
        std::cout << "3. Avsluta programmet" << std::endl;
}

//Tar in en sökterm.
std::string getInput()  
{
    std::string searchterm;

    std::cout << "Skriv in sökterm:" << std::endl;
    std::getline(std::cin, searchterm); //Tar in hela raden utifall inmatningen innehåller mellanslag
    
    return searchterm;
}

//Tar in en entertryckning.
void getEnter() 
{
    std::cout << std::endl << "Tryck ENTER för att återgå till menyn" << std::endl;
    std::cin.get(); //Läser in en entertryckning
}

//Tar in en sträng och returnar strängen där samtliga tecken är omvandlade till lowercase.
std::string tolower(std::string str)   
{
    for(int i = 0; i<str.length();i++)  //Går igenom samtliga tecken i strängen och gör om de till lowercase
            str[i] = tolower(str[i]);
    
    /*
    *   tolower funktionen funktionen funkar ej för åäö därför används nedanstående metod
    *   för att göra dessa till lowercase.
    */
    while(str.find("Å") != std::string::npos)   //Sålänge ett eller flera "Å" kan hittas i strängen
        str.replace(str.find("Å"), 2, "å");     //Ersätt "Å" med "å"
    
    while(str.find("Ä") != std::string::npos)
        str.replace(str.find("Ä"), 2, "ä");
    
    while(str.find("Ö") != std::string::npos)
        str.replace(str.find("Ö"), 2, "ö");
    
    return str; //Returnerar den omvandlade strängen
}