/*
Name : Babacar Ndoye
Class Name : connectFour
Purpose : To make life simple instead of putting it all in the main
*/

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <deque>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class connectFour
{
public:
  connectFour();

  bool askRematch();
  char askSwap();
  void swapRoles(char swap);
  void resetAll();

  //AI NEEDED FUNCTIONS
  void AiPlay();
  char askColor();
  void askSoloName(char color);
  deque<char> generateMoves(char aBoard[6][7]);
  char getCharRow(int row);
  char evaluateGame(char color);
  void placePiece(char (&initialBoard)[6][7], char move, char color, int &aiRow, int &aiCol);
  int NPiecesIntact(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor);

  //THIS IS ALL THE OFFENSIVE MOVES THE AI CAN MAKE BUT THERE ARE STILL DEFENSIVE MOVES IT NEEDS TO UNDERSTAND
  int connectFourHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol);
  int centerHeurstic(char captureMove);
  //LEFT , RIGHT , UP , DOWN
  int rightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int downHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int upHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int leftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);

  int specialCaseLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int specialCaseRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);

  int upRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int upLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int downLeftHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  int downRightHeuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////MORE AI/////
  int calculateDefenseof2Heuristic(char (&initialBoard)[6][7], int aiRow, int aiCol, char aiColor, char matcher, char oppositeMatcher);
  //
  void askName();
  void play(int players);
  void displayBoard();

  char playeroneChoice();
  char playertwoChoice();

  void askplayerOne(int moveNumber);
  void askplayerTwo(int moveNumber);

  bool checkValid(char choice, int moveNumber);
  bool checkDown(char choice, int moveNumber);
  int getRow(char choice);

  bool checkGame();

  bool upConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool rightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool uprightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool upleftConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool leftConnect4(char aBoard[6][7], int tmpCol, int tmpRow);

private:
  int max;
  int total;

  bool gameOver;
  int row;
  int column;
  int moveNumber;

  deque<char> availableMoves;

  string playeroneName;
  string playertwoName;
  char theBoard[6][7];
};
