 #include "header.h"
#include "gamelogic.cpp"
#include "drawscreen.cpp"
#include "account.cpp"

// This part contain how Menus in this game work


void drawNormalMenu(int MenuSelecting, int MenuSize, string Menu[]){
    int x = offsetx+(width - 20) / 2;
    int y = offsety+(height - MenuSize*(2+1))/2;
    for (int i = 0;  i < MenuSize; i++)
            drawBox(x,y+i*2+i,20,2,(MenuSelecting == i ? 7*16 : 6), Menu[i]);

}

void drawSaveLoadMenu(){
    int x = offsetx + (width - 40) / 2;
    int y = offsety + (height - size(SlotMenu)*(2+1))/2;
    for ( int i = 0;  i < size(SlotMenu); i++)
        if (currentSave.state[i].p != 0){
            if (SlotMenuSelecting == i){
                drawBox(x,y+i*2+i,40,2,7*16, " ");
                gotoxy(x+1,y+i*2+i+1); cout << right << setw(2) << setfill('0') << currentSave.state[i].date.dd << "/" << setw(2)  << currentSave.state[i].date.mm << "/" << setw(4) << currentSave.state[i].date.yy << " Score:" << setw(6) << setfill(' ') << currentSave.state[i].points;
            }

            else{
                drawBox(x,y+i*2+i,40,2,2, " ");
                gotoxy(x+1,y+i*2+i+1); cout << right << setw(2) << setfill('0') << currentSave.state[i].date.dd << "/" << setw(2)  << currentSave.state[i].date.mm << "/" << setw(4) << currentSave.state[i].date.yy << " Score:" << setw(6) << setfill(' ') << currentSave.state[i].points;
            }

        }
        else{
             if (SlotMenuSelecting == i)
                drawBox(x,y+i*2+i,40,2,7*16, SlotMenu[i]);
            else
                drawBox(x,y+i*2+i,40,2,6, SlotMenu[i]);
        }
}

void navigateMenu(int &MenuSelecting, int &MenuChoice, int MenuSize){
    switch(_getch()){
        case KEY_UP: case 'w':
            if (MenuSelecting <= 0)
                MenuSelecting = MenuSize - 1;
            else
                MenuSelecting--;
            break;
        case KEY_DOWN: case 's':
            if (MenuSelecting >= MenuSize -1)
                MenuSelecting = 0;
            else
                MenuSelecting++;
            break;
        case ' ':
            MenuChoice = MenuSelecting;
            SetColor(0);
            clearScreen();
            break;
        default:
            break;
        }
}

void showGameMenu(){
    while(GameMenuChoice == -1){
        drawNormalMenu(GameMenuSelecting,size(GameMenu),GameMenu);
        navigateMenu(GameMenuSelecting,GameMenuChoice, size(GameMenu));
    }

}

void showLoginMenu(){
    while (GameMenuChoice == 0 && LoginMenuChoice == -1){
        drawNormalMenu(LoginMenuSelecting,size(LoginMenu),LoginMenu);
        navigateMenu(LoginMenuSelecting,LoginMenuChoice, size(LoginMenu));
    }

}

void showGuestMenu(){
    while (GameMenuChoice == 2 && GuestMenuChoice == -1) {
        drawNormalMenu(GuestMenuSelecting,size(GuestMenu),GuestMenu);
        navigateMenu(GuestMenuSelecting, GuestMenuChoice,size(GuestMenu));
    }

}

void showSaveMenu(){
    SlotMenuChoice = -1;
    SlotMenuSelecting = 0;
    while (save) {
        drawSaveLoadMenu();
        navigateMenu(SlotMenuSelecting,SlotMenuChoice,size(SlotMenu));
        if (SlotMenuChoice != -1)
             if (SlotMenuChoice == size(SlotMenu) - 1){
                SlotMenuChoice = -1;
                SlotMenuSelecting = -1;
                printBoard(p1,p2,boardposx,boardposy);
                stopPlay = false;
                play();
            }
            else if(currentSave.state[SlotMenuChoice].p == 0){
                saveGame(SlotMenuChoice);
                SlotMenuChoice = -1;
                SlotMenuSelecting = -1;
                LoginMenuChoice = -1;
                LoginMenuSelecting = -1;
                save = false;
                stopPlay = true;
            }
            else{
                drawBox(offsetx + (width - 30)/2,offsety + (height - 4)/2,30,4,9,"Overwrite ? Y(YES) / N(NO)");
                char c = _getch();
                if (c == 'y' || c == 'Y'){
                    saveGame(SlotMenuChoice);
                    SlotMenuChoice = -1;
                    SlotMenuSelecting = -1;
                    LoginMenuChoice = -1;
                    LoginMenuSelecting = -1;
                    save = false;
                    stopPlay = true;
                    deleteBoard();
                }
                else{
                    save = true;
                    SlotMenuChoice = -1;
                    clearScreen();
                    showSaveMenu();
                }

            }
    }

}

