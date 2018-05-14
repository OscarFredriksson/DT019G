#include "maze.h"
#include <stack>
#include <unistd.h>

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
    
    fillMaze(); //Fyller vektorerna med väggar

    std::stack<node> nodes;

    maze[1][1].visited = true;
    nodes.push(maze[1][1]);

    for(int i = 1, j = 1, k = 0; k < 10000;k++)
    {
        node prev = nodes.top();

        std::vector<node> neighbours = getNeighbours(maze[i][j]);
        
        if(neighbours.empty()) 
        {
            while(nodes.top().visited)  
            {
                //std::cout << "Grannar!" << std::endl;
                prev = nodes.top();
                nodes.pop();
                //std::cout << "storlek: " << nodes.size() << std::endl;
            }
        }
        while(!neighbours.empty())
        {
            int rndm = rand() % neighbours.size();
            nodes.push(neighbours[rndm]);
            neighbours.erase(neighbours.begin() + rndm);
        }
        
        node P = nodes.top();
        if(!P.visited)
        {
            nodes.top().visited = true;
            maze[P.x][P.y].visited = true;

            //std::cout << prev.x << prev.y << prev.visited << std::endl;
            //std::cout << P.x << P.y << P.visited << std::endl;

            //Testar samtliga kombinationer av väggar som ska tas bort
            if(P.x == prev.x && P.y > prev.y)   maze[P.x][P.y-1].wall = false;
            if(P.x == prev.x && P.y < prev.y)   maze[P.x][P.y+1].wall = false;
            if(P.y == prev.y && P.x > prev.x)   maze[P.x-1][P.y].wall = false;
            if(P.y == prev.y && P.x < prev.x)   maze[P.x+1][P.y].wall = false;
            
            i = P.x;
            j = P.y;
        }
        //std::cout << nodes.top().x << nodes.top().y << nodes.top().visited << std::endl;
        std::cin.get();
        system("clear");
        std::cout << "Varv " << k << ":" << std::endl; 
        printMaze();
        //std::cout << nodes.size() << std::endl;
    }

}

std::vector<Maze::node> Maze::getNeighbours(node P)
{
    std::vector <node> temp;
    if(P.x > 1                  && !maze[P.x-2][P.y].visited)   temp.push_back(maze[P.x-2][P.y]);    
    if(P.x < maze.size()-2      && !maze[P.x+2][P.y].visited)   temp.push_back(maze[P.x+2][P.y]);
    if(P.y > 1                  && !maze[P.x][P.y-2].visited)   temp.push_back(maze[P.x][P.y-2]);
    if(P.y < maze[0].size()-2   && !maze[P.x][P.y+2].visited)   temp.push_back(maze[P.x][P.y+2]);
    return temp;
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
            else if(j % 2 == 0) std::cout << PATH;    
            else                std::cout << PATH << PATH << PATH;
        }
        std::cout << std::endl;
    }
}