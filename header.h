#pragma once

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

#define blankspace (int)'-'

using namespace std;

//default board size
int M = 8, N = 16;
int **board;
int Level = 1;

int chosex, chosey,chosemenu = -1, isSelecting = -1;
bool halfpair = false, endgame = false, entermainmenu = true;
int width = 100, height = 40;
int boardposx = 0, boardposy = 0;
int w = 4, h = 2; // width & height of board 's cells

pair<int, int> p1, p2;
