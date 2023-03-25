#include "drawscreen.h"


// Set console pointer to coordinator (x,y)
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void resizeConsole(int posx, int posy, int width, int height)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd,posx,posy,width,height,TRUE);
}

void SetWindowSize()
{
    // SHORT is the type of variable in WINAPI
    SHORT width = 400; // Width of console
    SHORT height = 200;  // Height of console

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void TextColor(int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

//Set color for cout
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Clear Canvas

void clearCanvas(int x, int y, int width, int height){
    for (int i = x; i <=  x+width; i++)
    for (int j = y; j <= y+height; j++){
        gotoxy(i,j);
        cout <<" ";
    }
}

void clearScreen(){
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

// Draw box
void drawBox(int x, int y, int w, int h, int color, string s){

    SetColor(color);

    for (int i = x; i<= x+w; i++){
        gotoxy(i,y);
        cout <<char(205);
        gotoxy(i, y+h);
        cout << char(205);
    }
    for (int i = y; i <= y + h; i++){
        gotoxy(x,i);
        cout << char(186);
        gotoxy(x+w,i);
        cout << char(186);
    }
    if (s != " "){
        gotoxy(x+ 2, y+h/2); cout << s;

    }
    gotoxy(x,y); cout << char(201);
    gotoxy(x+w,y); cout << char(187);
    gotoxy(x,y+h); cout << char(200);
    gotoxy(x+w,y+h); cout << char(188);

}

void drawCell(int x, int y, int w, int h, int color, char c){
        if(c != blankspace){
                SetColor(color);
        for (int i = x; i<= x+w; i++){
            gotoxy(i,y);
            cout <<char(196);
            gotoxy(i, y+h);
            cout << char(196);
        }
        for (int i = y; i < y + h; i++){
            gotoxy(x,i);
            cout << char(179);
            gotoxy(x+w,i);
            cout << char(179);
        }
        gotoxy(x+ 2, y+h/2); cout << c;
        gotoxy(x,y); cout << char(218);
        gotoxy(x+w,y); cout << char(191);
        gotoxy(x,y+h); cout << char(192);
        gotoxy(x+w,y+h); cout << char(217);

        }
        else
            clearCanvas(x,y,w,h);

}
// Draw menu

/*
    Main Menu - 1
    Play: 0
    -Login: 5
    -Signup 6
    -Play as guest 7
    How to play 1
    Highscore: 2
    Credit: 3
    Quit: 4
*/
void drawMainMenu(int width,int height,int isSelecting){
    string s[5] = {"PLAY","HOW TO PLAY","HIGH SCORE","CREDIT", "QUIT"};
    int x = (width - 20) / 2;
    int y = (height - 4*3) / 2;
    int color = 6,selectcolor = 9;
    for (int i = 0; i<5; i++){
        if (isSelecting==i)
            drawBox(x,y +(i * 2 + i) , 20, 2,selectcolor, s[i]);
        else
            drawBox(x,y +(i * 2 + i) , 20, 2,color, s[i]);

    }
}

void drawLoginMenu(int width, int height, int isSelecting){

    string s[3] = {"Log in", "Sign up", "Play as guest" };
    int color = 6,selectcolor = 9;
    int x = ( width - 20) / 2;
    int y = (height - 3*3) / 2;
    for (int i = 0; i<3; i++){
        if (isSelecting==i)
            drawBox(x,y +(i * 2 + i) , 20, 2,selectcolor, s[i]);
        else
            drawBox(x,y +(i * 2 + i) , 20, 2,color, s[i]);
    }
}
// Draw Login/Signup Form

void drawLoginForm(int width, int height, char username[], char password[]){
    int x, y;
    x = (width - 20) / 2;
    y = (height - (2*4)) / 2;
    gotoxy(x,y);
    SetColor(6);
    cout << "USERNAME";
    drawBox(x,y+1,20,2,6," ");
    gotoxy(x, y + 5);
    cout << "PASSWORD";
    drawBox(x,y + 6, 20,2,6," ");
}

void drawSignupForm(int width, int height, char username[], char password[]){
    int x, y;
    x = (width - 20) / 2;
    y = (height - (2*6)) / 2;
    gotoxy(x,y);
    SetColor(6);
    cout << "USERNAME";
    drawBox(x,y+1,20,2,6," ");
    gotoxy(x, y + 4);
    cout << "PASSWORD";
    drawBox(x,y + 5, 20,2,6," ");
    gotoxy(x,y+8);
    cout << "RE-TYPE PASSWORD";
    drawBox(x,y+9,20,2,6," ");
}


// Draw How to play

void drawHow2Play(){
    gotoxy (5,5);
    cout << "Interaction:";
    gotoxy(10,6);
    cout << "Move :";
    gotoxy(12, 10);
    cout << "WASD";drawCell(17, 11,4,2,6,'A'); drawCell(23,8,4,2,6,'W'); drawCell(23,11,4,2,6,'S'); drawCell(29,11,4,2,6,'D');
    gotoxy(12,17);
    cout << "ARROWKEYS"; drawCell(22, 18,4,2,6,'<'); drawCell(28,15,4,2,6,'^'); drawCell(28,18,4,2,6,'v'); drawCell(34,18,4,2,6,'>');
    gotoxy(12,24);
    cout << "Select:"; drawBox(22,23,16,2,6,"   SPACEBAR   ");
}
// Draw In-game HUD

void drawHUD(int width, int height){
    drawBox(0,height+1,width / 2 - 1, 4, 6, "Player: Username");
    drawBox(width/2+1,height+1,width /2 - 1,4,6, "Score: XXX");
    drawBox(width+1,0,15,4,6,"LEVEL: X");
    drawBox(width+1,5,15,4,6,"TIMER");
}

// Draw play board
int calculateCellPosX(int j, int w, int h, int boardposx){
    return (boardposx + j*w + j);
}

int calculateCellPosY(int i, int w, int h, int boardposy){
    return (boardposx + i*h + i);
}

int calculatBoardPosX(int width,int w,int N){
    return (width  - ((N+2)*(w+1)))/2 ;

}

int calculatBoardPosY(int height,int h, int M){
    return (height -((M+2)*(h+1)))/2;

}

void printBoard(int width, int height,pair<int, int> p1, pair<int,int> p2,int boardposx,int boardposy) {

    for (int i = 0; i <= M+1; i++) {
        for (int j = 0; j <=  N+1; j++){
            if((p1.first == i && p1.second == j)|| (p2.first == i && p2.second ==j))
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 4 , board[i][j]);
            else if (chosex == i && chosey == j)
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 1 , board[i][j]);
            else
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 6 , board[i][j]);

        }
    }
}

