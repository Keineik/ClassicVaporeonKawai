#include "header.h"

vector<pair<int, int>> path;

// board manipulation
void initializeBoard();
void deleteBoard();
void shuffle();
void shiftColUp(int col);
void shiftColDown(int col);
void shiftRowLeft(int row);
void shiftRowRight(int row);

//moves related
bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
bool checkLine(pair<int, int> p1, pair<int, int> p2);
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2);
bool checkBigRect(pair<int, int> p1, pair<int, int> p2);
pair<pair<int, int>, pair<int, int>> moveSuggestion();

//board status
bool isPlayable();
bool isWin();
