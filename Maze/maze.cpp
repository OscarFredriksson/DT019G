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

    std::stack<node*> nodes;

    maze[1][1].visited = true;
    node * temp = &maze[1][1];
    //node * temp = new node(maze[1][1]);
    nodes.push(temp);

    
    for(int i = 1, j = 1, k = 0; !nodes.empty();k++)
    {
        std::vector<Maze::node*> neighbours = getNeighbours(&maze[i][j]);
        
        if(neighbours.empty())  nodes.pop();    //Om den inte hittar några obesökta grannar, poppa stacken och prova igen
        else
        {
            node * prev = nodes.top();  //Spara föregående nod

            nodes.push(neighbours[rand() % neighbours.size()]); //Lägg till en slumpad granne till stacken

            node * P = nodes.top(); //Spara den slumpade grannen för enkelhetens skull

            P->visited = true;  //Sätt den som besökt

            //Testar samtliga kombinationer av väggar som ska tas bort
            if(P->x == prev->x && P->y > prev->y)   maze[P->x][P->y-1].wall = false;
        
            if(P->x == prev->x && P->y < prev->y)   maze[P->x][P->y+1].wall = false;

            if(P->y == prev->y && P->x > prev->x)   maze[P->x-1][P->y].wall = false;
            
            if(P->y == prev->y && P->x < prev->x)   maze[P->x+1][P->y].wall = false;
                   
        }
        if(!nodes.empty())
        {
            i = nodes.top()->x;
            j = nodes.top()->y;
        }
        system("clear");
        //std::cout << *this << std::endl;
        //usleep(50000);

    }
    std::cout << *this << std::endl;
}

std::vector<Maze::node*> Maze::getNeighbours(node * P)
{
    std::vector <node*> temp;
    if(P->x > 1                  && !maze[P->x-2][P->y].visited)   temp.push_back(&maze[P->x-2][P->y]);    
    if(P->x < maze.size()-2      && !maze[P->x+2][P->y].visited)   temp.push_back(&maze[P->x+2][P->y]);
    if(P->y > 1                  && !maze[P->x][P->y-2].visited)   temp.push_back(&maze[P->x][P->y-2]);
    if(P->y < maze[0].size()-2   && !maze[P->x][P->y+2].visited)   temp.push_back(&maze[P->x][P->y+2]);
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

/*void Maze::printMaze()  //Skriv ut
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

    for(int i = 0; i < maze[0].size(); i++) //Loopar rader
    {
        for(int j = 0; j < maze.size(); j++)    //Loopar kolumner
        {
            std::cout << maze[j][i].visited;
        }
        std::cout << std::endl;
    }
}*/