// Draw legal move
void drawBar(int startx, int endx, int posy){
    if (startx > endx) swap(startx,endx);
    for (int i =  startx; i <= endx; i++){
                gotoxy(i,posy);
                cout << char(205);
            }
}

void drawColumn(int starty, int endy, int posx){
    if (starty > endy) swap(starty,endy);
    for (int i =  starty; i <= endy; i++){
                gotoxy(posx,i);
                cout << char(186);
            }
}
void drawPath(vector<pair<int,int>> path,int boardposx,int boardposy){
    SetColor(2);
    int point = size(path);
    if (point == 2){
        if (path[0].second != path[1].second){

            int startx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
            int endx = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int posy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            drawBar(startx, endx, posy);

        }
        else
        {

            int starty = calculateCellPosY(path[0].first,w,h,boardposx) + h/2;
            int endy = calculateCellPosY(path[1].first,w,h,boardposx) + h/2;
            int posx = calculateCellPosX(path[0].second,w,h,boardposy) + w/2;
            drawColumn(starty,endy,posx);

        }

    }

    if (point == 3){
        if (path[2].second > path[0].second) swap(path[2], path[0]);
        if(path[2].first == path[1].first){
            int startx = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
            int middlex = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int middley = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            drawBar(startx,middlex,middley);
            drawColumn(middley,endy,middlex);
            gotoxy(middlex,middley);
            cout << char((path[1].first < path[0].first) ? 187: 188);

        }
        else
        {
            int starty = calculateCellPosY(path[2].first,w,h,boardposx) + h/2;
            int middlex = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int middley = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int endx = calculateCellPosX(path[0].second,w,h,boardposy) + w/2;
            drawColumn(starty,middley,middlex);
            drawBar(middlex,endx,middley);
            gotoxy(middlex,middley);
            cout << char((path[1].first < path[2].first) ? 201: 200);
        }

    }

    if (point == 4){

        if (path[1].first ==  path[2].first){
            if (path[0].first < path[1].first && path[3].first < path[2].first){
                //3   0
                //|   |
                //|   |
                //2---1

                int starty = calculateCellPosY(path[3].first,w,h,boardposy) + h/2;
                int middley = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middlex2 = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middlex1 = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
                int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
                drawColumn(starty,middley,middlex2);
                drawBar(middlex1,middlex2,middley);
                drawColumn(endy,middley,middlex1);
                if(path[1].second < path[2].second){
                    gotoxy(middlex1,middley);cout << char(200);
                    gotoxy(middlex2,middley);cout << char(188);
                }
                else{
                    gotoxy(middlex2,middley);cout << char(200);
                    gotoxy(middlex1,middley);cout << char(188);
                }

            }
            if (path[0].first > path[1].first && path[3].first > path[2].first){
                //2---1
                //|   |
                //|   |
                //3   0

                int starty = calculateCellPosY(path[3].first,w,h,boardposy) + h/2;
                int middley = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middlex2 = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middlex1 = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
                int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
                drawColumn(middley,starty,middlex2);
                drawBar(middlex2,middlex1,middley);
                drawColumn(middley,endy,middlex1);
                if(path[1].second < path[2].second){
                    gotoxy(middlex1,middley);cout << char(201);
                    gotoxy(middlex2,middley);cout << char(187);
                }
                else{
                    gotoxy(middlex2,middley);cout << char(201);
                    gotoxy(middlex1,middley);cout << char(187);
                }
            }
            if (path[0].first < path[1].first && path[3].first > path[2].first){
                //    0
                //    |
                //2---1
                //|
                //3

                int starty = calculateCellPosY(path[3].first,w,h,boardposy) + h/2;
                int middley = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middlex2 = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middlex1 = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
                int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
                drawColumn(middley,starty,middlex2);
                drawBar(middlex2,middlex1,middley);
                drawColumn(endy,middley,middlex1);
                if(path[1].second < path[2].second){
                    gotoxy(middlex1,middley);cout << char(200);
                    gotoxy(middlex2,middley);cout << char(187);
                }
                else{
                    gotoxy(middlex2,middley);cout << char(201);
                    gotoxy(middlex1,middley);cout << char(188);
                }
            }
            if (path[0].first > path[1].first && path[3].first < path[2].first){
                //3
                //|
                //2---1
                //    |
                //    0

                int starty = calculateCellPosY(path[3].first,w,h,boardposy) + h/2;
                int middley = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middlex2 = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middlex1 = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
                int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
                drawColumn(starty,middley,middlex2);
                drawBar(middlex2,middlex1,middley);
                drawColumn(middley,endy,middlex1);
                if(path[1].second > path[2].second){
                    gotoxy(middlex1,middley);cout << char(200);
                    gotoxy(middlex2,middley);cout << char(187);
                }
                else{
                    gotoxy(middlex2,middley);cout << char(201);
                    gotoxy(middlex1,middley);cout << char(188);
                }
            }

        }
        else{
            if (path[0].second < path[1].second && path[3].second < path[2].second){
                /*
                  3--2
                     |
                  0--1
                */
                int startx = calculateCellPosX(path[3].second,w,h,boardposx) + w/2;
                int middlex = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middley2 = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middley1 = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
                int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
                drawBar(startx,middlex,middley2);
                drawColumn(middley2,middley1,middlex);
                drawBar(endx,middlex,middley1);
                if (path[2].first < path[1].first){
                    gotoxy(middlex,middley2); cout<<char(187);
                    gotoxy(middlex,middley1); cout << char(188);

                }
                else{
                    gotoxy(middlex,middley1); cout<<char(187);
                    gotoxy(middlex,middley2); cout << char(188);
                }
            }
            if (path[0].second > path[1].second && path[3].second > path[2].second){


                /*
                  2--3
                  |
                  1--0
                */
                int startx = calculateCellPosX(path[3].second,w,h,boardposx) + w/2;
                int middlex = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middley2 = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middley1 = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
                int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
                drawBar(middlex,startx,middley2);
                drawColumn(middley1,middley2,middlex);
                drawBar(middlex,endx,middley1);
                if (path[1].first < path[2].first){
                    gotoxy(middlex,middley2); cout<<char(200);
                    gotoxy(middlex,middley1); cout << char(201);

                }
                else{
                    gotoxy(middlex,middley1); cout<<char(200);
                    gotoxy(middlex,middley2); cout << char(201);
                }

            }
            if (path[0].second > path[1].second && path[3].second < path[2].second){
                /*
                  3--2
                     |
                     1--0
                */
                int startx = calculateCellPosX(path[3].second,w,h,boardposx) + w/2;
                int middlex = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middley2 = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middley1 = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
                int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
                drawBar(startx,middlex,middley2);
                drawColumn(middley2,middley1,middlex);
                drawBar(middlex,endx,middley1);
                if (path[2].first < path[1].first){
                    gotoxy(middlex,middley2); cout<<char(187);
                    gotoxy(middlex,middley1); cout << char(200);

                }
                else{
                    gotoxy(middlex,middley1); cout<<char(201);
                    gotoxy(middlex,middley2); cout << char(188);
                }
            }
            if (path[0].second < path[1].second && path[3].second > path[2].second){
                /*
                     2--3
                     |
                  0--1
                */
                int startx = calculateCellPosX(path[3].second,w,h,boardposx) + w/2;
                int middlex = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
                int middley2 = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
                int middley1 = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
                int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
                drawBar(middlex,startx,middley2);
                drawColumn(middley2,middley1,middlex);
                drawBar(endx,middlex,middley1);
                if (path[2].first < path[1].first){
                    gotoxy(middlex,middley2); cout<<char(201);
                    gotoxy(middlex,middley1); cout << char(188);

                }
                else{
                    gotoxy(middlex,middley1); cout<<char(187);
                    gotoxy(middlex,middley2); cout << char(200);
                }
            }
        }

    }
}



//Hide show cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
