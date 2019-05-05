#include "colors.h"
#include "connect4.h"

//************************************************************************
// Function: connectFour()
// Purpose:  Setting up all the values for the program
//************************************************************************
connectFour::connectFour()
{
    max = 0;
    total = 0;

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
char connectFour::askColor()
{
    cout << "would you like to be yellow or red? (y/r)" << endl;
    char color;
    cin >> color;
    color = tolower(color);
    return color;
}

void connectFour::askSoloName(char color)
{
    cout << "What's your name? " << endl;
    string name;
    cin.ignore();
    getline(cin, name);
    if (color == 'y')
    {
        playeroneName = name + "'s Turn: ";
        playertwoName = "Ai's Turn: ";
    }
    else
    {
        playertwoName = name + "'s Turn: ";
        playeroneName = "Ai's Turn: ";
    }
}
deque<char> connectFour::generateMoves(char aBoard[6][7])
{
    deque<char> availableMoves;
    bool notGoodMove = false;
    char availableSpots[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    for (int i = 0; i < 7; ++i)
    {
        char choice = availableSpots[i];
        int tmpRow = getRow(choice);
        int tmpCol = 5;

        while ((aBoard[tmpCol][tmpRow] == '1' || aBoard[tmpCol][tmpRow] == '2') && notGoodMove == false)
        {
            tmpCol--;
            if (tmpCol < 0)
            {

                notGoodMove = true;
            }
        }

        if (notGoodMove == false)
        {
            //cout << "im here" << endl;
            availableMoves.push_front(choice);
        }
        notGoodMove = false;
    }

    return availableMoves;
}
//2 is red 1 is yellow
void connectFour::placePiece(char (&initialBoard)[6][7], char move, char aiColor, int &aiRow, int &aiCol)
{
    int tmpRow = getRow(move);
    int tmpCol = 5;

    while (initialBoard[tmpCol][tmpRow] == '1' || initialBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
        if (tmpCol < 0)
        {
            return;
        }
    }
    if (aiColor == 'r')
    {
        initialBoard[tmpCol][tmpRow] = '2';
    }
    else
    {
        initialBoard[tmpCol][tmpRow] = '1';
    }
    aiCol = tmpCol;
    aiRow = tmpRow;
}
int connectFour::rightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    //right
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol][aiRow + i] == matcher && aiRow + i <= 6)
    {
        i++;
        counter++;
    }
    return 3 * counter;
}

int connectFour::downHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol + i][aiRow] == matcher && aiCol + i <= 5)
    {
        i++;
        counter++;
    }
    return 4 * counter;
}
int connectFour::leftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    //left
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol][aiRow - i] == matcher && aiRow - i >= 0)
    {
        i++;
        counter++;
    }
    return 3 * counter;
}

int connectFour::upRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{

    //Upright
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol - i][aiRow + i] == matcher && aiRow + i <= 6 && aiCol - i >= 0)
    {
        i++;
        counter++;
    }
    return 3 * counter;
}

int connectFour::downRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{

    //Upright
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol + i][aiRow + i] == matcher && aiRow + i <= 6 && aiCol + i <= 5)
    {
        i++;
        counter++;
    }

    return 3 * counter;
}

