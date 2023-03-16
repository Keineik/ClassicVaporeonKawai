#pragma once
#include <bits/stdc++.h>

#define blankspace (int)'-'

using namespace std;

int generatePoke();
void initializeBoard();

void printBoard();

bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
void play();