#include "PuzzleSolver.h"
#include <cmath>

bool PuzzleSolver::solve(int puzzle[9], std::vector<int> & moves) {
	Node *a = new Node();
	a->parent = NULL;
	a->move = 0;
	a->movesCount = 0;
	a->priority = costFunction(puzzle, 0);
	a->data = puzzle;
	int emptyCellIndex = -1;

	for (int i = 0; i < 9; i++) {
		if (puzzle[i] == -1) {
			emptyCellIndex = i;
		}
	}
	a->emptyCellIndex = emptyCellIndex;

	queue.push(a);
	while (queue.size() > 0) {
		Node *hs = queue.top();
		queue.pop();
		std::string hash = getHash(hs->data);
		if (isSolution(hs->data)) {
			std::vector<int> m = getMoves(hs);
			for (int i = 0; i < m.size(); i++) {
				moves.push_back(m.at(i));
			}
			return true;
		}

		if (visited.find(hash) != visited.end()) {
			continue;
		}
		else {
			visited.insert(hash);
		}

		int * newPuzzleLeftMove = move(MOVE_LEFT, hs->data, hs->emptyCellIndex);

		if (newPuzzleLeftMove) {

			Node *newNode = new Node();
			newNode->parent = hs;
			newNode->emptyCellIndex = hs->emptyCellIndex + MOVE_LEFT;
			newNode->move = MOVE_LEFT;
			newNode->priority = costFunction(newPuzzleLeftMove, newNode->movesCount);
			newNode->data = newPuzzleLeftMove;
			newNode->movesCount = hs->movesCount + 1;
			queue.push(newNode);
		}
		int * newPuzzleRightMove = move(MOVE_RIGHT, hs->data, hs->emptyCellIndex);

		if (newPuzzleRightMove) {

			Node *newNode = new Node();
			newNode->parent = hs;
			newNode->emptyCellIndex = hs->emptyCellIndex + MOVE_RIGHT;
			newNode->move = MOVE_RIGHT;
			newNode->movesCount = hs->movesCount + 1;
			newNode->priority = costFunction(newPuzzleRightMove, newNode->movesCount);
			newNode->data = newPuzzleRightMove;
			queue.push(newNode);
		}
		int * newPuzzleUpMove = move(MOVE_UP, hs->data, hs->emptyCellIndex);

		if (newPuzzleUpMove) {

			Node *newNode = new Node();
			newNode->parent = hs;
			newNode->emptyCellIndex = hs->emptyCellIndex + MOVE_UP;
			newNode->move = MOVE_UP;
			newNode->priority = costFunction(newPuzzleUpMove, newNode->movesCount);
			newNode->data = newPuzzleUpMove;
			newNode->movesCount = hs->movesCount + 1;

			queue.push(newNode);
		}
		int * newPuzzleDownMove = move(MOVE_DOWN, hs->data, hs->emptyCellIndex);

		if (newPuzzleDownMove) {

			Node *newNode = new Node();
			newNode->parent = hs;
			newNode->emptyCellIndex = hs->emptyCellIndex + MOVE_DOWN;
			newNode->move = MOVE_DOWN;
			newNode->priority = costFunction(newPuzzleDownMove, newNode->movesCount);
			newNode->data = newPuzzleDownMove;
			newNode->movesCount = hs->movesCount + 1;
			queue.push(newNode);
		}
	}
	return false;
}

std::string PuzzleSolver::getHash(int puzzle[]) {
	std::string hash = "";
	for (int i = 0; i < 9; i++) {
		hash += std::to_string(puzzle[i]);
	}
	return hash;
}


std::vector<int> PuzzleSolver::getMoves(Node *node) {
	Node *n = node;
	std::vector<int> moves;
	while (n->parent != NULL) {
		moves.push_back(n->move);
		n = n->parent;
	}
	return moves;
}

bool PuzzleSolver::isSolution(int puzzle[]) {
	for (int i = 0; i < 8; i++) {
		if (puzzle[i] != i + 1) {
			return false;
		}
	}
	return true;
}

int * PuzzleSolver::move(int m, int puzzle[], int emptyCellIndex) {
	if (m == MOVE_LEFT) {
		if ((emptyCellIndex - 2) % 3 == 0) {
			return NULL;
		}
	}
	else if (m == MOVE_RIGHT) {
		if (emptyCellIndex % 3 == 0) {
			return NULL;
		}

	}
	else if (m == MOVE_UP) {
		if (emptyCellIndex >= 6) {
			return NULL;
		}
	}
	else if (m == MOVE_DOWN) {
		if (emptyCellIndex <= 2) {
			return NULL;
		}
	}

	int * newPuzzle = new int[9];
	for (int i = 0; i < 9; i++) {
		newPuzzle[i] = puzzle[i];
	}
	int temp = newPuzzle[emptyCellIndex + m];
	newPuzzle[emptyCellIndex + m] = -1;
	newPuzzle[emptyCellIndex] = temp;
	return newPuzzle;
}

int PuzzleSolver::costFunction(int puzzle[], int movesSoFar) {

	int score = 0;
	for (int i = 0; i < 9; i++) {

		//this cell is on the right place
		if (puzzle[i] != -1) {
			int rowGoal = (puzzle[i] - 1) / 3;
			int colGoal = (puzzle[i] - 1) % 3;
			int rowVal = i / 3;
			int colVal = i % 3;
			score += std::abs(rowVal - rowGoal) + std::abs(colVal - colGoal) + movesSoFar;
		}
	}
	return score;
}
