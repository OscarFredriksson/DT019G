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
    friend std::istream& operator>>(std::istream& is, Maze & maze);
    void solveMaze();
    void resetVisitedNodes();

private:
    const char PATH = ' ';
    const char WALL = '*';
    const char SOLVED = '.';
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
            solved = src.solved;
        };
        node(int x, int y, bool wall = false)
        : x(x), y(y), wall(wall)
        {
            visited = false;
            solved = false;
        };

        int x, y;
        bool wall, visited, solved;
    };
    std::vector<std::vector<node>> maze;
    
    std::vector<node> getNeighbours(node P);

};