# Inspiration 

This is one of my favorite games. Growing up I played this game so much with family and friends I lost a lot to them and that's why I'm kind of obsessed with the game because I hated losing. So I practiced a lot of programming so one day I could make this game and get a rematch!

# Goals
Right now, the game allows for 1v1 play but in the near future I plan to incorporate an AI with the concept of MiniMax **(Complete)**.

# Game Updates
I had to refactor the whole code because if I wanted to incorporate an AI my previous method would not be a suitable starting place but now I believe I am in good condition to implement an AI..see ya soon. I had to refactor some more because I generated the AI but it was difficult to maintain so I needed to change base version. 
- **May 12, 2019** : 
I had to refactor some more by adding functions that were solely for the AI.
- **May 30, 2019** : 
There was a lot of unncessary lines of code that didn't need to be there so the result is reduced code.
Also some changes to the evaluate(scoreMetric) function to make it stronger.
- **June 4, 2019** : 
The minimax function was wrong because I was just passing by value instead of reference so no matter how many depths I increased by it would evaluate only one board state.
- **July 31, 2019** :
Added a way to store game logs, someone suggested it to me and I thought it was a great idea and it's very practical because now I can start to analyze the AI's flaws and make it stronger ~~to take over the world~~ to make it always win or tie in the event it goes first.

# AI Time
I finally incorporated the AI, if you want to test out possible heuristics and make the AI truly dominant you can optimize the scoreMetric function aswell as coming up with a method to distinguish who is winning and losing in a game of connect4, I can only imagine how much creative things you can come up with.

Currently the AI looks 4 moves ahead if you are feeling good and think you can beat it change the value of the **lookForward value on line 839 at connect4.cc**, to a higher value.
Keep in mind the higher the value the longer you wait and please dont put it on a value of 100+...bad things can happen lol.

# Features Added
- Rematch Option
- Game Log Option
- Playing against AI 
- I am confident the AI can win now. (~~I hope the AI wins~~)

# Bugs
Bug Fix: **May 13, 2019**
- **AI scared to lose?** Once the AI figures out it's about to lose it doesn't want to play anymore so I had to **force** it to lose like I did.

Bug Fix: **May 15, 2019**
- In the event a user won right before the game state reaches a tie there would be conflicting screen results.

Bug Fix: **May 20, 2019**
- If you entered a capital letter as of the available moves the program would seg fault.

Bug Fix: **June 5,2019**
- For my whoWon function I was evaluating a location twice in example ```if(x[i] && x[i]...)``` when it should have been ```if(x[i] && x[i+1]..)``` not only did this disrupt the strength of the AI but also disrupted the flow of a simple player V. player game.

Bug Fix: **July 8, 2019**
- There was a lot of problems with the rematch functionality so I needed to organize the code/refactor because it was starting to get messy but now it makes sense and going forward I will be able to add more features such as a log of the moves.

Bug Fix: **July 31, 2019**
- In the event the AI wins against you and you deny a swap and play it again and no matter what the result(win/lose/tie) and deny a rematch there would be a instance of the board generated after because I wasn't properly ending the game.

# Running Code using Makefile

I recommend that you compile with ``make build``

Run the program with ``./game``

To delete the ``./game`` do:

 ``make clean``

