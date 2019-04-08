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
void conne
//1 is yellow and 2 is red
bool connectFour::play(int players)
{
    if (players == 1 && gameOver == false)
    {
        displayBoard();
        askPlayerOne();
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
