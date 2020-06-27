# games and puzzles
Hobby games, testing environment for different search algorithms for game play and puzzle solving. 

This repository contains three sepearate projects:

1) Tic-Tac-Toe: C++, WxWidgets
	- Different types of players are implemented.
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

2) 8-Puzzle: C++, WxWidgets
	- This project implements two versions of 8-puzzle: standard 8-puzzle and weighted 8-puzzle.
	- Both versions of the puzle can be formulized as a search problem.
	- Cost for standard 8-puzzle is the total number of moves from a given state to the goal state. That is every move has the same cost.
	- Cost for weighted 8-puzzle is the wighted sum of moves from a given state to the goal state. Move costs depend on the tile moved, tile-1: 1, tile-2, 2, ... tile-8:8 
	- Total number of states is 9!/2 = 181440
	- Hardest puzzle can be solved in 31 moves.
	- Different search algorithms (uninformed and informed) are implemented to solve a given the 8-puzzle.
	- Algorithms report the path (moves) to the solution and the total cost (for the weighted 8-puzzle).
	- Solutions can be simulated in the GUI.
	- Two different approach is applied for some of the search algorithms: Tree search and Graph search
		- Tree Search: 
			- Same nodes can be visited/expanded more than once as one node can be encountered at different depths in the search tree.
		- Graph Search: 
			- Each node is visited/expanded only once by keeping track (via hashing mechnishm) of the visited/expanded nodes.
			- Two different data structures are used for hashing: unordered_set or unordered_map.
				- unordered_set based hashing stores only the board states.
				- unordered_map based hashing stores the board states as key and the depth of the board (from the starting position) as value. 
				- Keeping the depth of a state makes a difference for some of the algorithms. A node is discarded only if it is visited/expanded before in a lower depth, otherwise it is explored again so that we might find a better solution if the node is a part of the solution.    				
				
	- Uninformed search algorithms: 
		- BFS (Breadth First Seach): 
			- BFS is guaranteed to give a solution with minimum number of moves. Since the cost of each move is equal in the standard 8-puzzle problem, BFS also computes the optimal solution. If the cost of successor states were not equal, BFS would still give the path to the goal state with minimum number of moves but it would not necessarily be the cheapest in terms of cost. The uninformed search algorithm for getting the path with minimum cost is Uniform Cost Search algorithm. 
			- A Queue (FIFO principle) is used to order node visits/expands.
			- Two versions of BFS is implemented one for tree search and one for graph search. The depth of the algorithm is limited to 16 for the tree search since beyond that depth the amount of memory needed is beyond my computer to handle. Therefore tree search version of BFS is neither complete nor optimal.
		- DFS (Depth First Search):
			- Three versions of this algorithm is implemented: non-recursive DFS - graph search, depth limited recursive DFS - tree search, depth limited recursive DFS - graph search,  	
			- Non-recursive DFS - graph search: Stack-based implementation, unordered_set is used for hashing, no depth limit, complete but not optimal.
			- Depth limited recursive DFS - tree search: recursive, depth_limit is set to 31, complete but not optimal.
			- Depth limited recursive DFS - graph search: recursive, depth_limit is set to 31, complete but not optimal. 
		- Depth Limited Iterative Deepening: 
			- Two versions of the algorithm one for tree search and one for graph search.
			- unordered_map is used for hashing for the graph search version of the algorithm.
			- Depth limit is set to 31 for both algorithms, both are complete and optimal.			
		-Uniform Cost Search (Cheapest First Search):
			- Orders the nodes to be expanded by path cost or backward cost (g(n))
			- Complete and optimal.
			
	- Informed (heuristic) search: 
		- Greedy Search (Best First Search):
			- Orders the nodes to be expanded by heuristic (estimated proximity to the goal state, forward cost h(n))
			- Implemeted with two different heuristics: number of misplaced tiles, Manhattan distance.
				- Both heuristics are admissible and consistent
				- A heuristic function h(N) is admissible if 0 <= h(N) <= h*(), where h*(N) is the actual cost from node N to a goal state.
				- An admissible heuristic h is consistent (or monotone) if for each node N and each child N' of N: h(N) - h(N') <= c(N,N'). Note that c(N,N') is the cost of moving from N to N'.
				- A consistent heuristic is also admissible. 
			- Complete but not optimal.
		- A* Search
			- Orders the nodes based on the sum of backward and forward costs (f(n) = g(n) + h(n)).
			- Implemeted with two different heuristics: number of misplaced tiles, Manhattan distance.
			- Tree search version: optimal if the heuristic used is admissible. This is not implemented as it takes a lot of time to compute, similar to BFS_Tree Search case. 
			- Graph search version: optimal if the heuristic used is consistent.
	- State Space Graph:
		- Full state space graph can also be computed and exported.
		- This graph can be used to find optimal solutions.
		- See the data folder for the exported graphs in csv format.  
		- State space graph for standard 8-puzzle is computed by a variant of BFS algorithm starting from the goal state.
		- State space graph for the weighted 8-puzzle is computed by Dijkstra's single source shortes path algorithm starting from the goal state.

3) Tetris: Processing, Java
	- A modern tetris game with lock-down, hold piece and display of multiple next pieces.
	- 15 levels
	- Single thread
	
4) Sudoku Solver: Processing, Java
	- Have look at the documentation in the project for the details.
