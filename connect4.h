/*
Name : Babacar Ndoye
Class Name : connectFour
Purpose : To make life simple instead of putting it all in the main
*/
#include <string>
#include <iostream>
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

  bool upConnect4(int tmpCol, int tmpRow);
  bool rightConnect4(int tmpCol, int tmpRow);
  bool uprightConnect4(int tmpCol, int tmpRow);
  bool upleftConnect4(int tmpCol, int tmpRow);

private:
  bool gameOver;
  int row;
  int column;
  int moveNumber;

  string playeroneName;
  string playertwoName;
  char theBoard[6][7];
};
