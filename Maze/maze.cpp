#include "maze.h"
#include <stack>

void Maze::fillMaze()
{
    /*for(int i = 0; i < 2*columns+1; i++)  //Loopar kolumner
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

    for(int i = 0; i < columns; i++)    //Fyller path-vektorn med false
    {
        std::vector<bool> temp;
        for(int j = 0; j < rows; j++)
            temp.push_back(false);
        path.push_back(temp);
    }*/

    for(int i = 0; i < columns; i++)
    {
        std::vector<node> temp_vec;
        for(int j = 0; j < rows; j++)
        {
            node temp(i, j);
            temp_vec.push_back(temp);
        }
        maze.push_back(temp_vec);
    }
}

void Maze::generateMaze()
{
    srand(time(NULL));
    fillMaze();
    
    std::stack<node> stk;

    node temp(0, 0, true);
    stk.push(temp);

    if(rand() % 2 == 0)
    {
        temp.x++;
        temp.leftWall = false;
        stk.push(temp);
    }
    else
    {
        temp.y++;
        temp.upWall = false;
    }

}

void Maze::printMaze()  //Skriv ut
{
    /*for(int i = 0; i < maze[0].size(); i++)
    {
        for(int j = 0; j < maze.size(); j++)
        {
            std::cout << maze[j][i];
        }
        std::cout << std::endl;
    }*/
    for(int i = 0; i < 2*maze[0].size()+1; i++)
    {
        for(int j = 0; j < 2*maze.size()+1; j++)
        {
            if(i == 0)   std::cout << WALL;
            
            else if(i == 2*maze[0].size())      std::cout << WALL;
            
            else if(j == 0)                     std::cout << WALL;
            
            else if(j == 2*maze.size())       std::cout << WALL;

            else std::cout << PATH;
            
        }
        std::cout << std::endl;
    }
}