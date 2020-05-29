//
//  main.cpp
//  Tic Tac Toe
//
//  Created by Mateusz Wygonny on 06/05/2020.
//  Copyright © 2020 Mateusz Wygonny. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
using namespace std;



void printTable(vector<string> table);
int  getPlace();
void mainLoop();
void versusComputer();
void versusPlayer();
bool isGameOver(const vector<string> &table);
void gameWon(const string &winner);
void gameTied();
string switchTurn(const string &currentPlayer);
vector<string> playerMove(vector<string> table, string playerTurn);
vector<string> computerMove(vector<string> table);
vector<int> findSpots(const vector<string> &table, const string &spotType);
int findPossibleWin(const vector<int> &takenSpots, const vector<int> &freeSpots);
bool isNumberWithinVector(const vector<int> &givenVector, const int &givenNumber);
int getRandomNumberFromVector(const vector<int> &givenVector);

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
        string gameMode = "";
        cin >> gameMode;
        if(gameMode == "1"){
            versusComputer();
        }else if(gameMode == "2"){
            versusPlayer();
        }else if(gameMode == "3"){
            break;
        }else{
            cout << "This is not a proper option, please specify correct game mode by typing its number" << endl;
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
        cout << "--------------------------" << endl;
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
            if(isGameOver(table)){
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
        cout << "--------------------------" << endl;
        table = playerMove(table, turn);
        turnCounter++;

        if(turnCounter >= 5){
            if(isGameOver(table)){
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
int findPossibleWin(const vector<int> &takenSpots, const vector<int> &freeSpots){
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
bool isNumberWithinVector(const vector<int> &givenVector, const int &givenNumber)
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
int getRandomNumberFromVector(const vector<int> &givenVector)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, givenVector.size()-1);
    return givenVector[dis(gen)];
}
vector<int> findSpots(const vector<string> &table, const string &spot)
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
string switchTurn(const string &turn)
{
    string nextPlayer = turn.compare("X") == 0 ? "O" : "X";
    return nextPlayer;
}

bool isGameOver (const vector<string> &table) {
    for (int i = 0; i < 3; i++) {
        if (table[3 * i] == table[3 * i + 1] && table[3 * i + 1] == table[3 * i + 2] && table[3 * i] != " ")
        {
            return true;
        }
        if (table[i] == table[3 + i] && table[3 + i] == table[6 + i] && table[i] != " ")
        {
            return true;
        }
    }
    if(table[0] == table[4] && table[4] == table[8] && table[0] != " ")
    {
        return true;
    }
    if(table[2] == table[4] && table[4] == table[6] && table[2] != " ")
    {
        return true;
    }
    return false;
}

void gameWon(const string &winner)
{
    cout << "The game is over! " << winner << " has won! Going back to menu..." << endl;

}
void gameTied()
{
    cout << "The game is over! Unfortunately no one has won. Going back to menu..." << endl;
}
