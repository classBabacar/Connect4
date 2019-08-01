#include "colors.h"
#include "connect4.h"

// This is to stop the stack from repeating output
bool connectFour::initialized = true;

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
// Purpose:  asks a user would they like a rematch
//************************************************************************
bool connectFour::askRematch()
{
    cout << "Would you like a rematch? (Y/N): ";
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
// Purpose:  would yellow like to switch with red or vice versa
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
// Purpose:  changes everything back to it's default
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
// Function: checkLog()
// Purpose:  To eliminate code repitition
//************************************************************************
void connectFour::checkLog()
{
    if (initialized)
    {
        if (askgameLog())
        {
            printResults();
        }
        cout << WHITE << "Thank you for playing" << endl;
    }
}

//************************************************************************
// Function: askSwap()
// Purpose:  packaging question to ask user to swap
//************************************************************************
char connectFour::askSwap()
{
    cout << "Would you like to swap on who goes first? (Y/N): ";
    char swap;
    cin >> swap;
    swap = tolower(swap);
    return swap;
}

//************************************************************************
// Function: playerOneWin(gameOver, areyouagainstAi)
// Purpose:  In the case playerOne(Yellow) wins what to do
//************************************************************************
void connectFour::playerOneWin(bool gameOver, bool againstAi)
{

    displayBoard();
    playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
    cout << YELLOW << playeroneName << "...Wins" << WHITE << endl;
    moveLog.push_back(make_pair(playeroneName, 'y'));

    if (askRematch())
    {
        playeroneName = playeroneName + "'s Turn: ";
        char swap = askSwap();
        resetAll();
        if (againstAi == false)
        {
            swapRoles(swap);
            play(3);
        }
        else if (swap == 'y' && againstAi == true)
        {
            aiPlay('1', '2', playeroneName.substr(0, playeroneName.length() - 9));
        }
        else if (swap != 'y' && againstAi == true)
        {
            aiPlay('2', '1', playeroneName.substr(0, playeroneName.length() - 9));
        }
    }
    else
    {
        checkLog();
    }
}

//************************************************************************
// Function: playerTwoWin(gameOver,, areyouagainstAi)
// Purpose:  In the case playerTwo(Red) wins what to do
//************************************************************************
void connectFour::playerTwoWin(bool gameOver, bool againstAi)
{
    displayBoard();
    playertwoName = playertwoName.substr(0, playertwoName.length() - 9);
    cout << RED << playertwoName << "...Wins" << WHITE << endl;
    moveLog.push_back(make_pair(playertwoName, 'r'));

    if (askRematch())
    {
        playertwoName = playertwoName + "'s Turn: ";
        char swap = askSwap();
        resetAll();
        if (againstAi == false)
        {
            swapRoles(swap);
            play(3);
        }
        else if (swap == 'y' && againstAi == true)
        {
            aiPlay('2', '1', playertwoName.substr(0, playertwoName.length() - 9));
        }
        else if (swap != 'y' && againstAi == true)
        {
            aiPlay('1', '2', playertwoName.substr(0, playertwoName.length() - 9));
        }
    }
    else
    {
        checkLog();
    }
}

//************************************************************************
// Function: playerAiRedWin(gameOver, ais Color , humans Color, the name of the human)
// Purpose:  In the case playerTwo(Red) is an AI and won..what to do
//************************************************************************
void connectFour::playerAiRedWin(bool gameOver, char aiColor, char humanColor, string name)
{
    displayBoard();
    playertwoName = playertwoName.substr(0, playertwoName.length() - 9);
    cout << RED << playertwoName << "...Wins" << WHITE << endl;
    moveLog.push_back(make_pair(playertwoName, 'r'));

    if (askRematch())
    {
        playertwoName = playertwoName + "'s Turn: ";
        char swap = askSwap();
        resetAll();
        if (swap == 'y')
        {
            aiPlay('1', '2', name);
        }
        else
        {
            aiPlay('2', '1', name);
        }
    }
    else
    {
        checkLog();
    }
}

//************************************************************************
// Function: playerAiYellowWin(gameOver, ais Color , humans Color, the name of the human)
// Purpose:  In the case playerOne(Yellow) is an AI and won..what to do
//************************************************************************
void connectFour::playerAiYellowWin(bool gameOver, char aiColor, char humanColor, string name)
{
    displayBoard();
    playeroneName = playeroneName.substr(0, playeroneName.length() - 9);
    cout << YELLOW << playeroneName << "...Wins" << WHITE << endl;
    moveLog.push_back(make_pair(playeroneName, 'y'));

    if (askRematch())
    {
        playeroneName = playeroneName + "'s Turn: ";
        char swap = askSwap();
        resetAll();
        if (swap == 'y')
        {
            aiPlay('2', '1', name);
        }
        else
        {
            aiPlay('1', '2', name);
        }
    }
    else
    {
        checkLog();
    }
}

//************************************************************************
// Function: checkTie()
// Purpose:  To determine if the game is in a tie state
//************************************************************************
bool connectFour::checkTie(char aBoard[6][7], bool isMinimax)
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
    //This part is so minimax does print the statement everytime
    if (redCount + yellowCount == 42 && isMinimax == true)
    {
        return true;
    }
    else if (redCount + yellowCount == 42 && isMinimax == false)
    {
        cout << RED << " IT'S A " << YELLOW << "TIE" << endl;
        return true;
    }
    else
        return false;
}

