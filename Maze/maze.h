#include <vector>
#include <cstddef>  //size_t
#include <iostream>
#include <cstdlib> //srand
#include <ctime>

class Maze
{
    public:
    size_t columns = 99;
    size_t rows = 99;
    
    void fillMaze();
    void generateMaze();
    void printMaze();

private:
    const char PATH = ' ';
    const char WALL = '*';
    const char START = 'S';
    const char END = 'X';
    
    struct node 
    {
        node(int x, int y, bool wall, bool visited = false)
        : x(x), y(y), wall(wall), visited(visited) 
        {
            if(wall)    visited = true;
        };

        int x, y;
        bool wall, visited;
    };

    std::vector<std::vector<node>> maze;
};