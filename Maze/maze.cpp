#include "maze.h"
#include <stack>

void Maze::fillMaze()
{
    for(int i = 0; i < 2*columns+1; i++)  //Loopar kolumner
    {
        std::vector<node> temp; //Temporär vektor att spara varje rad i 
                
        for(int j = 0; j < 2*rows+1; j++) //Loopar rader
        {            
            if(i == 0) //Om det är första kolumnen ska startpunkten skrivas
            {
                if(j == 1)  temp.push_back(node(false)); //Om startpunkten är nådd skriv denna
                else        temp.push_back(node(true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i == 2*columns)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == 2*rows-1)   temp.push_back(node(false));   //Om slutpunkten är nådd skriv denna
                else                temp.push_back(node(true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i % 2 == 0) temp.push_back(node(true)); //Vertikal vägg
            else if(j % 2 == 0) temp.push_back(node(true)); //Horisontell vägg
            else                temp.push_back(node(false)); 
        }
        maze.push_back(temp);  //Lägg till raden 
    } 
}

void Maze::generateMaze()
{
    srand(time(NULL));
    
    fillMaze();
}

void Maze::printMaze()  //Skriv ut
{
    for(int i = 0; i < maze[0].size(); i++) //Loopar rader
    {
        for(int j = 0; j < maze.size(); j++)    //Loopar kolumner
        {
            if(j == 0 && i == 1)    std::cout << START;
            else if(j == maze.size()-1 && i == maze[0].size()-2) std::cout << END;
            else if(maze[j][i].wall == true) 
            {
                if(j % 2 == 1)  std::cout << WALL << WALL << WALL;
                else            std::cout << WALL;
            }
            else    std::cout << PATH << PATH << PATH;
        }
        std::cout << std::endl;
    }
}