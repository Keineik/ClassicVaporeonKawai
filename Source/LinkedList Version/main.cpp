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

// GAMEPLAY FUNCTION

void updateBoard(){
    if (getData(oldchoosing.first,oldchoosing.second) != blankspace && oldchoosing.first > 0 && oldchoosing.second > 0){
        drawCell(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h , CellColor[(getData(oldchoosing.first,oldchoosing.second)- 59)/3] , getData(oldchoosing.first,oldchoosing.second));
    }
    else{
        SetColor(6);
        clearCanvas(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h);
    }
    if (choosing.first >= 0 && choosing.second >=0)
        drawCell(calculateCellPosX(choosing.second,w,h,boardposx), calculateCellPosY(choosing.first,w,h,boardposy), w, h , 7*16 , getData(choosing.first,choosing.second));
    if (p1.first > 0 && p1.second > 0)
        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , 15*16 , getData(p1.first, p1.second));
    if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
        if (isLegalMove(p1, p2)) {
            drawPath(path,boardposx,boardposy);
            Sleep(100);
            clearVfx();
            changeData(p1.first, p1.second, blankspace);
            changeData(p2.first, p2.second, blankspace);
            if (Level > 1) {
                if (Level == 2 || Level == 3) {
                    deleteAndShiftBoard(p1.first);
                    deleteAndShiftBoard(p2.first);
                    redrawRow(p1.first);
                    redrawRow(p2.first);
                }
                else {
                    deleteAndShiftBoard(p1.second);
                    deleteAndShiftBoard(p2.second);
                    redrawCol(p1.second);
                    redrawCol(p2.second);
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
        case 'r':
            shuffle();
            printBoard();
            p1 = p2 = {0,0};
            choosing = {1,1};
            break;

        case ' ':
            if (getData(choosing.first, choosing.second)!= blankspace)
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
        case 'm':
            deleteBoard();
            stopPlay = true;
            break;
        default:
            break;
        }
}

// GAMEPLAY FUNCTION
void play() {
        drawBox(0,0,width,height, 6, " ");
        p1 = p2 = oldchoosing = {0,0};
        choosing = {1,1};
        initializeBoard();
        offsetx = 0;
        offsety = 0;
        boardposx = calculateBoardPosX();
        boardposy = calculateBoardPosY();
        stopPlay = false;
        printBoard();
        gotoxy(20, 42); cout << "PRESS H FOR HINT - PRESS M TO RETURN TO MENU - PRESS R TO SHUFFLE";
        while (!stopPlay) {
            updateBoard();
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
                    printBoard();
                    continue;
                }
                else{
                    drawBox((width - 40)/2, (height - 4)/2, 40, 4, 6, "NO VALID MOVE! SHUFFLE!!");
                     while (!isPlayable()){
                        shuffle();
                    }
                    clearCanvas(1,1,width - 2, height - 2);
                    printBoard();
                }
            }
            keyInput_Play();
        }
}



int main () {
    ShowConsoleCursor(FALSE);
    resizeConsole(0,0,900,800);
    Level = 1;
    endgame = false;
    while (!endgame){
        if (MenuChoice == -1)
            showMenu();
        SetColor(6);
        clearScreen();
        if (MenuChoice == 0){
            M = 8; N = 16;
            Level = 1;
            play();
            SetColor(6);
            clearScreen();
            MenuChoice = -1;
        }
        else if (MenuChoice == 1){
            M = N = 0;
            drawCustomnizeMenu();
            if (M != 0 && N != 0){
                Level = 1;
                play();
            }
            SetColor(6);
            clearScreen();
            MenuChoice = -1;
        }
        else
            endgame = true;
    }


    deleteBoard();
    return 0;
}
