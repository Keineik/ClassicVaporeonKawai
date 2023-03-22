#include "gamelogic.h"

int generatePoke() {
    // get seeds in nanoseconds
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    int numOfPoke = M*N/4;
    int randPoke = (rand()%numOfPoke) + 59;
    return randPoke;
}
void initializeBoard() {
    // dynamic memory allocation
    board = new int *[M+2];
    for (int i = 0; i <= M+1; i++)
        board[i] = new int [N+2];

    // generate board values
    int countPoke[256] = {};
    // upper border
    for (int i = 0; i <= N+1; i++)
        board[0][i] = blankspace;

    // main game board
    for (int i = 1; i <= M; i++) {
        board[i][0] = blankspace;
        for (int j = 1; j <= N; j++) {
            int randPoke;
            while (true) {
                randPoke = generatePoke();
                if (countPoke[randPoke] < 4) {
                    countPoke[randPoke]++;
                    break;
                }
            }
            board[i][j] = randPoke;
        }
        board[i][N+1] = blankspace;
    }

    // lower border
    for (int i = 0; i <= N+1; i++)
        board[M+1][i] = blankspace;
}
void deleteBoard() {
    for (int i = 0; i <= M+1; i++)
        delete [] board[i];
    delete [] board;
}
void shuffle() {
    // get seeds in nanoseconds
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            if (board[i][j] != blankspace) {
                while (true) {
                    int u = rand()%M + 1;
                    int v = rand()%N + 1;
                    if (board[u][v] != blankspace) {
                        swap(board[i][j], board[u][v]);
                        break;
                    }
                }
            }
}

bool isLegalMove(pair<int, int> p1, pair<int, int> p2) {
    //check if the same tile
    if (p1.first == p2.first && p1.second == p2.second)
        return false;
    //check if chose blankspace
    if (board[p1.first][p1.second] == blankspace || board[p2.first][p2.second] == blankspace)
        return false;
    //check if same poke
    if (board[p1.first][p1.second] != board[p2.first][p2.second])
        return false;

    //check if legal move
    bool isLegal = false;
    int temp1 = board[p1.first][p1.second];
    int temp2 = board[p2.first][p2.second];
    board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
    if (checkLine(p1, p2)) isLegal = true;
    else if (checkSmallRect(p1, p2)) isLegal = true;
    else if (checkBigRect(p1, p2)) isLegal = true;
    board[p1.first][p1.second] = temp1;
    board[p2.first][p2.second] = temp2;

    return isLegal;
}
bool checkLine(pair<int, int> p1, pair<int, int> p2) {
    //if line is horizontal
    if (p1.first == p2.first) {
        if (p1.second > p2.second) swap(p1, p2);
        for (int i = p1.second; i <= p2.second; i++)
            if (board[p1.first][i] != blankspace) return false;
    }
    //if line is vertical
    else if (p1.second == p2.second) {
        if (p1.first > p2.first) swap(p1, p2);
        for (int i = p1.first; i <= p2.first; i++)
            if (board[i][p1.second] != blankspace) return false;
    }
    else return false;
    return true;
}
bool checkSmallRect(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first > p2.first && p1.second > p2.second) swap(p1, p2);
    //check legal if middle path is a horizontal line
    for (int i = p1.first; i <= p2.first; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2))
            return true;
    }
    //check legal if middle path is a vertical line
    for (int i = p1.second; i <= p2.second; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2))
            return true;
    }
    return false;
}
bool checkBigRect(pair<int, int> p1, pair<int, int> p2) {
    //check big rect Ox+
    if (p1.second > p2.second) swap(p1, p2);
    for (int i = p2.second; i <= N+1; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2))
            return true;
    }
    //check big rect Ox-
    for (int i = p1.second; i >= 0; i--) {
        if (checkLine(p2, {p2.first, i}) &&
            checkLine({p2.first, i}, {p1.first, i}) &&
            checkLine({p1.first, i}, p1))
            return true;
    }
    //check big rect Oy+
    if (p1.first > p2.first) swap(p1, p2);
    for (int i = p1.first; i >= 0; i--) {
        if (checkLine(p2, {i, p2.second}) &&
            checkLine({i, p2.second}, {i, p1.second}) &&
            checkLine({i, p1.second}, p1))
            return true;
    }
    //check big rect Oy+
    for (int i = p2.first; i <= M+1; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2))
            return true;
    }
    return false;
}

bool isPlayable() {
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            for (int u = 1; u <= M; u++) {
                for (int v = 1; v <= N; v++) {
                    if (isLegalMove({i, j}, {u, v}))
                        return true;
                }
            }
        }
    }
    return false;
}
bool isWin() {
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            if (board[i][j] != blankspace) return false;
    return true;
}

