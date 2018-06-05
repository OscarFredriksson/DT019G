#include "maze.h"
#include <stack>
#include <cstdlib> //srand, atoi
#include <chrono>
#include <thread>

void Maze::generate()
{    
    rows = 2*rows+1;    //Omvandla rader och kolumner till "rätt" värden
    cols = 2*cols+1;

    fill(); //Fyller vektorerna med väggar

    std::stack<node> path;

    //Gå till första positionen i labyrinten
    maze[1][1].visited = true;      
    path.push(maze[1][1]);

    while(!path.empty())
    {
        std::vector<node> neighbours = getNeighbours(path.top());   //Hämta samtliga grannar till den översta noden
        
        if(neighbours.empty())  path.pop();    //Om den inte hittar några obesökta grannar, poppa stacken och prova igen
        else
        {
            node prev = path.top();  //Spara föregående nod

            path.push(neighbours[rand() % neighbours.size()]); //Lägg till en slumpad granne till stacken

            node P = path.top(); //Spara den slumpade grannen för enkelhetens skull

            maze[P.y][P.x].visited = true;   //Sätt den slumpade grannen som besökt

            //Testar samtliga kombinationer av väggar som ska tas bort
            if(P.x == prev.x && P.y > prev.y)   maze[P.y-1][P.x].wall = false;
            if(P.x == prev.x && P.y < prev.y)   maze[P.y+1][P.x].wall = false;
            if(P.y == prev.y && P.x > prev.x)   maze[P.y][P.x-1].wall = false;
            if(P.y == prev.y && P.x < prev.x)   maze[P.y][P.x+1].wall = false;
            
            if(showIterations)  //Om användaren vill se på medan labyrinten skapas
            {
                std::cout << *this << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
                system("clear");
            }
        }
    }
}

void Maze::fill()   //Fyller labyrinten med väggar och gångar i ett rutmönster
{
    int rndm = (rand() % (rows - 1)) | 0x1;   //Slumpa ett udda tal för slutpunkten, får ett udda tal genom att ta bitvis or med talet 00000001

    for(int i = 0; i < rows; i++)  //Loopar rader
    {
        std::vector<node> row; //Temporär vektor att spara varje rad i 
                        
        for(int j = 0; j < cols; j++) //Loopar kolumner
        {            
            if(j == 0 && i == 1)                row.push_back(node(j, i));         //Om startpunkten är nådd skriv denna
            else if(j == cols-1 && i == rndm)   row.push_back(node(j, i));         //Om slutpunkten är nådd skriv denna
            else if(j % 2 == 0 || i % 2 == 0)   row.push_back(node(j, i, true));   //Om antalet rader eller kolumner är jämnt, skriv vägg
            else                                row.push_back(node(j, i));         //Annars skriv gång
        }
        maze.push_back(row);  //Lägg till raden
    }
}

std::vector<Maze::node> Maze::getNeighbours(node P) //Hämtar alla obesökta grannar till en given nod
{
    std::vector <node> temp;    //Skapa en temporär vektor att spara alla hittade grannar i 
    
    //Går igenom alla grannar, är den inte besökt och inom ramarna, lägg till den i vektorn
    if(P.x > 1      && !maze[P.y][P.x-2].visited)   temp.push_back(maze[P.y][P.x-2]);   //Kollar grannen till vänster 
    if(P.x < cols-2 && !maze[P.y][P.x+2].visited)   temp.push_back(maze[P.y][P.x+2]);   //Kollar grannen till höger 
    if(P.y > 1      && !maze[P.y-2][P.x].visited)   temp.push_back(maze[P.y-2][P.x]);   //Kollar grannen ovanför
    if(P.y < rows-2 && !maze[P.y+2][P.x].visited)   temp.push_back(maze[P.y+2][P.x]);   //Kollar grannen under

    return temp;
}

