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
//************************************************************************
// Function: checkPlayerOne(gameOver)
// Purpose:  This is basically generating output for a arbritary playerOne
//
//************************************************************************
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
//************************************************************************
// Function: checkPlayerTwo(gameOver)
// Purpose:  This is basically generating output for a arbritary playerTwo
//
//************************************************************************
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
//************************************************************************
// Function: checkPlayerAiRed(gameOver, ais Color , humans Color, the name of the human)
// Purpose:  Generating output but also figuring out if the ai is playerTwo(Red Color)
//
//************************************************************************
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

//************************************************************************
// Function: checkPlayerAiYellow(gameOver, ais Color , humans Color, the name of the human)
// Purpose:  Generating output but also figuring our of the ai is playerOne(Yellow Color)
//
//************************************************************************
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
//************************************************************************
// Function: checkTie()
// Purpose:  To determine if the game is in a tie state
//
// In the askRematch if statemnts its important to add
// playeroneName = playeroneName + "'s Turn: ", because when a player wins
// I rip the "'s Turn: " part off so if that player does win I add it back
// and set it back to its default then proceed to swap
//************************************************************************
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

//************************************************************************
// Function: giveScoreLeftDiag(aBoard, aiColor, char humanColor)
// Purpose: scoring purpose
//
// This functions works by figuring our every possible upLeft diagnoal there is
// in the current game by collecting every 4 pieces and depening on the number of aiPieces or
// human pieces the AI notices and returns a score
//************************************************************************
int connectFour::giveScoreLeftDiag(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;
    string upLeftString;
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            upLeftString = "";
            if (isupLeftDiag(aBoard, i, j))
            {
                upLeftString += aBoard[i][j];
                upLeftString += aBoard[i - 1][j - 1];
                upLeftString += aBoard[i - 2][j - 2];
                upLeftString += aBoard[i - 3][j - 3];

                int aiPieces = countMyPieces(upLeftString, aiColor);
                int emptySpots = countMyPieces(upLeftString, '0');
                int humanPieces = countMyPieces(upLeftString, humanColor);
                score += scoreMetric(aiPieces, emptySpots, humanPieces);
            }
        }
    }
    return score;
}

//************************************************************************
// Function: giveScoreRightDiag(aBoard, aiColor, char humanColor)
// Purpose: scoring purpose
//
// This functions works by figuring our every possible upRight diagnoal there is
// in the current game by collecting every 4 pieces and depening on the number of aiPieces or
// human pieces the AI notices and returns a score
//************************************************************************
int connectFour::giveScoreRightDiag(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;
    string upRightString;
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            upRightString = "";
            if (isupRightDiag(aBoard, i, j))
            {
                upRightString += aBoard[i][j];
                upRightString += aBoard[i - 1][j + 1];
                upRightString += aBoard[i - 2][j + 2];
                upRightString += aBoard[i - 3][j + 3];

                int aiPieces = countMyPieces(upRightString, aiColor);
                int emptySpots = countMyPieces(upRightString, '0');
                int humanPieces = countMyPieces(upRightString, humanColor);
                score += scoreMetric(aiPieces, emptySpots, humanPieces);
            }
        }
    }
    return score;
}

//************************************************************************
// Function: isupLeftDiag(aBoard, column, row)
// Purpose: To Prevent a seg fault
//
// To help prevent a seg fault i made a helper function to determine if it
// was possible to go upleft
//************************************************************************
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

//************************************************************************
// Function: isupRightDiag(aBoard, column, row)
// Purpose: To Prevent a seg fault
//
// To help prevent a seg fault i made a helper function to determine if it
// was possible to go upRight
//************************************************************************
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

//************************************************************************
// Function: scoreMetric
// Purpose: The AI needs to know whats a "good" or "bad" move, so you must give
// weights to the most threatening possiblities such as the following:
//
//  if you can potential have connect4 (400) : Highest Value (most important)
//  if you can potential have connect3 (200) : Highest Value (less important but still priority)
//  if you can potential have connect2 (100) : Highest Value (less important but still priority)
//  if your opponent has connect3 (-300) : Keep on making moves until you find it(the negative is very important)
//************************************************************************
int connectFour::scoreMetric(int aiPieces, int emptySpots, int humanPieces)
{
    int score = 0;

    if (aiPieces == 3 && emptySpots == 1)
    {
        score += 7;
    }
    else if (aiPieces == 2 && emptySpots == 2)
    {
        score += 2;
    }
    if (humanPieces == 3 && emptySpots == 1)
    {
        score -= 95;
    }
    return score;
}
//************************************************************************
// Function: giveScoreHori(aBoard, aiColor, char humanColor)
// Purpose: scoring purpose
//
// This functions works by figuring our every possible horizontal there is
// in the current game by collecting every 4 pieces and depening on the number of aiPieces or
// human pieces the AI notices and returns a score
//************************************************************************
int connectFour::giveScoreHori(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;
    string colString = "";

    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            colString += aBoard[i][j];
        }

        int k = 0;
        string seperateByFour = "";
        while (k < 4)
        {
            seperateByFour += colString[k];
            seperateByFour += colString[k + 1];
            seperateByFour += colString[k + 2];
            seperateByFour += colString[k + 3];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);
            score += scoreMetric(aiPieces, emptySpots, humanPieces);

            seperateByFour = "";
            k++;
        }
        colString = "";
    }
    return score;
}
//************************************************************************
// Function: giveScoreCenter(aBoard, aiColor, char humanColor)
// Purpose: scoring purpose
//
// This part is a bit of tricky but to give the Ai a boost to make the move in the center
// seeing that its the best move. So for every piece that matches the AI that can be a better move
// However I have to think theres a more elegant way of doing this
//************************************************************************
int connectFour::giveScoreCenter(char aBoard[6][7], char aiColor, char humanColor)
{
    int score = 0;
    int counter = 0;
    for (int i = 0; i < column; ++i)
    {
        if (aBoard[i][3] == aiColor)
        {
            counter++;
        }
    }
    score += (counter + 1) * 99;
    return score;
}

