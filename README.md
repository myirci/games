# games
Hobby games, testing environment for different search algorithms for game play and puzzle solving. 

This repository contains three sepearate projects:

1) Tic-Tac-Toe: C++, WxWidgets
	- Different types of players implemented
		- Human player	
		- Computer plays random moves
		- Computer plays with some simple logical rules
		- Computer plays using the precomputed game tree.
			- Computer chooses moves such that the other player has more ways to go wrong.  
			- Computer chooses a random move first among the winning moves (if exist), then among the drawing moves (if exists) and among the loosing moves (if all of the moves are loosing).
		- Computer plays using the minimax algorithm.
		- Computer plays using the negamax algorithm which is exactly same with minimax algorithm with less code.
		- Computer plays with negamax algorithm and alpha beta prunning. (Not implemented yet.)
		- Computer plays using Monte Carlo Tree Search algortihm. (Not implemented yet.)

2) Eight Number: C++, WxWidgets
	- Different search algorithms are implemented.
	- Uninformed search: BFS, Non-recursive DFS, Recursive DFS, Iterative Deepening
	- Informed search: A* (Not implemented yet.)

3) Tetris: Processing, Java
	- A modern tetris game with lock-down, hold piece and display of multiple next pieces.
	- 15 levels
	- Single thread
