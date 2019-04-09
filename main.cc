#include <iostream>
#include <cstdlib>
#include <fstream>

#include "connect4.h"
#include "colors.h"
//#include "

using namespace std;

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
   //ifstream fin;
}
int displayIntro()
{
   cout << "+-----------+" << endl;
   cout << "| Connect " << RED << "4" << WHITE << " |" << endl;
   cout << "+-----------+" << WHITE << endl;

   cout << "Welcome, let's play some connect 4" << endl;
   cout << "Would you like to play against Ai (1) or (2) player vs player " << endl;

   int players;
   cin >> players;

   return players;
}
