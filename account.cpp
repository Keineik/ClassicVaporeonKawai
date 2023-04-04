#include "account.h"

void readBinFile() {
    fstream fs;
    fs.open("savefile.bin", ios::in | ios::binary);

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

void writeBinFile() {
    fstream fs;
    fs.open("savefile.bin", ios::out | ios::binary);

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
    }
    deleteBoard();
    M = 8, N = 16;
    initializeBoard();
}

void saveGame(int saveSlot) {
    // save to currentSave
    currentSave.state[saveSlot] = {M, N, 1, 1};
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            currentSave.state[saveSlot].board[i*N + j] = board[i + 1][j + 1];
    currentSave.state[saveSlot].board[M*N] = '\0';

    // save to saves data
    for (auto &user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            user.state[saveSlot] = currentSave.state[saveSlot];
        }
    }
}

void loadGame(int saveSlot) {
    for (auto user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            currentSave.state[saveSlot] = user.state[saveSlot];
        }
    }

    deleteBoard();
    M = currentSave.state[saveSlot].p;
    N = currentSave.state[saveSlot].q;
    initializeBoard();
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i + 1][j + 1] = currentSave.state[saveSlot].board[i*N + j];
}