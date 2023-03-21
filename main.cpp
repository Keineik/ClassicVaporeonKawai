#include "header.h"
#include "userAccount.h"
#include "drawscreen.cpp"
int chosex, chosey,chosemenu = -1, isSelecting = -1;
bool halfpair = false, endgame = false;
int width = 90, height = 29;
int w = 4, h = 2; // width & height of board 's cells
bool gameover = false;
pair<int, int> p1,p2;
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

// In game key input
void keyInput_Play(){
        switch(_getch()){
        case KEY_UP: case 'w':
            if (chosex > 1)
                chosex--;
            else
                chosex = 1;
            break;
        case KEY_DOWN: case 's':
            if (chosex < M)
                chosex++;
            else
                chosex = M;
            break;
        case KEY_LEFT: case 'a':
            if (chosey > 1)
                chosey--;
            else
                chosey = 1;
            break;
        case KEY_RIGHT: case 'd':
            if (chosey < N)
                chosey++;
            else
                chosey = N;
            break;
        case ' ':
            if (halfpair){
                p2.first = chosex;
                p2.second = chosey;
                halfpair = false;
            }
            else{
                p1.first = chosex;
                p1.second = chosey;
                halfpair = true;
            }

            break;
        case 'm':
            chosemenu = -1;
            clearCanvas(0,0,120,50);
            drawBox(0,0,width,height,6, " ");
            break;
        default:
            break;
        }
}
// Key input for menus
void keyInput_Navigator(int sizeofMenu){
    switch(_getch()){
    case KEY_UP: case 'w':
        if (isSelecting <= 0)
            isSelecting = 0;
        else
            isSelecting--;
        break;
    case KEY_DOWN: case 's':
        if (isSelecting >= sizeofMenu-1)
            isSelecting = sizeofMenu -1;
        else
            isSelecting++;
        break;
    case 'm':
        chosemenu = -1;
        isSelecting = -1;
        break;
    case ' ':
        if (isSelecting == 0){
            initializeBoard();
            chosex = 1; chosey = 1;
            p1 = {0,0};
            p2 = {0,0};
        }
        if (chosemenu == 0){
            chosemenu = isSelecting + 5;
        }
        else
            chosemenu = isSelecting;
        isSelecting = -1;
        clearCanvas(1,1,width - 2, height - 2);
        break;
    default:
        break;
    }

}

// Draw play board
void printBoard(pair<int, int> p1, pair<int,int> p2) {
    int floor = 0;
    for (int i = 1; i <= M; i++) {
        floor = (i-1)*h;
        gotoxy(5,floor);
        for (int j = 1; j <=  N; j++){
            if((p1.first == i && p1.second == j)|| (p2.first == i && p2.second ==j))
                drawCell(2+(j-1)*w + j, 2+floor+i, w, h , 4 , board[i][j]);
            else if (chosex == i && chosey == j)
                drawCell(2+(j-1)*w + j, 2+floor+i, w, h , 1 , board[i][j]);
            else
                drawCell(2+(j-1)*w + j, 2+floor+i, w, h , 6 , board[i][j]);

        }
    }
}

void shiftBoardUp(pair<int, int> p1, pair<int, int> p2) {

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
    drawHUD(width, height);

    if (!isPlayable()) {
        clearCanvas(1,1,width - 2, height - 2);
        drawBox((width - 20)/2,(height-5)/2,20,5,6,"No valid move, shuffle!!!");
        shuffle();
        Sleep(10);
        clearCanvas(1,1,width - 2, height - 2);
    }
    else {
        printBoard(p1,p2);
        keyInput_Play();
        if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
            if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1)
                shuffle();
            else if (isLegalMove(p1, p2)) {
                board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
                p1 = p2 = {0,0};
                }
                else
                {
                    p1 = p2 = {0,0};
                }

            if (Level == 2) {
                shiftBoardUp(p1, p2);
            }
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

    chosex = 1; chosey = 1;
    SetWindowSize();
    MoveWindow(0,0);
    drawBox(0,0,width,height,6, " ");
    Sleep(10);
    initializeBoard();
    while (!endgame) {
        //if (isWin()) {
            //cout << "Ket thuc man " << Level++ << ". Chuyen sang man " << Level << endl;
            //initializeBoard();
        //}
        //play();
        if (chosemenu == -1){
            drawMainMenu((width - 20) / 2, (height - 4*3) / 2, isSelecting);
            keyInput_Navigator(5);
        }
        else if(chosemenu == 0){
            drawLoginMenu((width - 20) / 2, (height - 3*3) / 2, isSelecting);
            keyInput_Navigator(3);

        }
        else if(chosemenu == 1){

        }

        else if(chosemenu == 2){

        }

        else if(chosemenu == 3){

        }

        else if(chosemenu == 4){
            endgame = true;
        }

        else if(chosemenu == 5){

        }

        else if(chosemenu == 6){

        }
        else if (chosemenu == 7){
            if (!isWin())
                play();
            else chosemenu = -1;
        }
    }
    //if (isWin()) {
      //  cout << "Ban da daotanbu Vaporeon";
    //}

    return 0;
}
