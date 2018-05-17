#include <vector>
#include <cstddef>  //size_t
#include <iostream>


class Maze
{
    public:
    size_t columns = 99;
    size_t rows = 99;
    
    void fillMaze();
    void generateMaze();
    friend std::ostream& operator<<(std::ostream& os, const Maze & maze);

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
            //if(wall)    visited = true;
            //else        visited = false;
            visited = false;
        };

        int x, y;
        bool wall, visited;
    };
    std::vector<std::vector<node>> maze;
    
    std::vector<node> getNeighbours(node P);


};