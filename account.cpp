#include "account.h"

void readBinFile() {
    fstream fs;
    fs.open("savefile.bin", ios::in | ios::binary);

    if (!fs.is_open()) {
        cout << "File invalid";
    }
    else {
        fs.seekg(0, ios::end);
        int file_size = (int) fs.tellg();
        fs.seekg(0, ios::beg);

        char tempBoard[999];

        while(fs.tellg() < file_size) {
            savefile tempsf;
            char temp[50];

            fs.read(&tempsf.mask, 1);

            fs.read(temp, NAMESIZE);
            xorCstr(tempsf.name, temp, tempsf.mask, NAMESIZE);

            fs.read(temp, PASSSIZE);
            xorCstr(tempsf.password, temp, tempsf.mask, PASSSIZE);

            fs.read(temp, 3); // get 3 because of struct alignment

            for (int i = 0; i < 5; i++)
                fs.read((char*)&tempsf.record[i], sizeof(Record));

            for (int i = 0; i < 5; i++) {
                fs.read((char*) &tempsf.state[i], 16); // get p, q, p_, q_
                fs.read(tempBoard, BOARDSIZE);
                xorCstr(tempsf.state[i].board, tempBoard, tempsf.mask, strlen(tempBoard));
                fs.read(temp, 1); // get 1 because of struct alignment
                fs.read(tempsf.state[i].file_background, 100);
                fs.read(tempsf.state[i].padding, PADDING);
            }

            saves.push_back(tempsf);
            listOfUsername.insert(tempsf.name);
        }
    }

    fs.close();
}

void xorCstr(char* dcstr, char* cstr, char mask, int size) {
    int i = 0;
    for (i = 0; cstr[i] != '\0'; i++) {
        dcstr[i] = cstr[i] ^ mask;
    }
    dcstr[i] = '\0';
}

void writeBinFile() {
    fstream fs;
    fs.open("savefile.bin", ios::out | ios::binary);

    char blank[4] = {0, 0, 0, 0}, tempBoard[999];

    for (auto tempsf: saves) {
        char temp[50], blank[2] = "\0";
        fs.write(&tempsf.mask, 1);

        xorCstr(temp, tempsf.name, tempsf.mask, NAMESIZE);
        fs.write(temp, NAMESIZE);

        xorCstr(temp, tempsf.password, tempsf.mask, PASSSIZE);
        fs.write(temp, PASSSIZE);

        fs.write(blank, 3); // write 3 because of struct alignment

        for (int i = 0; i < 5; i++)
            fs.write((char*)&tempsf.record[i], sizeof(Record));

        for (int i = 0; i < 5; i++) {
            fs.write((char*) &tempsf.state[i], 16); // print p, q, p_, q_
            xorCstr(tempBoard, tempsf.state[i].board, tempsf.mask, strlen(tempsf.state[i].board));
            fs.write(tempBoard, BOARDSIZE);
            fs.write(blank, 1); // print 1 because of struct alignment
            fs.write(tempsf.state[i].file_background, 100);
            fs.write(tempsf.state[i].padding, PADDING);
        }
    }
    fs.close();
}

int signUp(char* username, char* password, char* retypePassword) {
    if (listOfUsername.count(username))
        return -1; // username exsisted
    else if (username[0] == '\0')
        return -2; // username invalid
    else if (strcmp(password, retypePassword) != 0) {
        return 0; // password and retypePassword do not match
    }
    else {
        currentSave.mask = 's';
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
    if (listOfUsername.count(username) == 0)
        return false;
    for (auto user: saves) {
        if (strcmp(username, user.name) == 0) {
            if (strcmp(password, user.password) != 0)
                return false;
            else {
                currentSave.mask = user.mask;
                strcpy(currentSave.name, user.name);
                strcpy(currentSave.password, user.password);
                for (int i = 0; i < 5; i++) {
                    currentSave.record[i] = user.record[i];
                    currentSave.state[i].p = user.state[i].p;
                    currentSave.state[i].q = user.state[i].q;
                    currentSave.state[i].p_ = user.state[i].p_;
                    currentSave.state[i].q_ = user.state[i].q_;
                    strcpy(currentSave.state[i].board, user.state[i].board);
                    strcpy(currentSave.state[i].file_background, user.state[i].file_background);
                }
                return true;
            }
        }
    }
    return false;
}

void logout() {
    currentSave.mask = 's';
    currentSave.name[0] = '\0';
    currentSave.password[0] = '\0';
    for (int i = 0; i < 5; i++) {
        currentSave.record[i] = {0, 0, 0, 0};
        currentSave.state[i] = {0, 0, 1, 1};
        currentSave.state[i].board[0] = '\0';
        currentSave.state[i].file_background[0] = '\0';
    }
}

void saveGame(int saveSlot) {
    // save to currentSave
    currentSave.state[saveSlot] = {M, N, 1, 1};
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            currentSave.state[saveSlot].board[i*N + j] = board[i + 1][j + 1];
    currentSave.state[saveSlot].board[M*N + 1] = '\0';

    // save to saves data
    for (auto &user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            user.state[saveSlot].p = M;
            user.state[saveSlot].q = N;
            strcpy(user.state[saveSlot].board, currentSave.state[saveSlot].board);
        }
    }
}

