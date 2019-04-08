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
    playeroneName = "";
    playertwoName = "";

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            theBoard[i][j] = '0';
        }
    }
    //theBoard[5][0] = '1';
}

void connectFour::askName()
{
    string p1name;
    cout << "Who wants to be" << YELLOW << " playerOne, enter name : " << endl;
    cin.ignore();
    getline(cin, p1name);
    playeroneName = p1name + "'s Turn: ";
    cout << WHITE;

    string p2name;
    cout << "Who wants to be" << RED << " playerTwo, enter name : " << endl;
    getline(cin, p2name);
    playertwoName = p2name + "'s Turn: ";
    cout << WHITE;
}
//1 is yellow and 2 is red
void connectFour::play(int players)
{
    if (players == 2)
    {
        askName();
    }
    while (players == 2 && gameOver == false)
    {
        //player one
        displayBoard();
        askplayerOne(moveNumber);
        moveNumber++;
        gameOver = checkGame();

        if (gameOver == true)
        {
            displayBoard();
            cout << YELLOW << "Player One...Wins" << WHITE << endl;
        }
        else
        {
            displayBoard();
            askplayerTwo(moveNumber);
            moveNumber++;
            gameOver = checkGame();

            if (gameOver == true)
            {
                displayBoard();
                cout << RED << "Player Two....Wins" << WHITE << endl;
            }
        }
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
char connectFour::playeroneChoice()
{
    cout << YELLOW << playeroneName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}

char connectFour::playertwoChoice()
{
    cout << RED << playertwoName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}
void connectFour::askplayerOne(int moveNumber)
{
    char choice = playeroneChoice();

    if (!checkValid(choice, moveNumber))
    {
        cout << endl;
        displayBoard();
        cout << YELLOW << "Invalid Move....Try again" << YELLOW << endl;
        askplayerOne(moveNumber);
    }
}
void connectFour::askplayerTwo(int moveNumber)
{

    char choice = playertwoChoice();

    if (!checkValid(choice, moveNumber))
    {
        cout << endl;
        displayBoard();
        cout << RED << "Invalid Move....Try again" << WHITE << endl;
        askplayerTwo(moveNumber);
    }
}

bool connectFour::checkValid(char choice, int MoveNumber)
{
    if (toupper(choice) >= 'A' && 'G' >= toupper(choice))
    {
        if (checkDown(tolower(choice), moveNumber))
        {
            return true;
        }
    }
    return false;
}

bool connectFour::checkDown(char choice, int moveNumber)
{
    int tmpRow = getRow(choice);
    int tmpCol = 5;

    while (theBoard[tmpCol][tmpRow] == '1' || theBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
        if (tmpCol < 0)
        {
            return false;
        }
    }

    if (moveNumber % 2 == 0)
    {
        theBoard[tmpCol][tmpRow] = '1';
    }
    else
    {
        theBoard[tmpCol][tmpRow] = '2';
    }
    return true;
}

bool connectFour::checkGame()
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (upConnect4(i, j))
            {
                return true;
            }
        }
    }
    return false;
}
//1 is yellow
//2 is red
bool connectFour::upConnect4(int tmpCol, int tmpRow)
{

    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (theBoard[yelCol][yelRow] == '1' && yelCol >= 0)
    {
        yellowCounter++;
        --yelCol;
    }

    while (theBoard[redCol][redRow] == '2' && redCol >= 0)
    {
        redCounter++;
        --redCol;
    }

    if (redCounter == 4 || yellowCounter == 4)
    {
        return true;
    }
    return false;
}
int connectFour::getRow(char choice)
{
    switch (choice)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case 'c':
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    default:
        return 99;
    }
}