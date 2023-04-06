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
void SetColor(int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

// Clear Canvas

void clearCanvas(int x, int y, int width, int height){
    for (int i = x; i <=  x+width; i++)
    for (int j = y; j <= y+height; j++){
        gotoxy(i,j);
        cout <<" ";
    }
}

void exposeBackground(int x, int y, int width, int height, char **background, int backgroundx, int backgroundy){
    for (int i = x; i <=  x+width; i++)
        for (int j = y; j <= y+height; j++){
            gotoxy(i,j);
            cout << background[j-backgroundy][i-backgroundx];
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

// Draw solid box
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

    for (int i = x+1 ; i < x+w; i++){
        for (int j = y+1; j < y+h; j++){
            gotoxy(i,j);
            cout <<  " ";
        }
    }
    gotoxy(x+2, y+h/2); cout << s;


    gotoxy(x,y); cout << char(201);
    gotoxy(x+w,y); cout << char(187);
    gotoxy(x,y+h); cout << char(200);
    gotoxy(x+w,y+h); cout << char(188);

}
// Draw empty box
void drawBoxOnly(int x, int y, int w, int h, int color, string s){

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
    gotoxy(x+2, y+h/2); cout << s;
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
            for (int i = x+1 ; i < x+w; i++){
                for (int j = y+1; j < y+h; j++){
                    gotoxy(i,j);
                    cout <<  " ";
                }
            }
            gotoxy(x+ 2, y+h/2); cout << c;
            gotoxy(x,y); cout << char(218);
            gotoxy(x+w,y); cout << char(191);
            gotoxy(x,y+h); cout << char(192);
            gotoxy(x+w,y+h); cout << char(217);
        }
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

// Draw Login/Signup Form

void drawLoginForm(){
    int x, y;
    x = offsetx+(width - 60) / 2;
    y = offsety+ (height - (2*4)) / 2;
    char c; int countchar = 0;
    gotoxy(x,y);
    SetColor(6);
    cout << "Username (No longer than 15 chars)";
    drawBox(x,y+1,60,2,6," ");
    gotoxy(x, y + 5);
    cout << "PASSWORD (No longer than 15 chars)";
    drawBox(x,y + 6, 60,2,6," ");
    ShowConsoleCursor(true);
    gotoxy(x+1,(y+1)+(2/2));
    while(c = _getch()){
        if (c == ENTER){
            username[countchar] = '\0';
            break;
        }

        else if (c == 8 && countchar > 0){
            countchar = ((countchar - 1)>0 ? countchar -1 : 0);
            gotoxy(x+1+countchar,y+1+2/2);
            cout << " ";
            gotoxy(x+1+countchar,y+1+2/2);

        }
        else if (c!= 8 && countchar < 50 && countchar >= 0){
            cout << c;
            username[countchar] = c;
            countchar++;
        }

    }
    countchar = 0;
    gotoxy(x+1,(y+6)+(2/2));
    while(c = _getch()){
        if (c == ENTER){
            password[countchar] = '\0';
            break;

        }
        else if (c == 8 && countchar > 0){
            countchar = ((countchar - 1)>0 ? countchar -1 : 0);
            gotoxy(x+1+countchar,y+6+2/2);
            cout << " ";
            gotoxy(x+1+countchar,y+6+2/2);

            }
        else
            if (c!= 8 && countchar < 50 && countchar >= 0 ){
                cout << c;
                password[countchar] = c;
                countchar++;
            }

    }
    ShowConsoleCursor(false);
}

void drawSignupForm(){
    int x, y;
    int countchar = 0;
    char rewritepassword[60];
    char c;
    x = offsetx + (width - 60) / 2;
    y = offsety + (height - (2*6)) / 2;
    gotoxy(x,y);
    SetColor(6);
    cout << "USERNAME (No longer than 15 chars)";
    drawBox(x,y+1,60,2,6," ");
    gotoxy(x, y + 4);
    cout << "PASSWORD (No longer than 15 chars)";
    drawBox(x,y + 5, 60,2,6," ");
    gotoxy(x,y+8);
    cout << "RE-TYPE PASSWORD";
    drawBox(x,y+9,60,2,6," ");
    ShowConsoleCursor(true);
    gotoxy(x+1,(y+1)+(2/2));
    while(c = _getch()){
        if (c == ENTER){
            username[countchar] = '\0';
            break;
        }

        else if (c == 8 && countchar > 0){
            countchar = ((countchar - 1)>0 ? countchar -1 : 0);
            gotoxy(x+1+countchar,y+1+2/2);
            cout << " ";
            gotoxy(x+1+countchar,y+1+2/2);

        }
        else if (c!= 8 && countchar < 49 && countchar >= 0){
            cout << c;
            username[countchar] = c;
            countchar++;
        }

    }

    countchar = 0;
    gotoxy(x+1,(y+5)+(2/2));
    while(c = _getch()){
        if (c == ENTER){
            password[countchar] = '\0';
            break;

        }
        else if (c == 8 && countchar > 0){
            countchar = ((countchar - 1)>0 ? countchar -1 : 0);
            gotoxy(x+1+countchar,y+5+2/2);
            cout << " ";
            gotoxy(x+1+countchar,y+5+2/2);

            }
        else
            if (c!= 8 && countchar < 49 && countchar >= 0 ){
                cout << c;
                password[countchar] = c;
                countchar++;
            }

    }
    countchar = 0;
    gotoxy(x+1,(y+9)+(2/2));
    while(c = _getch()){
        if (c == ENTER){
            rewritepassword[countchar] = '\0';
            break;
        }

        else if (c == 8 && countchar > 0){
            countchar = ((countchar - 1)>0 ? countchar -1 : 0);
            gotoxy(x+1+countchar,y+9+2/2);
            cout << " ";
            gotoxy(x+1+countchar,y+9+2/2);

        }
        else if (c!= 8 && countchar < 49 && countchar >= 0 ){
            cout << c;
            retypepassword[countchar] = c;
            countchar++;
        }

    }

    ShowConsoleCursor(false);


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



// Draw play board
int calculateCellPosX(int j, int w, int h, int boardposx){
    return (boardposx + j*w + j);
}

int calculateCellPosY(int i, int w, int h, int boardposy){
    return (boardposy + i*h + i);
}

int calculateBoardPosX(){
    return offsetx + (width  - ((N+2)*(w+1)))/2 ;

}

int calculateBoardPosY(){
    return offsety + (height -((M+2)*(h+1)))/2;

}

void printBoard(pair<int, int> p1, pair<int,int> p2,int boardposx,int boardposy) {

    for (int i = 0; i <= M+1; i++) {
        for (int j = 0; j <=  N+1; j++){
            if((p1.first == i && p1.second == j)|| (p2.first == i && p2.second ==j))
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15*16 , board[i][j]);
            else if (choosing.first == i && choosing.second == j)
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15 , board[i][j]);
            else
                drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , CellColor[(board[i][j] - 59)/3] , board[i][j]);

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

void eraseBar(char **background, int backgroundx, int backgroundy, int startx, int endx, int posy, int w, int h){
    if (startx > endx) swap(startx,endx);
    for (int i =  startx; i <= endx; i+=w){
                exposeBackground(i - w/2 ,posy - h/2, w, h,background,backgroundx,backgroundy);
            }
}

void eraseColumn(char **background, int backgroundx, int backgroundy, int starty, int endy, int posx, int w, int h){
    if (starty > endy) swap(starty,endy);
    for (int i =  starty; i <= endy; i+=h){
                exposeBackground(posx - w/2,i - h/2,w,h,background,backgroundx,backgroundy);
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

            int starty = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            int endy = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int posx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
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
            int starty = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
            int middlex = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int middley = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
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

void clearVfx(pair <int,int> p1, pair <int,int> p2, vector<pair<int,int>> path, int backgroundx, int backgroundy){
    SetColor(7);
    exposeBackground(calculateCellPosX(p1.second,w,h,boardposx),calculateCellPosY(p1.first,w,h,boardposy), w, h,background,backgroundx,backgroundy);
    exposeBackground(calculateCellPosX(p2.second,w,h,boardposx),calculateCellPosY(p2.first,w,h,boardposy), w, h,background,backgroundx,backgroundy);
    int point = size(path);
    for (int i = 0; i < point; i++)
        exposeBackground(calculateCellPosX(path[i].second,w,h,boardposx),calculateCellPosY(path[i].first,w,h,boardposy), w, h,background,backgroundx,backgroundy);
    if (point == 2){
        if (path[0].second != path[1].second){

            int startx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
            int endx = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int posy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            eraseBar(background,backgroundx,backgroundy,startx, endx, posy,w,h);

        }
        else
        {

            int starty = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            int endy = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int posx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
            eraseColumn(background,backgroundx,backgroundy, starty,endy,posx,w,h);

        }

    }

    if (point == 3){
        if (path[2].second > path[0].second) swap(path[2], path[0]);
        if(path[2].first == path[1].first){
            int startx = calculateCellPosX(path[2].second,w,h,boardposx) + w/2;
            int middlex = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int middley = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int endy = calculateCellPosY(path[0].first,w,h,boardposy) + h/2;
            eraseBar(background,backgroundx,backgroundy, startx,middlex,middley,w,h);
            eraseColumn(background,backgroundx,backgroundy, middley,endy,middlex,w,h);

        }
        else
        {
            int starty = calculateCellPosY(path[2].first,w,h,boardposy) + h/2;
            int middlex = calculateCellPosX(path[1].second,w,h,boardposx) + w/2;
            int middley = calculateCellPosY(path[1].first,w,h,boardposy) + h/2;
            int endx = calculateCellPosX(path[0].second,w,h,boardposx) + w/2;
            eraseColumn(background,backgroundx,backgroundy, starty,middley,middlex,w,h);
            eraseBar(background,backgroundx,backgroundy, middlex,endx,middley,w,h);
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
                eraseColumn(background,backgroundx,backgroundy, starty,middley,middlex2,w,h);
                eraseBar(background,backgroundx,backgroundy, middlex1,middlex2,middley,w,h);
                eraseColumn(background,backgroundx,backgroundy, endy,middley,middlex1,w,h);

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
                eraseColumn(background,backgroundx,backgroundy, middley,starty,middlex2,w,h);
                eraseBar(background,backgroundx,backgroundy, middlex2,middlex1,middley,w,h);
                eraseColumn(background,backgroundx,backgroundy, middley,endy,middlex1,w,h);
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
                eraseColumn(background,backgroundx,backgroundy, middley,starty,middlex2,w,h);
                eraseBar(background,backgroundx,backgroundy, middlex2,middlex1,middley,w,h);
                eraseColumn(background,backgroundx,backgroundy, endy,middley,middlex1,w,h);

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
                eraseColumn(background,backgroundx,backgroundy,starty,middley,middlex2,w,h);
                eraseBar(background,backgroundx,backgroundy, middlex2,middlex1,middley,w,h);
                eraseColumn(background,backgroundx,backgroundy,middley,endy,middlex1,w,h);

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
                eraseBar(background,backgroundx,backgroundy,startx,middlex,middley2,w,h);
                eraseColumn(background,backgroundx,backgroundy,middley2,middley1,middlex,w,h);
                eraseBar(background,backgroundx,backgroundy,endx,middlex,middley1,w,h);
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
                eraseBar(background,backgroundx,backgroundy,middlex,startx,middley2,w,h);
                eraseColumn(background,backgroundx,backgroundy,middley1,middley2,middlex,w,h);
                eraseBar(background,backgroundx,backgroundy,middlex,endx,middley1,w,h);

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
                eraseBar(background,backgroundx,backgroundy,startx,middlex,middley2,w,h);
                eraseColumn(background,backgroundx,backgroundy,middley2,middley1,middlex,w,h);
                eraseBar(background,backgroundx,backgroundy,middlex,endx,middley1,w,h);
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
                eraseBar(background,backgroundx,backgroundy,middlex,startx,middley2,w,h);
                eraseColumn(background,backgroundx,backgroundy,middley2,middley1,middlex,w,h);
                eraseBar(background,backgroundx,backgroundy,endx,middlex,middley1,w,h);
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


//Draw Game Title
void drawImage(int x, int y, string imagefile){
    ifstream ifs;
    ifs.open(imagefile);
    int imagew, imageh;
    ifs >> imagew >> imageh;
    char image[imageh][imagew];
    int colors = 0;
    ifs >> colors;
    char pattern[colors-1];
    int color[colors];
    int i = 0, j = 0;
    for (i = 0; i < colors; i++)
        ifs >> color[i];
    for (i = 0; i < colors-1; i++)
        ifs >> pattern[i];
    if (ifs.is_open()){
        gotoxy(offsetx+x,offsety+y);
        for (i = 0; i < imageh; i++){
            ifs.getline(image[i],imagew+5,'\n');
            j = 0;
            while (image[i][j] != '\0'){
                if (image[i][j] != ' '){
                    if (colors == 1)
                        if (image[i][j] == pattern[0])
                            SetColor(color[0]);
                        else
                            SetColor(7);
                    else if (colors == 2){
                        if (image[i][j] == pattern[0])
                            SetColor(color[0]);
                        else
                            SetColor(color[1]);
                    }
                    else if (colors == 3){
                        if (image[i][j] == pattern[0])
                            SetColor(color[0]);
                        else if (image[i][j] == pattern[1])
                            SetColor(color[1]);
                        else
                            SetColor(color[2]);
                        }
                    else if (colors == 4){
                        if (image[i][j] == pattern[0])
                            SetColor(color[0]);
                        else if (image[i][j] == pattern[1])
                            SetColor(color[1]);
                        else if (image[i][j] == pattern[2])
                            SetColor(color[2]);
                        else
                            SetColor(color[3]);
                    }
                    gotoxy(x+j,y+i);
                    cout << image[i][j];
                }
                j++;
            }
        }
    }
    ifs.close();
}

void initializeBackground(char **&background,int &backw, int &backh, int &backgroundx, int &backgroundy, string filename){
    ifstream ifs;
    ifs.open(filename);
    ifs >> backw >> backh;
    backgroundx = offsetx + (width-backw) / 2;
    backgroundy = offsety + (height-backh) / 2;
    background = new char *[backh];
    for (int i = 0; i< backh; i++)
        background[i] = new char[backw];

    for (int i = 0; i < backh; i++)
        ifs.getline(background[i], backw+1, '\n');
    ifs.close();
}

void deleteBackgroundInfo(char **&background,int &backw, int &backh, int &backgroundx, int &backgroundy){
    for (int i = 0; i < backh; i++)
        delete [] background[i];
    delete [] background;
    backh =  backw = backgroundx = backgroundy = 0;
}
void drawBackground(char **background,int backw, int backh, int backgroundx, int backgroundy){
    SetColor(7);
    for (int i = 0; i < backh;i++){
        gotoxy(backgroundx , backgroundy + i);
        cout << background[i];
    }

}

// Draw Game status on the screen when first enter play()
void drawHUD(){
    SetColor(15);
    gotoxy(offsetx + 10, offsety + height + 3); cout << "Score: " << right << score;
    gotoxy(offsetx + 10, offsety + height + 5); cout << "Time left: " << right << timeRemain;
    gotoxy(offsetx + 10, offsety + height + 7); cout << "Streak: " << right << streak;}


// display time and Game status during gameplay
void displayTimeAndStatus(){
    miliseconds -= tick;
    // Sleep for 40 milisecond;
    if (miliseconds == 0){
        if (streakTimeRemain > 0)
            streakTimeRemain --;
        timeRemain --;
        SetColor(15);
        gotoxy(offsetx + 10,offsety + height + 3); cout <<"Score: "     << setw(7) << right << score;
        gotoxy(offsetx + 10,offsety + height + 5); cout << "Time left: " << setw(3) << right << timeRemain;
        gotoxy(offsetx + 10,offsety + height + 7); cout << "Streak: "    << setw(6) << right << streak;
        if (streak > 0){
            gotoxy(offsetx + 25 , offsety + height + 7); cout << "Streak resets after: " << setw(2)<< right << streakTimeRemain;
        }
        else{
            gotoxy(offsetx + 25 , offsety + height + 7); cout << "                                       ";

        }
        if (score >= 200) {
            gotoxy(offsetx + 10 , offsety + height + 9); cout << "Press H(Hint) for 200 scores";
        }
        else
        {
            gotoxy(offsetx + 10 , offsety +  height + 9); cout << "                             ";
        }
        miliseconds = 1000;
    }
}

bool validateColandRow(int M, int N){
    return (M*N != 0 && M*N <= 8*16 && M*N %2 == 0);
}

void drawCustomnizeMenu(){
    int minM, maxM, selectingM, minN, maxN, selectingN, menuOption, menuSelecting, finishCustom = false;
    selectingM = selectingN = minN = minM = 2;
    maxM = 8; maxN = 16;
    M = N = 0;
    menuOption = 0;
    menuSelecting = 1;
    int x = offsetx + (width - 60) / 2;
    int y = offsety + (height - 4*(2+1)) / 2;
    while (!finishCustom){
        drawBoxOnly(x,y,60,2,(menuSelecting == 1 ? 15: 6),"NUMBERS OF ROWS: "); gotoxy(x+20,y+1); cout << (selectingM > minM ? "< ": "  ") << setw(2) << right << selectingM << (selectingM < maxM ? " >": "  ");
        drawBoxOnly(x,y + 3 ,60,2,(menuSelecting == 2 ? 15: 6),"NUMBERS OF COLS: "); gotoxy(x+20,y+4); cout << (selectingN > minN ? "< ": "  ") << setw(2) << right << selectingN << (selectingN < maxN ? " >": "  ");
        drawBox(x,y + 6,60,2,(menuSelecting == 3 ? 15 * 16: 6),"CONFIRM");
        drawBox(x,y + 9,60,2,(menuSelecting == 4 ? 15 * 16: 6),"RETURN");
        switch(_getch()){
        case KEY_UP: case 'w':
            if (menuSelecting <= 1)
                menuSelecting = 4;
            else
                menuSelecting--;
            break;
        case KEY_DOWN: case 's':
            if (menuSelecting >= 4)
                menuSelecting = 1;
            else
                menuSelecting++;
            break;
        case KEY_LEFT: case 'a':
            if (menuSelecting == 1){
                selectingM = max(selectingM - 1, minM);
            }
            else if (menuSelecting == 2){
                selectingN = max(selectingN - 1, minN);
            }
            break;

        case  KEY_RIGHT: case 'd':
            if (menuSelecting == 1){
                selectingM = min(selectingM + 1, maxM);
            }
            else if (menuSelecting == 2){
                selectingN = min(selectingN + 1, maxN);
            }
            break;
        case ' ':
            menuOption = menuSelecting;
            SetColor(0);
            clearScreen();
            break;
        default:
            break;
        }
        if (menuOption == 3){
            if (validateColandRow(selectingM,selectingN)){
                M = selectingM;
                N = selectingN;
                break;
            }
            else{
                drawBox(offsetx + (width - 60) / 2, offsety + (height - 4)/2, 60,2,14*16+4,"M*N must be divisible by 2!! Press M(Menu) or R(Re-select)");
                switch(_getch()){
                case 'm':
                    finishCustom = true;
                    menuOption = -1;
                    SetColor(7);
                    clearScreen();
                    break;
                default:
                    menuOption = -1;
                    SetColor(7);
                    clearScreen();
                    break;
                }
            }

        }
        if (menuOption == 4){
            finishCustom = true;
            break;
        }

    }

}