int connectFour::upLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    //Up Left
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol - i][aiRow - i] == matcher && aiRow - i >= 0 && aiCol - i >= 0)
    {
        i++;
        counter++;
    }
    return 3 * counter;
}
int connectFour::downLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    //Up Left
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol + i][aiRow - i] == matcher && aiRow - i >= 0 && aiCol + i <= 5)
    {
        i++;
        counter++;
    }
    return 3 * counter;
}
int connectFour::specialCaseLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{

    //Special Case
    int i = 1;
    int availableSpot = 0;
    int aiPiece = 0;
    if ((initialBoard[aiCol][aiRow - i] == oppositeMatcher || initialBoard[aiCol][aiRow - i] == '0') && aiRow - i >= 0 && (initialBoard[aiCol + i][aiRow - i] == '1' || initialBoard[aiCol + i][aiRow - i] == '2'))
    {
        while (initialBoard[aiCol][aiRow + i] != oppositeMatcher && aiRow + i <= 6)
        {
            if (initialBoard[aiCol][aiRow + i] == '0' && (initialBoard[aiCol + i][aiRow + i] == '1' || initialBoard[aiCol + i][aiRow + i] == '2'))
            {
                availableSpot++;
            }
            if (initialBoard[aiCol][aiRow + i] == matcher)
            {
                aiPiece++;
            }
            i++;
        }
    }
    if (initialBoard[aiCol][aiRow - 1] == '0' && (aiPiece + availableSpot + 1 >= 4) && (aiRow - 1 >= 0))
    {
        return 20;
    }
    else if (initialBoard[aiCol][aiRow - 1] == oppositeMatcher && (aiPiece + availableSpot >= 4) && (aiRow - 1 >= 0))
    {
        return -300;
    }
}

int connectFour::specialCaseRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{

    //Special Case
    int i = 1;
    int availableSpot = 0;
    int aiPiece = 0;
    if ((initialBoard[aiCol][aiRow + i] == oppositeMatcher || initialBoard[aiCol][aiRow + i] == '0') && aiRow + i <= 6 && (initialBoard[aiCol + i][aiRow + i] == '1' || initialBoard[aiCol + i][aiRow + i] == '2'))
    {
        while (initialBoard[aiCol][aiRow - i] != oppositeMatcher && aiRow - i >= 0)
        {
            if (initialBoard[aiCol][aiRow - i] == '0' && (initialBoard[aiCol + i][aiRow - i] == '1' || initialBoard[aiCol + i][aiRow - i] == '2'))
            {
                availableSpot++;
            }
            if (initialBoard[aiCol][aiRow - i] == matcher)
            {
                aiPiece++;
            }
            i++;
        }
    }
    if (initialBoard[aiCol][aiRow + 1] == '0' && (aiPiece + availableSpot + 1 >= 4) && (aiRow + 1 <= 6))
    {
        return 20;
    }
    else if (initialBoard[aiCol][aiRow + 1] == oppositeMatcher && (aiPiece + availableSpot >= 4) && (aiRow - 1 >= 0))
    {
        return -300;
    }
}

int connectFour::connectFourHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol)
{
    if (upConnect4(initialBoard, aiCol, aiRow))
    {
        return 10000;
    }
    if (rightConnect4(initialBoard, aiCol, aiRow))
    {
        return 10000;
    }
    if (uprightConnect4(initialBoard, aiCol, aiRow))
    {
        return 10000;
    }
    if (upleftConnect4(initialBoard, aiCol, aiRow))
    {
        return 10000;
    }
    if (leftConnect4(initialBoard, aiCol, aiRow))
    {
        return 10000;
    }
    return 0;
}
int connectFour::centerHeurstic(char captureMove)
{
    switch (captureMove)
    {
    case 'a':
        return 2;
    case 'b':
        return 5;
    case 'c':
        return 10;
    case 'd':
        return 30;
    case 'e':
        return 10;
    case 'f':
        return 5;
    case 'g':
        return 2;
    default:
        return 99;
    }
}
char connectFour::evaluateGame(char aiColor)
{
    int aiRow, aiCol = 0;
    char initialBoard[6][7];
    int max = 0;
    int total = 0;
    char captureMove;
    char finalDecision;
    deque<char> aiMoves;
    char matcher;
    char oppositeMatcher;
    if (aiColor == 'r')
    {
        matcher = '2';
        oppositeMatcher = '1';
    }
    else
    {
        matcher = '1';
        oppositeMatcher = '2';
    }
    aiMoves = generateMoves(theBoard);

    while (!aiMoves.empty())
    {
        memcpy(initialBoard, theBoard, sizeof(initialBoard));
        captureMove = aiMoves.back();
        //cout << "the front is " << captureMove << endl;
        aiMoves.pop_back();
        placePiece(initialBoard, captureMove, aiColor, aiRow, aiCol);

        total += centerHeurstic(captureMove);
        total += connectFourHeuristic(initialBoard, aiRow, aiCol);
        total += rightHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += downHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += leftHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);

        total += upRightHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += upLeftHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += downLeftHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += downRightHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);

        total += specialCaseLeftHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += calculateDefenseof2Heuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);
        total += specialCaseRightHeuristic(initialBoard, aiRow, aiCol, aiColor, matcher, oppositeMatcher);

        if (total > max)
        {
            max = total;
            finalDecision = captureMove;
        }
        total = 0;
    }
    //memcpy(&initialBoard, &theBoard, sizeof(theBoard));

    return finalDecision;
}

