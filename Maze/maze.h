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
        node(bool wall, bool visited = false)
        : wall(wall), visited(visited) {};

        bool wall;
        bool visited;
    };

    std::vector<std::vector<node>> maze;
};