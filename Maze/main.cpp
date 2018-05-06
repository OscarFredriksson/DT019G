#include "maze.h"
#include <iostream>
#include <unistd.h> //getopt
#include <cstdlib> //atoi, srand
#include <stack>
#include <ctime>    //time


void printHelp();   //Skriver ut hjälptext

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    Maze maze;
    
    //std::stack<char> path;

    int arg;
    while ((arg = getopt(argc, argv, "hvs: c: r:")) != -1)
    {
        if(arg == 'v')    std::cout << "Version 1.0" << std::endl;
        if(arg == 'h')
        { 
            printHelp();    
            return 0;   
        }
        if(arg == 's')
        {
            maze.columns = atoi(optarg);
            maze.rows = atoi(optarg);
        }
        if(arg == 'c')  maze.columns = atoi(optarg);
        if(arg == 'r')  maze.rows = atoi(optarg);
        if(arg == '?')  std::cout << "Felaktigt argument" << std::endl;
    }

    //Generera
    for(int i = 0; i <= maze.columns; i++)  //Loopar kolumner
    {
        std::vector<char> temp; //Temporär vektor att spara varje rad i 
        int rndm;
        if(i == 0 || i == maze.columns-1)   rndm = rand() % (maze.rows-2) + 1;  //Slumpa start/slut position
        
        for(int j = 0; j <= maze.rows; j++) //Loopar rader
        {
            if(j == 0 || j == maze.rows-1)    temp.push_back(maze.WALL);    //Första och sista raden ska vara solida väggar
            else if(i == 0) //Om det är första kolumnen ska startpunkten skrivas
            {
                if(j == rndm)   temp.push_back(maze.START); //Om startpunkten är nådd skriv denna
                else            temp.push_back(maze.WALL);  //Annars skriv vägg
            }
            else if(i == maze.columns-1)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == rndm)   temp.push_back(maze.END);   //Om slutpunkten är nådd skriv denna
                else            temp.push_back(maze.WALL);  //Annars skriv vägg
            }
            else    //Annars slumpas vägg eller gång, har ska DFS-metoden senare tillämpas
            {
                int rndm = rand() % 2;
                if(rndm % 2 == 0)   temp.push_back(maze.WALL);
                else                temp.push_back(maze.PATH);
            }
        }
        maze.maze.push_back(temp);  //Lägg till raden 
    }

    //Skriv ut
    for(int i = 0; i < maze.columns; i++)  //Skriv ut
    {
        for(int j = 0; j < maze.rows; j++)
            std::cout << maze.maze[j][i];
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

void printHelp()    //Skriver ut hjälptext
{
    std::cout << std::endl;
    std::cout << "\t--version  | -v.      Skriver ut versionsnummer." << std::endl;
    std::cout << "\t--help     | -h.      Skriver ut tillgängliga argument." << std::endl;
    std::cout << "\t(--size    | -s)N.    Skapa en labyrint med storleken N. Defaultvärde: 100." << std::endl;
    std::cout << "\t(--columns | -c)W.    Skapa en labyrint med bredden W. Defaultvärde: 100." << std::endl;
    std::cout << "\t(--rows    | -r)H.    Skapa en labyrint med höjden N. Defaultvärde: 100." << std::endl;
    std::cout << "\t(--input   | -i)file. Använd filen file som indata." << std::endl;
    std::cout << "\t(--output  | -o)file. Använd filen file för utdata. Annars cout." << std::endl;
    std::cout << "\t--check    | -b.      Skriver ut endast \"Solution found\" om en lösning finnes, annars \"Solution not found\"." << std::endl;
    std::cout << std::endl;
}
