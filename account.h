#include "header.h"

#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

struct Date{
    int dd, mm, yy;
};
struct State{ //Representing a board state
    int p, q; // Size of the board game
    int p_, q_; // Current cursor position
    char board[BOARDSIZE]; // Current board state
    char file_background[URLSIZE] = {}; // Link to background file. This variable’s value is NULL if there is no current background
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
struct topPlayer {
    char name[NAMESIZE];
    int points;
};
vector<topPlayer> leaderboard(5, {"\0", 0});

// for sorting record
bool sortingPriority(Record rec1, Record rec2) {
    if (rec1.points != rec2.points) return rec1.points > rec2.points;
    else if (rec1.date.yy != rec2.date.yy) return rec1.date.yy > rec2.date.yy;
    else if (rec1.date.mm != rec2.date.mm) return rec1.date.mm > rec2.date.mm;
    return rec1.date.dd > rec2.date.dd;
}

// BINARY FILE INTERACTIONS
void readBinFile();
// xor cstr with mask and asign that to dcstr
void xorCstr(char* cstr, char mask);
void writeBinFile();

// ACCOUNT INTERACTIONS
// Sign Up: 1 -> succesful, 0 -> password don't match, -1 -> username exsisted, -2 -> username invalid 
int signUp(char* username, char* password, char* retypePassword);
bool login(char* username, char* password);
void logout();
void saveGame(int saveSlot);
void loadGame(int saveSlot);
void updateRecord();

// LEADERBOARD
void updateLeaderboard();
