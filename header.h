#pragma once
#include <bits/stdc++.h>

#define blankspace (int)'-'

using namespace std;

//board manipulation
int generatePoke();
void initializeBoard();
void printBoard();

//moves checking
bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
bool checkLine(pair<int, int> p1, pair<int, int> p2);
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2);
bool checkBigRect(pair<int, int> p1, pair<int, int> p2);

//shuffling if no moves left
bool isPlayable();
void shuffle();

//game actions
void play();