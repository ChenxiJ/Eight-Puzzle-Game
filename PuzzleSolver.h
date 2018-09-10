#pragma once
#include <queue>
#include <vector>
#include <set>
#include <string>
#define MOVE_LEFT 1
#define MOVE_RIGHT -1
#define MOVE_UP 3
#define MOVE_DOWN -3

struct Node {
	Node * parent;
	int move;
	int* data;
	int priority;
	int movesCount;
	int emptyCellIndex;
};

struct compare {
	bool operator()(const Node * l, const Node * r)
	{
		return l->priority > r->priority;
	}
};

class PuzzleSolver {
public:
	bool solve(int puzzle[9], std::vector<int> & moves);
	int * move(int m, int puzzle[], int emptyCellIndex);

private:
	std::set<std::string> visited;
	std::string getHash(int puzzle[]);
	bool isSolution(int puzzle[]);
	std::vector<int> getMoves(Node *node);
	std::priority_queue<Node*, std::vector<Node*>, compare> queue;
	int costFunction(int puzzle[], int movesSoFar);
};