void loadGame(int saveSlot) {
    for (auto user: saves) {
        if (strcmp(user.name, currentSave.name) == 0) {
            currentSave.state[saveSlot].p = user.state[saveSlot].p;
            currentSave.state[saveSlot].q = user.state[saveSlot].q;
            currentSave.state[saveSlot].p_ = user.state[saveSlot].p_;
            currentSave.state[saveSlot].q_ = user.state[saveSlot].q_;
            strcpy(currentSave.state[saveSlot].board, user.state[saveSlot].board);
        }
    }

    M = currentSave.state[saveSlot].p;
    N = currentSave.state[saveSlot].q;
    deleteBoard();
    initializeBoard();
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i + 1][j + 1] = currentSave.state[saveSlot].board[i*N + j];
}

// int main () {
//     currentSave.mask = 's';
//     strcpy(currentSave.name, "Bocchi The Rock");
//     strcpy(currentSave.password, "UoghhhSegsss");
//     for (int i = 0; i < 5; i++) {
//         currentSave.record[i] = {25, 3, 2023, i*100};
//         currentSave.state[i] = {0, 0, 1, 1};
//     }

//     char username[50], password[50], retypePassword[50];
//     int type = 1;
//     while (type != 0) {
//         int type;
//         cout << "Sign Up or Login: "; cin >> type;
//         cin.ignore();
//         if (type == 1) {
//             cout << "Type username: "; cin.getline(username, 50);
//             cout << "Type password: "; cin.getline(password, 50);
//             cout << "Confirm password: "; cin.getline(retypePassword, 50);
//             int signUpStatus = signUp(username, password, retypePassword);
//             if (signUpStatus == 1) 
//                 cout << "Sign Up successfully" << endl;
//             else if (signUpStatus == -1)
//                 cout << "Username already exsisted" << endl;
//             else if (signUpStatus == -2)
//                 cout << "Username is not valid" << endl;
//             else {
//                 cout << "Password do not match" << endl;
//             }
//         }
//         else if (type == 2) {
//             cout << "Type username: "; cin.getline(username, 50);
//             cout << "Type password: "; cin.getline(password, 50);
//             if (login(username, password)) {
//                 cout << "Login successful" << endl;
//             }
//             else {
//                 cout << "Login failed" << endl;
//             }
//         }
//         else if (type == 3) {
//             logout();
//         }
//         else if (type == 4) {
//             cout << "User info: " << endl;
//             cout << "Mask: " << currentSave.mask << endl;
//             cout << "Username: " << currentSave.name << endl;
//             cout << "Password: " << currentSave.password << endl;

//             for (int i = 0; i < 5; i++) {
//                 auto rec = currentSave.record[i];
//                 cout << "Record " << i + 1 << ": ";
//                 cout << rec.date.dd << "/" << rec.date.mm << "/" << rec.date.yy << ": " << rec.points << endl;
//             }

//             for (int i = 0; i < 5; i++) {
//                 auto st = currentSave.state[i];
//                 cout << "Board size: " << st.p << " " << st.q << endl;
//                 cout << "Current position: " << st.p_ << " " << st.q_ << endl;
//             }
//             cout << endl;
//         }
//     }
//     for (auto sf: saves) {
//         cout << "Mask: " << sf.mask << endl;
//         cout << "Username: " << sf.name << endl;
//         cout << "Password: " << sf.password << endl;

//         for (int i = 0; i < 5; i++) {
//             auto rec = sf.record[i];
//             cout << "Record " << i + 1 << ": ";
//             cout << rec.date.dd << "/" << rec.date.mm << "/" << rec.date.yy << ": " << rec.points << endl;
//         }

//         for (int i = 0; i < 5; i++) {
//             auto st = sf.state[i];
//             cout << "Board size: " << st.p << " " << st.q << endl;
//             cout << "Current position: " << st.p_ << " " << st.q_ << endl;
//         }
//         cout << endl;
//     }
// }