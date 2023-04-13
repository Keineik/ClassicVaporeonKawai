#pragma once
#define __WIN32_WINNT 0x500
#include <bits/stdc++.h>
#include <windows.h>
#include <mmsystem.h>
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
struct menu{
    string choice;
    string about;
};

menu GameMenu[4] = {{"LOGIN",        "         PLAY WITH YOUR OWN ACCOUNT       "},
                    {"SIGN UP",      "             CREATE YOUR ACCOUNT          "},
                    {"PLAY AS GUEST","PLAY WITHOUT SAVE-GAME, LOAD-GAME FEATURES"},
                    {"QUIT",         "            THE NAME SAYS IT ALL          "}};
//string GameMenu [] = {"LOGIN", "SIGN UP", "PLAY AS GUEST", "QUIT"};
menu LoginMenu[7] = {{"NEW GAME",    "               PLAY FROM LEVEL 1                "},
                    {"LOAD GAME",    "        CONTINUE YOUR UNFINISHED GAMEPLAY       "},
                    {"CUSTOM GAME",  "             CHOOSE YOUR BOARDSIZE              "},
                    { "HOW TO PLAY", "             TOTURIAL FOR THIS GAME             "},
                     {"LEADERBOARD", "  SEE WHO HAS THE HIGHEST SCORE ON THIS DEVICE  "},
                     {"CREDIT",     "BEST REGARDS TO WHO CREATE AND SUPPORT THIS GAME"},
                     {"LOG OUT",     "             LOG YOU OUT OF COURSE              "}};
//string LoginMenu [] = {"NEW GAME", "LOAD GAME", "CUSTOM GAME", "AUDIO SETTING", "HOW TO PLAY", "LEADERBOARD","CREDIT","LOG OUT"};
//string GuestMenu [] = {"NEW GAME", "CUSTOM GAME", "AUDIO SETTING", "HOW TO PLAY", "CREDIT", "MAIN MENU"};
menu GuestMenu[5] = {{"NEW GAME",    "               PLAY FROM LEVEL 1                "},
                    {"CUSTOM GAME",  "             CHOOSE YOUR BOARDSIZE              "},
                    { "HOW TO PLAY", "             TOTURIAL FOR THIS GAME             "},
                     {"CREDIT",      "BEST REGARDS TO WHO CREATE AND SUPPORT THIS GAME"},
                     {"MAIN MENU",   "              RETURN TO MAIN MENU               "}};
string SlotMenu[] = {"SLOT 1", "SLOT 2",  "SLOT 3", "SLOT 4", "SLOT 5", "RETURN/RESUME"};
string leaders[5] = {"ligma","sigmaduck","sudenend","amogus","nevergonnagiveyouup"};
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

struct Game {
    int M = 8, N = 16, **board, Level = 1;
    pair<int, int> p1, p2, choosing, oldchoosing;
    int timeRemain = 360, streakTimeRemain = 0, streak = 0, score = 0;
    char background_file[100];
} game;

int &M = game.M, &N = game.N, **&board = game.board, &Level = game.Level;
pair<int, int> &p1 = game.p1, &p2 = game.p2, &choosing = game. choosing, &oldchoosing = game.oldchoosing;
int &timeRemain = game.timeRemain, &streakTimeRemain = game.streakTimeRemain, &streak = game.streak, &score = game.score;
char *background_file = game.background_file;

int tick = 40, maxstreak = 3, streakscore = 100, miliseconds = 1000;

bool halfpair = false, endgame = false, entermainmenu = true, newAccount = false, successLogin = false;
int width = 120, height = 40, offsetx, offsety, backgroundx, backgroundy;
int boardposx = 0, boardposy = 0;
int w = 4, h = 2; // width & height of board 's cells
int backw = 0, backh = 0;
char **background;

bool save = false, load = false, stopPlay = false;
bool isHint = false;
void play();

// account related
struct Date{
    int dd, mm, yy;
};
struct State{ //Representing a board state
    int p, q; // Size of the board game
    int p_, q_; // Current cursor position
    char board[BOARDSIZE]; // Current board state
    char file_background[URLSIZE] = {}; // Link to background file. This variable�s value is NULL if there is no current background
    char trash[1] = {}; // self added trash
    int level, points, time;
    Date date;
    char padding[PADDING - 4*6] = {};// 500 byte NULL
};
struct Record{
    Date date; // Date of completed record
    int points; // points achieved
    char padding[PADDING] = {};// 500 byte NULL
};
struct savefile{
    char mask; // You are required to transfer all char-type variables by performing xor each with the mask-variable, bit-by-bit.
    char name[NAMESIZE]; // username
    char password[PASSSIZE]; // password
    char trash[3] = {}; // self added trash
    // 500 byte NULL
    Record record[5]; // List of sorted best records
    State state[5]; // List of save state
};
unordered_set<string> listOfUsername;
savefile currentSave;
vector<savefile> saves;

// LEADERBOARD
struct highScore {
    int points;
    Date date;
    char name[NAMESIZE];
    char trash[2];
};
vector<highScore> leaderboard(5, {0, 0, 0, 0, "\0"});
