#include <vector>
#include <cstddef>  //size_t
#include <iostream>
#include <cstdlib> //srand
#include <ctime>

class Maze
{
private:
    const std::string y_WALL = "*";
    const std::string x_WALL = "***";
    const std::string PATH = "   ";
    const std::string START = "S";
    const std::string END = "X";
    std::vector<std::vector<std::string>> maze;
    std::vector<std::vector<bool>> path;

public:
    size_t columns = 99;
    size_t rows = 99;
    
    void generateMaze();
    void printMaze();

    /*struct node 
    {
        node * left = nullptr;
        node * right = nullptr;
        node * up = nullptr;
        node * down = nullptr;
    };*/
};