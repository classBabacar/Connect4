#include "colors.h"
#include "connect4.h"

//************************************************************************
// Function: connectFour()
// Purpose:  Setting up all the values for the program
//************************************************************************
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
    char theMoves[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    for (int i = 0; i < 7; ++i)
    {
        availableMoves.push_back(theMoves[i]);
    }
}

//************************************************************************
// Function: askName()
// Purpose:  asks each individual user their name
//************************************************************************
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

//************************************************************************
// Function: askRematch()
// Purpose:  asks the winner would they like a rematch
//************************************************************************
bool connectFour::askRematch()
{
    cout << "Would you like a rematch? (Y/N) : ";
    char rematch;
    cin >> rematch;
    rematch = tolower(rematch);

    if (rematch == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//************************************************************************
// Function: swapRoles(#char confirmining if they like to swap or not)
// Purpose:  would white like to switch with red or stay the same
//************************************************************************
void connectFour::swapRoles(char swap)
{
    if (swap == 'y')
    {
        string tmp = playeroneName;
        playeroneName = playertwoName;
        playertwoName = tmp;
    }
}

//************************************************************************
// Function: resetAll()
// Purpose:  changes everything back to its default
//************************************************************************
void connectFour::resetAll()
{
    moveNumber = 0;
    gameOver = false;

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            theBoard[i][j] = '0';
        }
    }
}

//************************************************************************
// Function: askSwap()
// Purpose:  making the question asking part a function to make it easier
//************************************************************************
char connectFour::askSwap()
{
    cout << "Would you like to swap on who goes first? (Y/N) : ";
    char swap;
    cin >> swap;
    swap = tolower(swap);

    return swap;
}
void connectFour::checkPlayerOne(bool gameOver)
{
    if (gameOver == true)
    {
        displayBoard();
        playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
        cout << YELLOW << playeroneName << "...Wins" << WHITE << endl;

        if (askRematch())
        {
            playeroneName = playeroneName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            play(3);
        }
        else
        {
            cout << "Thanks for playing the game" << endl;
        }
    }
}

void connectFour::checkPlayerTwo(bool gameOver)
{
    if (gameOver == true)
    {
        displayBoard();
        playertwoName = playertwoName.substr(0, playertwoName.length() - 9);
        cout << RED << playertwoName << "...Wins" << WHITE << endl;

        if (askRematch())
        {
            playertwoName = playertwoName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            play(3);
        }
        else
        {
            cout << "Thanks for playing the game" << endl;
        }
    }
}
void connectFour::checkPlayerAiRed(bool gameOver, char aiColor, char humanColor, string name)
{
    if (gameOver == true)
    {
        displayBoard();
        playertwoName = playertwoName.substr(0, playertwoName.length() - 9);
        cout << RED << playertwoName << "...Wins" << WHITE << endl;

        if (askRematch())
        {
            playertwoName = playertwoName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            aiPlay(humanColor, aiColor, name);
        }
        else
        {
            cout << "Thanks for playing the game" << endl;
        }
    }
}
void connectFour::checkPlayerAiYellow(bool gameOver, char aiColor, char humanColor, string name)
{
    if (gameOver == true)
    {
        displayBoard();
        playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
        cout << YELLOW << playeroneName << "...Wins" << WHITE << endl;

        if (askRematch())
        {
            playeroneName = playeroneName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            aiPlay(humanColor, aiColor, name);
        }
        else
        {
            cout << "Thanks for playing the game" << endl;
        }
    }
}

