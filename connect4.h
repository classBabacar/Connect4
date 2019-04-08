
#include <termios.h>
#include <unistd.h>

class connectFour
{
  public:
    connectFour();
    void play(int players);
    void displayBoard();

    void askplayerOne(int moveNumber);
    //void askPlayerTwo();

    bool checkValid(char choice, int moveNumber);
    bool checkDown(char choice, int moveNumber);
    int getRow(char choice);

  private:
    bool gameOver;
    int row;
    int column;
    int moveNumber;
    char theBoard[6][7];
};
