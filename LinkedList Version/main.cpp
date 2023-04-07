#include "header.h"
#include "gamelogic.cpp"
#include "drawscreen.cpp"
/*
void printBoard() {
    cout << M << " " << N << endl;
    for (int i = 0; i <= M + 1; i++) {
        for (int j = 0; j <= N + 1; j++) {
            cout << (char) getData(i, j) << " ";
        }
        cout << endl;
    }
}
*/
void printBoard() {

    for (int i = 0; i <= M+1; i++) {
        for (int j = 0; j <=  N+1; j++){
            if (getData(i,j) != blankspace)
                if((p1.first == i && p1.second == j)|| (p2.first == i && p2.second ==j))
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 13*16 , getData(i,j));
                else if (choosing.first == i && choosing.second == j)
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15*16 , getData(i,j));
                else
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , CellColor[(getData(i,j) - 59)/3] , getData(i,j));
            else{
                SetColor(7);
                clearCanvas(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w,h);
            }
        }
    }
}
// GAMEPLAY FUNCTION

void updateBoard(){

    drawCell(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h , CellColor[(getData(oldchoosing.first,oldchoosing.second)- 59)/3] , getData(oldchoosing.first,oldchoosing.second));
    drawCell(calculateCellPosX(choosing.second,w,h,boardposx), calculateCellPosY(choosing.first,w,h,boardposy), w, h , 7*16 , getData(choosing.first,choosing.second));
    if (p1.first != 0 && p1.second != 0)
        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , 15*16 , getData(p1.first, p1.second));
    if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
        if (isLegalMove(p1, p2)) {
            changeData(p1.first, p1.second, blankspace);
            changeData(p2.first, p2.second, blankspace);
            drawPath(path,boardposx,boardposy);
            Sleep(100);
            clearVfx();
            if (Level > 1) {
                if (Level == 2 || Level == 3) {
                    deleteAndShiftBoard(p1.first);
                    deleteAndShiftBoard(p2.first);
                }
                else {
                    deleteAndShiftBoard(p1.second);
                    deleteAndShiftBoard(p2.second);
                }
            }
            p1 = p2 = {0,0};
            }
            else
            {
                drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(getData(p1.first, p1.second) - 59)/3] , getData(p1.first, p1.second));
                p1 = p2 = {0,0};
            }
    }

}

void keyInput_Play(){
        switch(_getch()){
        case KEY_UP: case 'w':
            if (choosing.first > 1){
                oldchoosing = choosing;
                choosing.first--;
            }

            else{
                oldchoosing = choosing;
                choosing.first = M;
            }

            break;
        case KEY_DOWN: case 's':
            if (choosing.first < M){
                oldchoosing = choosing;
                choosing.first++;
            }

            else{
                oldchoosing = choosing;
                choosing.first = 1;
            }

            break;
        case KEY_LEFT: case 'a':
            if (choosing.second > 1){
                oldchoosing = choosing;
                choosing.second--;
            }

            else{
                oldchoosing = choosing;
                choosing.second = N;
            }

            break;
        case KEY_RIGHT: case 'd':
            if (choosing.second < N){
                oldchoosing = choosing;
                choosing.second++;
            }

            else{
                oldchoosing = choosing;
                choosing.second = 1;
            }
            break;

        case ' ':
            if (halfpair){
                p2 = choosing;
                halfpair = false;
            }
            else{
                p1 = choosing;
                halfpair = true;
            }

            break;
        case 'h':{
            //if (score >= 200){
                //a hint is worth 200 score
                auto moveSuggested = moveSuggestion();
                oldchoosing = choosing;
                p1 = moveSuggested.first;
                choosing = moveSuggested.second;
                halfpair = true;

            //}
            break;
        }
        default:
            break;
        }
}

// GAMEPLAY FUNCTION
void play() {
        boardposx = calculateBoardPosX();
        boardposy = calculateBoardPosY();
        printBoard();
        while (!isWin()){
            if (!isPlayable()) {
                drawBox(offsetx+(width - 50)/2,offsety+(height-5)/2,50,5,6,"No valid move, shuffle!!! Press any key");
                _getch();
                shuffle();
                Sleep(50);
                clearScreen();
                printBoard();

            }
            else {
                keyInput_Play();
                updateBoard();
                }
            Sleep(40);
        }
        if (isWin()){
            p1 = p2 = oldchoosing = {0,0};
            halfpair = false;
            choosing = {1,1};
            Sleep(20);
            play();
        }


}



int main () {

    Level = 1;
    p1 = p2 = oldchoosing = {0,0};
    choosing = {1,1};
    initializeBoard();
    resizeConsole(0,0,1000,600);
    offsetx = 0;
    offsety = 0;
    boardposx = calculateBoardPosX();
    boardposy = calculateBoardPosY();
    printBoard();
    while (true) {
        if (!isPlayable()) {
            if (isWin() && Level == 5) {
                 drawBox(offsetx + (width - 60) / 2,offsety + (height - 4) / 2,60, 4, 14*16 + 4 , " VICTORY!! PRESS ANY KEY");
                _getch();

                break;
            }
            else if (isWin()) {
                p1 = p2 = oldchoosing = {0,0};
                halfpair = false;
                choosing = {1,1};
                deleteBoard();
                Level++;
                initializeBoard();
                continue;
            }
            else{
                while (!isPlayable()){
                    shuffle();
                }
            }
        }
        printBoard();
        keyInput_Play();
        if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
            if (isLegalMove(p1, p2)) {
                changeData(p1.first, p1.second, blankspace);
                changeData(p2.first, p2.second, blankspace);
                drawPath(path,boardposx,boardposy);
                Sleep(100);
                clearVfx();
                if (Level > 1) {
                    if (Level == 2 || Level == 3) {
                        deleteAndShiftBoard(p1.first);
                        deleteAndShiftBoard(p2.first);
                    }
                    else {
                        deleteAndShiftBoard(p1.second);
                        deleteAndShiftBoard(p2.second);
                    }
                }
                p1 = p2 = {0,0};
                }
                else
                    p1 = p2 = {0,0};
        }


    }

    deleteBoard();
    return 0;
}
