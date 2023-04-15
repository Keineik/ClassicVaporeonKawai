#include "drawscreen.h"
// Set console pointer to coordinator (x,y)
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Modify console window
void resizeConsole(int posx, int posy, int width, int height)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd,posx,posy,width,height,TRUE);
}

/*
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
*/
//Set color for cout
//Color is set by this format: X/16 is background color, X%16 is character color
void SetColor(int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

// Clear Canvas by cout ' ' character
void clearCanvas(int x, int y, int width, int height){
    for (int i = x; i <=  x+width; i++)
    for (int j = y; j <= y+height; j++){
        gotoxy(i,j);
        cout <<" ";
    }
}
// Expose the area of background according to cell's location on the game canvas
void exposeBackground(int x, int y, int width, int height, char **background, int backgroundx, int backgroundy){
    SetColor(7);
    for (int i = x; i <=  x+width; i++)
        for (int j = y; j <= y+height; j++){
            gotoxy(i,j);
            cout << background[j-backgroundy][i-backgroundx];
        }
}
// clear the entire console by Window's API
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
// Draw cell, actually the same functions with draw box, but I seperate into two different functions for easy code read
void drawCell(int x, int y, int w, int h, int color, char c){
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

// DrawLogin and drawSignupForm also act as getInput function

void drawLoginForm(){
    int x, y;
    x = offsetx+(width - 60) / 2;
    y = offsety+ (height - (2*4)) / 2;
    char c; int countchar = 0;
    gotoxy(x,y);
    SetColor(6);
    cout << "Username (No longer than 50 chars)";
    drawBox(x,y+1,60,2,6," ");
    gotoxy(x, y + 5);
    cout << "PASSWORD (No longer than 50 chars)";
    drawBox(x,y + 6, 60,2,6," ");
    gotoxy(x, y + 11); cout << "Press ENTER to confirm";
    gotoxy(x, y + 12); cout << "Press BACKSPACE to erase while typing";
    gotoxy(x, y + 13); cout << "Please don't press arrowkeys while typing. Please.";
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
    char c;
    x = offsetx + (width - 60) / 2;
    y = offsety + (height - (2*6)) / 2;
    gotoxy(x,y);
    SetColor(6);
    cout << "USERNAME (No longer than 50 chars)";
    drawBox(x,y+1,60,2,6," ");
    gotoxy(x, y + 4);
    cout << "PASSWORD (No longer than 50 chars)";
    drawBox(x,y + 5, 60,2,6," ");
    gotoxy(x,y+8);
    cout << "RE-TYPE PASSWORD";
    drawBox(x,y+9,60,2,6," ");
    gotoxy(x, y + 13); cout << "Press ENTER to confirm";
    gotoxy(x, y + 14); cout << "Press BACKSPACE to erase while typing";
    gotoxy(x, y + 15); cout << "Please don't press arrowkeys while typing. Please.";
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
            retypepassword[countchar] = '\0';
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
    offsetx = offsetx + 10;
    offsety += 5;
    SetColor(6);
    gotoxy (offsetx + 4, offsety + 4);
    cout << "Interaction:";
    gotoxy(offsetx + 10, offsety + 6);
    cout << "Move :";
    gotoxy(offsetx + 12, offsety + 10);
    cout << "WASD";drawCell(offsetx + 22, offsety + 11,4,2,6*16,'A'); drawCell(offsetx +28,offsety + 7,4,2,6*16,'W'); drawCell(offsetx + 28 ,offsety + 11,4,2,6*16,'S'); drawCell(offsetx + 34,offsety + 11,4,2,6*16,'D');
    gotoxy(offsetx + 12,offsety +17);
    SetColor(6);
    cout << "ARROWKEYS"; drawCell(offsetx + 22, offsety +19,4,2,6*16,'<'); drawCell(offsetx +28,offsety +15,4,2,6*16,'^'); drawCell(offsetx + 28,offsety +19 ,4,2,6*16,'v'); drawCell(offsetx +34,offsety +19,4,2,6*16,'>');
    gotoxy(offsetx +12,offsety +24);
    SetColor(6);
    cout << "Select:"; drawBox(offsetx +22,offsety +23,16,2,6*16,"   SPACEBAR   ");
    gotoxy(offsetx + width / 2 + 4, offsety + 4);
    SetColor(6);
    cout << "Legal Move: I, L, Z (3 lines max)";

    while(true){
        Sleep(1000);
        clearCanvas(offsetx + width/2 + 5, offsety + 6,20,20);
        drawCell(offsetx + width/2 + 5, offsety + 9, w,h, 6, 'A'); drawCell(offsetx + width/2 + 15, offsety + 9, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 10, offsety + 16, w,h, 6, 'A'); drawCell(offsetx + width/2 + 10, offsety + 22, w,h, 6, 'A');
        Sleep(500);
        drawBar(offsetx + width/2 + 5 + w/2 + 1, offsetx + width/2 + 15 + w/2-1, offsety + 9 + h/2);
        drawColumn(offsety + 16+ h/2 + 1, offsety + 22 + h/2 - 1, offsetx + width/2 + 10 + w/2);
        Sleep(1000);
        clearCanvas(offsetx + width/2 + 5, offsety + 6,20,20);
        drawCell(offsetx + width/2 + 5, offsety + 6, w,h, 6, 'A'); drawCell(offsetx + width/2 + 15, offsety + 6, w,h, 6, 'B');
                                                                    drawCell(offsetx + width/2 + 15, offsety + 12, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 5, offsety + 16, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 5, offsety + 22, w,h, 6, 'B'); drawCell(offsetx + width/2 + 15, offsety + 22, w,h, 6, 'A');
        Sleep(500);
        drawColumn(offsety + 6 + h/2 + 1, offsety + 12 + h/2, offsetx + width/2 + 5 + w/2);
        drawBar(offsetx + width/2 + 5 + w/2 + 1, offsetx + width/2 + 15 + w/2, offsety + 16 + h/2);
        Sleep(500);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 15 + w/2 - 1, offsety + 12 + h/2);
        drawColumn(offsety + 16 + h/2, offsety + 22 + h/2 - 1, offsetx + width/2 + 15 + w/2);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 12 + h/2);
        cout << char(200);
        gotoxy(offsetx + width/2 + 15 + w/2,offsety + 16 + h/2);
        cout << char(187);
        Sleep(1000);
        clearCanvas(offsetx + width/2 + 5, offsety + 6,20,20);
        drawCell(offsetx + width/2 + 5, offsety + 6, w,h, 6, 'B'); drawCell(offsetx + width/2 + 15, offsety + 6, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 5, offsety + 12, w,h, 6, 'A');
                                                                    drawCell(offsetx + width/2 + 15, offsety + 16, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 5, offsety + 22, w,h, 6, 'A'); drawCell(offsetx + width/2 + 15, offsety + 22, w,h, 6, 'B');
        Sleep(500);
        drawBar(offsetx + width/2 + 5 + w/2 + 1, offsetx + width/2 + 15 + w/2, offsety + 12 + h/2);
        drawColumn(offsety + 16 + h/2 , offsety + 22 + h/2 - 1, offsetx + width/2 + 5 + w/2);
        Sleep(500);
        drawColumn(offsety + 6 + h/2 + 1, offsety + 12 + h/2, offsetx + width/2 + 15 + w/2);
        drawBar(offsetx + width/2 + 5 + w/2 + 1, offsetx + width/2 + 15 + w/2 - 1, offsety + 16 + h/2);
        gotoxy(offsetx + width/2 + 15 + w/2,offsety + 12 + h/2);
        cout << char(188);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 16 + h/2);
        cout << char(201);
        Sleep(1000);
        clearCanvas(offsetx + width/2 + 5, offsety + 6,20,20);
        drawCell(offsetx + width/2 + 5, offsety + 10, w,h, 6, 'A'); drawCell(offsetx + width/2 + 10, offsety + 10, w,h, 6, 'B'); drawCell(offsetx + width/2 + 15, offsety + 10, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 10, offsety + 16, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 10, offsety + 19, w,h, 6, 'B');
        drawCell(offsetx + width/2 + 10, offsety + 22, w,h, 6, 'A');
        Sleep(500);
        drawColumn(offsety + 6 + h/2, offsety + 10 + h/2 - 1, offsetx + width/2 + 5 + w/2);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 10 + w/2 - 1, offsety + 16 + h/2);
        Sleep(500);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 15 + w/2, offsety + 6 + h/2);
        drawColumn(offsety + 16 + h/2, offsety + 22 + h/2, offsetx + width/2 + 5 + w/2);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 6 + h/2);
        cout << char(201);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 16 + h/2);
        cout << char(201);
        Sleep(500);
        drawColumn(offsety + 6 + h/2, offsety + 10 + h/2 - 1, offsetx + width/2 + 15 + w/2);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 10 + w/2 - 1, offsety + 22 + h/2);
        gotoxy(offsetx + width/2 + 15 + w/2,offsety + 6 + h/2);
        cout << char(187);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 22 + h/2);
        cout << char(200);
        Sleep(1000);
        clearCanvas(offsetx + width/2 + 5, offsety + 6,20,20);
        drawCell(offsetx + width/2 + 5, offsety + 6, w,h, 6, 'B'); drawCell(offsetx + width/2 + 15, offsety + 6, w,h, 6, 'A');
        drawCell(offsetx + width/2 + 5, offsety + 12, w,h, 6, 'A'); drawCell(offsetx + width/2 + 15, offsety + 12, w,h, 6, 'B');
        drawCell(offsetx + width/2 + 5, offsety + 16, w,h, 6, 'A'); drawCell(offsetx + width/2 + 15, offsety + 16, w,h, 6, 'B');
        drawCell(offsetx + width/2 + 5, offsety + 22, w,h, 6, 'B'); drawCell(offsetx + width/2 + 15, offsety + 22, w,h, 6, 'A');
        Sleep(500);
        drawColumn(offsety + 12 + h/2 - 1, offsety + 9 + h/2, offsetx + width/2 + 5 + w/2);
        drawColumn(offsety + 16 + h/2 + 1, offsety + 19 + h/2, offsetx + width/2 + 5 + w/2);
        Sleep(500);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 15 + w/2, offsety + 9 + h/2);
        drawBar(offsetx + width/2 + 5 + w/2, offsetx + width/2 + 15 + w/2, offsety + 19 + h/2);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 9 + h/2);
        cout << char(201);
        gotoxy(offsetx + width/2 + 5 + w/2,offsety + 19 + h/2);
        cout << char(200);
        Sleep(500);
        drawColumn(offsety + 6 + h/2+1, offsety + 9 + h/2 , offsetx + width/2 + 15 + w/2);
        drawColumn(offsety + 22 + h/2-1, offsety + 19 + h/2 , offsetx + width/2 + 15 + w/2);
        gotoxy(offsetx + width/2 + 15 + w/2,offsety + 9 + h/2);
        cout << char(188);
        gotoxy(offsetx + width/2 + 15 + w/2,offsety + 19 + h/2);
        cout << char(187);
        gotoxy(offsetx +  width/2 - 30, offsety + height - 5);
        SetColor(6);
        cout << "PRESS R TO REWATCH M TO RETURN TO MENU";
        if (_getch() == 'm')
            return;
        else if (_getch() == 'r')
        {
            gotoxy(offsetx +  width/2 - 30, offsety + height - 5);
            cout << "                                      ";
            continue;
        }
    }
}

