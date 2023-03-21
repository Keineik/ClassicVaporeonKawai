#include "header.h"
#include "userAccount.h"

bool isValidBoardSize() {
    return M*N % 4 == 0;
}
int generatePoke() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    int randPoke = (rand()%(M*N/4)) + 59;
    return randPoke;
}
void initializeBoard() {
    board.clear();
    int countPoke[256] = {};

    vector<int> border;
    for (int i = 0; i <= N+1; i++) {
        border.push_back(blankspace);
    }
    board.push_back(border);

    for (int i = 1; i <= M; i++) {
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
    for (int i = 0; i <= M+1; i++) {
        for (int j = 0; j <= N+1; j++) {
            cout << (char) board[i][j] << " ";
        }
        cout << endl;
    }
}
void shiftBoardUp(pair<int, int> p1, pair<int, int> p2) {
    
}


bool isLegalMove(pair<int, int> p1, pair<int, int> p2) {
    //check if inside board
    if (p1.first < 1 || p1.first > M ||
        p1.second < 1 || p1.second > N ||
        p2.first < 1 || p2.first > M ||
        p2.second < 1 || p2.second > N)
        return false;
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
    if (p1.first > p2.first && p1.second > p2.second) swap(p1, p2);
    //check big rect Ox+
    if (checkLine(p1, {p1.first, p2.second})) {
        for (int i = p2.second; i <= N+1; i++) {
            if (checkLine({p1.first, p2.second}, {p1.first, i}) &&
                checkLine({p1.first, i}, {p2.first, i}) &&
                checkLine({p2.first, i}, p2))
                return true;
        }
    }
    //check big rect Oy+
    if (checkLine(p2, {p1.first, p2.second})) {
        for (int i = p1.first; i >= 0; i--) {
            if (checkLine({p1.first, p2.second}, {i, p2.second}) &&
                checkLine({i, p2.second}, {i, p1.second}) &&
                checkLine({i, p1.second}, p1))
                return true;
        }
    }
    //check big rect Ox-
    if (checkLine(p2, {p2.first, p1.second})) {
        for (int i = p1.second; i >= 0; i--) {
            if (checkLine({p2.first, p1.second}, {p2.first, i}) &&
                checkLine({p2.first, i}, {p1.first, i}) &&
                checkLine({p1.first, i}, p1))
                return true;
        }
        
    }
    //check big rect Oy+
    if (checkLine(p1, {p2.first, p1.second})) {
        for (int i = p2.first; i <= M+1; i++) {
            if (checkLine({p2.first, p1.second}, {i, p1.second}) &&
                checkLine({i, p1.second}, {i, p2.second}) &&
                checkLine({i, p2.second}, p2))
                return true;
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
void play() {
    if (!isPlayable()) {
        cout << "No moves detected, shuffling!" << endl;
        shuffle();
    }
    else {
        pair<int, int> p1, p2;
        printBoard();
        cout << "Type in 2 sets of coordinates you want to match (format: x1 y1 x2 y2): ";
        cin >> p1.first >> p1.second >> p2.first >> p2.second;
        if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1) shuffle();
        else if (isLegalMove(p1, p2)) {
            board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
            cout << "Move is legal" << endl;
        }
        else 
            cout << "Move is not legal" << endl;

        if (Level == 2) {
            shiftBoardUp(p1, p2);
        }
    }
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
void shuffle() {
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

int main () {
    cout << "Welcome to Classic Vaporeon Kawai" << endl;
    
    initializeBoard();
    while (Level < 3) {
        if (isWin()) {
            cout << "Ket thuc man " << Level++ << ". Chuyen sang man " << Level << endl;
            initializeBoard();
        }
        play();
    }
    if (isWin()) {
        cout << "Ban da daotanbu Vaporeon";
    }

    return 0;
}