#include <iostream>
#include <cstdlib>
#include <fstream>

#include "connect4.h"
//#include "

using namespace std;

int main()
{
   //int choice;

   //string restart;
   //string colorSwap;
   cout << "Enter 1 for one player or 2 for two player" << endl;
   int players;
   cin >> players;

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
