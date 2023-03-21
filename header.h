#pragma once
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#define blankspace (int)'-'
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
using namespace std;

int M = 8, N = 16;
vector<vector<int>> board;
int Level = 1;

//board manipulation
int generatePoke();
void initializeBoard();
void printBoard();
bool isValidBoardSize();
void shiftBoardUp(pair<int, int> p1, pair<int, int> p2);
void shiftBoardDown(pair<int, int> p1, pair<int, int> p2);
void shiftBoardLeft(pair<int, int> p1, pair<int, int> p2);
void shiftBoardRight(pair<int, int> p1, pair<int, int> p2);

//moves checking
bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
bool checkLine(pair<int, int> p1, pair<int, int> p2);
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2);
bool checkBigRect(pair<int, int> p1, pair<int, int> p2);

//shuffling if no moves left
bool isPlayable();
void shuffle();

//game actions
bool isWin();
void play();
