/*
Name : Babacar Ndoye
Personal Project
*/
#include <iomanip> // std::setw
#include <fstream>
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
  void playerAiRedWin(bool gameOver, char aiColor, char humanColor, string name);
  void playerAiYellowWin(bool gameOver, char aiColor, char humanColor, string name);

  //Game Finished States
  bool askRematch();
  bool askgameLog();
  void checkLog();
  char askSwap();
  void swapRoles(char swap);
  void resetAll();
  void printResults();

  //User Specific Functions
  void playerOneWin(bool gameOver, bool againstAi);
  void playerTwoWin(bool gameOver, bool againstAi);
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

  //Game State Patterns
  bool isGameOver(char (&aBoard)[6][7]);
  bool checkTie(char aBoard[6][7], bool isMinimax);

  //Move Association
  int getRow(char choice);
  bool checkValidMove(char choice, int moveNumber);
  bool checkDown(char aBoard[6][7], char choice);
  void dropPiece(char (&aBoard)[6][7], char choice, int moveNumber);
  void simulatePieceDrop(char aBoard[6][7], int aCol, int aRow, char aPlayer);

private:
  static bool initialized;
  ofstream myfile;

  bool gameOver;
  int row;
  int column;
  int moveNumber;

  string playeroneName;
  string playertwoName;
  vector<char> availableMoves;
  vector<pair<string, char> > moveLog;
  char theBoard[6][7];
};
