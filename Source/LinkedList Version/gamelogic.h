#include "header.h"

struct Node {
    int data = 0;
    Node* next = NULL;
};

struct LinkedList {
    int size = 0;
    Node *firstNode = NULL;
    LinkedList* next = NULL;
};

LinkedList *board = NULL;

// linked list manipulation
void levelDif(int &x, int &y);
void addHead(Node *&pHead, int val);
void addHeadLL(LinkedList *&pHeadLL);
int getData(int x, int y);
void changeData(int x, int y, int data);

// board manipulation
void initializeBoard();
void deleteBoard();
void shuffle();
void deleteAndShiftBoard(int indexLL);

//moves related
bool isLegalMove(pair<int, int> p1, pair<int, int> p2);
bool checkLine(pair<int, int> p1, pair<int, int> p2);
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2);
bool checkBigRect(pair<int, int> p1, pair<int, int> p2);
pair<pair<int, int>, pair<int, int>> moveSuggestion();

//board status
bool isPlayable();
bool isWin();
