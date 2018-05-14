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
                if(j == 1)  temp.push_back(node(i, j, false)); //Om startpunkten är nådd skriv denna
                else        temp.push_back(node(i, j, true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i == 2*columns)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == 2*rows-1)   temp.push_back(node(i, j, false));   //Om slutpunkten är nådd skriv denna
                else                temp.push_back(node(i, j, true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i % 2 == 0 || j % 2 == 0) 
                temp.push_back(node(i, j, true)); 
            else                
                temp.push_back(node(i, j, false)); 
        }
        maze.push_back(temp);  //Lägg till raden 
    } 
}

void Maze::generateMaze()
{
    srand(time(NULL));
    fillMaze();

    std::stack<node> nodes;

    maze[1][1].visited = true;
    nodes.push(maze[1][1]);

    for(int i = 1, j = 1; i < 2 && j < 2;)
    {
        node prev = nodes.top();
        if(rand() % 2 == 0) 
        {
            nodes.push(maze[i+2][j]);
            nodes.push(maze[i][j+2]);
        }
        else                
        {
            nodes.push(maze[i][j+2]);
            nodes.push(maze[i+2][j]);
        }
        
        node P = nodes.top();
        
        P.visited = true;
        
        if(P.x == prev.x) 
            maze[prev.x][prev.y+1].wall = false;
        else
            maze[prev.x+1][prev.y].wall = false;
        
        i = P.x;
        j = P.y;

    }

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