// Draw play board
// ------------Calculating function for board and cells-------
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
// ------------Stop here-------
// Print the board
void printBoard() {

    for (int i = 0; i <= M+1; i++) {
        for (int j = 0; j <=  N+1; j++){
            if (board[i][j] != blankspace){
                if (choosing.first == i && choosing.second == j)
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15 , board[i][j]);
                else
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , CellColor[(board[i][j] - 59)/3] , board[i][j]);
            }
        else
            exposeBackground(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy),w,h,background,backgroundx,backgroundy);

        }
    }
}

//Level-based functions: these two functions used to redraw col or row after a shift
void redrawCol(int j){
    for (int i = 0; i <= M +1; i++)
         if (board[i][j] != blankspace){
                if (choosing.first == i && choosing.second == j)
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15 , board[i][j]);
                else
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , CellColor[(board[i][j] - 59)/3] , board[i][j]);
            }
        else
            exposeBackground(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy),w,h,background,backgroundx,backgroundy);
}

void redrawRow(int i){
    for (int j = 0; j <= N+1; j++)
        if (board[i][j] != blankspace){
                if (choosing.first == i && choosing.second == j)
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , 15 , board[i][j]);
                else
                    drawCell(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy), w, h , CellColor[(board[i][j] - 59)/3] , board[i][j]);
            }
        else
            exposeBackground(calculateCellPosX(j,w,h,boardposx), calculateCellPosY(i,w,h,boardposy),w,h,background,backgroundx,backgroundy);
}
// Draw horizontal line and vertical line, used in drawPath functions
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
// Draw legal move from vector paths
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

