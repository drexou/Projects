#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//tells the program the game mode
enum class gameState
{
    manual,
    thruFile
};

//for manual input, tells the program if the game is still ongoing
enum class condition
{
    cont,
    stopped
};

//map object that contains the board itself, dimensions, as well as the location of the player
class Map
{
public:
    Map(const vector<string> n, int a, int b)
    {
        board = n;
        height = a;
        width = b;
    }

    vector<string> board;
    int height;
    int width;
    int xCoor;
    int yCoor;
    gameState currGameState = gameState::thruFile;
    condition currCondition = condition::cont;
};

//prints board upon function call by iterating through each element while printing the walls on the sides
void printBoard(const Map myMap)
{
    for (int i = 0; i < myMap.width+2; i++) //for loop prints the top border
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < myMap.height; i++) //for loop prints the walls plus the board
    {
        cout << "|" << myMap.board[i] << "|" << endl;
    }

    for (int i = 0; i < myMap.width+2; i++) // for loop prints the bottom border
    {
        cout << "-";
    }
    cout << endl;
}

//following four functions takes the map as an argument and determines if the player can move in the desired direction
Map moveLeft(Map myMap)
{
    if (myMap.xCoor == 0) //test if it's hitting the edge
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else if (myMap.board[myMap.yCoor].at(myMap.xCoor - 1) == '#') //test if it's hitting the wall
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else
    {
        if (myMap.board[myMap.yCoor].at(myMap.xCoor - 1) == '$')
        {
            myMap.currCondition = condition::stopped;
        }
        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
        myMap.board[myMap.yCoor].at(myMap.xCoor - 1) = '@';
        myMap.xCoor -= 1;
    }
    return myMap;
}

Map moveRight(Map myMap)
{
    if (myMap.xCoor == myMap.width-1)
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else if (myMap.board[myMap.yCoor].at(myMap.xCoor + 1) == '#')
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else
    {
        if (myMap.board[myMap.yCoor].at(myMap.xCoor + 1) == '$')
        {
            myMap.currCondition = condition::stopped;
        }
        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
        myMap.board[myMap.yCoor].at(myMap.xCoor + 1) = '@';
        myMap.xCoor += 1;
    }
    return myMap;
}

Map moveUp(Map myMap)
{
    if (myMap.yCoor == 0)
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else if (myMap.board[myMap.yCoor - 1].at(myMap.xCoor) == '#')
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else
    {
        if (myMap.board[myMap.yCoor - 1].at(myMap.xCoor) == '$')
        {
            myMap.currCondition = condition::stopped;
        }
        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
        myMap.board[myMap.yCoor - 1].at(myMap.xCoor) = '@';
        myMap.yCoor -= 1;
    }
    return myMap;
}

Map moveDown(Map myMap)
{
    if (myMap.yCoor == myMap.height-1)
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else if (myMap.board[myMap.yCoor + 1].at(myMap.xCoor) == '#')
    {
        cout << "You can't move there." << endl;
        return myMap;
    }
    else
    {
        if (myMap.board[myMap.yCoor + 1].at(myMap.xCoor) == '$')
        {
            myMap.currCondition = condition::stopped;
        }
        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
        myMap.board[myMap.yCoor + 1].at(myMap.xCoor) = '@';
        myMap.yCoor += 1;
    }
    return myMap;
}

/*
takes the initialized board and starts up the game.
iterate through user input to determine whether the action will hit a wall, advance, or win the game
*/
int gameStartUserInput(Map myMap)
{
    while(myMap.currCondition == condition::cont)
    {
        printBoard(myMap);
        char input;
        cout << "> ";
        cin >> input;
        switch(input)
        {
            case 'a':
                myMap = moveLeft(myMap);
                break;
            case 'w':
                myMap = moveUp(myMap);
                break;
            case 'd':
                myMap = moveRight(myMap);
                break;
            case 's':
                myMap = moveDown(myMap);
                break;
            case 'q':
                cout << "You quit the game." << endl;
                return 1;
            default :
                cout << "Invalid input." << endl;
        }
    }
    printBoard(myMap);
    cout << "You won the game." << endl;
    return 0;
}

