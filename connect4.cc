#include "colors.h"
#include "connect4.h"
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

connectFour::connectFour()
{
    row = 7;
    column = 6;
    moveNumber = 0;
    gameOver = false;

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            theBoard[i][j] = '0';
        }
    }
    //theBoard[5][0] = '1';
}
//1 is yellow and 2 is red
void connectFour::play(int players)
{
    if (players == 1 && gameOver == false)
    {
        displayBoard();
        askplayerOne(moveNumber);
        moveNumber++;
    }
}
void connectFour::displayBoard()
{
    cout << RED << " A   B   C   D   E   F   G " << WHITE << endl;
    cout << " +-----------------------+ " << endl;
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; j++)
        {
            if (theBoard[i][j] == '1')
            {
                cout << YELLOW << " O  " << WHITE;
            }
            else if (theBoard[i][j] == '2')
            {
                cout << RED << " O  " << WHITE;
            }
            else
            {
                cout << BLUE << " |  " << WHITE;
            }
        }
        cout << endl;
    }
    cout << " +-----------------------+ " << endl;
}

void connectFour::askplayerOne(int moveNumber){
    cout << "Where would you like to go? " << endl;
    char choice;
    cin >> choice;

    if(checkValid(choice, moveNumber)){
        //cout << "good choice" << endl;
    }else{
        cout << "bad choice" << endl;
    }
}

bool connectFour::checkValid(char choice, int MoveNumber){
    if( toupper(choice) >= 'A' && 'G' >= toupper(choice)){
        if(checkDown(tolower(choice), moveNumber)){

        }
        //return true;
    }
    else{
        return false;
    }
}

bool connectFour::checkDown(char choice, int moveNumber){
    int goDown = getRow(choice);
    
}
int connectFour::getRow(char choice){
    switch(choice) { 
    case 'a' :
        return 0;
    case 'b' :
        return 1;
    case 'c' :
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    }
}