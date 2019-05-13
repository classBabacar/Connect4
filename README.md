# Inspiration 

This is one of my favorite games. Growing up I played this game so much with family and friends I took a lot of losses and that's why I kind of got obsessed with the game
because I hate losing. So I practiced a lot of programming so one day I could make this game now I did but now I have another goal which is the AI... **(Complete)**

# Goals
Right now, the game allows for 1v1 play but in the near future I plan to incorporate an AI with the concept of MiniMax **(Complete)**.

# Game Updates
I had to refactor the whole code because if I wanted to incorporate an AI my previous method would not be a suitable starting place but now I believe I am in good condition to implement an AI..see ya soon. I had to refactor some more because I generated the ai but it was difficult to maintain so I needed to change base version. 
- **May 12, 2019** : 
I had to refactor some more by adding functions that were solely for the AI.

# AI Time
I finally incorporated the AI, if you want to test out possible heuristics and make the AI truly dominant you can optimize the scoreMetric function by setting different values, there is probably a sophisticated math behind it. Hopefully you enjoy and don't lose.

Currently the AI look 5 moves ahead depending on if you want to change difficulty increase or decrease..lookForward value.

# Features Added
- Rematch Option
- Playing against AI (~~I hope the AI wins~~)

# Bugs
Bug Fix: May 13, 2019
- **AI scared to lose?** Once the AI figures out it's about to lose it doesn't want to play anymore so I had to **force** it to hold the L. 

# Running Code using Makefile

I recommend that you compile with ``make build``

Run the program with ``./game``

To delete the ``./game`` do ``make clean``

