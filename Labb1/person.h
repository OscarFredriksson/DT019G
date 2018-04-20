#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct location
{
    std::string street;
    int zip;
    std::string city;
};

struct person
{
    std::string name;
    std::string id;
    location adress;
};

//Öppnar filen med det givna filnamnet och läser in de personer som finns i den.
std::vector <person> read_file(std::string filename);

//Överlagrar inströmsoperatorn för inläsning av personer.
std::istream& operator>>(std::istream& in, person& p);

//Returnerar antalet personer som innehåller den givna söksträngen.
size_t find_in_names(std::vector <person> persons, std::string name_part);

//Returnerar alla personer som bor i de städer som innehåller den givna söksträngen.
std::vector <person> find_person_from_city(std::vector <person> haystack, std::string city);