//************************************************************************
// Function: play(#number of players 1 or 2)
// Purpose:  Game loop specificially for player v. player
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
        askplayerOneMove(moveNumber);
        moveNumber++;

        if (isGameOver(theBoard))
        {
            playerOneWin(true, false);
            gameOver = true;
        }
        else
        {
            displayBoard();
            askplayerTwoMove(moveNumber);
            moveNumber++;
            if (isGameOver(theBoard))
            {
                playerTwoWin(true, false);
                gameOver = true;
            }
        }

        if (checkTie(theBoard, false) && gameOver != true)
        {
            moveLog.push_back(make_pair("", 't'));
            displayBoard();
            if (askRematch())
            {
                char swap = askSwap();
                if (swap != 'y')
                {
                    swapRoles(swap);
                    resetAll();
                }
                play(3);
            }
            else
            {
                checkLog();
                gameOver = true;
            }
        }
    }
}

//************************************************************************
// Function: askgameLog()
// Purpose: packaging user input
//************************************************************************
bool connectFour::askgameLog()
{
    cout << "Would you like to recieve a game log? (Y/N): ";
    char rsp;
    cin >> rsp;
    rsp = tolower(rsp);

    if (rsp == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//************************************************************************
// Function: printResults()
// Purpose:  Algorithm to display game log
//************************************************************************
void connectFour::printResults()
{
    myfile.open("result.txt");
    int internalCounter = 0;
    int indent = 3;
    int matchCounter = 1;

    myfile << "Yellow" << setw(5) << "Red" << endl;
    for (int i = 0; i < moveLog.size(); ++i)
    {
        if (moveLog[i].second == 'r' || moveLog[i].second == 'y' || moveLog[i].second == 't')
        {
            if (moveLog[i].second == 'r')
            {
                myfile << "Match #" << matchCounter << " - (" << moveLog[i].first << ") Red Won this game" << endl;
                myfile << endl;
            }
            else if (moveLog[i].second == 'y')
            {
                myfile << endl;
                myfile << "Match #" << matchCounter << " - (" << moveLog[i].first << ") Yellow Won this game" << endl;
                myfile << endl;
            }
            else if (moveLog[i].second == 't')
            {
                myfile << "Match #" << matchCounter << " - This game was a tie" << endl;
                myfile << endl;
            }
            if (i + 1 < moveLog.size())
            {
                myfile << "Yellow" << setw(5) << "Red" << endl;
            }
            internalCounter = 0;
            indent = 3;
            matchCounter++;
        }
        else
        {
            myfile << setw(indent) << moveLog[i].second;
            indent += 4;
            internalCounter++;
            if (internalCounter % 2 == 0)
            {
                myfile << endl;
                indent = 3;
                internalCounter = 0;
            }
        }
    }

    myfile << endl;
    initialized = false;
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
    string seperateByFour;
    for (int i = 3; i < column; ++i)
    {
        for (int j = 3; j < row; ++j)
        {
            seperateByFour = "";

            seperateByFour += aBoard[i][j];
            seperateByFour += aBoard[i - 1][j - 1];
            seperateByFour += aBoard[i - 2][j - 2];
            seperateByFour += aBoard[i - 3][j - 3];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);
            score += scoreMetric(aiPieces, emptySpots, humanPieces);
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
    string seperateByFour;
    for (int i = 3; i < column; ++i)
    {
        for (int j = 0; j < row - 3; ++j)
        {
            seperateByFour = "";

            seperateByFour += aBoard[i][j];
            seperateByFour += aBoard[i - 1][j + 1];
            seperateByFour += aBoard[i - 2][j + 2];
            seperateByFour += aBoard[i - 3][j + 3];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);
            score += scoreMetric(aiPieces, emptySpots, humanPieces);
        }
    }
    return score;
}

//************************************************************************
// Function: scoreMetric
// Purpose: The AI needs to know whats a "good" or "bad" move, so you must give
// weights to the most threatening possiblities such as the following:
//
//
//  if you can potential have connect3 (7) : Highest Value (less important but still priority)
//  if you can potential have connect2 (2) : Highest Value (less important but still priority)
//  if your opponent has connect3 (-95) : Keep on making moves until you find it(the negative is very important)
//************************************************************************
int connectFour::scoreMetric(int aiPieces, int emptySpots, int humanPieces)
{
    int score = 0;

    if (aiPieces == 2 && emptySpots == 2)
    {
        score += 2;
    }
    if (humanPieces == 2 && emptySpots == 2)
    {
        score -= 10;
    }
    else if (humanPieces == 3 && emptySpots == 1)
    {
        score -= 50;
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
    string seperateByFour;
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row - 3; ++j)
        {
            seperateByFour = "";

            seperateByFour += aBoard[i][j];
            seperateByFour += aBoard[i][j + 1];
            seperateByFour += aBoard[i][j + 2];
            seperateByFour += aBoard[i][j + 3];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);
            score += scoreMetric(aiPieces, emptySpots, humanPieces);
        }
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
    score += (counter + 1) * 80;
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
bool connectFour::whoWon(char (&aBoard)[6][7], char playerPiece)
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
            if (aBoard[i][j] == playerPiece && aBoard[i - 1][j + 1] == playerPiece && aBoard[i - 2][j + 2] == playerPiece && aBoard[i - 3][j + 3] == playerPiece)
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
pair<char, int> connectFour::lookAhead(char (&aBoard)[6][7], int depth, char aiColor, char humanColor, bool maximizingPlayer, int mover)
{
    if (depth == 0 || (isGameOver(aBoard) == true) || checkTie(aBoard, true) == true)
    {
        if (isGameOver(aBoard))
        {
            if (whoWon(aBoard, aiColor))
            {
                return make_pair(' ', 10000000);
            }
            else if (whoWon(aBoard, humanColor))
            {
                return make_pair(' ', -10000000);
            }
            else if (checkTie(aBoard, true))
            {
                return make_pair(' ', 0);
            }
        }
        else
        {
            return make_pair(' ', getScoreOf(aBoard, aiColor, humanColor));
        }
    }

    char fakeBoard[6][7];
    pair<char, int> answer;

    if (maximizingPlayer)
    {
        int largestValue = -10000000;
        char bestRow = ' ';

        for (int i = 0; i < availableMoves.size(); ++i)
        {
            copyMe(fakeBoard, aBoard);
            if (checkDown(fakeBoard, tolower(availableMoves[i])))
            {
                dropAiPiece(fakeBoard, availableMoves[i], mover);
                answer = lookAhead(fakeBoard, depth - 1, aiColor, humanColor, false, mover + 1);

                if (get<1>(answer) >= largestValue)
                {
                    bestRow = availableMoves[i];
                    largestValue = get<1>(answer);
                }
            }
        }
        return make_pair(bestRow, largestValue);
    }
    else
    {
        int smallestValue = 10000000;
        char bestColumn = ' ';

        for (int i = 0; i < availableMoves.size(); ++i)
        {
            copyMe(fakeBoard, aBoard);
            if (checkDown(fakeBoard, tolower(availableMoves[i])))
            {
                dropAiPiece(fakeBoard, availableMoves[i], mover);
                answer = lookAhead(fakeBoard, depth - 1, aiColor, humanColor, true, mover + 1);

                if (get<1>(answer) <= smallestValue)
                {
                    bestColumn = availableMoves[i];
                    smallestValue = get<1>(answer);
                }
            }
        }
        return make_pair(bestColumn, smallestValue);
    }
}

//************************************************************************
// Function: copyMe(fakeBoard by reference, actualBoard)
// Purpose: making a replica of the previous board
//************************************************************************
void connectFour::copyMe(char (&fakeBoard)[6][7], char (&aBoard)[6][7])
{
    for (int i = 0; i < column; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            fakeBoard[i][j] = aBoard[i][j];
        }
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
    string seperateByFour;
    for (int i = 0; i < column - 3; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            seperateByFour = "";

            seperateByFour += aBoard[i][j];
            seperateByFour += aBoard[i + 1][j];
            seperateByFour += aBoard[i + 2][j];
            seperateByFour += aBoard[i + 3][j];

            int aiPieces = countMyPieces(seperateByFour, aiColor);
            int emptySpots = countMyPieces(seperateByFour, '0');
            int humanPieces = countMyPieces(seperateByFour, humanColor);
            score += scoreMetric(aiPieces, emptySpots, humanPieces);
        }
    }
    return score;
}

//************************************************************************
// Function: aiPlay(char aiColor, char humanColor, string name)
// Purpose: (Player(Yellow) v AI(Red)) or (AI(Yellow) v. Player(Red))
//************************************************************************
void connectFour::aiPlay(char aiColor, char humanColor, string name)
{
    int lookForward = 4;
    while (humanColor == '1' && gameOver == false)
    {
        playeroneName = name + "'s Turn: ";
        playertwoName = "Ai's Turn: ";

        displayBoard();
        askplayerOneMove(moveNumber);
        moveNumber++;

        if (isGameOver(theBoard))
        {
            playerOneWin(true, true);
            gameOver = true;
        }
        else
        {
            pair<char, int> result;
            result = lookAhead(theBoard, lookForward, aiColor, humanColor, true, moveNumber);
            char aiMove = get<0>(result);

            moveLog.push_back(make_pair("", aiMove));
            dropPiece(theBoard, aiMove, moveNumber);
            moveNumber++;

            if (isGameOver(theBoard))
            {
                playerAiRedWin(true, aiColor, humanColor, name);
                gameOver = true;
            }
        }
        if (checkTie(theBoard, false) && gameOver != true)
        {
            moveLog.push_back(make_pair("", 't'));
            displayBoard();
            playertwoName = playertwoName + "'s Turn: ";
            char swap = askSwap();
            resetAll();
            if (swap == 'y')
            {
                aiPlay('1', '2', playeroneName.substr(0, playeroneName.length() - 9));
            }
            else
            {
                aiPlay('2', '1', playeroneName.substr(0, playeroneName.length() - 9));
            }
        }
    }
    while (humanColor == '2' && gameOver == false)
    {
        playeroneName = "Ai's Turn: ";
        playertwoName = name + "'s Turn: ";

        pair<char, int> result;
        result = lookAhead(theBoard, lookForward, aiColor, humanColor, true, moveNumber);
        char aiMove = get<0>(result);

        moveLog.push_back(make_pair("", aiMove));
        dropPiece(theBoard, aiMove, moveNumber);
        moveNumber++;

        if (isGameOver(theBoard))
        {
            playerAiYellowWin(true, aiColor, humanColor, name);
            gameOver = true;
        }
        else
        {
            displayBoard();
            askplayerTwoMove(moveNumber);
            moveNumber++;

            if (isGameOver(theBoard))
            {
                playerTwoWin(true, true);
                gameOver = true;
            }
        }

        if (checkTie(theBoard, false) && gameOver != true)
        {
            moveLog.push_back(make_pair("", 't'));
            displayBoard();
            playeroneName = playeroneName + "'s Turn: ";

            char swap = askSwap();
            resetAll();
            if (swap == 'y')
            {
                aiPlay('2', '1', playertwoName.substr(0, playertwoName.length() - 9));
            }
            else
            {
                aiPlay('1', '2', playertwoName.substr(0, playertwoName.length() - 9));
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
// Function: getplayeroneChoice()
// Purpose:  asks where a arbritary player one wants to go
//************************************************************************
char connectFour::getplayeroneChoice()
{
    cout << YELLOW << playeroneName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}

//************************************************************************
// Function: getplayertwoChoice()
// Purpose:  asks where a arbritrary player two wants to go
//************************************************************************
char connectFour::getplayertwoChoice()
{
    cout << RED << playertwoName << WHITE;
    char choice;
    cin >> choice;

    return choice;
}

//************************************************************************
// Function: askplayerOneMove(#of moves made)
// Purpose:  confirms if players ones move is valid
//************************************************************************
void connectFour::askplayerOneMove(int moveNumber)
{
    char choice = getplayeroneChoice();
    if (!checkValidMove(choice, moveNumber))
    {
        cout << endl;
        displayBoard();
        cout << YELLOW << "Invalid Move....Try again" << YELLOW << endl;
        askplayerOneMove(moveNumber);
    }
}

//************************************************************************
// Function: askplayerTwoMove(#of moves made)
// Purpose:  confirms if player twos move is valid
//************************************************************************
void connectFour::askplayerTwoMove(int moveNumber)
{
    char choice = getplayertwoChoice();
    if (!checkValidMove(choice, moveNumber))
    {
        cout << endl;
        displayBoard();
        cout << RED << "Invalid Move....Try again" << WHITE << endl;
        askplayerTwoMove(moveNumber);
    }
}

//************************************************************************
// Function: checkValidMove(choice from either player 1/2, #of moves made)
// Purpose:  The algorithm to confirm if you are choosing a proper row
//************************************************************************
bool connectFour::checkValidMove(char choice, int MoveNumber)
{
    if (toupper(choice) >= 'A' && 'G' >= toupper(choice))
    {
        if (checkDown(theBoard, tolower(choice)))
        {
            moveLog.push_back(make_pair("", choice));
            dropPiece(theBoard, choice, moveNumber);
            return true;
        }
    }
    return false;
}

//************************************************************************
// Function: simulatePieceDrop(a arbitrary board, a column, a row, whoevers turn)
// Purpose:  The piece drop function where it looks like it might in real life
//************************************************************************
void connectFour::simulatePieceDrop(char aBoard[6][7], int aCol, int aRow, char aPlayer)
{
    int i = 0;
    while (i != aCol)
    {
        aBoard[i][aRow] = aPlayer;
        displayBoard();
        aBoard[i][aRow] = '0';
        i++;
        usleep(250000);
    }
    cout << string(50, '\n');
}

//************************************************************************
// Function: getRow(eithers players choice)
// Purpose:  used to convert their choice into a number to play into board
//************************************************************************
int connectFour::getRow(char choice)
{
    choice = tolower(choice);
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
        simulatePieceDrop(aBoard, tmpCol, tmpRow, '1');
        aBoard[tmpCol][tmpRow] = '1';
    }
    else
    {
        simulatePieceDrop(aBoard, tmpCol, tmpRow, '2');
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
    if (aBoard[0][tmpRow] == '0')
    {
        return true;
    }
    return false;
}

//************************************************************************
// Function: isGameOver()
// Purpose:  checking if either player has won the game, by evaluating each cell
//************************************************************************
bool connectFour::isGameOver(char (&aBoard)[6][7])
{
    if (whoWon(aBoard, '1') || whoWon(aBoard, '2'))
    {
        return true;
    }
    return false;
}
