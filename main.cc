#include <iostream>
#include "connect4.h"
#include "colors.h"

using namespace std;

//************************************************************************
// Function: displayIntro()
// Purpose:  showing the people what they came here for....the logo
//************************************************************************
int displayIntro();
void askInfo(char &humanColor, char &aiColor, string &name);
int main()
{
   int players = displayIntro();
   connectFour obj;

   if (players == 2)
   {
      obj.play(players);
   }
   else
   {
      char aiColor;
      char humanColor;
      string name;
      cout << "Would you like to be Yellow or Red (y/r)?" << endl;
      cin >> humanColor;
      askInfo(humanColor, aiColor, name);
      obj.aiPlay(aiColor, humanColor, name);
   }
}
void askInfo(char &humanColor, char &aiColor, string &name)
{
   if (tolower(humanColor) == 'y')
   {
      aiColor = '2';    // Red
      humanColor = '1'; //Yellow
      cout << YELLOW << "What's your name? " << endl;
      cin.ignore();
      getline(cin, name);
      cout << WHITE;
   }
   else
   {
      aiColor = '1';
      humanColor = '2';
      cout << RED << "What's your name? " << endl;
      cin.ignore();
      getline(cin, name);
      cout << WHITE;
   }
}
int displayIntro()
{
   cout << YELLOW << "+-----------+" << WHITE << endl;
   cout << "| Connect " << RED << "4" << WHITE << " |" << endl;
   cout << RED << "+-----------+" << WHITE << endl;

   cout << "Welcome, let's play some " << YELLOW << "Connect 4" << WHITE << endl;
   cout << RED << "1) Play against AI" << endl;
   cout << YELLOW << "2) Player vs Player " << WHITE << endl;
   cout << "Choice : ";
   int players;
   cin >> players;

   return players;
}
