/*
Name : Babacar Ndoye
Purpose : To enjoy programming...THIS IS NOT A SCHOOL PROJECT
*/
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include "stdio.h" /* printf, NULL */
#include <time.h>
#include <vector>

using namespace std;

class connectFour
{
public:
  connectFour();

  //Game Dependencies (Game Loop for Player vs Player)
  void askName();
  void play(int players);
  void displayBoard();

  //Game Loop for AI
  void aiPlay(char aiColor, char humanColor, string name);

  //Ai Winning States
  void ifPlayerAiRedWin(bool gameOver, char aiColor, char humanColor, string name);
  void ifPlayerAiYellowWin(bool gameOver, char aiColor, char humanColor, string name);

  //Game Finished States
  bool askRematch();
  char askSwap();
  void swapRoles(char swap);
  void resetAll();

  //User Specific Functions
  void ifPlayerOneWin(bool gameOver);
  void ifPlayerTwoWin(bool gameOver);
  void askplayerOneMove(int moveNumber);
  void askplayerTwoMove(int moveNumber);
  char getplayeroneChoice();
  char getplayertwoChoice();

  //AI Heuristic Functions
  int countMyPieces(string matcher, char anyPiece);
  int giveScoreHori(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreVert(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreLeftDiag(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreRightDiag(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreCenter(char aBoard[6][7], char aiColor, char humanColo);
  int scoreMetric(int aiPieces, int emptySpots, int humanPieces);

  // AI Helper Functions
  void copyMe(char (&fakeBoard)[6][7], char (&aBoard)[6][7]);
  bool whoWon(char (&aBoard)[6][7], char playerPiece);
  void dropAiPiece(char (&aBoard)[6][7], char choice, int mover);

  // Important Minimax
  pair<char, int> lookAhead(char (&aBoard)[6][7], int depth, char aiColor, char humanColor, bool maximizingPlayer, int mover);
  int getScoreOf(char aBoard[6][7], char aiColor, int humanColor);

  //Winning Connect4 Patterns
  bool isGameOver(char aBoard[6][7]);
  bool upConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool rightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool uprightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool upleftConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool checkTie(char aBoard[6][7], bool isMinimax);

  //Move Association
  int getRow(char choice);
  bool checkValidMove(char choice, int moveNumber);
  bool checkDown(char aBoard[6][7], char choice);
  void dropPiece(char (&aBoard)[6][7], char choice, int moveNumber);

private:
  bool gameOver;
  int row;
  int column;
  int moveNumber;

  string playeroneName;
  string playertwoName;
  vector<char> availableMoves;
  char theBoard[6][7];
};