void showLoadMenu(){
    SlotMenuChoice = -1;
    SlotMenuSelecting = 0;
    while (load) {
        drawSaveLoadMenu();
        navigateMenu(SlotMenuSelecting,SlotMenuChoice,size(SlotMenu));
        if (SlotMenuChoice != -1)
            if (SlotMenuChoice == size(SlotMenu) - 1){
                // Return to Login Menu
                LoginMenuChoice = -1;
                load = false;
            }
            else if(currentSave.state[SlotMenuChoice].p != 0){
                // Load old gameplay from selected slot and start play
                loadGame(SlotMenuChoice);
                load = false;
                boardposx = calculateBoardPosX();
                boardposy = calculateBoardPosY();
                p1 = p2 = oldchoosing = {0,0};
                choosing = {currentSave.state[SlotMenuChoice].p_,currentSave.state[SlotMenuChoice].q_};
                score = currentSave.state[SlotMenuChoice].points;
                printBoard(p1,p2,boardposx,boardposy);
                stopPlay = false;
                load = false;
                play();
                }
                else
                {
                    // This happen when the selected slot contains no data, output a dialog box
                    drawBox(offsetx + (width - 30)/2,offsety + (height - 4)/2,30,4,9,"No data! Press any key");
                    _getch();
                    clearScreen();
                    load = true;
                    SlotMenuChoice = -1;
                    showLoadMenu();
                }

    }



}

void updateBoard(int **board, int boardposx, int boardposy, pair<int,int> &p1, pair<int,int> &p2, pair <int,int> choosing, pair<int,int> oldchoosing, int &score ){

    drawCell(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h , CellColor[(board[oldchoosing.first][oldchoosing.second] - 59)/3] , board[oldchoosing.first][oldchoosing.second]);
    drawCell(calculateCellPosX(choosing.second,w,h,boardposx), calculateCellPosY(choosing.first,w,h,boardposy), w, h , 7*16 , board[choosing.first][choosing.second]);
    if (p1.first != 0 && p1.second != 0)
        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , 15*16 , board[p1.first][p1.second]);
    if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
                if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1){
                    shuffle();
                    drawBackground(background,backw,backh,backgroundx,backgroundy);
                    printBoard(p1,p2,boardposx,boardposy);
                }
                else if (isLegalMove(p1, p2)) {
                    ScoreAndStreak();
                    streakTimeRemain = 15;
                    board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
                    drawPath(path,boardposx,boardposy);
                    Sleep(100);
                    clearVfx(p1,p2,path, backgroundx, backgroundy);
                    switch (Level){
                    case 2:
                        shiftRowLeft(p1.first);
                        shiftRowLeft(p2.first);
                        drawBackground(background,backw,backh,backgroundx,backgroundy);
                        printBoard(p1,p2,boardposx,boardposy);
                        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(board[p1.first][p1.second] - 59)/3] , board[p1.first][p1.second]);
                        break;
                    case 3:
                        shiftRowRight(p1.first);
                        shiftRowRight(p2.first);
                        drawBackground(background,backw,backh,backgroundx,backgroundy);
                        printBoard(p1,p2,boardposx,boardposy);
                        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(board[p1.first][p1.second] - 59)/3] , board[p1.first][p1.second]);
                        break;
                    case 4:
                        shiftColUp(p1.second);
                        shiftColUp(p2.second);
                        drawBackground(background,backw,backh,backgroundx,backgroundy);
                        printBoard(p1,p2,boardposx,boardposy);
                        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(board[p1.first][p1.second] - 59)/3] , board[p1.first][p1.second]);
                        break;
                    case 5:
                        shiftColDown(p1.second);
                        shiftColDown(p2.second);
                        drawBackground(background,backw,backh,backgroundx,backgroundy);
                        printBoard(p1,p2,boardposx,boardposy);
                        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(board[p1.first][p1.second] - 59)/3] , board[p1.first][p1.second]);
                        break;
                    default:
                        break;
                    }
                    p1 = p2 = {0,0};
                    }
                    else
                    {
                        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , CellColor[(board[p1.first][p1.second] - 59)/3] , board[p1.first][p1.second]);
                        p1 = p2 = {0,0};
                        streak = 0;

                    }

    }
}