int connectFour::calculateDefenseof2Heuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher)
{
    int i = 1;
    int counter = 0;
    while (initialBoard[aiCol][aiRow + i] == oppositeMatcher && aiRow + i <= 6)
    {
        counter++;
        i++;
    }
    if (counter >= 2)
    {
        return 500;
    }

    i = 1;
    counter = 0;
    while (initialBoard[aiCol][aiRow - i] == oppositeMatcher && aiRow - i >= 0)
    {
        counter++;
        i++;
    }
    if (counter >= 2)
    {
        return 500;
    }

    i = 1;
    counter = 0;
    while (initialBoard[aiCol + i][aiRow] == oppositeMatcher && aiCol + i <= 6)
    {
        counter++;
        i++;
    }
    if (counter >= 2)
    {
        return 500;
    }
}
void connectFour::AiPlay()
{
    char color = askColor(); //color player wants to play a
    askSoloName(color);
    deque<char> aiMoves;
    char aiColor;
    while (color == 'y' && gameOver == false)
    {
        aiColor = 'r';
        displayBoard();
        askplayerOne(moveNumber);
        moveNumber++;
        //Up until here is all the Human players move

        //aiMoves = generateMoves();
        char done = evaluateGame(aiColor);
        checkValid(done, moveNumber);
        moveNumber++;

        //displayBoard();
        //break;
        //displayBoard();
        //askplayerTwo(moveNumber);
        //moveNumber++;
    }
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
        gameOver = checkGame();

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
        else
        {
            displayBoard();
            askplayerTwo(moveNumber);
            moveNumber++;
            gameOver = checkGame();

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
        if (checkDown(tolower(choice), moveNumber))
        {
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

char connectFour::getCharRow(int row)
{
    switch (row)
    {
    case 0:
        return 'a';
    case 1:
        return 'b';
    case 2:
        return 'c';
    case 3:
        return 'd';
    case 4:
        return 'e';
    case 5:
        return 'f';
    case 6:
        return 'g';
    default:
        return 'Q';
    }
}

//************************************************************************
// Function: checkDown(player 1/2 choice, #of moves made)
// Purpose:  algorithm to figure out if the move is available or not
//************************************************************************
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
            usleep(250000);
        }
        cout << string(50, '\n');
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
            usleep(250000);
        }
        cout << string(50, '\n');
        theBoard[tmpCol][tmpRow] = '2';
    }
    return true;
}

//************************************************************************
// Function: checkGame()
// Purpose:  checking if either player has won the game, by evaluating each cell
//************************************************************************
bool connectFour::checkGame()
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (upConnect4(theBoard, i, j))
            {
                return true;
            }
            else if (rightConnect4(theBoard, i, j))
            {
                return true;
            }
            else if (uprightConnect4(theBoard, i, j))
            {
                return true;
            }
            else if (upleftConnect4(theBoard, i, j))
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

bool connectFour::leftConnect4(char aBoard[6][7], int tmpCol, int tmpRow)
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
        --yelRow;
    }

    while (aBoard[redCol][redRow] == '2' && redRow <= 6)
    {
        redCounter++;
        --redRow;
    }

    if (redCounter == 4 || yellowCounter == 4)
    {
        return true;
    }
    return false;
}