// the following functions delete the output of previous drawPath function
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


//Draw Image funtion, Image is stored under texts file, demonstrated by ASCII 128 characters
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
// Get background from txt files
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
// Delete to avoid memory leaks

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
    hudx = offsetx + width + 1;
    hudy = offsety;
    drawBox(hudx, hudy, 40, height, 6," ");
    SetColor(15);
    gotoxy(hudx + 2,hudy + 2); cout <<"Level: " << setw(10) << setfill(' ') << right << Level;
    gotoxy(hudx + 2,hudy + 4); cout << "Score: "     << setw(10) << setfill(' ') << right << score;
    gotoxy(hudx + 2,hudy + 6); cout << "Streak: "    << setw(9) << setfill(' ') << right << streak;
    gotoxy(hudx + 2, hudy + 8); cout << "Streak time remain: ";
    drawBoxOnly(hudx + 9, hudy + 10, 16, 2, 15, " ");
    gotoxy(hudx + 10, hudy + 11); SetColor(4*16+10); cout << setw(15) << setfill(' ') << right << StreakTimeBar;
    SetColor(6);
    drawBar(hudx, hudx + 40, 13);
    gotoxy(hudx, hudy + 13); cout << char(204);
    gotoxy(hudx + 40, hudy + 13); cout << char(185);
    SetColor(15);
    gotoxy(hudx + 2, hudy + 15);
    cout << "Move :";
    drawCell(hudx + 4, hudy + 20,4,2,15*16,'A'); drawCell(hudx + 9,hudy + 17,4,2,15*16,'W'); drawCell(hudx + 9,hudy + 20,4,2,15*16,'S'); drawCell(hudx + 14 , hudy + 20,4,2,15*16,'D');
    drawCell(hudx+ 20, hudy + 20,4,2,15*16,'<'); drawCell(hudx + 25, hudy + 17,4,2,15*16,'^'); drawCell(hudx + 25, hudy + 20 ,4,2,15*16,'v'); drawCell(hudx + 30, hudy + 20,4,2,15*16,'>');
    gotoxy(hudx + 2,hudy+25);
    SetColor(15);
    cout << "Select:"; drawBox(hudx+10, hudy + 27,20,2,15*16,"     SPACEBAR     ");
    SetColor(15);
    gotoxy(hudx+2, hudy + 33);
    if(newAccount || successLogin)
        cout << "Save and return to menu: ";
    else
        cout << "Return to menu: ";
    drawCell(hudx + 28, hudy + 32,w,h,15*16, 'M');
    SetColor(15);
    gotoxy(hudx+2, hudy + 37);
    cout << "Hint( costs 200 scores): "; drawCell(hudx + 28, hudy + 36,w,h,15*16, 'H');
    drawBoxOnly(offsetx + 10,offsety + height + 5, 121,3,15," ");
    gotoxy(offsetx + 11,offsety + height + 6); SetColor(4*16+10); cout << setw(120) << setfill(' ') << right << UpperTimeBar;
    gotoxy(offsetx + 11,offsety + height + 7); SetColor(4*16+10); cout << setw(120) << setfill(' ') << right << LowerTimeBar;
    drawBox(offsetx + 10, offsety + height + 2, 20, 2, 15*16, "    Game Timer    ");

}
void initializeTimeBar(){
    for (int i = 0; i < timeRemain/3; i++){
        UpperTimeBar[i] = LowerTimeBar[i] = char(219);
    }
    UpperTimeBar[timeRemain/3 + 1] = LowerTimeBar[timeRemain/3 + 1] = '\0';
}

