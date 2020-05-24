//
//  main.cpp
//  Tic Tac Toe
//
//  Created by Mateusz Wygonny on 06/05/2020.
//  Copyright © 2020 Mateusz Wygonny. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;



void printTable(vector<string> table);
int  getPlace();
void mainLoop();
void versusComputer();
void versusPlayer();
bool isGameOver(vector<string> table, int turnCounter);
void gameWon(string winner);
void gameTied();
string switchTurn(string currentPlayer);
vector<string> playerMove(vector<string> table, string playerTurn);
vector<string> computerMove(vector<string> table);
vector<int> findSpots(vector<string> table, string spotType);
vector<int> findEnemySpots(vector<string> table);
int findPossibleWin(vector<int> takenSpots, vector<int> freeSpots);
bool isNumberWithinVector(vector<int> givenVector, int givenNumber);
int getRandomNumberFromVector(vector<int> givenVector);

int main(int argc, const char * argv[])
{
    mainLoop();
}
// insert code here...
//
//}
void mainLoop(){
    bool menuLoop = true;
    while(menuLoop)
    {
        cout << "Tic Tac Toe. Choose an option by typing its number: " << endl;
        cout << "1. Versus Computer" << endl << "2. Versus Player" << endl << "3. Quit" << endl;
        int gameMode = 0;
        cin >> gameMode;
        switch (gameMode)
        {
            case 1:
                versusComputer();
                break;
            case 2:
                versusPlayer();
                break;
            case 3:
                menuLoop = false;
                break;
            default:
                cout << "This is not a proper option, please specify correct gamemode by typing its number" << endl;
                
        }
    }
}
void printTable (vector<string> table){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(j < 2){
                cout << table[i*3+j] << "|";
            }
            else{
                cout << table[i*3+j]<< endl;
            }
        }
        if(i < 2){
            cout << "- - -" << endl;
        }
    }
}
int getPlace(){
    
    int column = 0;
    int row = 0;
    bool rowGiven = false;
    bool columnGiven = false;
    cout << "Column (horizontal position):  " << endl;
    
    while(!columnGiven)
    {
        cin >> column;
        if(!(column > 0 && column < 4)){
            cout << "Give number within range [1,3]" << endl;
        }else{
            columnGiven = true;
        }
    }
    
    cout << "Row (vertical position): " << endl;
    
    while(!rowGiven)
    {
        cin >> row;
        
        if(!(row > 0 && row < 4))
        {
            cout << "Give number within range [1,3]" << endl;
        }
        else
        {
            rowGiven = true;
        }
    }
    return 3*(row-1) + column-1;
    
}
void versusComputer()
{
    cout << "You're playing against computer" << endl;
    int turnCounter = 0;
    bool gameOn = true;
    vector<string> table = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
    string turn = "X";
    while(gameOn)
    {
        printTable(table);
        if(turn.compare("X") == 0)
        {
            table = playerMove(table, turn);
        }
        else
        {
            table = computerMove(table);
        }
        turnCounter++;
        if(turnCounter >= 5){
            isGameOver(table, turnCounter);
            if(isGameOver(table, turnCounter)){
                gameOn = false;
                printTable(table);
                gameWon(turn);
                
            }else if(turnCounter>=9){
                gameOn = false;
                printTable(table);
                gameTied();
                
            }
        }
        turn = switchTurn(turn);
        
        
    }
}
void versusPlayer()
{
    cout << "You're playing against another player" << endl;
    int turnCounter = 0;
    bool gameOn = true;
    vector<string> table = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
    string turn = "X";
    while(gameOn){
        
        printTable(table);
        table = playerMove(table, turn);
        turnCounter++;
        
        if(turnCounter >= 5){
            isGameOver(table, turnCounter);
            if(isGameOver(table, turnCounter)){
                gameOn = false;
                printTable(table);
                gameWon(turn);
                
            }else if(turnCounter>=9){
                gameOn = false;
                printTable(table);
                gameTied();
                
            }
        }
        turn = switchTurn(turn);
    }
}