bool connectFour::checkTie(char aBoard[6][7])
{
    int redCount = 0;
    int yellowCount = 0;
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (aBoard[i][j] == '2')
                redCount++;
            else if (aBoard[i][j] == '1')
                yellowCount++;
        }
    }
    if (redCount + yellowCount == 42)
    {
        cout << RED << "ITS A " << YELLOW << "TIE" << endl;
        return true;
    }
    else
        return false;
}
//************************************************************************
// Function: play(#number of players 1 or 2)
// Purpose:  The whole game loop thats runs on the condtion while the game isnt completed
//
// In the askRematch if statemnts its important to add
// playeroneName = playeroneName + "'s Turn: ", because when a player wins
// I rip the "'s Turn: " part off so if that player does win I add it back
// and set it back to its default then proceed to swap
//************************************************************************
void connectFour::play(int players)
{
    if (players == 2)
    {
        askName();
    }
    while (gameOver == false)
    {
        displayBoard();
        askplayerOne(moveNumber);
        moveNumber++;
        gameOver = checkGame(theBoard);
        checkPlayerOne(gameOver);

        if (gameOver != true)
        {
            displayBoard();
            askplayerTwo(moveNumber);
            moveNumber++;
            gameOver = checkGame(theBoard);
            checkPlayerTwo(gameOver);
        }
        if (checkTie(theBoard))
        {
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            play(3);
        }
    }
}
char connectFour::aiHeuristic(vector<char> availableMoves, char aBoard[6][7], char aiColor, char humanColor, int moveNumber)
{
    //srand(time(NULL));
    int max = -100000;
    int score = 0;
    char aiChoice;
    char lastDecision;
    char fakeBoard[6][7];
    //a b c d e f g
    for (int i = availableMoves.size() - 1; i >= 0; --i)
    {
        memcpy(fakeBoard, aBoard, sizeof(fakeBoard));
        //fakeBoard[5][3] = '2';
        //aiChoice = availableMoves[availableMoves.size() - 1];

        aiChoice = availableMoves[i];
        //cout << "AI CHOICE" << aiChoice << endl;
        if (checkDown(fakeBoard, tolower(aiChoice)))
        { // I need to get the column and row of a piece and evalute everything next to it
            dropAiPiece(fakeBoard, aiChoice, moveNumber);
            score += giveScoreCenter(fakeBoard, aiColor, humanColor);

            score += giveScoreHori(fakeBoard, aiColor, humanColor);

            score += giveScoreVert(fakeBoard, aiColor, humanColor);

            score += giveScoreLeftDiag(fakeBoard, aiColor, humanColor);

            score += giveScoreRightDiag(fakeBoard, aiColor, humanColor);
            if (score > max)
            {
                max = score;
                lastDecision = aiChoice;
            }
        }
        //availableMoves.pop_back();
        score = 0;
    }
    //cout << "the max is " << lastDecision << endl;
    //cout << "Real Shit" << endl;
    cout << max << endl;
    return lastDecision;
}

int connectFour::giveScoreLeftDiag(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;

    //cout << "CHOICE############# " << aiChoice << endl;
    string rowString = "";
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            rowString = "";
            //upleftConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
            if (isupLeftDiag(aBoard, i, j))
            {
                rowString += aBoard[i][j];
                rowString += aBoard[i - 1][j - 1];
                rowString += aBoard[i - 2][j - 2];
                rowString += aBoard[i - 3][j - 3];

                int aiPieces = countMyPieces(rowString, aiColor);
                int emptySpots = countMyPieces(rowString, '0');
                int humanPieces = countMyPieces(rowString, humanColor);
                score += scoreMetric(aiPieces, emptySpots, humanPieces);
            }
        }
    }

    return score;
}

