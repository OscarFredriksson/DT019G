#include "maze.h"
#include <iostream>
#include <unistd.h> //getopt, mm
#include <stdlib.h> //atoi

void printHelp();   //Skriver ut hjälptext

int main(int argc, char* argv[])
{
    Maze maze;
   
    int arg;
    while ((arg = getopt(argc, argv, "hvs:")) != -1)
    {
        if(arg == 'v')    std::cout << "Version 1.0" << std::endl;
        if(arg == 's')
        {
            std::cout << "Size flaggan är på, dess värde är: " << optarg << std::endl;
            maze.size = atoi(optarg);
        }
        if(arg == 'h')    printHelp();
        if(arg == '?')  std::cout << "Felaktigt argument" << std::endl;
    }

    return EXIT_SUCCESS;
}

void printHelp()
{
    std::cout << std::endl;
    std::cout << "\t--version  | -v. Skriver ut versionsnummer." << std::endl;
    std::cout << "\t--help     | -h. Skriver ut tillgängliga argument." << std::endl;
    std::cout << "\t(--size    | -s)N. Skapa en labyrint med storleken N." << std::endl;
    std::cout << "\t(--columns | -c)W. Skapa en labyrint med bredden W." << std::endl;
    std::cout << "\t(--rows    | -r)H. Skapa en labyrint med höjden N." << std::endl;
    std::cout << "\t(--input   | -i)file. Använd filen file som indata." << std::endl;
    std::cout << "\t(--output  | -o)file. Använd filen file för utdata. Annars cout." << std::endl;
    std::cout << "\t--check    | -b. Skriver ut endast \"Solution found\" om en lösning finnes, annars \"Solution not found\"." << std::endl;
    std::cout << std::endl;
}
