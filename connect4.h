
#include <termios.h>
#include <unistd.h>
#include <string>

using namespace std;

class connectFour
{
  public:
    connectFour();

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

  private:
    bool gameOver;
    int row;
    int column;
    int moveNumber;

    string playeroneName;
    string playertwoName;
    char theBoard[6][7];
};
