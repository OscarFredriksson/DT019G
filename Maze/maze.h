#include <vector>
#include <cstddef>  //size_t

struct Maze
{
    size_t size = 100;
    const char WALL = '*';
    const char PATH = ' ';
    std::vector<std::vector<char>> maze;
};