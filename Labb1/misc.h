#include <iostream>

#ifdef WIN32    //Om systemet är windows
    #define clr_str "CLS"   
#else
    #define clr_str "clear"
#endif

//Rensar skärmen och skriver sedan ut menytexten.
void printMenu();   

//Tar in en sökterm.
std::string getInput(); 

//Tar in en entertrycking.
void getEnter();    

//Tar in en sträng och returnar strängen där samtliga tecken är omvandlade till lowercase.
std::string tolower(std::string str);   