//************************************************************************
// Function: whoWon(aBoard, whoisWho(human or AI))
// Purpose: figuring out who won the game
//
// The reason I made this function even though I have like 40 checkConnect4 functions is because
// all of those were ambiguous and werent really checking is a particular individual won but rather if anyone
// won...instead of changing the whole structure of the program and since im lazy I just made a thing where I just figure out
// who won the game(human or ai )
//************************************************************************
bool connectFour::whoWon(char aBoard[6][7], char playerPiece)
{
    //Horizontal Checker
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row - 3; ++j)
        {
            if (aBoard[i][j] == playerPiece && aBoard[i][j + 1] == playerPiece && aBoard[i][j + 2] == playerPiece && aBoard[i][j + 3] == playerPiece)
            {
                return true;
            }
        }
    }

    //Vertical Checker
    for (int i = 0; i < column - 3; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            if (aBoard[i][j] == playerPiece && aBoard[i + 1][j] == playerPiece && aBoard[i + 2][j] == playerPiece && aBoard[i + 3][j] == playerPiece)
            {
                return true;
            }
        }
    }

    //Upleft Checker
    for (int i = 3; i < column; ++i)
    {
        for (int j = 3; j < row; ++j)
        {
            if (aBoard[i][j] == playerPiece && aBoard[i - 1][j - 1] == playerPiece && aBoard[i - 2][j - 2] == playerPiece && aBoard[i - 3][j - 3] == playerPiece)
            {
                return true;
            }
        }
    }

    //UpRight Checker
    for (int i = 3; i < column; ++i)
    {
        for (int j = 0; j < row - 3; ++j)
        {
            if (aBoard[i - 1][j + 1] == playerPiece && aBoard[i - 2][j + 2] == playerPiece && aBoard[i - 3][j + 3] == playerPiece && aBoard[i - 3][j + 3] == playerPiece)
            {
                return true;
            }
        }
    }
    return false;
}

//************************************************************************
// Function: getScoreOf(aBoard, aiColor, char humanColor)
// Purpose: instead of repeating code everywhere I just made it generalized here
// Also the base case for the minimax function
//************************************************************************
int connectFour::getScoreOf(char aBoard[6][7], char aiColor, int humanColor)
{
    int score = 0;
    score += giveScoreCenter(aBoard, aiColor, humanColor);
    score += giveScoreHori(aBoard, aiColor, humanColor);
    score += giveScoreVert(aBoard, aiColor, humanColor);
    score += giveScoreLeftDiag(aBoard, aiColor, humanColor);
    score += giveScoreRightDiag(aBoard, aiColor, humanColor);

    return score;
}
//************************************************************************
// Function: lookAhead(aBoard, #how many moves ahead you want to see, aiColor, humanColor, are you the AI? )
// Purpose: scoring purpose
// Sources : https://en.wikipedia.org/wiki/Minimax#Pseudocode
// Sources : A lot Tic Tac Toe Minimax examples
//
// The concept of MINIMAX(lookAhead) is basically alternating between players with a evaluation function
// Things to Note:
//
// The point is to find the best possible moves for either player some things to note though:
// 1. aiPlayer is the maximizing player who always looks for the highest score
// 2. humanPlayer is the minimizing player who always looks for the smallest score
// 3. This process is very clever because you always assume your opponent will play the best
//    and if they don't thats where the ai gains an advantage.
// 4. There are a lot of variations such as (negamax) but as long as you follow this rule set you should be ok