void initializeStreakTimeBar(){
    for (int i = 0; i < streakTimeRemain/2; i++){
        StreakTimeBar[i] = char(219);
    }
    StreakTimeBar[streakTimeRemain/2 + 1] = '\0';
}
// display time and Game status during gameplay
void displayTimeAndStatus(){
    miliseconds -= tick;
    // Sleep for tick milisecond;
    if (miliseconds == 0){
        if (streakTimeRemain > 0){
            streakTimeRemain --;
            if (streakTimeRemain % 2 == 0){
                StreakTimeBar[streakTimeRemain/2 + 1] =  '\0';
            }
        }
        timeRemain --;
        if (timeRemain % 3 == 0){
            UpperTimeBar[timeRemain/3 + 1] = LowerTimeBar[timeRemain/3 + 1] = '\0';
        }

        miliseconds = 1000;
    }
    SetColor(15);
    gotoxy(hudx + 2,hudy + 4); cout << "Score: "     << setw(10) << setfill(' ') << right << score;
    gotoxy(hudx + 2,hudy + 6); cout << "Streak: "    << setw(9) << setfill(' ') << right << streak;
    gotoxy(offsetx + 11,offsety + height + 6); SetColor(4*16+10); cout << setw(120) << setfill(' ') << right << UpperTimeBar;
    gotoxy(offsetx + 11,offsety + height + 7); SetColor(4*16+10); cout << setw(120) << setfill(' ') << right << LowerTimeBar;
    if (streakTimeRemain > 0){
        gotoxy(hudx + 10, hudy + 11); SetColor(4*16+10); cout << setw(15) << setfill(' ') << right << StreakTimeBar;
    }
    else
    {
        gotoxy(hudx + 10, hudy + 11); SetColor(15); cout << setw(15) << setfill(' ') << right << " ";
    }
    Sleep(tick);
}

