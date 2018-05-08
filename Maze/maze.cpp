#include "maze.h"

void Maze::generateMaze()
{
    for(int i = 0; i <= columns; i++)  //Loopar kolumner
    {
        std::vector<char> temp; //Temporär vektor att spara varje kolumn i 
        
        int rndm;
        if(i == 0 || i == columns-1)   rndm = rand() % (rows-2) + 1;  //Slumpa start/slut position
        
        for(int j = 0; j <= rows; j++) //Loopar rader
        {
            if(j == 0 || j == rows-1)    temp.push_back(WALL);    //Första och sista raden ska vara solida väggar
            
            else if(i == 0) //Om det är första kolumnen ska startpunkten skrivas
            {
                if(j == rndm)   temp.push_back(START); //Om startpunkten är nådd skriv denna
                else            temp.push_back(WALL);  //Annars skriv vägg
            }
            else if(i == columns-1)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == rndm)   temp.push_back(END);   //Om slutpunkten är nådd skriv denna
                else            temp.push_back(WALL);  //Annars skriv vägg
            }
            else    //Annars slumpas vägg eller gång, har ska DFS-metoden senare tillämpas
            {
                int rndm = rand() % 2;
                if(rndm % 2 == 0)   temp.push_back(WALL);
                else                temp.push_back(PATH);
            }
        }
        maze.push_back(temp);  //Lägg till raden 
    }
    /*
     * !!! 
     * Rader och kolumner är ihopmixade atm. Felkällan okänd.
     * !!!
     */
    std::cout << "Rows: " << maze[0].size()-1 << " Columns: " << maze.size()-1 << std::endl;
}

void Maze::printMaze()
{
    for(int i = 0; i < rows; i++)  //Skriv ut
    {
        for(int j = 0; j < columns; j++)
            std::cout << maze[j][i];
        std::cout << std::endl;
    }
}