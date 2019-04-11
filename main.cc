#include <iostream>
#include "connect4.h"
#include "colors.h"

using namespace std;

//************************************************************************
// Function: displayIntro()
// Purpose:  showing the people what they came here for....the logo
//************************************************************************
int displayIntro();
int main()
{
   int players = displayIntro();

   if (players == 2)
   {
      connectFour obj;
      obj.play(players);
   }
   else
   {
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