// this sub-function belongs to drawCustomizeMenu()
bool validateColandRow(int M, int N){
    return (M*N != 0 && M*N <= 8*16 && M*N %2 == 0);
}
// Interactive customize Menu
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
// Draw Leaderboard and Highscore
void drawLeaderboardandHighScore(){
    int x = (ConsoleCol - 80)/2;
    int y = (ConsoleRow - 35)/2;
    drawBox(offsetx + (width - 14) / 2, y - 4, 14,2, 6*16, "LEADERBOARD ");
    drawBox(x - 2,y,82,15,6*16," ");
    gotoxy(x,y + 1); cout << setw(10)<< setfill(' ') << left << "RANK" << setw(50) << left << "USERNAME" <<  setw(10) << "POINT" << setw(10)  << "DATE";
    int i = 0;
    for (auto leader : leaderboard){
        if (leader.points == 0){
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout << setw(10) <<setfill(' ') << left << 5-i << setw(50) << left << leaders[4-i] <<  setw(10) << "----------" << setw(10) << setfill(' ')<< right << "dd/mm/yyyy";

        }
        else{
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout << setw(10) <<setfill(' ') << left << 5-i << setw(50) << left << leader.name <<  setw(10) << leader.points
                << setw(2) << setfill('0')<< right <<  leader.date.dd << "/" << setw(2) << leader.date.mm << "/" << setw(4) << leader.date.yy;

        }
        i++;
    }
    drawBar(x-2,x+80,y+2);
    gotoxy(x-2,y+2); cout << char(204);
    gotoxy(x+80,y+2); cout << char (185);
    drawColumn(y,y+15,x+ 8); gotoxy(x+8,y); cout << char(203); gotoxy(x+8,y+15); cout << char(202);
    drawColumn(y,y+15,x+ 59); gotoxy(x+59,y); cout << char(203); gotoxy(x+59,y+15); cout << char(202);
    drawColumn(y,y+15,x+ 69); gotoxy(x+69,y); cout << char(203); gotoxy(x+69,y+15); cout << char(202);
    gotoxy(x+8, y+2); cout << char(206);
    gotoxy(x+59, y+2); cout << char(206);
    gotoxy(x+69, y+2); cout << char(206);


    x = offsetx + (width - 30)/2;
    y += 21;
    drawBox(offsetx + (width - 14) / 2, y - 4, 14,2, 6*16, "YOUR RECORD ");
    drawBox(x - 2,y,33,15,6*16," ");
    SetColor(6*16);
    gotoxy(x,y + 1); cout <<setfill(' ') << setw(9) << left << "RANK" << setw(11) << "POINT" << setw(10)  << "DATE";
    i = 0;
    for (auto player : currentSave.record ){
        if (player.points == 0){
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout <<  setw(9) <<setfill(' ')  << left << 5-i << setw(11) << "----------" <<  setw(10) << "dd/mm/yyyy";

        }
        else{
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout << setw(9) <<setfill(' ') << left << 5-i << setw(11) << left << player.points
               << setw(2) << setfill('0')<< right <<  player.date.dd << "/" << setw(2) << player.date.mm << "/" << setw(4) << player.date.yy;


        }
        i++;
    }
    drawBar(x-2,x+31,y+2);
    gotoxy(x-2,y+2); cout << char(204);
    gotoxy(x+31,y+2); cout << char (185);
    drawColumn(y,y+15,x+ 8); gotoxy(x+8,y); cout << char(203); gotoxy(x+8,y+15); cout << char(202);
    drawColumn(y,y+15,x+ 19); gotoxy(x+19,y); cout << char(203); gotoxy(x+19,y+15); cout << char(202);
    gotoxy(x+8, y+2); cout << char(206);
    gotoxy(x+19, y+2); cout << char(206);
    if (LoginMenuChoice == 4)
        drawBox(offsetx + (width - 25) / 2, y + 20, 25,2, 6*16, "PRESS ANY KEY TO EXIT");

}