int connectFour::giveScoreRightDiag(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;

    //cout << "CHOICE############# " << aiChoice << endl;
    string rowString = "";
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            rowString = "";
            if (isupRightDiag(aBoard, i, j))
            {
                rowString += aBoard[i][j];
                rowString += aBoard[i - 1][j + 1];
                rowString += aBoard[i - 2][j + 2];
                rowString += aBoard[i - 3][j + 3];

                int aiPieces = countMyPieces(rowString, aiColor);
                int emptySpots = countMyPieces(rowString, '0');
                int humanPieces = countMyPieces(rowString, humanColor);
                score += scoreMetric(aiPieces, emptySpots, humanPieces);
            }
        }
    }

    return score;
}
bool connectFour::isupLeftDiag(char aboard[6][7], int aiColumn, int aiRow)
{
    int tmpCol = aiColumn;
    int tmpRow = aiRow;
    int counter = 0;

    while ((aboard[tmpCol][tmpRow] == '0' || aboard[tmpCol][tmpRow] == '1' || aboard[tmpCol][tmpRow] == '2') && (tmpRow >= 0 && tmpCol >= 0 && counter != 4))
    {
        counter++;
        tmpCol--;
        tmpRow--;
    }

    if (counter == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool connectFour::isupRightDiag(char aboard[6][7], int aiColumn, int aiRow)
{
    int tmpCol = aiColumn;
    int tmpRow = aiRow;
    int counter = 0;

    while ((aboard[tmpCol][tmpRow] == '0' || aboard[tmpCol][tmpRow] == '1' || aboard[tmpCol][tmpRow] == '2') && (tmpRow <= 6 && tmpCol >= 0 && counter != 4))
    {
        counter++;
        tmpCol--;
        tmpRow++;
    }

    if (counter == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int connectFour::scoreMetric(int aiPieces, int emptySpots, int humanPieces)
{
    int score = 0;
    if (aiPieces == 4)
    {
        score += 100;
    }
    else if (aiPieces == 3 && emptySpots == 1)
    {
        score += 10;
    }
    else if (aiPieces == 2 && emptySpots == 2)
    {
        score += 5;
    }
    if (humanPieces == 2 && emptySpots == 2)
    {
        score -= 14;
    }
    if (humanPieces == 3 && emptySpots == 1)
    {
        score -= 80;
    }
    //cout << "Human Pieces" << humanPieces << endl;

    return score;
}
int connectFour::giveScoreHori(char aBoard[6][7], char aiColor, char humanColor)
{

    int score = 0;

    //cout << "CHOICE############# " << aiChoice << endl;
    string rowString = "";

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            rowString += aBoard[i][j];
        }
        //rowString = reverseString(rowString);
        //cout << rowString << endl;
        int k = 0;
        string matcher = "";
        while (k < 4)
        {
            matcher += rowString[k];
            matcher += rowString[k + 1];
            matcher += rowString[k + 2];
            matcher += rowString[k + 3];

            int aiPieces = countMyPieces(matcher, aiColor);
            int emptySpots = countMyPieces(matcher, '0');
            int humanPieces = countMyPieces(matcher, humanColor);
            //cout << matcher << endl;
            //cout << aiColor << endl;
            score += scoreMetric(aiPieces, emptySpots, humanPieces);

            matcher = "";
            k++;
        }
        rowString = "";
    }
    return score;
    // return max;
}

int connectFour::giveScoreCenter(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;
    int counter = 0;
    for (int i = 0; i < column; ++i)
    {
        //aBoard[i][4];
        if (aBoard[i][3] == aiColor)
        {
            counter++;
        }
    }
    score += counter * 6;
    return score;

    //return counter * 6;
}

// int connectFour::minimax(char aBoard[6][7], int depth, bool whoAreYou, char aiColor, char humanColor)
// {
//     int aiCounter = 0;
//     int humanCounter = 0;
//     if (depth == 0 || (checkGame(theBoard) == true) || checkTie(theBoard) == true)
//     {
//         //aiCounter = calculatePieces(aBoard[6][7], aiColor);
//         //humanCounter = calculatePieces(aBoard[6][7], humanColor);

//         if (checkGame(aBoard))
//         {
//             if (aiCounter > humanCounter)
//             {
//                 return 10000000000000;
//             }
//             else if (humanCounter > aiCounter)
//             {
//                 return -1000000000000;
//             }
//             else
//             {
//             }
//         }
//     }
// }
int connectFour::countMyPieces(string matcher, char anyPiece)
{
    int counter = 0;
    for (int b = 0; b < 4; ++b)
    {
        if (matcher[b] == anyPiece)
        {
            counter++;
        }
    }
    return counter;
}
int connectFour::giveScoreVert(char aBoard[6][7], char aiColor, char humanColor)
{

    int score = 0;
    //char move = ' ';

    //cout << "CHOICE############# " << aiChoice << endl;
    string rowString = "";

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            rowString += aBoard[j][i];
        }
        //rowString = reverseString(rowString);
        //cout << rowString << endl;
        int k = 0;
        string matcher = "";
        while (k < 4)
        {
            matcher += rowString[k];
            matcher += rowString[k + 1];
            matcher += rowString[k + 2];
            matcher += rowString[k + 3];

            int aiPieces = countMyPieces(matcher, aiColor);
            int emptySpots = countMyPieces(matcher, '0');
            int humanPieces = countMyPieces(matcher, humanColor);

            //cout << "Vert" << matcher << endl;
            //cout << aiColor << endl;
            score += scoreMetric(aiPieces, emptySpots, humanPieces);

            matcher = "";
            k++;
        }
        rowString = "";
    }

    return score;
    // cout << endl;
}