/*
takes the map and the inputs to determine if the inputs result in a victory or not
*/
int gameStartFileInput(Map myMap, vector<string> instr, int instrLen)
{
    for (int i=0; i<instrLen; i++)
    {
        char input = instr[i][0];
        switch(input)
        {
            case 'a':
                if (myMap.xCoor == 0) //test if it's hitting the edge
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else if (myMap.board[myMap.yCoor].at(myMap.xCoor - 1) == '#') //test if it's hitting the wall
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else
                    {
                        if (myMap.board[myMap.yCoor].at(myMap.xCoor - 1) == '$')
                        {
                            cout << "That input results in a victory." << endl;
                            return 0;
                        }
                        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
                        myMap.board[myMap.yCoor].at(myMap.xCoor - 1) = '@';
                        myMap.xCoor -= 1;
                    }           
                break;
            case 'w':
                if (myMap.yCoor == 0) //test if it's hitting the edge
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else if (myMap.board[myMap.yCoor - 1].at(myMap.xCoor) == '#') //test if it's hitting the wall
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else
                    {
                        if (myMap.board[myMap.yCoor - 1].at(myMap.xCoor) == '$')
                        {
                            cout << "That input results in a victory." << endl;
                            return 0;
                        }
                        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
                        myMap.board[myMap.yCoor - 1].at(myMap.xCoor) = '@';
                        myMap.yCoor -= 1;
                    }
                break;
            case 'd':
                if (myMap.xCoor == myMap.width-1) //test if it's hitting the edge
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else if (myMap.board[myMap.yCoor].at(myMap.xCoor + 1) == '#') //test if it's hitting the wall
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else
                    {
                        if (myMap.board[myMap.yCoor].at(myMap.xCoor + 1) == '$')
                        {
                            cout << "That input results in a victory." << endl;
                            return 0;
                        }
                        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
                        myMap.board[myMap.yCoor].at(myMap.xCoor + 1) = '@';
                        myMap.xCoor += 1;
                    }
                break;
            case 's':
                if (myMap.yCoor == myMap.height - 1) //test if it's hitting the edge
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else if (myMap.board[myMap.yCoor + 1].at(myMap.xCoor) == '#') //test if it's hitting the wall
                    {
                        cout << "Hit wall." << endl;
                        return 0;
                    }
                else
                    {
                    if (myMap.board[myMap.yCoor + 1].at(myMap.xCoor) == '$')
                        {
                            cout << "That input results in a victory." << endl;
                            return 0;
                        }
                        myMap.board[myMap.yCoor].at(myMap.xCoor) = '.';
                        myMap.board[myMap.yCoor + 1].at(myMap.xCoor) = '@';
                        myMap.yCoor += 1;
                    }
                break;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc == 1 || argc > 3)
    {
        cerr << "Wrong number of arguments.\n";
        return 1;
    }
    ifstream mapFile; //reads file
    mapFile.open(argv[1]);
    string str;

    vector<string> mapVector; //creates vector of strings to later store into map object
    int height = 0;

    while (getline(mapFile, str)) //takes file line by line and stores as a vector of strings
    {
        mapVector.push_back(str);
        height += 1;
    }
    
    int width = mapVector[1].length();
    Map myMap(mapVector, height, width); //creates a map object for the game

    if(!argv[2]) //checks if there is a direction input file and changes the gamestate
    {
        myMap.currGameState = gameState::manual;
    }

    for(int i = 0; i < height; i++) //finds the coordinate of the @
    {
        for(int k = 0; k < width; k++)
        {
            if(myMap.board[i].at(k) == '@')
            {
                myMap.xCoor = k; // sets 
                myMap.yCoor = i;
                break;
            }
        }
    }

    if(myMap.currGameState == gameState::manual)
    {
        gameStartUserInput(myMap);
    }
    else
    {
        ifstream instrFile; //reads instruction file and stores in a vector of strings
        instrFile.open(argv[2]);
        vector<string> instr;
        string str;
        int instrLen = 0;
        while (getline(instrFile, str))
        {
            instr.push_back(str);
            instrLen += 1;
        }
        for (int i=0; i<instrLen; i++)
        {
            if(instr[i] == "w" || instr[i] == "d" || instr[i] == "s" || instr[i] == "a")
            {}
            else
            {
                cout << "Invalid input encountered in input sequence." << endl;
                return 0;
            }
        }
        return gameStartFileInput(myMap, instr, instrLen);
    }
    return 0;
}