#include "maze.h"
#include <getopt.h>
#include <cstdlib> //atoi
#include <fstream>
#include <string>

void printHelp();   //Skriver ut hjälptext

bool validateArg(char* optarg);

int main(int argc, char* argv[])
{    
    srand(time(NULL));

    Maze maze;
    
    std::string inputFile;  //Filnamnet för den fil som ska läsas från
    std::string outputFile; //Filnamnet för den fil som ska skrivas till (behövs två utifall det ska skrivas och läsas från olika filer)

    bool readFromFile = false;  //Om det ska läsas från filen eller inte
    bool writeToFile = false;   //Om det ska skrivas till filen eller inte

    bool check = false;
    
    const char    * short_opts = "vhbws: c: r: i: o: ";    //Definierar samtliga getopt flaggor
    const struct option long_opts[] =   //Definierar samtliga långa getopt flaggor
    {
        {"version", 0,  NULL, 'v'},
        {"help",    0,  NULL, 'h'},
        {"watch",   0,  NULL, 'w'},
        {"check",   0,  NULL, 'b'},
        {"size",    1,  NULL, 's'},
        {"columns", 1,  NULL, 'c'},
        {"rows",    1,  NULL, 'r'},
        {"input",   1,  NULL, 'i'},
        {"output",  1,  NULL, 'o'},
        {NULL,      1,  NULL, '?'}
    };

    int arg;
    while ((arg = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1)   //Loopa igenom alla argument
    {
        switch(arg)
        {
            case 'v':
                std::cout << "Version 1.0" << std::endl;  //Skriv ut version
                return EXIT_SUCCESS;
            case 'h':
            { 
                printHelp();    
                return EXIT_SUCCESS;   
            }
            case 'w':
            {
                if(check)
                {
                    std::cerr << "--watch och --check kan inte anges samtidigt." << std::endl;
                    return EXIT_FAILURE;
                }
                else    maze.showIterations = true;
                break;
            }
            case 'b':
            {
                if(maze.showIterations)
                {
                    std::cerr << "--watch och --check kan inte anges samtidigt." << std::endl;
                    return EXIT_FAILURE;
                }
                else    check = true;
                break;
            }
            case 's':   //Storlek
            {
                if(validateArg(optarg))
                {
                    size_t size = atoi(optarg);

                    maze.cols = size;
                    maze.rows = size;
                } 
                else 
                {
                    std::cerr << "Felaktigt argument: --size måste vara en integer." << std::endl;
                    return EXIT_FAILURE;  
                }
                break;
            }
            case 'c':  //Kolumner
            {
                if(validateArg(optarg))
                {
                    size_t size = atoi(optarg);

                    maze.cols = size;
                } 
                else 
                {
                    std::cerr << "Felaktigt argument: --columns måste vara en integer." << std::endl;
                    return EXIT_FAILURE; 
                } 
                break;
            }
            case 'r':   //Rader
            {
                if(validateArg(optarg))
                {
                    size_t size = atoi(optarg);

                    maze.rows = size;
                }   
                else    
                {
                    std::cerr << "Felaktigt argument: --rows måste vara en integer." << std::endl;
                    return EXIT_FAILURE;
                }
                break;
            }
            case 'i':  //Om flaggan för utdata till en fil istället för cout
            {
                readFromFile = true;
                inputFile = std::string(optarg); //Spara filnamnet
                break;
            }
            case 'o':  //Om flaggan för utdata till en fil istället för cout
            {
                writeToFile = true;
                outputFile = std::string(optarg); //Spara filnamnet
                break;
            }
            case '?':  return EXIT_FAILURE; //Om ett felaktigt argument ges
            default:
            {
                std::cerr << "Nått gick fel, programmet bör ej komma hit." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    if(readFromFile)
    {
        std::ifstream input(inputFile.c_str());
        if(!input.is_open())
        {
            std::cerr << "Kunde inte öppna filen \"" << inputFile << "\"." << std::endl;
            return EXIT_FAILURE;
        }
        try //Testar läsa in från filen
        {
            input >> maze;
        }
        catch(char const* c)
        {
            std::cerr << "Error: " << c << std::endl;
            return EXIT_FAILURE;
        }
    }
    else    maze.generate();
    
    if(check)
    {
        if(maze.solve())    std::cout << "Löste labyrinten!" << std::endl;
        else                std::cout << "Lyckades inte lösa labyrinten." << std::endl;
    } 
    else if(maze.solve())
    { 
        if(writeToFile) //Om det ska skrivas till filen
        {
            std::ofstream output(outputFile.c_str()); //Öppna filen med filnamnet
            if(!output.is_open())
            {
                std::cerr << "Kunde inte öppna eller skapa filen \"" << outputFile << "\"." << std::endl;
                return EXIT_FAILURE;
            }
            output << maze << std::endl;    //Skriv labyrinten till den
        }
        else    std::cout << maze << std::endl;
    }
    else std::cout << "Lyckades inte lösa labyrinten." << std::endl;

    return EXIT_SUCCESS;    //Om den tar sig igenom hela koden utan problem, returnera att körningen gick bra
}

void printHelp()    //Skriver ut hjälptext
{
    std::cout << std::endl;
    std::cout << "\t --version  | -v.      Skriver ut versionsnummer." << std::endl;
    std::cout << "\t --help     | -h.      Skriver ut detta." << std::endl;
    std::cout << "\t --watch    | -w.      Visar varje iteration medan labyrinten skapas/löses." << std::endl;
    std::cout << "\t --check    | -b.      Skriver ut endast \"Löste labyrinten!\" om en lösning finnes, annars \"Lyckades inte lösa labyrinten.\"." << std::endl;
    std::cout << "\t(--size    | -s)N.    Skapa en labyrint med storleken N. Defaultvärde: 10." << std::endl;
    std::cout << "\t(--columns | -c)W.    Skapa en labyrint med bredden W.   Defaultvärde: 10." << std::endl;
    std::cout << "\t(--rows    | -r)H.    Skapa en labyrint med höjden H.    Defaultvärde: 10." << std::endl;
    std::cout << "\t(--input   | -i)file. Använd filen file som indata istället för att generera en labyrint." << std::endl;
    std::cout << "\t(--output  | -o)file. Använd filen file för utdata. Annars cout." << std::endl;
    std::cout << std::endl;
}

bool validateArg(char* optarg)  //Kollar om ett argument innehåller endast integers
{
    std::string temp(optarg);   //Gör om char* till string
    
    for(int i = 0; i < temp.size(); i++)    //Loopa igenom samtliga
        if(!isdigit(temp[i]))   return false;   //Returnera false om något som inte är en siffra hittas

    return true;    //Om den tar sig igenom hela loopen är samtliga elemenet integers
}