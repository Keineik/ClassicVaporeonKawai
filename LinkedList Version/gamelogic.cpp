#include "gamelogic.h"

// linked list manipulation
void levelDif(int &x, int &y) {
    if (Level == 3) {
        y = N + 1 - y;
    }
    else if (Level == 4) {
        swap(M, N);
        swap(x, y);
    }
    else if (Level == 5) {
        x = M + 1 - x;
        swap(M, N);
        swap(x, y);
    }
}

void addHead(Node *&pHead, int val) {
    Node *newNode = new Node;
    newNode->data = val;

    if (pHead == NULL) pHead = newNode;
    else {
        newNode->next = pHead;
        pHead = newNode;
    }
}

void addHeadLL(LinkedList *&pHeadLL) {
    LinkedList *newLL = new LinkedList;

    if (pHeadLL == NULL) pHeadLL = newLL;
    else {
        newLL->next = pHeadLL;
        pHeadLL = newLL;
    }
}

int getData(int x, int y) {
    if (x == 0 || y == 0 || x > M || y > N) return blankspace;
    levelDif(x, y);

    LinkedList *curLL = board;
    // move to desired linked list
    for (int i = 1; i < x; i++)
        curLL = curLL->next;

    Node *curNode = curLL->firstNode;
    if (y > curLL->size) {
        levelDif(x, y);
        return blankspace;
    }
    else {
        for (int i = 1; i < y; i++)
            curNode = curNode->next;
        levelDif(x, y);
        return curNode->data;
    }
}

void changeData(int x, int y, int data) {
    levelDif(x, y);

    LinkedList *curLL = board;
    // move to desired linked list
    for (int i = 1; i < x; i++)
        curLL = curLL->next;
    
    // move to desired node and change data
    Node *curNode = curLL->firstNode;
    for (int i = 1; i < y; i++)
        curNode = curNode->next;
    curNode->data = data;

    levelDif(x, y);
}

// board manipulation
void initializeBoard() {
    int x = 0, y = 0;
    levelDif(x, y);

    Node *pHead = NULL;
    LinkedList *pHeadLL = NULL;

    int poke = 59, count = 0;
    // create M linked lists
    for (int i = 1; i <= M; i++) {
        // create linked list with N nodes
        addHeadLL(pHeadLL);
        pHead = NULL;
        for (int j = 1; j <= N; j++) {
            addHead(pHead, poke);
            if (++count % 4 == 0) poke++;
        }
        pHeadLL->firstNode = pHead;
        pHeadLL->size = N;
    }
    board = pHeadLL;

    levelDif(x, y);

    shuffle();
}

void deleteBoard() {
    LinkedList *pHeadLL = board, *nextLL;
    Node *pHead, *nextNode;

    while (pHeadLL != NULL) {
        pHead = pHeadLL->firstNode;
        while (pHead != NULL) {
            nextNode = pHead->next;
            delete pHead;
            pHead = nextNode;
        }
        nextLL = pHeadLL->next;
        delete pHeadLL;
        pHeadLL = nextLL;
    }
}

void shuffle() {
    mt19937 mt{ static_cast<unsigned int>(
		chrono::steady_clock::now().time_since_epoch().count()
		) };
    // uniform_int_distribution ran{1, 6};

    // put data in array for faster access
    vector<int> allData;
    LinkedList *curLL = board;
    Node *curNode;
    while (curLL != NULL) {
        curNode = curLL->firstNode;
        while (curNode != NULL) {
            allData.push_back(curNode->data);
            curNode = curNode->next;
        }
        curLL = curLL->next;
    }

    // randomize the data
    curLL = board;
    while (curLL != NULL) {
        curNode = curLL->firstNode;
        while (curNode != NULL) {
            uniform_int_distribution<int> ran{0, (int) allData.size() - 1};
            int rNum = ran(mt);
            curNode->data = allData[rNum];
            allData.erase(allData.begin() + rNum);
            curNode = curNode->next;
        }
        curLL = curLL->next;
    }
}

void deleteAndShiftBoard(int indexLL) {
    // move to desired linked list
    LinkedList *curLL = board;
    for (int i = 1; i < indexLL; i++)
        curLL = curLL->next;

    // delete and shift linked list
    Node *curNode = curLL->firstNode;
    // if the first node needs to be deleted
    while (curNode != NULL && curNode->data == blankspace) {
        curLL->firstNode = curNode->next;
        delete curNode;
        curNode = curLL->firstNode;
        curLL->size--;
    }
    // delete and shift linked list if needed
    while (curNode != NULL && curNode->next != NULL) {
        // if next node needs to be deleted
        if (curNode->next->data == blankspace) {
            Node *delNode = curNode->next;
            curNode->next = curNode->next->next;
            delete delNode;
            curLL->size--;
        }
        curNode = curNode->next;
    }
}

