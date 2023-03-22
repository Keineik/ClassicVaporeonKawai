#include "header.h"
#include <windows.h>

void gotoxy(int x, int y);
void MoveWindow(int posx, int posy);

void SetWindowSize();

void TextColor(int x);

//Set color for cout
void SetColor(WORD color);

// Clear Canvas

void clearCanvas(int x, int y, int width, int height);


// Draw box
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

// Draw In-game HUD

void drawHUD(int width, int height);

void printBoard(pair<int, int> p1, pair<int,int> p2);