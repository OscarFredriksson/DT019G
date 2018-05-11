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
    /*const std::string y_WALL = "*";
    const std::string x_WALL = "***";
    const std::string PATH = "   ";*/
    const char PATH = ' ';
    const char WALL = '*';
    const char START = 'S';
    const char END = 'X';
    
    /*std::vector<std::vector<std::string>> maze;
    std::vector<std::vector<bool>> path;*/
    struct node 
    {
        node(int x, int y, bool visited = false)
        : x(x), y(y), visited(visited) {};

        int x, y;
        bool visited;

        bool leftWall, rightWall, upWall, downWall = false;
    };

    std::vector<std::vector<node>> maze;
};