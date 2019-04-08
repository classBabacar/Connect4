#include "game.h"
#include "piece.h"
#include <termios.h>
#include <unistd.h>

class connectFour
{
  public:
    connectFour();
    bool play(int players);
    void displayBoard();

    void askplayerOne();
    void askPlayerTwo();

  private:
    bool gameOver;
    int row;
    int column;
    int moveNumber;
    char theBoard[6][7];
};
