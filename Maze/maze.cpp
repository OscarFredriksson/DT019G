#include "maze.h"
#include <stack>
#include <cstdlib> //srand
#include <ctime>    //time
#include <chrono>
#include <thread>

void Maze::fillMaze()
{
    srand(time(NULL));

    for(int i = 0; i < rows; i++)  //Loopar kolumner
    {
        std::vector<node> temp; //Temporär vektor att spara varje rad i 
                
        int rndm = 2 * (rand() % rows/2) + 1;   //Slumpa ett udda tal för slutpunkten
        
        //int rndm = rows-2;

        for(int j = 0; j < cols; j++) //Loopar rader
        {            
            if(j == 0 && i == 1)                    temp.push_back(node(j, i));         //Om startpunkten är nådd skriv denna
            else if(j == cols-1 && i == rndm)       temp.push_back(node(j, i));         //Om slutpunkten är nådd skriv denna
            else if(j % 2 == 0 || i % 2 == 0)       temp.push_back(node(j, i, true));   //Om antalet rader eller kolumner är jämnt, skriv vägg
            else                                    temp.push_back(node(j, i));         //Annars skriv gång
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

            maze[P.y][P.x].visited = true;   //Sätt den slumpade grannen som besökt

            //Testar samtliga kombinationer av väggar som ska tas bort
            if(P.x == prev.x && P.y > prev.y)   maze[P.y-1][P.x].wall = false;
            if(P.x == prev.x && P.y < prev.y)   maze[P.y+1][P.x].wall = false;
            if(P.y == prev.y && P.x > prev.x)   maze[P.y][P.x-1].wall = false;
            if(P.y == prev.y && P.x < prev.x)   maze[P.y][P.x+1].wall = false;
            
            /*system("clear");
            std::cout << *this << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));*/         
        }
    }
}

//NÅTT ÄR FEL HÄR I NÅNSTANS, VET EJ VART
std::vector<Maze::node> Maze::getNeighbours(node P) //Hämtar alla obesökta grannar till en given nod
{
    std::vector <node> temp;    //Skapa en temporär vektor att spara alla hittade grannar i 
    
    //Går igenom alla grannar, är den inte besökt och inom ramarna, lägg till den i vektorn
    if(P.x > 1                  && !maze[P.y][P.x-2].visited)   temp.push_back(maze[P.y][P.x-2]);   //Kollar grannen till vänster 
    if(P.x < maze[0].size()-2   && !maze[P.y][P.x+2].visited)   temp.push_back(maze[P.y][P.x+2]);   //Kollar grannen till höger 
    if(P.y > 1                  && !maze[P.y-2][P.x].visited)   temp.push_back(maze[P.y-2][P.x]);   //Kollar grannen ovanför
    if(P.y < maze.size()-2      && !maze[P.y+2][P.x].visited)   temp.push_back(maze[P.y+2][P.x]);   //Kollar grannen under
    
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Maze & maze)
{
    for(int i = 0; i < maze.maze.size(); i++) //Loopar igenom alla rader
    {
        for(int j = 0; j < maze.maze[0].size(); j++)    //Loopar igenom alla kolumner
        {
            //if(j == 0 && !maze.maze[j][i].wall)                         std::cout << maze.START;
            //else if(j == maze.maze.size()-1 && !maze.maze[j][i].wall)   std::cout << maze.END;
            if(maze.maze[i][j].solved)  
            {
                if(j % 2 == 1) os << maze.PATH << maze.SOLVED << maze.PATH;
                else           os << maze.SOLVED;
            }
            else if(maze.maze[i][j].wall == true) 
            {
                if(j % 2 == 1)  os << maze.WALL << maze.WALL << maze.WALL;
                else            os << maze.WALL;
            }
            else if(j % 2 == 0) os << maze.PATH;    
            else                os << maze.PATH << maze.PATH << maze.PATH;
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Maze & maze)
{
    std::string temp_row;
    for(int i = 0; std::getline(is, temp_row); i++)    //Rader
    {
        if(temp_row != "")
        {
            std::vector<Maze::node> row;
            for(int j = 0, y = 0; j < temp_row.size(); j++, y++) //Kolumner, behövs två iteratorer här, en för att hålla koll i temp_row och en för den faktiska koordinaten
            {
                if      (temp_row[j] == '*') row.push_back(Maze::node(i, y, true));
                else if (temp_row[j] == ' ') row.push_back(Maze::node(i, y));             

                if(j % 2 == 1) j+=2;    //Om det är en udda kolumn finns det tre st tecken för denna, skippa till nästa kolumn   
            }
            maze.maze.push_back(row);
        }
    }
    return is;
}

void Maze::resetVisitedNodes()
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(maze[i][j].visited == true)
                maze[i][j].visited = true;
}

void Maze::solveMaze()
{
    srand(time(NULL));


    std::stack<node> nodes;
    
    maze[1][1].visited = true;
    maze[1][1].solved = true;

    nodes.push(maze[1][1]);
    
    //while(nodes.top().x != maze[0].size()-2)
    while(true)
    {
        std::cout << nodes.top().x << nodes.top().y << std::endl << std::endl;

        std::vector<node> neighbours = getNeighbours(nodes.top());   //Hämta samtliga grannar till den översta noden
        
        for(int i = 0; i < neighbours.size(); i++)
            std::cout << neighbours[i].x << neighbours[i].y << std::endl;
        
        //if(neighbours.empty())  nodes.pop();    //Om den inte hittar några obesökta grannar, poppa stacken och prova igen
        //else
        //{
            nodes.push(neighbours[rand() % neighbours.size()]); //Lägg till en slumpad granne till stacken

            std::cout << std::endl << nodes.top().x << nodes.top().y << std::endl;

            node P = nodes.top(); //Spara den slumpade grannen för enkelhetens skull

            //std::cout << P.x << P.y << std::endl;

            maze[P.y][P.x].visited = true;   //Sätt den slumpade grannen som besökt
            maze[P.y][P.x].solved = true;
          
            //system("clear");
            std::cout << *this << std::endl;
            std::cin.get();
            //std::this_thread::sleep_for(std::chrono::milliseconds(50));        
        //}
    }
}