void drawLeaderboard(){
    int x = offsetx + (width - 80)/2;
    int y = offsety + (height - 15)/2;
    drawBox(offsetx + (width - 14) / 2, y - 4, 14,2, 6*16, " LEADERBOARD ");
    drawBox(x - 2,y,82,15,6*16," ");
    gotoxy(x,y + 1); cout << setw(10)<< setfill(' ') << left << "RANK" << setw(50) << left << "USERNAME" <<  setw(10) << "POINT" << setw(10)  << "DATE";
    int i = 0;
    for (auto leader : leaderboard){
        if (leader.points == 0){
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout << setw(10) <<setfill(' ') << left << 5-i << setw(50) << left << leaders[4-i] <<  setw(10) << "----------" << setw(10) << setfill(' ')<< right << "dd/mm/yyyy";

        }
        else{
            SetColor(6*16);
            gotoxy(x,y + 4 + (4-i)*2);
            cout << setw(10) <<setfill(' ') << left << 5-i << setw(50) << left << leader.name <<  setw(10) << leader.points
                << setw(2) << setfill('0')<< right <<  leader.date.dd << "/" << setw(2) << leader.date.mm << "/" << setw(4) << leader.date.yy;

        }
        i++;
    }
    drawBar(x-2,x+80,y+2);
    gotoxy(x-2,y+2); cout << char(204);
    gotoxy(x+80,y+2); cout << char (185);
    drawColumn(y,y+15,x+ 8); gotoxy(x+8,y); cout << char(203); gotoxy(x+8,y+15); cout << char(202);
    drawColumn(y,y+15,x+ 59); gotoxy(x+59,y); cout << char(203); gotoxy(x+59,y+15); cout << char(202);
    drawColumn(y,y+15,x+ 69); gotoxy(x+69,y); cout << char(203); gotoxy(x+69,y+15); cout << char(202);
    gotoxy(x+8, y+2); cout << char(206);
    gotoxy(x+59, y+2); cout << char(206);
    gotoxy(x+69, y+2); cout << char(206);
}
// This function take menu - arrays of string variables and its size to draw onto the console
void drawNormalMenu(int MenuSelecting, int MenuSize, menu Menu[]){
    int x = offsetx + (width - 20) / 2;
    int y = offsety+(height - MenuSize*(2+1))/2;
    for (int i = 0;  i < MenuSize; i++)
            drawBox(x,y+i*2+i,20,2,(MenuSelecting == i ? 7*16 : 6), Menu[i].choice);
    if (MenuSelecting >= 0){
        gotoxy(offsetx + (width - Menu[MenuSelecting].about.length())/2, y + MenuSize*(2+1) + 2);
        SetColor(6);
        cout << setw(50) << setfill(' ') << left << Menu[MenuSelecting].about;
    }


}
// Save load menu or Slot menu is different, it indicates whether a slot is occupied
void drawSaveLoadMenu(){
    int x = offsetx + (width - 20) / 2;
    int y = offsety + (height - size(SlotMenu)*(2+1))/2;
    for ( int i = 0;  i < size(SlotMenu); i++)
        if (currentSave.state[i].p != 0){
            drawBox(x,y+i*2+i,20,2,(SlotMenuSelecting == i? 7*16 : 2) , " ");
            gotoxy(x+1,y+i*2+i+1); cout << right << setw(2) << setfill('0') << currentSave.state[i].date.dd << "/"
                                        << setw(2)  << currentSave.state[i].date.mm << "/"
                                        << setw(4) << currentSave.state[i].date.yy;
        if (currentSave.state[SlotMenuSelecting].p != 0 && SlotMenuSelecting >= 0 ){
            SetColor(2);
            gotoxy(offsetx + (width - 40) / 2, y+size(SlotMenu)*(2+1) + 2);
            cout << "Score:" << setw(6) << right << setfill(' ') << currentSave.state[SlotMenuSelecting].points
                                        <<" | " << "Level: " << currentSave.state[SlotMenuSelecting].level
                                        <<" | " << "Time remains: " << setw(3)  << currentSave.state[SlotMenuSelecting].time;
        }
        else{
            SetColor(2);
            gotoxy(offsetx + (width - 40) / 2, y+size(SlotMenu)*(2+1) + 2);
            cout << "                                                              ";
        }
        }
        else{
             if (SlotMenuSelecting == i)
                drawBox(x,y+i*2+i,20,2,7*16, SlotMenu[i]);
            else
                drawBox(x,y+i*2+i,20,2,6, SlotMenu[i]);
        }



}

