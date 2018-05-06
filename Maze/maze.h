#include <vector>
#include <cstddef>  //size_t

struct Maze
{
    size_t columns = 100;
    size_t rows = 100;
    const char WALL = '*';
    const char PATH = ' ';
    const char START = 'S';
    const char END = 'X';
    std::vector<std::vector<char>> maze;
};