#include "header.h"

int N = 10;
vector<vector<int>> board;

int generatePoke() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    int randPoke = rand()%25 + 65;
    return randPoke;
}
void initializeBoard() {
    int countPoke[256] = {};

    vector<int> border;
    for (int i = 0; i <= N+1; i++) {
        border.push_back(blankspace);
    }
    board.push_back(border);

    for (int i = 1; i <= N; i++) {
        vector<int> vtemp;
        vtemp.push_back(blankspace);
        for (int j = 1; j <= N; j++) {
            int randPoke;
            while (true) {
                randPoke = generatePoke();
                if (countPoke[randPoke] < 4) {
                    countPoke[randPoke]++;
                    break;
                }
            }
            vtemp.push_back(randPoke);
        }
        vtemp.push_back(blankspace);
        board.push_back(vtemp);
    }
    board.push_back(border);
}

void printBoard() {
    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= N+1; j++) {
            cout << (char) board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isLegalMove(pair<int, int> p1, pair<int, int> p2) {
    
}

void play() {
    pair<int, int> p1, p2;
    printBoard();
    cout << "Type in 2 sets of coordinates you want to match (format: x1 y1 x2 y2): ";
    cin >> p1.first >> p1.second >> p2.first >> p2.second;
}

int main () {
    cout << "Welcome to Classic Vaporeon Kawai" << endl;
    cout << "Choose board size (N x N): "; cin >> N; N = 10;
    initializeBoard();
    printBoard();
    

    return 0;
}