// moves related
bool isLegalMove(pair<int, int> p1, pair<int, int> p2) {
    //check if the same tile
    if (p1.first == p2.first && p1.second == p2.second)
        return false;
    //check if chose blankspace
    if (getData(p1.first, p1.second) == blankspace || getData(p2.first, p2.second) == blankspace)
        return false;
    //check if same poke
    if (getData(p1.first, p1.second) != getData(p2.first, p2.second))
        return false;

    //check if legal move
    int temp1 = getData(p1.first, p1.second);
    int temp2 = getData(p2.first, p2.second);
    changeData(p1.first, p1.second, blankspace);
    changeData(p2.first, p2.second, blankspace);

    bool isLegal = false;
    if (checkLine(p1, p2)) isLegal = true;
    else if (checkSmallRect(p1, p2)) isLegal = true;
    else if (checkBigRect(p1, p2)) isLegal = true;

    changeData(p1.first, p1.second, temp1);
    changeData(p2.first, p2.second, temp2);

    return isLegal;
}

bool checkLine(pair<int, int> p1, pair<int, int> p2) {
    //if line is horizontal
    if (p1.first == p2.first) {
        if (p1.second > p2.second) swap(p1, p2);
        for (int i = p1.second; i <= p2.second; i++)
            if (getData(p1.first, i) != blankspace) return false;
    }
    //if line is vertical
    else if (p1.second == p2.second) {
        if (p1.first > p2.first) swap(p1, p2);
        for (int i = p1.first; i <= p2.first; i++)
            if (getData(i, p1.second) != blankspace) return false;
    }
    else return false;

    // if line is legal
    path.clear();
    path.insert(path.end(), {p1, p2});
    return true;
}

bool checkSmallRect(pair<int, int> p1, pair<int, int> p2) {
    //check legal if middle path is a horizontal line
    if (p1.first > p2.first) swap(p1, p2);
    for (int i = p1.first; i <= p2.first; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2)) {
                path.clear();
                pair<int, int> tempPath[4] = {p1, {i, p1.second}, {i, p2.second}, p2};
                path.push_back(p1);
                for (int i = 1; i < 4; i++)
                    if (tempPath[i] != tempPath[i - 1])
                        path.push_back(tempPath[i]);
                return true;
        }
    }
    //check legal if middle path is a vertical line
    if (p1.second > p2.second) swap(p1, p2);
    for (int i = p1.second; i <= p2.second; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2)) {
                path.clear();
                pair<int, int> tempPath[4] = {p1, {p1.first, i}, {p2.first, i}, p2};
                path.push_back(p1);
                for (int i = 1; i < 4; i++)
                    if (tempPath[i] != tempPath[i - 1])
                        path.push_back(tempPath[i]);
                return true;
        }
    }
    return false;
}

bool checkBigRect(pair<int, int> p1, pair<int, int> p2) {
    //check big rect Ox+
    if (p1.second > p2.second) swap(p1, p2);
    for (int i = p2.second; i <= N+1; i++) {
        if (checkLine(p1, {p1.first, i}) &&
            checkLine({p1.first, i}, {p2.first, i}) &&
            checkLine({p2.first, i}, p2)) {
                path.clear();
                path.insert(path.end(), {p1, {p1.first, i}, {p2.first, i}, p2});
                return true;
        }
    }
    //check big rect Ox-
    for (int i = p1.second; i >= 0; i--) {
        if (checkLine(p2, {p2.first, i}) &&
            checkLine({p2.first, i}, {p1.first, i}) &&
            checkLine({p1.first, i}, p1)) {
                path.clear();
                path.insert(path.end(), {p2, {p2.first, i}, {p1.first, i}, p1});
                return true;
        }
    }
    //check big rect Oy+
    if (p1.first > p2.first) swap(p1, p2);
    for (int i = p1.first; i >= 0; i--) {
        if (checkLine(p2, {i, p2.second}) &&
            checkLine({i, p2.second}, {i, p1.second}) &&
            checkLine({i, p1.second}, p1)) {
                path.clear();
                path.insert(path.end(), {p2, {i, p2.second}, {i, p1.second}, p1});
                return true;
        }
    }
    //check big rect Oy-
    for (int i = p2.first; i <= M+1; i++) {
        if (checkLine(p1, {i, p1.second}) &&
            checkLine({i, p1.second}, {i, p2.second}) &&
            checkLine({i, p2.second}, p2)) {
                path.clear();
                path.insert(path.end(), {p1, {i, p1.second}, {i, p2.second}, p2});
                return true;
        }
    }
    return false;
}

pair<pair<int, int>, pair<int, int>> moveSuggestion() {
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (getData(i, j) == blankspace) continue;
            for (int u = 1; u <= M; u++) {
                for (int v = 1; v <= N; v++) {
                    if (isLegalMove({i, j}, {u, v}))
                        return {{i, j}, {u, v}};
                }
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

bool isPlayable() {
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (getData(i, j) == blankspace) continue;
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

bool isWin() {
    int count = 0;
    LinkedList *curLL = board;

    while (curLL != NULL) {
        Node *curNode = curLL->firstNode;
        while (curNode != NULL) {
            count++;
            curNode = curNode->next;
        }
        curLL = curLL->next;
    }

    return count;
}
