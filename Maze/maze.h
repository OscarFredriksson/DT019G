#include <vector>
#include <cstddef>  //size_t
#include <iostream>

class Maze
{
private:
    const char WALL = '*';
    const char PATH = ' ';
    const char START = 'S';
    const char END = 'X';

public:
    size_t columns = 11;
    size_t rows = 11;
    std::vector<std::vector<char>> maze;
    
    void generateMaze();
    void printMaze();
};