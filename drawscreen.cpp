#include "drawscreen.h"


// Set console pointer to coordinator (x,y)
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MoveWindow(int posx, int posy)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posx, posy, 400, 200, TRUE);
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
    if (c != blankspace){
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
void drawMainMenu(int x,int y,int isSelecting){
    string s[5] = {"PLAY","HOW TO PLAY","HIGH SCORE","CREDIT", "QUIT"};
    int color = 6,selectcolor = 9;
    for (int i = 0; i<5; i++){
        if (isSelecting==i)
            drawBox(x,y +(i * 2 + i) , 20, 2,selectcolor, s[i]);
        else
            drawBox(x,y +(i * 2 + i) , 20, 2,color, s[i]);

    }
}

void drawLoginMenu(int x, int y, int isSelecting){

    string s[3] = {"Log in", "Sign up", "Play as guest" };
    int color = 6,selectcolor = 9;
    for (int i = 0; i<3; i++){
        if (isSelecting==i)
            drawBox(x,y +(i * 2 + i) , 20, 2,selectcolor, s[i]);
        else
            drawBox(x,y +(i * 2 + i) , 20, 2,color, s[i]);
    }
}

// Draw In-game HUD

void drawHUD(int width, int height){
    drawBox(0,height+1,width / 2 - 1, 4, 6, "Player: Username");
    drawBox(width/2+1,height+1,width /2 - 1,4,6, "Score: XXX");
    drawBox(width+1,0,15,4,6,"LEVEL: X");
    drawBox(width+1,5,15,4,6,"TIMER");
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