std::ostream& operator<<(std::ostream& os, const Maze & maze)   //Skriver ut en labyrint
{
    for(int i = 0; i < maze.rows; i++) //Loopar igenom alla rader
    {
        for(int j = 0; j < maze.cols; j++)    //Loopar igenom alla kolumner
        {
            if(maze.maze[i][j].solved)  //Om positionen är löst gång
            {
                if(j % 2 == 1)  //Om det är en udda antal kolumn ska det skrivas ut tre tecken för en nod
                { 
                    //Testa samtliga kombinationer av löst gång
                    if(maze.maze[i][j-1].solved && !maze.maze[i][j+1].solved)   //Om den kommer från vänster och ska gå upp eller ner
                        os << maze.SOLVED << maze.SOLVED << maze.PATH;
                    
                    else if(maze.maze[i][j+1].solved && !maze.maze[i][j-1].solved)  //Om den kommer från höger och ska gå upp eller ner
                        os << maze.PATH << maze.SOLVED << maze.SOLVED;
                    
                    else if(maze.maze[i][j-1].solved && maze.maze[i][j+1].solved)  //Om den går rakt i x-led
                        os << maze.SOLVED << maze.SOLVED << maze.SOLVED;
                    
                    else                                                            
                        os << maze.PATH << maze.SOLVED << maze.PATH; //Om den går rakt i y-led
                }
                else    os << maze.SOLVED;  //Annars ska det bara skrivas ett tecken
            }
            else if(maze.maze[i][j].wall)   //Om positionen är vägg
            {
                if(j % 2 == 1)  os << maze.WALL << maze.WALL << maze.WALL;  //Om det är en udda kolumn ska det skrivas tre tecken för en nod
                else            os << maze.WALL;    //Annars ska det bara skrivas ett tecken
            }
            else if(j % 2 == 1) os << maze.PATH << maze.PATH << maze.PATH;  //Om det är en udda kolumn ska det skrivas tre tecken för en nod  
            else                os << maze.PATH;    //Annars ska det bara skrivas ett tecken
        }
        os << std::endl;    //Skriv radbrytning efter varje rad
    }
    return os;
}

std::istream& operator>>(std::istream& is, Maze & maze) //Läser in en labyrint
{
    while(!maze.maze.empty()) maze.maze.pop_back();   //Töm vektorn om det finns nått i den.

    std::string temp_row;   //Skapar en temporär variabel att läsa in en rad i
    std::string prev_row;   //Den föregående inlästa raden
    
    for(int i = 0; std::getline(is, temp_row); i++)    //Läser en hel rad ur den givna strömmen
    {        
        if(temp_row != "")  //Om raden inte är en tom radbrytning
        {
            if(i && temp_row.size() != prev_row.size()) //Kollar varje varv så att den tidigare raden är lika stor som den föregående, samtliga rader måste vara lika stora
                throw "En eller flera rader i filen är i felaktigt format.";    //Kasta ett undantag om de inte är lika
 
            std::vector<Maze::node> row;    //Skapar en temporär vektor för varje rad

            /* Loopar igenom alla kolumner i den temporära variabeln 
             * behövs två iteratorer här, en för att hålla koll i temp_row och en för den faktiska koordinaten
             */        
            for(int j = 0, x = 0; j < temp_row.size(); j++, x++)
            {
                if(temp_row[j] == maze.WALL)  //Om tecknet är vägg
                    row.push_back(Maze::node(x, i, true));  //Lägg till en vägg i raden
                
                else if(temp_row[j] == maze.PATH || temp_row[j] == maze.SOLVED) //Om tecknet är gång eller löst gång
                    row.push_back(Maze::node(x, i));    //Lägg till en gång i raden
                
                else    
                    throw "Hittade ett okänt tecken i filen."; //Om den hittar något annat tecken, kasta ett undantag

                if(j % 2 == 1) j+=2;    //Om det är en udda kolumn finns det tre st tecken för denna, skippa till nästa kolumn   
            }
            maze.maze.push_back(row);   //Lägg till raden
        }
        prev_row = temp_row;    //Spara den nuvarande raden för att kunna jämföra den med nästa
    }

    maze.cols = maze.maze[0].size();    //Spara antal kolumner i labyrinten
    maze.rows = maze.maze.size();       //Spara antal rader i labyrinten

    if(maze.cols % 2 == 0)  throw "Labyrinten måste ha udda antal kolumner.";   //Om den läst in ett jämnt antal kolumner har nått gått fel, kasta ett undantag
    if(maze.rows % 2 == 0)  throw "Labyrinten måste ha udda antal rader.";      //Samma med rader

    return is;
}

