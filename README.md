# HiShinUnit
 A simple AI for a simple game

## Gomoku
The [Gomoku](https://en.wikipedia.org/wiki/Gomoku) is a simple japanese game that play like tic-tac-toe, 
except that you need to align 5 pieces instead of just 3.

## The AI
HiShinUnit uses a cell value evaluation algorithm. The evaluation is multi-threaded to allow use of available cores in order to acceleration the evaluation process.
After all the cell are evaluated, HiShinUnit interpret the different values and tries to select the ones with the best value.
If several cells have the same values, HiShinUnit tries to select the one that blocks most of the enemy possible best cells.

## Rules
This AI was developed in the goal to participate in a Gomoku tournament :
+ 5 second turns
+ 70 mb memory
+ 1 thread

with this rules our AI isn't really optimized for the tournament, but we architectured our project with the goal to be able to implement multiple 
different AIs easly (ie: we developped a MonteCarlo based algorithm that had better results, but the recursive was too heavy to fit in the tournament rules).