void keyInput_Play(){
    if(_kbhit())
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
        case 'm': // Save game and go back to login menu
            if (newAccount || successLogin){
                save = true;
                SetColor(7);
                clearScreen();
                drawBox(offsetx,offsety,width,height,6, " ");
                showSaveMenu();
            }
            else
            {
                stopPlay = true;
                GuestMenuChoice = -1;
                deleteBoard();
                clearScreen();
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
            if (score >= 200){
                //a hint is worth 200 score
                isHint = true;
                auto moveSuggested = moveSuggestion();
                oldchoosing = choosing;
                p1 = moveSuggested.first;
                choosing = moveSuggested.second;
                halfpair = true;

            }
            break;

        }
        default:
            break;
        }
}

// GAMEPLAY FUNCTION
void play() {
        initializeBackground(background, backw, backh,backgroundx,backgroundy, "./assets/txtimages/amongustwerk_allwhite.txt");
        drawBox(offsetx, offsety, width, height,6," ");
        drawBackground(background,backw,backh,backgroundx,backgroundy);
        boardposx = calculateBoardPosX();
        boardposy = calculateBoardPosY();
        drawHUD();
        printBoard(p1,p2,boardposx,boardposy);
        while (!isWin() && timeRemain > 0){
            displayTimeAndStatus();
            if (!isPlayable()) {
                drawBox(offsetx+(width - 50)/2,offsety+(height-5)/2,50,5,6,"No valid move, shuffle!!! Press any key");
                _getch();
                shuffle();
                Sleep(50);
                clearScreen();
                drawBox(offsetx,offsety,width,height,6," ");
                drawBackground(background,backw,backh,backgroundx,backgroundy);
                printBoard(p1,p2,boardposx,boardposy);

            }
            else {
                keyInput_Play();
                if (stopPlay)
                    break;
                updateBoard(board,boardposx,boardposy,p1,p2,choosing,oldchoosing,score);
                }
            Sleep(tick);
        }
        if (isWin()){
            drawImage(offsetx+(width - backw)/2,offsety+(height - backh)/2,"./assets/txtimages/amongustwerk.txt");
            deleteBackgroundInfo(background,backw,backh,backgroundx,backgroundy);
            Sleep(1000);
            drawBox(offsetx + (width - 60) / 2,offsety + (height - 4) / 2,60, 4, 14*16 + 4 , " BOARD CLEAR SIR!! Press R to continue or M to quit");
            _getch();
            p1 = p2 = oldchoosing = {0,0};
            halfpair = false;
            deleteBoard();
            initializeBoard();
            choosing = {1,1};
            Sleep(20);
            Level ++;
            stopPlay = false;
            play();
        }
        else if(timeRemain == 0 ){
            drawBox(offsetx + (width - 60) / 2, offsety + (height - 4) / 2,60,4, 4, "Skill issues detected!! Press R to replay or M to quit");
            switch(_getch()){
                case 'r':
                    p1 = p2 = oldchoosing = {0,0};
                    halfpair = false;
                    deleteBoard();
                    initializeBoard();
                    shuffle();
                    clearCanvas(1,1,width - 2, height - 2);
                    choosing = {1,1};
                    Sleep(20);
                    stopPlay = false;
                    play();
                    break;
                default:
                    deleteBoard();
                    deleteBackgroundInfo(background,backw,backh,backgroundx,backgroundy);
                    stopPlay = true;
                    entermainmenu = true;
                    clearScreen();
                    drawBox(offsetx,offsety,width,height,6, " ");
                    break;
            }
        }
}




