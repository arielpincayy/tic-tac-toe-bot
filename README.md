# Tic-Tac-Toe with Minimax in C

This project implements the Tic-Tac-Toe game using the Minimax algorithm in C. The human player competes against an AI that uses the Minimax algorithm to choose the best possible move.

## Description

The program creates a tree of possible board states using the Minimax algorithm to determine the optimal AI move each turn. The human player always plays with 'o' and the AI ​​plays with 'x'.

## Compilation and Execution

### Requirements

- A C compiler (for example, `gcc`).
- A C development environment on your system (Linux, macOS, Windows with MinGW, etc.).

### Compilation

To compile the program, use the following command in the terminal:

```bash
gcc -o tic_tac_toe tic_tac_toe.c
```
##How to play

player
Enter position (0-8): 0

 o | |
-----------
   | |
-----------
   | |
computer

 o | | x
-----------
   | |
-----------
   | |
player
Enter position (0-8): 4

 o  | | x
-----------
    |o|
-----------
    | |
computer

 o  | | x
-----------
   |o|
-----------
 x | |
...
