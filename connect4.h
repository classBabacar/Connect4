/*
Name : Babacar Ndoye
Class Name : connectFour
Purpose : To make life simple instead of putting it all in the main
*/
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <stdio.h> /* printf, NULL */
#include <time.h>
#include <vector>

using namespace std;

class connectFour
{
public:
  connectFour();

  //Game Finished Functions
  void aiPlay(char aiColor, char humanColor, string name);
  bool askRematch();
  char askSwap();
  void swapRoles(char swap);
  void resetAll();

  //UserSpecificFunctions
  void checkPlayerOne(bool gameOver);
  void checkPlayerTwo(bool gameOver);
  void checkPlayerAiRed(bool gameOver, char aiColor, char humanColor, string name);
  void checkPlayerAiYellow(bool gameOver, char aiColor, char humanColor, string name);
  bool checkTie(char aBoard[6][7]);

  //Ai Helper Functions
  int giveScoreHori(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreVert(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreLeftDiag(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreRightDiag(char aBoard[6][7], char aiColor, char humanColor);
  int giveScoreCenter(char aBoard[6][7], char aiColor, char humanColo);
  bool isupLeftDiag(char aboard[6][7], int aiColumn, int aiRow);
  bool isupRightDiag(char aboard[6][7], int aiColumn, int aiRow);
  int scoreMetric(int aiPieces, int emptySpots, int humanPieces);
  bool whoWon(char aBoard[6][7], char playerPiece);
  pair<char, int> lookAhead(char aBoard[6][7], int depth, char aiColor, char humanColor, bool maximizingPlayer, int mover);
  int getScoreOf(char aBoard[6][7], char aiColor, int humanColor);
  void dropAiPiece(char (&aBoard)[6][7], char choice, int mover);
  int countMyPieces(string matcher, char anyPiece);

  //Game Dependencies
  void askName();
  void play(int players);
  void displayBoard();
  bool checkGame(char aBoard[6][7]);
  bool upConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool rightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool uprightConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool upleftConnect4(char aBoard[6][7], int tmpCol, int tmpRow);
  bool checkValid(char choice, int moveNumber);
  bool checkDown(char aBoard[6][7], char choice);
  void dropPiece(char (&aBoard)[6][7], char choice, int moveNumber);
  int getRow(char choice);
  char playeroneChoice();
  char playertwoChoice();
  void askplayerOne(int moveNumber);
  void askplayerTwo(int moveNumber);

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
