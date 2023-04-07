#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#define WindowW 1200
#define WindowH 900
#define ConsoleCol 144
#define ConsoleRow 52
#define blankspace (int)'-'
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100
using namespace std;
//default board size
int M = 8, N = 16;
int Level = 1;
int CellColor[] = {3,4,5,6,7,8,9,10,11,12,13};
int width = 100, height = 40, offsetx, offsety;
int backw = 0, backh = 0;
int w = 4, h = 2;
int boardposx = 0, boardposy = 0;
bool halfpair = false;
bool isHint = false;
void play();
vector<pair<int, int>> path;
pair<int, int> p1, p2,choosing,oldchoosing;
