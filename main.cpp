#include "header.h"
#include "gamelogic.cpp"
#include "drawscreen.cpp"
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80




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
        case 'r':
            //for testing
            p1 = p2 = {0,0};
            halfpair = false;
            deleteBoard();
            initializeBoard();
            shuffle();
            clearCanvas(1,1,width - 2, height - 2);
            chosex = chosey = 1;
            Sleep(20);
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
        case 'h':{
            auto moveSuggested = moveSuggestion();
            p1= moveSuggested.first;
            chosex = moveSuggested.second.first;
            chosey = moveSuggested.second.second;
            halfpair = true;
            break;
        }

        case 'm':
            chosemenu = -1;
            entermainmenu = true;
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
                deleteBoard();
            initializeBoard();
            chosex = 1; chosey = 1;
            p1 = {0,0};
            p2 = {0,0};
            boardposx = calculatBoardPosX(width,w,N);
            boardposy = calculatBoardPosY(height,h,M);
        }
        if (chosemenu == 0){
            chosemenu = isSelecting + 5;
        }
        else
            chosemenu = isSelecting;
        isSelecting = -1;
        entermainmenu = true;
        clearCanvas(1,1,width - 2, height - 2);
        break;
    default:
        break;
    }

}


void play() {
    drawHUD(width, height);

    if (!isPlayable()) {
        clearCanvas(1,1,width - 2, height - 2);
        drawBox((width - 50)/2,(height-5)/2,50,5,6,"No valid move, shuffle!!! Press any key");
        _getch();
        shuffle();
        Sleep(50);
        clearCanvas(1,1,width - 2, height - 2);
    }
    else {
        printBoard(width,height,p1,p2,boardposx,boardposy);
        keyInput_Play();
        if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
            if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1)
                shuffle();
            else if (isLegalMove(p1, p2)) {
                board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
                drawPath(path,boardposx,boardposy);
                gotoxy(101,40);
                cout << size(path);
                Sleep(100);
                p1 = p2 = {0,0};
                }
                else
                {
                    p1 = p2 = {0,0};
                }

        }

    }
}

int main () {
    ShowConsoleCursor(false);
    resizeConsole((1920-1000)/2,(1080-800)/2, 1000,800);
    char username[100], password[100];
    chosex = 1; chosey = 1;
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
            if(entermainmenu){
                drawImage(1,1,100,"title.txt");
                drawImage(1,20,50,"pikachu.txt");
                drawImage(61,17,50,"vaporeon.txt");
                entermainmenu = false;
            }
            drawMainMenu(width, height , isSelecting);
            keyInput_Navigator(5);
        }
        else if(chosemenu == 0){
            drawLoginMenu(width, height, isSelecting);
            keyInput_Navigator(3);

        }
        else if(chosemenu == 1){
            drawHow2Play();
            if(_getch()){
               // clearCanvas(1,1,width - 2, height - 2);
               clearScreen();
                drawBox(0,0,width,height,6, " ");
                chosemenu = -1;

            }

        }

        else if(chosemenu == 2){

        }

        else if(chosemenu == 3){

        }

        else if(chosemenu == 4){
            endgame = true;
        }

        else if(chosemenu == 5){
            drawLoginForm(width,height,username,password);
            if(_getch()){
               // clearCanvas(1,1,width - 2, height - 2);
                clearScreen();
                drawBox(0,0,width,height,6, " ");
                chosemenu = -1;

            }
        }

        else if(chosemenu == 6){
            drawSignupForm(width,height,username,password);
            if(_getch()){
               // clearCanvas(1,1,width - 2, height - 2);
                clearScreen();
                drawBox(0,0,width,height,6, " ");
                chosemenu = -1;
                entermainmenu =  true;

            }
        }
        else if (chosemenu == 7){
            if (!isWin())
                play();
            else {
                chosemenu = -1;
                entermainmenu =  true;
            }

        }
    }
    deleteBoard();
    return 0;
}

