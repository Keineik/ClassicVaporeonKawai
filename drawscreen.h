#include "header.h"
#include <windows.h>
#define ENTER '\r'
#define SPACE ' '
#define BACKSPACE 8
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
void drawMainMenu(int width,int height,int isSelecting);
void drawLoginMenu(int width, int height, int isSelecting) ;
// Draw Login/Signup Form
void drawLoginForm(int width, int height);
void drawSignupForm(int width, int height);
// Draw How to play
void drawHow2Play();
void drawHUD();
// Draw play board
int calculateCellPosX(int j, int w, int h, int boardposx);
int calculateCellPosY(int i, int w, int h, int boardposy);
int calculatBoardPosX();
int calculatBoardPosY();
void printBoard(int width, int height,pair<int, int> p1, pair<int,int> p2,int boardposx,int boardposy);
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
void initializeBackground(char **&background,int &backw, int &backh, string filename);
void deleteBackgroundInfo(char **&background, int &backw, int &backh);
