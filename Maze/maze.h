#include <vector>
#include <cstddef>  //size_t
#include <iostream>

class Maze
{
public:
    size_t cols = 10;
    size_t rows = 10;

    bool showIterations = false;    //Om varje iteration vid generering och lösning ska visas för användaren

    void generate();    //Skapar labyrinten
    bool solve();   //Löser labyrinten

    friend std::ostream& operator<<(std::ostream& os, const Maze & maze);   //För inläsning av en labyrint
    friend std::istream& operator>>(std::istream& is, Maze & maze); //För utskrift av en labyrint
    

private:
    const char PATH = ' ';
    const char WALL = '*';
    const char SOLVED = '.';
    
    const int iterationSpeed = 50;  //Hur snabbt programmet ska iterera lösning och generering när den visar varje iteration för användaren. Värdet 50 ger en iteration var 50e millisekund

    struct node //En nod motsvarar en "koordinat" i labyrinten, alltså en gång eller vägg
    {
        node(const node & src)  //Kopierings konstruktor
        {
            x = src.x;
            y = src.y;
            wall = src.wall;
            visited = src.visited;
            solved = src.solved;
        };
        
        /* Denna konstruktor används när en ny nod ska läggas till vid generering
         * Konstruktorn tar in x och y koordinat samt valfritt att sätta att noden motsvarar en vägg, annars är den gång
         */
        node(int x, int y, bool wall = false)    
        : x(x), y(y), wall(wall)
        {
            //Sätter defaultvärde att noden inte är besökt och inte löst
            visited = false;    
            solved = false;
        };
        int x, y;
        bool wall, visited, solved;
    };
    
    std::vector<std::vector<node>> maze;
    
    void fill();    //Fyller labyrinten med väggar och gångar i ett rutmönster
    std::vector<node> getNeighbours(node P);    //Hämtar samtliga grannar till en given nod
    
    void resetNodes();  //Återställer alla besökta och lösta noder
    std::vector<node> validateNeighbours(std::vector<node> nodes, node current);    //Kollar vilka grannar i vektorn som inte är bakom en vägg
    void fixPath(node P, node prev, bool state);    //Plockar bort/sätter dit löst gång mellan två noder, ger snyggare utskrift


};