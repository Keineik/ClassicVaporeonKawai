#include "account.h"

void readBinFile(string filename = "savefile.bin") {
    fstream fs;
    fs.open(filename, ios::in | ios::binary);

    if (!fs.is_open()) {
        cout << "File invalid";
    }
    else {
        // get file size
        fs.seekg(0, ios::end);
        int file_size = (int) fs.tellg();
        fs.seekg(0, ios::beg);

        while(fs.tellg() < file_size) {
            savefile tempsf;
            fs.read((char*) &tempsf, sizeof(savefile));
            xorCstr(tempsf.name, tempsf.mask);
            xorCstr(tempsf.password, tempsf.mask);
            for (int i = 0; i < 5; i++) {
                xorCstr(tempsf.state[i].board, tempsf.mask);
                xorCstr(tempsf.state[i].file_background, tempsf.mask);
            }

            saves.push_back(tempsf);
            listOfUsername.insert(tempsf.name);
        }
    }

    fs.close();
}

void xorCstr(char* cstr, char mask) {
    for (int i = 0; cstr[i] != '\0'; i++)
        cstr[i] ^= mask;
}

void writeBinFile(string filename = "savefile.bin") {
    fstream fs;
    fs.open(filename, ios::out | ios::binary);

    for (auto tempsf: saves) {
        xorCstr(tempsf.name, tempsf.mask);
        xorCstr(tempsf.password, tempsf.mask);
        for (int i = 0; i < 5; i++) {
            xorCstr(tempsf.state[i].board, tempsf.mask);
            xorCstr(tempsf.state[i].file_background, tempsf.mask);
        }
        fs.write((char*) &tempsf, sizeof(savefile));
    }

    fs.close();
}

int signUp(char* username, char* password, char* retypePassword) {
    if (listOfUsername.count(username))
        return -1; // username exsisted
    else if (username[0] == '\0')
        return -2; // username invalid
    else if (strcmp(password, retypePassword) != 0)
        return 0; // password and retypePassword do not match
    else {
        currentSave.mask = '\n';
        strcpy(currentSave.name, username);
        strcpy(currentSave.password, password);
        for (int i = 0; i < 5; i++) {
            currentSave.record[i] = {0, 0, 0, 0};
            currentSave.state[i] = {0, 0, 1, 1};
            currentSave.state[i].level = 0;
            currentSave.state[i].points = 0;
            currentSave.state[i].time = 0;
        }

        listOfUsername.insert(username);
        saves.push_back(currentSave);
        return 1;
    }
}

bool login(char* username, char* password) {
    // if username doesn't exist
    if (listOfUsername.count(username) == 0)
        return false;

    // if username exist
    for (auto user: saves) {
        if (strcmp(username, user.name) == 0) {
            // if password doesn't match
            if (strcmp(password, user.password) != 0)
                return false;
            else {
                currentSave = user;
                return true;
            }
        }
    }
    return false;
}

void logout() {
    currentSave.mask = '\0';
    currentSave.name[0] = '\0';
    currentSave.password[0] = '\0';
    for (int i = 0; i < 5; i++) {
        currentSave.record[i] = {0, 0, 0, 0};
        currentSave.state[i] = {0, 0, 1, 1};
        currentSave.state[i].board[0] = '\0';
        currentSave.state[i].file_background[0] = '\0';
        currentSave.state[i].level = 0;
        currentSave.state[i].points = 0;
        currentSave.state[i].time = 0;
    }
}

void saveGame(int saveSlot) {
    // save to currentSave
    currentSave.state[saveSlot] = {M, N, 1, 1};
    currentSave.state[saveSlot].level = Level;
    currentSave.state[saveSlot].points = score;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    currentSave.state[saveSlot].date = {ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};
    currentSave.state[saveSlot].time = timeRemain;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            currentSave.state[saveSlot].board[i*N + j] = board[i + 1][j + 1];
    currentSave.state[saveSlot].board[M*N] = '\0';

    // update record to currentSave
    updateRecord();

    // save to saves data
    for (auto &user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            user = currentSave;
        }
    }
}

void loadGame(int saveSlot) {
    for (auto user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            currentSave.state[saveSlot] = user.state[saveSlot];
        }
    }

    M = currentSave.state[saveSlot].p;
    N = currentSave.state[saveSlot].q;
    Level = currentSave.state[saveSlot].level;
    timeRemain = currentSave.state[saveSlot].time;
    initializeBoard();
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i + 1][j + 1] = currentSave.state[saveSlot].board[i*N + j];
}

void updateRecord() {
    sort(currentSave.record, currentSave.record + 5, sortingPriority);
    if (currentSave.record[0].points <= score) {
        // get dd/mm/yyyy
        // https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
        time_t now = time(0);
        tm *ltm = localtime(&now);
        currentSave.record[0] = {ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year, score};
    }
    sort(currentSave.record, currentSave.record + 5, sortingPriority);
}

// LEADERBOARD

void readLeaderboardFile(string filename = "leaderboard.bin") {
    fstream fs;
    fs.open(filename, ios::in | ios::binary);

    if (fs.is_open()) {
        for (int i = 0; i < 5; i++) {
            highScore tempHS;
            fs.read((char*) &tempHS, sizeof(highScore));
            leaderboard[i] = tempHS;
        }
        fs.close();
    }
    else {
        cout << "File not found" << endl;
    }
}

void writeLeaderboardFile(string filename = "leaderboard.bin") {
    fstream fs;
    fs.open(filename, ios::out | ios::binary);

    for (auto tempHS: leaderboard) {
        fs.write((char*) &tempHS, sizeof(highScore));
    }

    fs.close();
}

void updateLeaderboard() {
    sort(leaderboard.begin(), leaderboard.end(), isHigherScoreLB);
    if (score > leaderboard[0].points) {
        strcpy(leaderboard[0].name, currentSave.name);
        leaderboard[0].points = score;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        leaderboard[0].date = {ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};
    }
    sort(leaderboard.begin(), leaderboard.end(), isHigherScoreLB);
}

// hacking interactions
void hackState(int slot, int level, int points, int time, Date date) {
    for (auto &user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            user.state[slot].level = level;
            user.state[slot].points = points;
            user.state[slot].time = time;
            user.state[slot].date = date;
            if (points > user.record[0].points) {
                user.record[0].date = date;
                user.record[0].points = points;
                sort(user.record, user.record + 5, sortingPriority);
            }
            if (points > leaderboard[0].points) {
                leaderboard[0].date = date;
                strcpy(leaderboard[0].name, user.name);
                leaderboard[0].points = points;
                sort(leaderboard.begin(), leaderboard.end(), isHigherScoreLB);
            }
        }
    }
}

void hackRecord(int slot, Date date, int points) {
    for (auto &user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            user.record[slot].date = date;
            user.record[slot].points = points;
            sort(user.record, user.record + 5, sortingPriority);
        }
        if (points > leaderboard[0].points) {
            leaderboard[0].date = date;
            strcpy(leaderboard[0].name, user.name);
            leaderboard[0].points = points;
            sort(leaderboard.begin(), leaderboard.end(), isHigherScoreLB);
        }
    }
}