// Get the input key from the user to change the menu
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
        case '/':
            if (GameMenuChoice == 0)
            {
                SetColor(10);
                clearScreen();
                LoginMenuChoice = 10;
            }
            break;
        default:
            break;
        }
}

// Show different kinds of menu, each has their own conditions
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
                printBoard();
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
                updateLeaderboard();
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
                    updateLeaderboard();
                    writeBinFile();
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
                stopPlay = false;
                play();
                }
                else
                {
                    // This happen when the selected slot contains no data, output a dialog box
                    drawBox(offsetx + (width - 30)/2,offsety + (height - 4)/2,30,4,9,"No data! Press any key");
                    _getch();
                    SetColor(6);
                    clearScreen();
                    load = true;
                    SlotMenuChoice = -1;
                    showLoadMenu();
                }

    }



}

// saveFile hacking interactive console
void drawHackingConsole(){
    int isHacking = -1;
    SetColor(10);
    gotoxy(0,0);
    char code[25] = {};
    int x = offsetx + (width - 30)/2;
    int y = offsety + (height - (2*2))/2;
    int countchar = 0;
    gotoxy(x,y);
    SetColor(10);
    cout << "Enter the code or M only to exit";
    gotoxy(x, y+3);
    drawBox(x,y+1,30,2,10," ");
    char c;
    gotoxy(x+1,(y+1)+(2/2));
    ShowConsoleCursor(TRUE);
    while (strcmp(code,"22clcxisgoat")!=0 ){
        countchar = 0;
        while(c = _getch()){
            if (c == ENTER){
                code[countchar] = '\0';
                break;
            }
            else if (c == 8 && countchar > 0){
                countchar = ((countchar - 1)>0 ? countchar -1 : 0);
                gotoxy(x+1+countchar,y+1+2/2);
                cout << " ";
                gotoxy(x+1+countchar,y+1+2/2);

            }
            else if (c!= 8 && countchar < 20 && countchar >= 0){
                cout << c;
                code[countchar] = c;
                countchar++;
            }
        }
        if (strcmp(code,"m") == 0)
            return;
    }
    if (strcmp(code,"22clcxisgoat")==0){
        int slot = 0, level = 0, points = 0, time = 0;
        Date date = {};
        isHacking = -1;
        clearScreen();
        x = offsetx + (width - 20) / 2;
        y = offsety + (height - (3*3))/2;
        int curHack = 0;
        while(isHacking == -1){
            drawBox(x,y,20,2,(curHack == 0? 10*16: 10), "Hack save slot");
            drawBox(x,y+3,20,2,(curHack == 1? 10*16:10), "Hack record");
            drawBox(x,y+6,20,2,(curHack == 2? 10*16:10),"Return to menu");
            navigateMenu(curHack,isHacking,3);
        }
        if (isHacking == 2 )
            return;
        if (isHacking == 0){
            SlotMenuChoice = -1;
            SlotMenuSelecting = 0;
            x = offsetx + (width - 20) / 2;
            y = offsety + (height - (size(SlotMenu)-1)*(2+1))/2;
            while(true){
                drawSaveLoadMenu();
                navigateMenu(SlotMenuSelecting,SlotMenuChoice,size(SlotMenu));
                if (SlotMenuChoice == size(SlotMenu) - 1){
                    return;
                }
                else if (currentSave.state[SlotMenuChoice].p != 0){
                    slot =  SlotMenuChoice;
                    break;
                }
            }
            x = offsetx + (width - 30)/2;
            y = offsety + 10;
            drawBox(x-1,y,30,15,6*16," ");
            gotoxy(x,y + 1); cout << setw(15) << left << "SLOT INFO" << setw(11) << left << "VALUE";
            int i = 0;
            SetColor(6*16);
            gotoxy(x,y + 4); cout << setw(15) << left << "DATE" << setw(2) << setfill('0') << right << currentSave.state[slot].date.dd << "/" << setw(2)<< currentSave.state[slot].date.mm << "/" << setw(4) << currentSave.state[i].date.yy;
            gotoxy(x,y + 6); cout << setw(15) << setfill(' ') << left << "LEVEL" << setw(11) << left << currentSave.state[slot].level;
            gotoxy(x,y + 8); cout << setw(15) << left << "POINTS" << setw(11) << left << currentSave.state[slot].points;
            gotoxy(x,y + 10); cout << setw(15) << left << "TIME LEFT" << setw(11) << left << currentSave.state[slot].time;
            drawBar(x-1,x+29,y+2);
            gotoxy(x-1,y+2); cout << char(204);
            gotoxy(x+29,y+2); cout << char (185);
            drawColumn(y,y+15,x + 14); gotoxy(x+14,y); cout << char(203); gotoxy(x+14,y+15); cout << char(202);
            gotoxy(x+14, y+2); cout << char(206);
            x = 0;
            y += 2;
            char choice, temp; // temp to discard slash
            gotoxy(x,y);
            SetColor(10);
            cout << "Type your desired new value: "<< endl;
            cout << "Change date ? Y/n: "; cin  >> choice;
            while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' ){
                cout << "Please type Y or N: "; cin >> choice;
            }
            if (choice == 'y' || choice == 'Y'){
                cout << "New date value(dd/mm/yyyy): "; cin >> date.dd >> temp >> date.mm >> temp >> date.yy;
                while(!isValidDate(date)){
                    cout << "Invalid date! Max is 31/12/9999, min is 01/01/0001" << endl; cout << "Please retype (dd/mm/yyyy): ";
                    cin >> date.dd >> temp >> date.mm >> temp >> date.yy;
                }
            }
            cout << "Change level (1-5)? Y/n: "; cin >> choice;
            while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' ){
                cout << "Please type Y or N: "; cin >> choice;
            }
            if (choice == 'y' || choice == 'Y'){
                cout << "New level value: "; cin >> level;
                while (level > 5 || level < 1){
                    cout << "Invalid level!! Please choose 1-5: "; cin >> level;
                }
            }

            cout << "Change points? Y/n: "; cin >> choice;
            while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' ){
                cout << "Please type Y or N: "; cin >> choice;
            }
            if (choice == 'y' || choice == 'Y'){
                cout << "New points value:"; cin >> points;
            }
            cout << "Change time left? Y/n: "; cin >> choice;
            while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' ){
                cout << "Please type Y or N: "; cin >> choice;
            }
            if (choice == 'y' || choice == 'Y'){
                cout << "New time left value:"; cin >> time;
            }
            hackState(slot,level,points,time,date);
            writeBinFile();
            writeLeaderboardFile();
        }
        else if (isHacking = 1){
            drawLeaderboardandHighScore();
            gotoxy(0,30);
            char temp;
            SetColor(10);
            cout << "Choose slot to (1-5): "; cin >> slot;
            while (slot < 1 || slot > 5){
                cout << "Invalid slot!!! \n Please choose slot tobetween 1 and 5: "; cin >> slot;
            }
            cout << "Type your desired new record: "<< endl;
            cout << "Date value(dd/mm/yyyy): "; cin >> date.dd >> temp >> date.mm >> temp >> date.yy;
            while(!isValidDate(date)){
                    cout << "Invalid date! Max is 31/12/9999, min is 01/01/0001" << endl; cout << "Please retype (dd/mm/yyyy): ";
                    cin >> date.dd >> temp >> date.mm >> temp >> date.yy;
                }
            cout << "Points value:"; cin >> points;
            hackRecord(5-slot,date,points);
            writeBinFile();
            writeLeaderboardFile();
            return;

        }
    }

    ShowConsoleCursor(FALSE);
}

void drawCredit(){
    int x; int y;
    x = (ConsoleCol - 80) / 2;
    y = 2;
    drawBox(x,y,80,40,14," ");
    string filename = ImageDir + "credit.txt";
    ifstream ifs;
    string s = {}; int line = 0;
    ifs.open(filename);
    SetColor(15);
    while (ifs){
        getline(ifs,s);
        gotoxy(x + (80 - s.length())/2, y + 1 + line); cout << s;
        line ++;
    }

    ifs.close();
}
