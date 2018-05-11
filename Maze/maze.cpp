#include "maze.h"

void Maze::generateMaze()
{
    srand(time(NULL));

    for(int i = 0; i < 2*columns+1; i++)  //Loopar kolumner
    {
        std::vector<std::string> temp; //Temporär vektor att spara varje kolumn i 
                
        for(int j = 0; j < 2*rows+1; j++) //Loopar rader
        {            
            if(i == 0) //Om det är första kolumnen ska startpunkten skrivas
            {
                if(j == 1)  temp.push_back(START); //Om startpunkten är nådd skriv denna
                else        temp.push_back(y_WALL);  //Annars skriv vägg
            }
            else if(i == 2*columns)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == 2*rows-1)   temp.push_back(END);   //Om slutpunkten är nådd skriv denna
                else                temp.push_back(y_WALL);  //Annars skriv vägg
            }
            else if(i % 2 == 0) temp.push_back(y_WALL);
            else if(j % 2 == 0) temp.push_back(x_WALL);
            else                temp.push_back(PATH); 
        }
        maze.push_back(temp);  //Lägg till raden 
    }
    
    std::cout << "Rows: " << maze[0].size() << " Columns: " << maze.size() << std::endl;
}

void Maze::printMaze()  //Skriv ut
{
    for(int i = 0; i < maze[0].size(); i++)
    {
        for(int j = 0; j < maze.size(); j++)
            std::cout << maze[j][i];
        std::cout << std::endl;
    }
}