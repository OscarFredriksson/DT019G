#include "person.h"
#include "misc.h"

//Öppnar filen med det givna filnamnet och läser in de personer som finns i den.
std::vector<person> read_file(std::string filename)
{
    std::vector<person> temp_vec;   //Skapar en temporär vektor att läsa in personerna i
    
    std::ifstream input;
    input.open(filename.c_str());   //Öppnar filen
    
    if(!input.is_open()) return temp_vec;   //Om filen inte kan öppnas, returnera den tomma vektorn.
    
    person temp_pers;   //Skapar en temporär person att läsa till från filen
    
    while(input >> temp_pers)   //Sålänge personer kan läsas ur filen
        temp_vec.push_back(temp_pers);  //Lägg till dessa i vektorn

    return temp_vec;  //Returnerar vektorn
}

//Överlagrar inströmsoperatorn för inläsning av personer.
std::istream& operator>>(std::istream& in, person& p)
{
    std::getline(in, p.name);
    
    if(p.name == "") 
        return in; //Om kontakten är tom, gå ur funktionen

    std::getline(in, p.id);
    
    std::getline(in, p.adress.street, ','); //Läser fram tills nästa kolon och sparar det i gatuvariabeln

    //Skapar en temporär adress-variabel att läsa in resten av raden i, för att sedan kunna skapa substrings utifrån detta.
    std::string temp_adress;
    std::getline(in, temp_adress);    
    
    //Skapar en temporär variabel för zip-koden för att kunna hantera den som en sträng innan den tilldelas till den "riktiga" variabeln
    std::string temp_zip;   

    temp_zip = temp_adress.substr(1, 6); //extraherar zip-koden ur adressraden
    temp_zip.erase(std::remove_if(temp_zip.begin(), temp_zip.end(), isspace), temp_zip.end());   //Tar bort mellanslag i zip-koden
    
    p.adress.zip = stoi(temp_zip);  //Gör om den temporära zip-kodsvariabeln till en integer och tilldelar den till den "riktiga" variabeln
    
    p.adress.city = temp_adress.substr(temp_adress.find("  ")+2);   //Extraherar staden ur adressraden

    p.adress.city.erase(p.adress.city.begin() + p.adress.city.find("  "), p.adress.city.end()); //Tar bort samtliga mellanslag efter staden
    
    return in;
}

//Returnerar antalet personer som innehåller den givna söksträngen
size_t find_in_names(std::vector <person> persons, std::string name_part)
{
    name_part = tolower(name_part); //Gör samtliga tecken i söksträngen små bokstäver
   
    size_t count = 0;   //Håller koll på antal hittade personer som innehåller söksträngen
    
    for(int i = 0;i<persons.size();i++) //Går igenom samtliga personer i vektorn
    {
        std::string temp_name;
        temp_name = tolower(persons[i].name); //Gör samtliga tecken i namnet till små bokstäver och sparar det i en temporär variabel
        
        if(temp_name.find(name_part) != std::string::npos)  //Om söksträngen finns i namnet, öka på räknaren
            count++;
    }
    return count;   //Returnera antalet hittade personer
}

//Returnerar alla personer som bor i de städer som innehåller den givna söksträngen
std::vector<person> find_person_from_city(std::vector <person> haystack, std::string city)
{    
    city = tolower(city);   //Gör samtliga tecken i söksträngen till små bokstäver. 

    std::vector<person> temp_matches;   //Skapar en temporär vektor att lagra de personer som ska returneras i 
    
    for(int i = 0; i<haystack.size();i++)   //Går igenom samtliga personer
    {
        std::string temp_city;

        temp_city = tolower(haystack[i].adress.city);   //Gör samtliga tecken i staden till små bokstäver och sparar det i en temporär variabel
        
        if(temp_city == city)   //Om söksträngen stämmer överens med staden
            temp_matches.push_back(haystack[i]);    //Lägg till personen i vektorn

    }
    return temp_matches;    //Returnera vektorn
}