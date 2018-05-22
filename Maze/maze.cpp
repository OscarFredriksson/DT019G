#include "maze.h"
#include <stack>
#include <cstdlib> //srand
#include <ctime>    //time
#include <chrono>
#include <thread>

void Maze::fillMaze()
{
    for(int i = 0; i < cols; i++)  //Loopar kolumner
    {
        std::vector<node> temp; //Temporär vektor att spara varje rad i 
                
        for(int j = 0; j < rows; j++) //Loopar rader
        {            
            if(i == 0) //Om det är första kolumnen ska startpunkten skrivas
            {
                if(j == 1 || j == rows-2)   temp.push_back(node(i, j)); //Om startpunkten är nådd skriv denna
                else                        temp.push_back(node(i, j, true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i == cols-1)   //Om det är sista kolumnen ska slutpunkten skrivas
            {
                if(j == rows-2) temp.push_back(node(i, j));   //Om slutpunkten är nådd skriv denna
                else            temp.push_back(node(i, j, true));  //Annars skriv vägg (vertikal vägg)
            }
            else if(i % 2 == 0 || j % 2 == 0)   temp.push_back(node(i, j, true));   //Skriv vägg
            else                                temp.push_back(node(i, j));  //Annars skriv gång
        }
        maze.push_back(temp);  //Lägg till raden
    } 
}

void Maze::generateMaze()
{
    srand(time(NULL));
    
    rows = 2*rows+1;    //Omvandla rader och kolumner till "rätt" värden
    cols = 2*cols+1;

    fillMaze(); //Fyller vektorerna med väggar

    std::stack<node> nodes;

    //Gå till första positionen i labyrinten
    maze[1][1].visited = true;      
    nodes.push(maze[1][1]);

    while(!nodes.empty())
    {
        std::vector<node> neighbours = getNeighbours(nodes.top());   //Hämta samtliga grannar till den översta noden
        
        if(neighbours.empty())  nodes.pop();    //Om den inte hittar några obesökta grannar, poppa stacken och prova igen
        else
        {
            node prev = nodes.top();  //Spara föregående nod

            nodes.push(neighbours[rand() % neighbours.size()]); //Lägg till en slumpad granne till stacken

            node P = nodes.top(); //Spara den slumpade grannen för enkelhetens skull

            maze[P.x][P.y].visited = true;   //Sätt den slumpade grannen som besökt

            //Testar samtliga kombinationer av väggar som ska tas bort
            if(P.x == prev.x && P.y > prev.y)   maze[P.x][P.y-1].wall = false;
            if(P.x == prev.x && P.y < prev.y)   maze[P.x][P.y+1].wall = false;
            if(P.y == prev.y && P.x > prev.x)   maze[P.x-1][P.y].wall = false;
            if(P.y == prev.y && P.x < prev.x)   maze[P.x+1][P.y].wall = false;
            
            system("clear");
            std::cout << *this << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));         
        }
    }
}

std::vector<Maze::node> Maze::getNeighbours(node P) //Hämtar alla obesökta grannar till en given nod
{
    std::vector <node> temp;    //Skapa en temporär vektor att spara alla hittade grannar i 
    
    //Går igenom alla grannar, är den inte besökt och inom ramarna, lägg till den i vektorn
    if(P.x > 1                  && !maze[P.x-2][P.y].visited)   temp.push_back(maze[P.x-2][P.y]);   //Kollar grannen till vänster   
    if(P.x < maze.size()-2      && !maze[P.x+2][P.y].visited)   temp.push_back(maze[P.x+2][P.y]);   //Kollar grannen till höger 
    if(P.y > 1                  && !maze[P.x][P.y-2].visited)   temp.push_back(maze[P.x][P.y-2]);   //Kollar grannen uppåt
    if(P.y < maze[0].size()-2   && !maze[P.x][P.y+2].visited)   temp.push_back(maze[P.x][P.y+2]);   //Kollar grannen nedåt
    
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Maze & maze)
{
    for(int i = 0; i < maze.maze[0].size(); i++) //Loopar rader
    {
        for(int j = 0; j < maze.maze.size(); j++)    //Loopar kolumner
        {
            if(j == 0 && i == 1)    std::cout << maze.START;
            else if(j == maze.maze.size()-1 && i == maze.maze[0].size()-2) std::cout << maze.END;
            else if(maze.maze[j][i].wall == true) 
            {
                if(j % 2 == 1)  std::cout << maze.WALL << maze.WALL << maze.WALL;
                else            std::cout << maze.WALL;
            }
            else if(j % 2 == 0) std::cout << maze.PATH;    
            else                std::cout << maze.PATH << maze.PATH << maze.PATH;
        }
        std::cout << std::endl;
    }
    return os;
}

