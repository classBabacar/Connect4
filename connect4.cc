#include "colors.h"
#include "connect4.h"
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>

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
            playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
            cout << YELLOW << playeroneName << "...Wins" << WHITE << endl;
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
                playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
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
        int i = 0;
        while (i != tmpCol)
        {
            theBoard[i][tmpRow] = '1';
            displayBoard();
            theBoard[i][tmpRow] = '0';
            i++;
            usleep(1000000);
        }
        theBoard[tmpCol][tmpRow] = '1';
    }
    else
    {
        int i = 0;
        while (i != tmpCol)
        {
            theBoard[i][tmpRow] = '2';
            displayBoard();
            theBoard[i][tmpRow] = '0';
            i++;
            usleep(1000000);
        }
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
            else if (rightConnect4(i, j))
            {
                return true;
            }
            else if (uprightConnect4(i, j))
            {
                return true;
            }
            else if (upleftConnect4(i, j))
            {
                return true;
            }
        }
    }
    return false;
}
bool connectFour::upleftConnect4(int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (theBoard[yelCol][yelRow] == '1' && yelRow >= 0 && yelCol >= 0)
    {
        yellowCounter++;
        --yelRow;
        --yelCol;
    }

    while (theBoard[redCol][redRow] == '2' && redRow >= 0 && redCol >= 0)
    {
        redCounter++;
        --redRow;
        --redCol;
    }

    if (redCounter == 4 || yellowCounter == 4)
    {
        return true;
    }
    return false;
}
bool connectFour::uprightConnect4(int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (theBoard[yelCol][yelRow] == '1' && yelRow <= 6 && yelCol >= 0)
    {
        yellowCounter++;
        ++yelRow;
        --yelCol;
    }

    while (theBoard[redCol][redRow] == '2' && redRow <= 6 && redCol >= 0)
    {
        redCounter++;
        ++redRow;
        --redCol;
    }

    if (redCounter == 4 || yellowCounter == 4)
    {
        return true;
    }
    return false;
}
bool connectFour::rightConnect4(int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (theBoard[yelCol][yelRow] == '1' && yelRow <= 6)
    {
        yellowCounter++;
        ++yelRow;
    }

    while (theBoard[redCol][redRow] == '2' && redRow <= 6)
    {
        redCounter++;
        ++redRow;
    }

    if (redCounter == 4 || yellowCounter == 4)
    {
        return true;
    }
    return false;
}
//1 is yellow
//yea
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