// BIG NOTE: notice how in the WhoWon funtion you return a large number(1000000000)
// and why it isnt identical to the number in the maximizing or minimizing player
// The reason this is because when I would play the AI at certain moments it would halt because it would
// know that it was about to lose and not make a move so you have to always make sure it makes a move so you have to
// reduce or add a 0.
//************************************************************************
pair<char, int> connectFour::lookAhead(char aBoard[6][7], int depth, char aiColor, char humanColor, bool maximizingPlayer, int mover)
{
    if (depth == 0 || (checkGame(aBoard) == true) || checkTie(aBoard) == true)
    {
        if (depth == 0)
        {
            return make_pair(' ', getScoreOf(aBoard, aiColor, humanColor));
        }
        if (checkGame(aBoard))
        {
            if (whoWon(aBoard, aiColor))
            {
                return make_pair(' ', 1000000000);
            }
            else if (whoWon(aBoard, humanColor))
            {
                return make_pair(' ', -100000000);
            }
            else if (checkTie(aBoard))
            {
                return make_pair(' ', 0);
            }
        }
    }
    char fakeBoard[6][7];
    pair<char, int> answer;

    if (maximizingPlayer)
    {

        int largestValue = -1000000000;
        char bestRow = ' ';

        for (int i = availableMoves.size() - 1; i >= 0; --i)
        {
            memcpy(fakeBoard, aBoard, sizeof(fakeBoard));
            if (checkDown(fakeBoard, tolower(availableMoves[i])))
            {
                dropAiPiece(fakeBoard, availableMoves[i], mover);
                answer = lookAhead(fakeBoard, depth - 1, aiColor, humanColor, !maximizingPlayer, mover + 1);

                if (answer.second > largestValue)
                {
                    bestRow = availableMoves[i];
                    largestValue = answer.second;
                }
            }
        }
        return make_pair(bestRow, largestValue);
    }
    else if (!maximizingPlayer)
    {
        int smallestValue = 100000000;
        char bestColumn = ' ';

        for (int i = availableMoves.size() - 1; i >= 0; --i)
        {
            memcpy(fakeBoard, aBoard, sizeof(fakeBoard));
            if (checkDown(fakeBoard, tolower(availableMoves[i])))
            {
                dropAiPiece(fakeBoard, availableMoves[i], mover);
                answer = lookAhead(fakeBoard, depth - 1, aiColor, humanColor, !maximizingPlayer, mover + 1);

                if (answer.second < smallestValue)
                {
                    bestColumn = availableMoves[i];
                    smallestValue = answer.second;
                }
            }
        }
        return make_pair(bestColumn, smallestValue);
    }
}
//************************************************************************
// Function: countMyPieces(anystring, a human color or ai color(red or yellow))
// Purpose: scoring purpose
//
// Every horizantal,vertical... angle it comes in packages like
// 1012
// In the case the human player goes first.
// 1 = Human ; 2 = Ai ; 0 = Empty Spot
// I felt like a helper function would be needed instead of copying in of each the
// functions such as (giveScoreVert or giveScoreHori) so now I can input a string
// and what character Im looking for it will find how many instaces it has
//************************************************************************
int connectFour::countMyPieces(string matcher, char anyPiece)
{
    int counter = 0;
    for (int b = 0; b < matcher.length(); ++b)
    {
        if (matcher[b] == anyPiece)
        {
            counter++;
        }
    }
    return counter;
}
//************************************************************************
// Function: giveScoreVert(aBoard, aiColor, char humanColor)
// Purpose: scoring purpose
//
// This functions works by figuring our every possible Vertical there is
// in the current game by collecting every 4 pieces and depening on the number of aiPieces or
// human pieces the AI notices and returns a score
//************************************************************************
int connectFour::giveScoreVert(char aBoard[6][7], char aiColor, char humanColor)
{

    int score = 0;
    string rowString = "";

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            rowString += aBoard[j][i];
        }

        int k = 0;
        string seperateByFour = "";
        while (k < 4)
        {
            seperateByFour += rowString[k];
            seperateByFour += rowString[k + 1];
            seperateByFour += rowString[k + 2];
            seperateByFour += rowString[k + 3];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);

            score += scoreMetric(aiPieces, emptySpots, humanPieces);

            seperateByFour = "";
            k++;
        }
        rowString = "";
    }

    return score;
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
            int mover = moveNumber;
            pair<char, int> answer;
            answer = lookAhead(theBoard, 5, aiColor, humanColor, true, mover);
            char move = answer.first;

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
        playeroneName = "Ai's Turn: ";
        playertwoName = name + "'s Turn: ";

        int mover = moveNumber;
        pair<char, int> answer;
        answer = lookAhead(theBoard, 5, aiColor, humanColor, true, mover);
        char move = answer.first;
        dropPiece(theBoard, move, moveNumber);
        moveNumber++;
        gameOver = checkGame(theBoard);
        checkPlayerAiYellow(gameOver, aiColor, humanColor, name);

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
            playeroneName = playeroneName + "'s Turn: ";
            char swap = askSwap();
            swapRoles(swap);
            resetAll();
            aiPlay(humanColor, aiColor, name);
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
    return (choice - '0') - 49;
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
//************************************************************************
// Function: dropAiPiece(aBoard, char , char humanColor)
// Purpose: scoring purpose
//
// This function is a simulation for the ai that drops a piece in the copy
// of the real board its the same as the same dropPiece function but this is
// designated for the AI
//************************************************************************
void connectFour::dropAiPiece(char (&aBoard)[6][7], char choice, int mover)
{
    int tmpRow = getRow(choice);
    int tmpCol = 5;

    while (aBoard[tmpCol][tmpRow] == '1' || aBoard[tmpCol][tmpRow] == '2')
    {
        tmpCol--;
    }
    if (mover % 2 == 0)
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