void connectFour::aiPlay(char aiColor, char humanColor, string name)
{

    while (humanColor == '1' && gameOver == false)
    {
        playeroneName = name + "'s Turn: ";
        playertwoName = "Ai's Turn: ";
        displayBoard();
        askplayerOne(moveNumber);
        moveNumber++;
        gameOver = checkGame(theBoard);
        checkPlayerOne(gameOver);

        if (gameOver != true)
        {
            char move = aiHeuristic(availableMoves, theBoard, aiColor, humanColor, moveNumber);
            dropPiece(theBoard, move, moveNumber);
            moveNumber++;
            gameOver = checkGame(theBoard);
            checkPlayerAiRed(gameOver, aiColor, humanColor, name);
        }
        if (checkTie(theBoard))
        {
            playertwoName = playertwoName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            aiPlay(humanColor, aiColor, name);
        }
    }
    while (humanColor == '2' && gameOver == false)
    {
        /*playeroneName = "Ai's Turn: ";
        playertwoName = name + "'s Turn: ";

        char move = aiHeuristic(availableMoves, theBoard, aiColor, humanColor, moveNumber);
        dropPiece(theBoard, move, moveNumber);
        moveNumber++;
        gameOver = checkGame(theBoard);
        checkPlayerAiYellow(gameOver, aiColor, humanColor, name);

        if (gameOver != true)
        {
            displayBoard();
            askplayerOne(moveNumber);
            moveNumber++;
            gameOver = checkGame(theBoard);
            checkPlayerOne(gameOver);
        }
        if (checkTie(theBoard))
        {
            playerName = playeroneName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            aiPlay(humanColor, aiColor, name);
        }*/
    }
}

//************************************************************************
// Function: displayBoard()
// Purpose:  Prints the board
//************************************************************************
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

//************************************************************************
// Function: playeroneChoice()
// Purpose:  asks where a arbritary player one wants to go
//************************************************************************
char connectFour::playeroneChoice()
{
    cout << YELLOW << playeroneName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}

//************************************************************************
// Function: playertwoChoice()
// Purpose:  asks where a arbritrary player two wants to go
//************************************************************************
char connectFour::playertwoChoice()
{
    cout << RED << playertwoName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}

//************************************************************************
// Function: askplayerOne(#of moves made)
// Purpose:  confirms if players ones move is valid
//************************************************************************
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

//************************************************************************
// Function: askplayerTwo(#of moves made)
// Purpose:  confirms if player twos move is valid
//************************************************************************
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

//************************************************************************
// Function: checkValid(choice from either player 1/2, #of moves made)
// Purpose:  The algorithm to confirm if you are choosing a proper row
//************************************************************************
bool connectFour::checkValid(char choice, int MoveNumber)
{
    if (toupper(choice) >= 'A' && 'G' >= toupper(choice))
    {
        if (checkDown(theBoard, tolower(choice)))
        {
            dropPiece(theBoard, choice, moveNumber);
            return true;
        }
    }
    return false;
}

//************************************************************************
// Function: getRow(eithers players choice)
// Purpose:  used to convert their choice into a number to play into board
//************************************************************************
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

void connectFour::dropPiece(char (&aBoard)[6][7], char choice, int moveNumber)
{
    int tmpRow = getRow(choice);
    int tmpCol = 5;

    while (aBoard[tmpCol][tmpRow] == '1' || aBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
    }
    if (moveNumber % 2 == 0)
    {
        int i = 0;
        while (i != tmpCol)
        {
            aBoard[i][tmpRow] = '1';
            displayBoard();
            aBoard[i][tmpRow] = '0';
            i++;
            usleep(250000);
        }
        cout << string(50, '\n');
        aBoard[tmpCol][tmpRow] = '1';
    }
    else
    {
        int i = 0;
        while (i != tmpCol)
        {
            aBoard[i][tmpRow] = '2';
            displayBoard();
            aBoard[i][tmpRow] = '0';
            i++;
            usleep(250000);
        }
        cout << string(50, '\n');
        aBoard[tmpCol][tmpRow] = '2';
    }
}

