#include "header.h"

// board manipulation
int generatePoke();
void initializeBoard();
void deleteBoard();
void shuffle();

//moves checking
bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
bool checkLine(pair<int, int> p1, pair<int, int> p2);
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2);
bool checkBigRect(pair<int, int> p1, pair<int, int> p2);

//board status
bool isPlayable();
bool isWin();
