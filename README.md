# games
Hobby games, testing environment for different search algorithms for game play. 

This repository contains three sepearate projects:

1) Tic-Tac-Toe: C++, WxWidgets
	- Different types of players implemented
		- Human player	
		- Computer plays random moves
		- Computer plays with some simple logical rules
		- Computer plays using the precomputed game tree.
			- Computer chooses moves such that the other player has more ways to go wrong.  
			- Computer chooses a random move first among the winning moves (if exist), then among the drawing moves (if exists) and among the loosing moves (if all of the moves are loosing).
		- Computer plays using the minimax algorithm. This is not implemented yet.
		- Computer plays using Monte Carlo Tree Search algortihm.

2) Eight Number: C++, WxWidgets


3) Tetris: Processing, Java
