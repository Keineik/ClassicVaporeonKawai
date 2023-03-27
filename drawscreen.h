#include "header.h"
#include <windows.h>
#define ENTER '\r'
#define SPACE ' '
#define BACKSPACE 8
void gotoxy(int x, int y);
void MoveWindow(int posx, int posy);
void resizeConsole(int posx, int posy, int width, int height);
void SetWindowSize();
void TextColor(int x);
//Set color for cout
void SetColor(WORD color);
// Clear Canvas
void clearCanvas(int x, int y, int width, int height);
// Draw box
void clearScreen();
void drawBox(int x, int y, int w, int h, int color, string s);
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
void drawMainMenu(int x,int y,int isSelecting);
void drawLoginMenu(int x, int y, int isSelecting);

// Draw form
void drawLoginForm(int width, int height, char username[], char password[]);
void drawSignupForm(int width, int height, char username[], char password[]);
// Draw In-game HUD
void drawHow2Play();
void drawHUD(int width, int height);
int calculateCellPosX(int j, int w, int h, int boardposx);
int calculateCellPosX(int j, int w, int h, int boardposx);
int calculatBoardPosX(int width,int w,int N);
int calculatBoardPosY(int height,int h, int M);
void printBoard(int width, int height,pair<int, int> p1, pair<int,int> p2,int boardposx,int boardposy);
void drawBar(int startx, int endx, int posy);
void drawColumn(int starty, int endy, int posx);
void drawPath(vector<pair<int,int>> path,int boardposx,int boardposy);
void ShowConsoleCursor(bool showFlag);