void connectFour::dropAiPiece(char (&aBoard)[6][7], char choice, int moveNumber)
{
    int tmpRow = getRow(choice);
    int tmpCol = 5;

    while (aBoard[tmpCol][tmpRow] == '1' || aBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
    }
    if (moveNumber % 2 == 0)
    {
        aBoard[tmpCol][tmpRow] = '1';
    }
    else
    {
        aBoard[tmpCol][tmpRow] = '2';
    }
}
//************************************************************************
// Function: checkDown(player 1/2 choice, #of moves made)
// Purpose:  algorithm to figure out if the move is available or not
//************************************************************************
bool connectFour::checkDown(char aBoard[6][7], char choice)
{
    int tmpRow = getRow(choice);
    int tmpCol = 5;

    while (aBoard[tmpCol][tmpRow] == '1' || aBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
        if (tmpCol < 0)
        {
            return false;
        }
    }

    return true;
}

//************************************************************************
// Function: checkGame()
// Purpose:  checking if either player has won the game, by evaluating each cell
//************************************************************************
bool connectFour::checkGame(char aBoard[6][7])
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (upConnect4(aBoard, i, j))
            {
                return true;
            }
            else if (rightConnect4(aBoard, i, j))
            {
                return true;
            }
            else if (uprightConnect4(aBoard, i, j))
            {
                return true;
            }
            else if (upleftConnect4(aBoard, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

//************************************************************************
// Function: upleftConnect4(col,row)
// Purpose:  a diagonal connect4
//
// note : you don't need to change the following:
// redCounter == 4 || yellowCounter == 4 to redCounter >= 4 || yellowCounter >= 4
// because each indivual cell is getting evaluated and out of curiosity,
// I tried to prove that it would always see a conect4 and proved it
//************************************************************************
bool connectFour::upleftConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (aBoard[yelCol][yelRow] == '1' && yelRow >= 0 && yelCol >= 0)
    {
        yellowCounter++;
        --yelRow;
        --yelCol;
    }

    while (aBoard[redCol][redRow] == '2' && redRow >= 0 && redCol >= 0)
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

//************************************************************************
// Function: uprightConnect4(col,row)
// Purpose:  a  reverse diagonal connect4
//
// note : you don't need to change the following:
// redCounter == 4 || yellowCounter == 4 to redCounter >= 4 || yellowCounter >= 4
// because each indivual cell is getting evaluated and out of curiosity,
// I tried to prove that it would always see a conect4 and proved it
//************************************************************************
bool connectFour::uprightConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (aBoard[yelCol][yelRow] == '1' && yelRow <= 6 && yelCol >= 0)
    {
        yellowCounter++;
        ++yelRow;
        --yelCol;
    }

    while (aBoard[redCol][redRow] == '2' && redRow <= 6 && redCol >= 0)
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

//************************************************************************
// Function: rightConnect4(col,row)
// Purpose:  a right connect4
//
// note : you don't need to change the following:
// redCounter == 4 || yellowCounter == 4 to redCounter >= 4 || yellowCounter >= 4
// because each indivual cell is getting evaluated and out of curiosity,
// I tried to prove that it would always see a conect4 and proved it
//************************************************************************
bool connectFour::rightConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
{
    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (aBoard[yelCol][yelRow] == '1' && yelRow <= 6)
    {
        yellowCounter++;
        ++yelRow;
    }

    while (aBoard[redCol][redRow] == '2' && redRow <= 6)
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

//************************************************************************
// Function: upConnect4(col,row)
// Purpose:  a up connect4
//
// note : you don't need to change the following:
// redCounter == 4 || yellowCounter == 4 to redCounter >= 4 || yellowCounter >= 4
// because each indivual cell is getting evaluated and out of curiosity,
// I tried to prove that it would always see a conect4 and proved it
//************************************************************************
bool connectFour::upConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
{

    int yelCol = tmpCol;
    int yelRow = tmpRow;

    int redCol = tmpCol;
    int redRow = tmpRow;

    int yellowCounter = 0;
    int redCounter = 0;

    while (aBoard[yelCol][yelRow] == '1' && yelCol >= 0)
    {
        yellowCounter++;
        --yelCol;
    }

    while (aBoard[redCol][redRow] == '2' && redCol >= 0)
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