int main () {
    readBinFile();
    ShowConsoleCursor(false);
    resizeConsole((1920-WindowW)/2,(1080-WindowH)/2, WindowW,WindowH);
    Sleep(10);
    newAccount = successLogin = false;
    while (!endgame) {
        offsetx = (ConsoleCol - width) / 2 ;
        offsety = 3;
        if (GameMenuChoice == -1){
             if(entermainmenu){
                drawImage(offsetx + 1, offsety + 1,"./assets/txtimages/title.txt");
                drawImage(offsetx + 1, offsety + 20,"./assets/txtimages/pikachu.txt");
                drawImage(offsetx + 61,offsety + 17,"./assets/txtimages/vaporeon.txt");
                entermainmenu = false;
            }
            showGameMenu();
        }

        else if (GameMenuChoice == 0)
        {
            if (!newAccount && !successLogin ){
                drawLoginForm();
                successLogin  = login(username,password);
                char choice;
                while(!successLogin){
                drawBox(offsetx +(width - 60)/2, offsety + (height - 4) / 2,60,4, 14*16+12, "Wrong username or Password!! Press any key or M(menu)" );
                choice = _getch();
                // If user choose M, return to game menu
                SetColor(15);
                if (tolower(choice) == 'm'){
                    GameMenuChoice = -1;
                    clearScreen();
                    entermainmenu = true;
                    break;
                }
                //Otherwise, continue get login input
                strcpy(username,""); // clear username
                strcpy(password,""); // clear password
                clearScreen();
                drawLoginForm();
                successLogin = login(username,password);

                }
            }

            if (successLogin || newAccount){
                clearScreen();
                showLoginMenu();
                if (LoginMenuChoice == 0){
                    M = 8; N = 16;
                    score = 0; timeRemain = 360;
                    streak = streakTimeRemain = 0;
                    initializeBoard();
                    choosing = {1,1};
                    p1 = p2 = oldchoosing = {0,0};
                    stopPlay = false;
                    Level = 1;
                    play();
                }
                else if (LoginMenuChoice == 1){
                    load = true;
                    SlotMenuChoice = -1;
                    SlotMenuSelecting = -1;
                    showLoadMenu();
                }
                else if (LoginMenuChoice == 2){

                }
                else if (LoginMenuChoice == 3){

                }
                else if (LoginMenuChoice == 4){
                    drawHow2Play();
                }
                else if (LoginMenuChoice == 5){

                }
                else if (LoginMenuChoice == 6){

                }
                else if (LoginMenuChoice == 7){
                    LoginMenuChoice = LoginMenuSelecting = -1;
                    GameMenuChoice = -1;
                    GameMenuSelecting = -1;
                    newAccount = false;
                    successLogin = false;
                    entermainmenu = true;
                    logout();
                }
            }
        }
        else if (GameMenuChoice == 1){
            //Using loop for Signing up, if success signup return to login menu
            drawSignupForm();
            int result  = signUp(username,password,retypepassword);
            char choice;
            while(result != 1){
                    switch (result){
                        case -1:
                            drawBox((width - 50)/2, (height - 4) / 2,50,4, 14*16+12, "Username existed!! Press any key or M(menu)" );
                            choice = _getch();
                            break;
                        case -2:
                            drawBox((width - 50)/2, (height - 4) / 2,50,4, 14*16+12, "Username invalid!! Press any key or M(menu)" );
                            choice = _getch();
                            break;
                        case 0:
                            drawBox((width - 60)/2, (height - 4) / 2,60,4, 14*16+12, "Retyped password doesn't match!! Press any key or M(menu)" );
                            choice = _getch();
                            break;
                    }
                // If user choose M, return to game menu
                SetColor(15);
                if (tolower(choice) == 'm'){
                    clearScreen();
                    entermainmenu = true;
                    GameMenuChoice = -1;
                    break;
                }
                clearScreen();
                // Otherwise continue getting signup input
                strcpy(username,""); // reset username
                strcpy(password,""); // reset password
                strcpy(retypepassword,""); // reset retype password
                drawSignupForm();
                result  = signUp(username,password,retypepassword);

            }
            if (result == 1){
                newAccount = true;
                GameMenuChoice = 0;
                clearScreen();
                drawBox(offsetx+(width - 40)/2, offsety+(height - 4) / 2,40,4, 14*16+12, "Success !! Press any key" );
                _getch();
                SetColor(15);
                clearScreen();
            }
        }
        else if (GameMenuChoice == 2){
            showGuestMenu();
            if (GuestMenuChoice == 0){
                    M = 8; N = 16;
                    initializeBoard();
                    choosing = {1,1};
                    p1 = p2 = oldchoosing = {0,0};
                    stopPlay = false;
                    Level = 1;
                    play();
                    GuestMenuChoice = -1;
                    GuestMenuSelecting = 0;
                }
                else if (GuestMenuChoice == 1){
                    M = N = 0;
                    drawCustomnizeMenu();
                    if (M != 0 && N != 0){
                        initializeBoard();
                        choosing = {1,1};
                        p1 = p2 = oldchoosing = {0,0};
                        stopPlay = false;
                        Level = 1;
                        play();
                    }
                    GuestMenuChoice = -1;
                    GuestMenuSelecting = 0;

                }
                else if (GuestMenuChoice == 2){

                }
                else if (GuestMenuChoice == 3){

                }
                else if (GuestMenuChoice == 4){
                    drawHow2Play();
                }
                else if (GuestMenuChoice == 5){
                    GuestMenuChoice = GuestMenuSelecting = -1;
                    GameMenuChoice = -1;
                    GameMenuSelecting = -1;
                    entermainmenu = true;

                }
        }
        else if (GameMenuChoice == 3){
            writeBinFile();
            endgame = true;

        }
    }
    writeBinFile();
    return 0;
}