bool Maze::solve()
{
    if(maze[1][1].visited) resetNodes(); //Kollar om noderna redan är använda, återställer dem isåfall.

    std::stack<node> path; //Stack med den lösta gången, kommer när körningen är klar motsvara vägen igenom labyrinten
    
    //Gå till första positionen
    maze[1][0].solved = true;
    maze[1][1].visited = true;
    maze[1][1].solved = true;
    path.push(maze[1][1]);
    
    while(path.top().x != cols-1)  //Sålänge den inte har tagit sig igenom väggen till höger
    {
        node P = path.top();   //Spara den översta noden

        if(P.x == cols-2 && !maze[P.y][P.x+1].wall) //Om den är på den sista kolumnen, kolla om den kan hitta utgången
        {
            //Gå isåfall ut ur labyrinten
            maze[P.y][P.x+1].solved = true;
            path.push(maze[P.y][P.x+1]);
        }
        else
        {
            std::vector<node> neighbours = validateNeighbours(getNeighbours(P), P);   //Hämta samtliga grannar till den översta noden
            
            node prev = path.top();    //Spara föregående nod

            if(neighbours.empty())  //Om den inte hittar någonstans att gå
            {
                //Plocka bort löst gång och backa i stacken
                maze[prev.y][prev.x].solved = false;
                path.pop();

                if(path.empty())   return false;   //Om den har tömt hela stacken har den inte hittat någon lösning, returnera detta
                
                fixPath(path.top(), prev, false);  //Plocka bort den lösta gången mellan föregående och nuvarande position
            }
            else
            {                
                path.push(neighbours[rand() % neighbours.size()]); //Lägg till en slumpad granne till stacken
                
                P = path.top(); //Spara den slumpade grannen för enkelhetens skull

                maze[P.y][P.x].visited = true;   //Sätt den slumpade grannen som besökt
                maze[P.y][P.x].solved = true;   //Sätt den slumpade grannen som löst

                fixPath(P, prev, true); //Sätt dit löst gång mellan föregående och nuvarande position

            }
        }
        if(showIterations)  //Om användaren vill se på medan labyrinten skapas
        {
            std::cout << *this << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            system("clear");
        }

    }
    return true;
}

void Maze::resetNodes()  //Återställer alla besökta och lösta noder
{
    //Loopar igenom hela labyrinten
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            if(maze[i][j].visited)  maze[i][j].visited = false; //Om en nod är besökt, återställ detta
            if(maze[i][j].solved)    maze[i][j].solved = false; //Om en nod är löst, återställ detta
        }
}

std::vector<Maze::node> Maze::validateNeighbours(std::vector<node> path, node current) //Kollar vilka grannar som inte är bakom en vägg
{
    std::vector<node> temp;
    for(int i = 0; i < path.size(); i++)
    {
        if(current.y > path[i].y && !maze[current.y-1][current.x].wall)    temp.push_back(path[i]);   //Kollar grannen ovanför
        if(current.y < path[i].y && !maze[current.y+1][current.x].wall)    temp.push_back(path[i]);   //Kollar grannen under
        if(current.x > path[i].x && !maze[current.y][current.x-1].wall)    temp.push_back(path[i]);   //Kollar grannen till vänster
        if(current.x < path[i].x && !maze[current.y][current.x+1].wall)    temp.push_back(path[i]);   //Kollar grannen till höger
    }
    return temp;
}

void Maze::fixPath(node P, node prev, bool state)   //Plockar bort/sätter dit löst gång mellan två noder, ger snyggare utskrift
{
    //Kollar samtliga riktningar
    if      (P.x == prev.x && P.y > prev.y)   maze[P.y-1][P.x].solved = state;  
    else if (P.x == prev.x && P.y < prev.y)   maze[P.y+1][P.x].solved = state;
    else if (P.y == prev.y && P.x > prev.x)   maze[P.y][P.x-1].solved = state;
    else if (P.y == prev.y && P.x < prev.x)   maze[P.y][P.x+1].solved = state;
}
