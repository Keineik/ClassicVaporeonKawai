#include "gamelogic.h"

void initializeBoard() {
    // dynamic memory allocation
    board = new int *[M+2];
    for (int i = 0; i <= M+1; i++)
        board[i] = new int [N+2];

    // generate board values
    // upper border
    for (int i = 0; i <= N+1; i++)
        board[0][i] = blankspace;

    // main game board
    int poke = 59, count = 0;
    for (int i = 1; i <= M; i++) {
        board[i][0] = blankspace;
        for (int j = 1; j <= N; j++) {
            board[i][j] = poke;
            if (++count % 2 == 0) poke++;
            if (poke == 91) poke = 59;
        }
        board[i][N+1] = blankspace;
    }

    // lower border
    for (int i = 0; i <= N+1; i++)
        board[M+1][i] = blankspace;

    shuffle();
}

void deleteBoard() {
    for (int i = 0; i <= M+1; i++)
        delete [] board[i];
    delete [] board;
}

void shuffle() {
    // random algo
    mt19937 mt{ static_cast<unsigned int>(
	    chrono::steady_clock::now().time_since_epoch().count()
	    ) };
    // uniform_int_distribution ran{1, 6};

    vector<int> allData;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            if (board[i][j] != blankspace)
                allData.push_back(board[i][j]);

    // put the randomize data back
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            if (board[i][j] != blankspace) {
                uniform_int_distribution<int> ran{0, (int) allData.size() - 1};
                int rNum = ran(mt);
                board[i][j] = allData[rNum];
                allData.erase(allData.begin() + rNum);
            }

}

void shiftColUp(int col) {
    for (int i = 1; i <= M; i++) {
        bool swapped = false;
        for (int j = 1; j <= M; j++) {
            if (board[j][col] == blankspace) {
                swap(board[j][col], board[j + 1][col]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void shiftColDown(int col) {
    for (int i = M; i >= 1; i--) {
        bool swapped = false;
        for (int j = M; j >= 1; j--) {
            if (board[j][col] == blankspace) {
                swap(board[j][col], board[j - 1][col]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void shiftRowLeft(int row) {
    for (int i = 1; i <= N; i++) {
        bool swapped = false;
        for (int j = 1; j <= N; j++) {
            if (board[row][j] == blankspace) {
                swap(board[row][j], board[row][j + 1]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void shiftRowRight(int row) {
    for (int i = N; i >= 1; i--) {
        bool swapped = false;
        for (int j = N; j >= 1; j--) {
            if (board[row][j] == blankspace) {
                swap(board[row][j], board[row][j - 1]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void levelDif() {
    if (Level == 2)
        for (int i = 1; i <= M; i++)
            shiftRowLeft(i);
    else if (Level == 3)
        for (int i = 1; i <= M; i++)
            shiftRowRight(i);
    else if (Level == 4)
        for (int i = 1; i <= N; i++)
            shiftColUp(i);
    else if (Level == 5)
        for (int i = 1; i <= N; i++)
            shiftColDown(i);
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

    // if line is legal
    path.clear();
    path.insert(path.end(), {p1, p2});
    return true;
}

bool checkSmallRect(pair<int, int> p1, pair<int, int> p2) {
    //check legal if middle path is a horizontal line
    if (p1.first > p2.first) swap(p1, p2);
    for (int i = p1.first; i <= p2.first; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2)) {
                path.clear();
                pair<int, int> tempPath[4] = {p1, {i, p1.second}, {i, p2.second}, p2};
                path.push_back(p1);
                for (int i = 1; i < 4; i++)
                    if (tempPath[i] != tempPath[i - 1])
                        path.push_back(tempPath[i]);
                return true;
        }
    }
    //check legal if middle path is a vertical line
    if (p1.second > p2.second) swap(p1, p2);
    for (int i = p1.second; i <= p2.second; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2)) {
                path.clear();
                pair<int, int> tempPath[4] = {p1, {p1.first, i}, {p2.first, i}, p2};
                path.push_back(p1);
                for (int i = 1; i < 4; i++)
                    if (tempPath[i] != tempPath[i - 1])
                        path.push_back(tempPath[i]);
                return true;
        }
    }
    return false;
}

bool checkBigRect(pair<int, int> p1, pair<int, int> p2) {
    //check big rect Ox+
    if (p1.second > p2.second) swap(p1, p2);
    for (int i = p2.second; i <= N+1; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2)) {
                path.clear();
                path.insert(path.end(), {p1, {p1.first, i}, {p2.first, i}, p2});
                return true;
        }
    }
    //check big rect Ox-
    for (int i = p1.second; i >= 0; i--) {
        if (checkLine(p2, {p2.first, i}) &&
            checkLine({p2.first, i}, {p1.first, i}) &&
            checkLine({p1.first, i}, p1)) {
                path.clear();
                path.insert(path.end(), {p2, {p2.first, i}, {p1.first, i}, p1});
                return true;
        }
    }
    //check big rect Oy+
    if (p1.first > p2.first) swap(p1, p2);
    for (int i = p1.first; i >= 0; i--) {
        if (checkLine(p2, {i, p2.second}) &&
            checkLine({i, p2.second}, {i, p1.second}) &&
            checkLine({i, p1.second}, p1)) {
                path.clear();
                path.insert(path.end(), {p2, {i, p2.second}, {i, p1.second}, p1});
                return true;
        }
    }
    //check big rect Oy-
    for (int i = p2.first; i <= M+1; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2)) {
                path.clear();
                path.insert(path.end(), {p1, {i, p1.second}, {i, p2.second}, p2});
                return true;
        }
    }
    return false;
}

pair<pair<int, int>, pair<int, int>> moveSuggestion() {
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (board[i][j] == blankspace) continue;
            for (int u = 1; u <= M; u++) {
                for (int v = 1; v <= N; v++) {
                    if (isLegalMove({i, j}, {u, v}))
                        return {{i, j}, {u, v}};
                }
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

bool isPlayable() {
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (board[i][j] == blankspace) continue;
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

// Calculate score according to streak
void updateScore(){
    if (streak < 5)
        streak ++;
    score += streak*streakscore;
    if (isHint){
         score -= (200 + streak*streakscore);
         streak --;
    }
    isHint = false;
}
