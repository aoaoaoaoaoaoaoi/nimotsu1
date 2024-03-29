#include "stdafx.h"
#include <iostream>
using namespace std;

const int HEIGHT = 5;
const int WIDTH = 8;

pair<int, int>PlayerPos = make_pair(1,5);
pair<int, int>GoalPos[2] = { make_pair(1, 2), make_pair(1, 3) };
pair<int, int>NimotsuPos[2] = { make_pair(2, 2), make_pair(2, 3) };

char field[5][8]={
	{'#','#','#','#','#','#','#','#'},
	{'#',' ','.','.',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ','#'},
	{'#',' ',' ',' ',' ',' ',' ','#'},
	{'#','#','#','#','#','#','#','#'},
};

bool isBlockPlace(int y, int x) {
	return y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1;
}

enum State
{
	INSESSION,
	FINISH,
};
State currentState = INSESSION;

bool isNimotsuPlace(int y, int x) {
	for (int n = 0; n < 2; ++n) {
		if (y == NimotsuPos[n].first && x == NimotsuPos[n].second)
			return true;
	}
	return false;
}

bool isMove(pair<int ,int> next, pair<int, int> nextNext) {

	if (!isBlockPlace(next.first, next.second)) {
		if (isNimotsuPlace(next.first, next.second)) {
			if (!isNimotsuPlace(nextNext.first,nextNext.second) && !isBlockPlace(nextNext.first, nextNext.second)) {
				return true;
			}
		}
		else {
			return true;
		}
	}
	return false;
}

void updateNimotsuPlace(pair<int, int>current, pair<int, int> next) {
	for (int n = 0; n < 2; ++n) {
		if (current.first == NimotsuPos[n].first && current.second == NimotsuPos[n].second) {
			NimotsuPos[n].first = next.first;
			NimotsuPos[n].second = next.second;
			return;
		}
	}
}

void getInput() {
	
	char c;
	cin >> c;

	pair<int, int> next;
	pair<int, int> nextNext;
	switch (c) {
		case 'w':
			next = make_pair(PlayerPos.first - 1, PlayerPos.second);
			nextNext = make_pair(PlayerPos.first - 2, PlayerPos.second);
			break;
		case 'z':
			next = make_pair(PlayerPos.first + 1, PlayerPos.second);
			nextNext = make_pair(PlayerPos.first + 2, PlayerPos.second);
			break;
		case 'a':
			next = make_pair(PlayerPos.first, PlayerPos.second - 1);
			nextNext = make_pair(PlayerPos.first, PlayerPos.second - 2);
			break;
		case 's':
			next = make_pair(PlayerPos.first, PlayerPos.second + 1);
			nextNext = make_pair(PlayerPos.first, PlayerPos.second + 2);
			break;
	}
	if (isMove(next, nextNext)) {
		if (isNimotsuPlace(next.first, next.second))updateNimotsuPlace(next, nextNext);
		PlayerPos = next;
	}
}

bool isFinish() {
	for (int g = 0; g < 2;++g) {
		if (!isNimotsuPlace(GoalPos[g].first, GoalPos[g].second))return false;
	}
	return true;
}

void updateGame() {
	if (isFinish()) {
		currentState = FINISH;
	}
}

bool isPlayerPlace(int y, int x) {
	return PlayerPos.first == y && PlayerPos.second == x;
}

bool isGoalPlace(int y, int x) {
	for (int g = 0; g < 2; ++g) {
		if (y == GoalPos[g].first && x == GoalPos[g].second)
			return true;
	}
	return false;
}

void draw() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (isNimotsuPlace(y, x)) {
				if (isGoalPlace(y, x)) cout << 'O';
				else cout << 'o';
				continue;
			}
			else  if (isPlayerPlace(y, x)) {
				if (isGoalPlace(y, x)) cout << 'P';
				else cout << 'p';
				continue;
			}
			cout << field[y][x];
		}
		cout << endl;
	}
	if (currentState == FINISH) {
		cout << "FINISH!!" << endl;
		cout << "CONGRATULLATION!!" << endl;
	}
	else {
		cout << "command?" << endl;
	}
}

void initialize() {
	draw();
}

int main()
{
	initialize();
	while (true) {
		getInput();
		updateGame();
		draw();
	}
    return 0;
}

