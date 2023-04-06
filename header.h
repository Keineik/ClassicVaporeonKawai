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
int GameMenuSelecting = -1, GameMenuChoice = -1;
int LoginMenuSelecting = -1, LoginMenuChoice = -1;
int GuestMenuSelecting = -1, GuestMenuChoice = -1;
int SignUpMenuSelecting = -1, SignUpMenuChoice = -1;
int SlotMenuSelecting = -1, SlotMenuChoice = -1;

string GameMenu [] = {"LOGIN", "SIGN UP", "PLAY AS GUEST", "QUIT"};
string LoginMenu [] = {"NEW GAME", "LOAD GAME", "CUSTOM GAME", "AUDIO SETTING", "HOW TO PLAY", "LEADERBOARD","CREDIT","LOG OUT"};
string GuestMenu [] = {"NEW GAME", "CUSTOM GAME", "AUDIO SETTING", "HOW TO PLAY", "CREDIT", "MAIN MENU"};
string SlotMenu[] = {"SLOT 1", "SLOT 2",  "SLOT 3", "SLOT 4", "SLOT 5", "RETURN/RESUME"};
int CellColor[] = {3,4,5,6,7,8,9,10,11,12,13};
/*
CellColor[ceil((int(Poke) - 58)/3)];
1	Blue	9	Light Blue
2	Green	0	Black
3	Aqua	A	Light Green
4	Red	    B	Light Aqua
5	Purple	C	Light Red
6	Yellow	D	Light Purple
7	White	E	Light Yellow
8	Gray	F	Bright White
*/
char username[NAMESIZE], password[PASSSIZE], retypepassword[PASSSIZE];
//default board size
int M = 8, N = 16;
int **board;
char **background;
int Level = 1;
bool halfpair = false, endgame = false, entermainmenu = true, newAccount = false, successLogin = false;
int width = 100, height = 40, offsetx, offsety, backgroundx, backgroundy;
int boardposx = 0, boardposy = 0;
int w = 4, h = 2; // width & height of board 's cells
int backw = 0, backh = 0;
pair<int, int> p1, p2,choosing,oldchoosing;
bool save = false, load = false, stopPlay = false;
int timeRemain = 360, streakTimeRemain = 0,  miliseconds = 1000, tick = 40, streak = 0, maxstreak = 3, score = 0, streakscore = 100; //Variables used ingame
bool isHint = false;
void play();
