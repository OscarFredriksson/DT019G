#include <vector>
#include <cstddef>  //size_t
#include <iostream>


class Maze
{
    public:
    size_t cols = 10;
    size_t rows = 10;
    
    void fillMaze();
    void generateMaze();
    friend std::ostream& operator<<(std::ostream& os, const Maze & maze);
    void loadMaze();

private:
    const char PATH = ' ';
    const char WALL = '*';
    const char START = 'S';
    const char END = 'X';
    
    struct node 
    {
        node(const node & src)
        {
            x = src.x;
            y = src.y;
            wall = src.wall;
            visited = src.visited;
        };
        node(int x, int y, bool wall = false)
        : x(x), y(y), wall(wall)
        {
            visited = false;
        };

        int x, y;
        bool wall, visited;
    };
    std::vector<std::vector<node>> maze;
    
    std::vector<node> getNeighbours(node P);


};