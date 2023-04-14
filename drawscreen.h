#include "header.h"
#include "account.cpp"

#include <windows.h>
#define ENTER '\r'
#define SPACE ' '
#define BACKSPACE 8
char UpperTimeBar[125] = {};
char LowerTimeBar[125] = {};
char StreakTimeBar[20] = {};
// Set console pointer to coordinator (x,y)
void gotoxy(int x, int y);

void resizeConsole(int posx, int posy, int width, int height);

void SetWindowSize();
void TextColor(int x);
//Set color for cout
void SetColor(int x);

// Clear Canvas

void clearCanvas(int x, int y, int width, int height);

void exposeBackground(int x, int y, int width, int height, char **background, int backgroundx, int backgroundy);

void clearScreen();
// Draw solid box
void drawBox(int x, int y, int w, int h, int color, string s);
// Draw empty box
void drawBoxOnly(int x, int y, int w, int h, int color, string s);

void drawCell(int x, int y, int w, int h, int color, char c);
// Draw menu

/*
    Main Menu - 1
    Play: 0
    -Login: 5
    -Signup 6
    -Play as guest 7
    How to play 1
    Highscore: 2
    Credit: 3
    Quit: 4
*/

// Draw Login/Signup Form

void drawLoginForm();

void drawSignupForm();

// Draw How to play

void drawHow2Play();

// Draw play board
int calculateCellPosX(int j, int w, int h, int boardposx);

int calculateCellPosY(int i, int w, int h, int boardposy);

int calculateBoardPosX();

int calculateBoardPosY();

void printBoard();

void redrawCol(int j);

void redrawRow(int i);
// Draw legal move
void drawBar(int startx, int endx, int posy);

void drawColumn(int starty, int endy, int posx);

void eraseBar(char **background, int backgroundx, int backgroundy, int startx, int endx, int posy, int w, int h);

void eraseColumn(char **background, int backgroundx, int backgroundy, int starty, int endy, int posx, int w, int h);
void drawPath(vector<pair<int,int>> path,int boardposx,int boardposy);
void clearVfx(pair <int,int> p1, pair <int,int> p2, vector<pair<int,int>> path, int backgroundx, int backgroundy);

//Hide show cursor
void ShowConsoleCursor(bool showFlag);


//Draw Game Title
void drawImage(int x, int y, string imagefile);

void initializeBackground(char **&background,int &backw, int &backh, int &backgroundx, int &backgroundy, string filename);

void deleteBackgroundInfo(char **&background,int &backw, int &backh, int &backgroundx, int &backgroundy);
void drawBackground(char **background,int backw, int backh, int backgroundx, int backgroundy);

// Draw Game status on the screen when first enter play()
void drawHUD();
void initializeTimeBar();
void initializeStreakTimeBar();
// display time and Game status during gameplay
void displayTimeAndStatus();

bool validateColandRow(int M, int N);

void drawCustomnizeMenu();

void drawLeaderboardandHighScore();


void drawNormalMenu(int MenuSelecting, int MenuSize, menu Menu[]);

void drawSaveLoadMenu();
void navigateMenu(int &MenuSelecting, int &MenuChoice, int MenuSize);
void showGameMenu();
void showLoginMenu();
void showGuestMenu();
void showSaveMenu();
void showLoadMenu();
void drawHackingConsole();
void drawCredit();
