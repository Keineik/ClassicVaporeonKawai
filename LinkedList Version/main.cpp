#include "header.h"
#include "gamelogic.cpp"

void printBoard() {
    cout << M << " " << N << endl;
    for (int i = 0; i <= M + 1; i++) {
        for (int j = 0; j <= N + 1; j++) {
            cout << (char) getData(i, j) << " ";
        }
        cout << endl;
    }
}

int main () {
    Level = 1;
    pair<int, int> p1, p2;
    initializeBoard();
    while (true) {
        if (!isPlayable()) {
            if (isWin() && Level == 5) {
                cout << "Victory!";
                break;
            }
            else if (isWin()) {
                Level++;
                continue;
            }
            else
                while (!isPlayable()) shuffle();
        }

        printBoard();
        cout << "Input: ";
        cin >> p1.first >> p1.second >> p2.first >> p2.second;
        if (p1.first == -1 && p1.second == -1 && p2.first == -1 && p2.second == -1) shuffle();
        else if (p1.first == -2 && p1.second == -2 && p2.first == -2 && p2.second == -2) {
            auto moveSuggested = moveSuggestion();
            cout << "Suggestion: "
                 << moveSuggested.first.first << " " << moveSuggested.first.second << " "
                 << moveSuggested.second.first << " " << moveSuggested.second.second << endl;
        }
        else if (isLegalMove(p1, p2)) {
            changeData(p1.first, p1.second, blankspace);
            changeData(p2.first, p2.second, blankspace);
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
            
            for (auto i: path) cout << "(" << i.first << ", " << i.second << ") ";
            cout << endl;
        }
    }
    
    deleteBoard();
    return 0;
}