#include "header.h"
#include "gamelogic.cpp"
#include "drawscreen.cpp"

void updateBoard(int **board, int boardposx, int boardposy, pair<int,int> &p1, pair<int,int> &p2, pair <int,int> choosing, pair<int,int> oldchoosing, int &score ){

    if (board[oldchoosing.first][oldchoosing.second] != blankspace){
         drawCell(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h , CellColor[(board[oldchoosing.first][oldchoosing.second] - 59)/3] , board[oldchoosing.first][oldchoosing.second]);
    }
    else
        exposeBackground(calculateCellPosX(oldchoosing.second,w,h,boardposx), calculateCellPosY(oldchoosing.first,w,h,boardposy), w, h,background, backgroundx,backgroundy);
    drawCell(calculateCellPosX(choosing.second,w,h,boardposx), calculateCellPosY(choosing.first,w,h,boardposy), w, h , 7*16 , board[choosing.first][choosing.second]);
    if (p1.first > 0 && p1.second > 0)
        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , 15*16 , board[p1.first][p1.second]);
    if (p1.first > 0 && p1.second > 0 && p2.first > 0 && p2.second > 0){
        drawCell(calculateCellPosX(p1.second,w,h,boardposx), calculateCellPosY(p1.first,w,h,boardposy), w, h , 15*16 , board[p1.first][p1.second]);
        if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1){
            shuffle();
            drawBackground(background,backw,backh,backgroundx,backgroundy);
            printBoard();
        }
        else if (isLegalMove(p1, p2)) {
            updateScore();
            streakTimeRemain = 30;
            initializeStreakTimeBar();
            board[p1.first][p1.second] = board[p2.first][p2.second] = blankspace;
            drawPath(path,boardposx,boardposy);
            Sleep(100);
            clearVfx(p1,p2,path, backgroundx, backgroundy);
            switch (Level){
            case 2:
                shiftRowLeft(p1.first);
                shiftRowLeft(p2.first);
                redrawRow(p1.first);
                redrawRow(p2.first);
                break;
            case 3:
                shiftRowRight(p1.first);
                shiftRowRight(p2.first);
                redrawRow(p1.first);
                redrawRow(p2.first);
                break;
            case 4:
                shiftColUp(p1.second);
                shiftColUp(p2.second);
                redrawCol(p1.second);
                redrawCol(p2.second);
                break;
            case 5:
                shiftColDown(p1.second);
                shiftColDown(p2.second);
                redrawCol(p1.second);
                redrawCol(p2.second);
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
                SetColor(6);
                deleteBoard();
                clearScreen();
            }
            break;

        case ' ':
            if (board[choosing.first][choosing.second]!= blankspace)
                if (halfpair){
                    p2 = choosing;
                    halfpair = false;
                }
                else{
                    p1 = choosing;
                    halfpair = true;
                }
            break;

            break;
        case 'h':{
           // if (score >= 200){
                //a hint is worth 200 score
                isHint = true;
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
        offsety = 0;
        offsetx = 0;
        stopPlay = false;
        halfpair = false;
        initializeTimeBar();
        background_file[0] = '\0';
        // Link to the directory of background files
        string filename = ImageDir + backgroundAllwhite[Level - 1];
        // Start create background
        initializeBackground(background, backw, backh,backgroundx,backgroundy, filename );
        string music = SoundDir + sound[Level - 1];
        PlaySound(TEXT(music.c_str()),NULL, SND_ASYNC | SND_LOOP);
        drawBox(offsetx, offsety, width, height,6," ");
        drawBackground(background,backw,backh,backgroundx,backgroundy);
        boardposx = calculateBoardPosX();
        boardposy = calculateBoardPosY();
        printBoard();
        drawHUD();
        while (!stopPlay){
            if (isWin()){
                if (Level < 5){
                filename = ImageDir + backgroundColor[Level - 1];
                drawImage(offsetx+(width - backw)/2,offsety+(height - backh)/2, filename);
                Sleep(1000);
                deleteBackgroundInfo(background,backw,backh,backgroundx,backgroundy);
                int bonusScore = timeRemain*50;
                score += bonusScore;
                string dialog ="TIME LEFT: " + to_string(timeRemain) + "!!! BONUS: " + to_string(bonusScore) + "!!! Press any keys to continue";
                drawBox(offsetx + (width - 65) / 2,offsety + (height - 4) / 2,65, 4, 14*16 + 4 , dialog);
                _getch();
                p1 = p2 = oldchoosing = {0,0};
                halfpair = false;
                deleteBoard();
                initializeBoard();
                choosing = {1,1};
                Sleep(20);
                Level ++;
                timeRemain = 360;
                streakTimeRemain = 0;
                streak = 0;
                initializeTimeBar();
                stopPlay = false;
                Sleep(1000);
                play();
                }
                else {
                    drawBox(offsetx + (width - 60) / 2,offsety + (height - 4) / 2,60, 4, 14*16 + 4 , " VICTORY!! Press R to continue or M to quit");
                    _getch();
                    updateRecord();
                    updateLeaderboard();
                    stopPlay = true;
                    score = 0;
                    deleteBoard();
                }
            }
            else if (timeRemain > 0){
                displayTimeAndStatus();
                if (!isPlayable()) {
                    drawBox(offsetx+(width - 50)/2,offsety+(height-5)/2,50,5,6,"No valid move, shuffle!!! Press any key");
                    _getch();
                    while(!isPlayable())
                        shuffle();
                    Sleep(50);
                    SetColor(6);
                    clearCanvas(offsetx+1, offsety+1, width - 2, height - 2);
                    drawHUD();
                    drawBackground(background,backw,backh,backgroundx,backgroundy);
                    printBoard();

                }
                else {
                    keyInput_Play();
                    updateBoard(board,boardposx,boardposy,p1,p2,choosing,oldchoosing,score);
                    }

            }
            else{
                drawBox(offsetx + (width - 60) / 2, offsety + (height - 4) / 2,60,4, 4, "Skill issues detected!! Press R to replay or M to quit");
                switch(_getch()){
                    case 'r':
                        p1 = p2 = oldchoosing = {0,0};
                        halfpair = false;
                        deleteBoard();
                        initializeBoard();
                        SetColor(6);
                        clearCanvas(offsetx+1, offsety+1, width - 2, height - 2);
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


}

int main () {
    readBinFile();
    readLeaderboardFile();
    ShowConsoleCursor(false);
    resizeConsole((1920-WindowW)/2,(1080-WindowH)/2, WindowW,WindowH);
    Sleep(10);
    newAccount = successLogin = false;

    while (!endgame) {
        if (GameMenuChoice == -1 || stopPlay )
        PlaySound(TEXT("./assets/sounds/menu.wav"),NULL, SND_ASYNC | SND_LOOP);
        offsetx = (ConsoleCol - width) / 2 ;
        offsety = 3;
        if (GameMenuChoice == -1){
             if(entermainmenu){
                drawImage(offsetx + 5, offsety ,"./assets/txtimages/title.txt");
                drawImage(offsetx - 10, offsety + 20,"./assets/txtimages/pikachu.txt");
                drawImage(offsetx + 75,offsety + 17,"./assets/txtimages/vaporeon.txt");
                entermainmenu = false;
            }
            SetColor(6);
            gotoxy(offsetx + 25, offsety + 40); cout << "USE ARROW KEYS OR WASD TO MOVE. PRESS SPACEBAR TO SELECT.";
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
                username[0] = '\0'; // clear username
                password[0] = '\0'; // clear password
                clearScreen();
                drawLoginForm();
                successLogin = login(username,password);

                }
            }

            if (successLogin || newAccount){
                SetColor(6);
                clearScreen();
                showLoginMenu();
                if (LoginMenuChoice == 0){
                    M = 8; N = 16;
                    score = 0; timeRemain = 360;
                    streak = streakTimeRemain = 0;
                    initializeTimeBar();
                    initializeBoard();
                    halfpair = false;
                    choosing = {1,1};
                    p1 = p2 = oldchoosing = {0,0};
                    stopPlay = false;
                    Level = 1;
                    play();
                    SetColor(6);
                    clearScreen();
                    LoginMenuChoice = -1;
                }
                else if (LoginMenuChoice == 1){
                    load = true;
                    SlotMenuChoice = -1;
                    SlotMenuSelecting = -1;
                    showLoadMenu();
                }
                else if (LoginMenuChoice == 2){
                    M = N = 0;
                    drawCustomnizeMenu();
                    if (M != 0 && N != 0){
                        initializeBoard();
                        score = 0;
                        initializeTimeBar();
                        choosing = {1,1};
                        p1 = p2 = oldchoosing = {0,0};
                        stopPlay = false;
                        Level = 1;
                        play();
                    }
                    SetColor(6);
                    clearScreen();
                    LoginMenuChoice = -1;
                }
                else if (LoginMenuChoice == 3){
                    drawHow2Play();
                    clearScreen();
                    LoginMenuChoice = -1;
                }
                else if (LoginMenuChoice == 4){
                    drawLeaderboardandHighScore();
                    _getch();
                    SetColor(6);
                    LoginMenuChoice = -1;
                }
                else if (LoginMenuChoice == 5){
                    drawCredit();
                    _getch();
                    LoginMenuChoice = -1;

                }
                else if (LoginMenuChoice == 6){
                    LoginMenuChoice = LoginMenuSelecting = -1;
                    GameMenuChoice = -1;
                    GameMenuSelecting = -1;
                    newAccount = false;
                    successLogin = false;
                    entermainmenu = true;
                    writeLeaderboardFile();
                    writeBinFile();
                    logout();
                }
                else if(LoginMenuChoice == 10){
                    drawHackingConsole();
                    SetColor(6);
                    clearScreen();
                    ShowConsoleCursor(FALSE);
                    LoginMenuChoice = -1;
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
                            drawBox(offsetx + (width - 50)/2,offsety +  (height - 4) / 2,50,4, 14*16+12, "Username existed!! Press any key or M(menu)" );
                            choice = _getch();
                            break;
                        case -2:
                            drawBox(offsetx + (width - 50)/2,offsety +  (height - 4) / 2,50,4, 14*16+12, "Username invalid!! Press any key or M(menu)" );
                            choice = _getch();
                            break;
                        case 0:
                            drawBox(offsetx + (width - 60)/2,offsety +  (height - 4) / 2,60,4, 14*16+12, "Retyped password doesn't match!! Press any key or M(menu)" );
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
                username[0] = '\0';
                password[0] = '\0';
                retypepassword[0] = '\0';
                drawSignupForm();
                result  = signUp(username,password,retypepassword);

            }
            if (result == 1){
                newAccount = true;
                GameMenuChoice = 0;
                clearScreen();
                drawBox(offsetx+(width - 40)/2, offsety+(height - 4) / 2,40,4, 14*16+12, "Success !! Press any key" );
                writeBinFile();
                _getch();
                SetColor(15);
                clearScreen();
            }
        }
        else if (GameMenuChoice == 2){
            showGuestMenu();
            if (GuestMenuChoice == 0){
                    score = 0;
                    PlaySound(NULL, NULL, 0);
                    initializeTimeBar();
                    PlaySound(TEXT("C:/Users/W.Long/Downloads/Megalovania.wav"),NULL, SND_ASYNC | SND_LOOP);
                    M = 8; N = 16;
                    initializeBoard();
                    choosing = {1,1};
                    p1 = p2 = oldchoosing = {0,0};
                    stopPlay = false;
                    Level = 1;
                    play();
                    SetColor(6);
                    clearScreen();
                    GuestMenuChoice = -1;
                    GuestMenuSelecting = 0;
                }
                else if (GuestMenuChoice == 1){
                    M = N = 0;
                    drawCustomnizeMenu();
                    if (M != 0 && N != 0){
                        initializeBoard();
                        score = 0;
                        initializeTimeBar();
                        choosing = {1,1};
                        p1 = p2 = oldchoosing = {0,0};
                        stopPlay = false;
                        Level = 1;
                        play();
                    }
                    SetColor(6);
                    clearScreen();
                    GuestMenuChoice = -1;
                    GuestMenuSelecting = 0;

                }
                else if (GuestMenuChoice == 2){
                    drawHow2Play();
                    clearScreen();
                    GuestMenuChoice = -1;
                }
                else if (GuestMenuChoice == 3){
                    drawLeaderboard();
                    _getch();
                    clearScreen();
                    GuestMenuChoice = -1;
                }
                else if (GuestMenuChoice == 4){
                    drawCredit();
                    _getch();
                    clearScreen();
                    GuestMenuChoice = -1;
                }
                else if (GuestMenuChoice == 5){
                    GuestMenuChoice = GuestMenuSelecting = -1;
                    GameMenuChoice = -1;
                    GameMenuSelecting = -1;
                    entermainmenu = true;

                }
        }
        else if (GameMenuChoice == 3){
            endgame = true;
        }
    }
    return 0;
}