vector<string> playerMove(vector<string> table, string player)
{
    bool freeSpot = false;
    while(!freeSpot){
        int desiredPlace = getPlace();
        if(!table[desiredPlace].compare(" ")){
            freeSpot = true;
            table[desiredPlace] = player;
        }else{
            cout << "This place is taken, give coordinates of a free spot" << endl;
        }
    }
    return table;
}
vector<string> computerMove(vector<string> table)
{
    vector<int> freeSpots = findSpots(table, " ");
    vector<int> playerSpots = findSpots(table, "X");
    vector<int> computerSpots = findSpots(table, "O");
    
    int possibleComputerWin = findPossibleWin(computerSpots, freeSpots);
    
    if(possibleComputerWin != -1)
    {
        table[possibleComputerWin] = "O";
    }
    else
    {
        int possiblePlayerWin = findPossibleWin(playerSpots, freeSpots);
        if(possiblePlayerWin != -1)
        {
            table[possiblePlayerWin] = "O";
        }
        else
        {
            int randomMove = getRandomNumberFromVector(freeSpots);
            table[randomMove] = "O";
        }
    }
    return table;
}
int findPossibleWin(vector<int> takenSpots, vector<int> freeSpots){
    vector<vector<int>> possibleWins = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    int winningMove = -1;
    for(int i = 0; i < possibleWins.size(); i++)
    {
        vector<int> matchingNumbers = {};
        vector<int> missingNumbers = {};
        for(int j = 0; j < 3; j++)
        {
            if(isNumberWithinVector(takenSpots, possibleWins[i][j]))
            {
                matchingNumbers.push_back(possibleWins[i][j]);
            }
            else
            {
                missingNumbers.push_back(possibleWins[i][j]);
            }
        }
        if(matchingNumbers.size() == 2)
        {
            if(isNumberWithinVector(freeSpots, missingNumbers[0]))
            {
                winningMove = missingNumbers[0];
                break;
            }
        }
    }
    return winningMove;
}
bool isNumberWithinVector(vector<int> givenVector, int givenNumber)
{
    for(int i = 0; i < givenVector.size(); i++)
    {
        if(givenVector[i] == givenNumber)
        {
            return true;
        }
    }
    return false;
}
int getRandomNumberFromVector(vector<int> givenVector)
{
    int randomNumber = rand() % givenVector.size();
    return randomNumber;
}
vector<int> findSpots(vector<string> table, string spot)
{
    vector <int> spots = {};
    for(int i = 0; i < table.size(); i++)
    {
        if(table[i].compare(spot) == 0)
        {
            spots.push_back(i);
        }
    }
    return spots;
}
string switchTurn(string turn)
{
    string nextPlayer = turn.compare("X") == 0 ? "O" : "X";
    return nextPlayer;
}

bool isGameOver (vector<string> table, int turnCounter){//TODO: rewrite using 3 loops, one for horizontal, vertical and skew lines
    if(table[0].compare(table[1]) + table[1].compare(table[2]) == 0 && table[0].compare(" ") != 0) // upper horizontal line
    {
        return true;
    }
    else if(table[3].compare(table[4]) == 0 && table[4].compare(table[5]) == 0 && table[3].compare(" ") != 0) // middle horizontal line
    {
        return true;
    }
    else if(table[6].compare(table[7]) == 0 && table[7].compare(table[8]) == 0 && table[6].compare(" ") != 0) // lower horizontal line
    {
        return true;
    }
    else if(table[0].compare(table[3]) == 0 && table[3].compare(table[6]) == 0 && table[0].compare(" ") != 0) // left vertical line
    {
        return true;
    }
    else if(table[1].compare(table[4]) == 0 && table[4].compare(table[7]) == 0 && table[1].compare(" ") != 0) // middle vertical line
    {
        return true;
    }
    else if(table[2].compare(table[5]) == 0 && table[5].compare(table[8]) == 0 && table[2].compare(" ") != 0) // right vertical line
    {
        return true;
    }
    else if(table[0].compare(table[4]) == 0 && table[4].compare(table[8]) == 0 && table[0].compare(" ") != 0) // top-left to bottom-right line;
    {
        return true;
    }
    else if(table[2].compare(table[4]) == 0 && table[4].compare(table[6]) == 0 && table[22].compare(" ") != 0) // top-right to bottom-left  line
    {
        return true;
    }
    else
    {
        return false;
    }
}
void gameWon(string winner)
{
    cout << "The game is over! " << winner << " has won! Going back to menu..." << endl;
    
}
void gameTied()
{
    cout << "The game is over! Unfortunately noone has won. Going back to menu..." << endl;
}
