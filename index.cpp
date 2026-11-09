#include <cstdlib>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string today() {
    time_t now = time(nullptr);
    string dateAndTime = ctime(&now);
    string date = dateAndTime.substr(0, 11);
    return date;
}

int createEntry(string diaryEntry, string filePath) {
    ifstream readingDiary(filePath);
    if (!readingDiary.is_open() ) {
        cerr << "Error: Something went wrong";
        return 0;
    }
    string line;
    while (line != "# " + today() && getline(readingDiary, line) ) {
        getline(readingDiary, line);
    }
    readingDiary.close();
    ofstream diary(filePath, ios::app);
    if (!diary.is_open()) {
        cerr << "Error: Something went wrong";
        return 0;
    }
    if (line != "# " + today())
        diary << "# " << today() << endl;

    diary << diaryEntry << "\n\n";
    return 0;
}

enum options {
    ADDENTRY,
    READENTRY,
    UPDATENTRY
};

int main() {
    string configPath = "/home/Ishan.config/myry.conf";
    string filePath = "/home/Ishan/Documents/diary.md";
    ifstream configFile(configPath);
    if (!configFile.is_open()) {
        cerr << "Error: Couldn't find Config File!\n";
        cout << "Reverting to default diary File " << filePath;
        cout << endl << endl;
    } else {
        getline(configFile, filePath); // TODO Add a config parser
    }
    configFile.close();
    ofstream diaryFile(filePath, ios::app);
    if (!diaryFile.is_open()) {
        cerr << "A new file will be created in " << filePath;
        cout << "\nYou can change the path in " << configPath;
    }
    char userChoice;
    cout << "What to do? (N): Write NEW Entry, (U): Update OLD ENTRY";
    cout << " (R): READ Entries (Q): QUIT ";
    cin >> userChoice;
    string diaryEntry;
    string dateEntry;
    switch (userChoice) {
        case 'N':
        case 'n': {
            cout << endl << "Share what happened today? " << today() << endl;
            cin.ignore();
            getline(cin, diaryEntry);
            createEntry(diaryEntry, filePath);
            break;
        }
        case 'R':
        case 'r': {
            cout << "Enter the date you want to read the entry of ";
            cin.ignore();
            getline(cin, dateEntry);
            string command =  "vim -c ?\"" + dateEntry + "?+1\" " + filePath;
            cout << command;
            system(command.c_str());
            break;
        }
        case 'U':
        case 'u':
            cout << "Using the text editor vim\n";
            cout << "Enter the date you want to update the Entry of: format (MM DD) : ";
            cin.ignore();
            getline(cin, dateEntry);
            system(("vim -c ?\"" + dateEntry + "?+1 \" -c\"startinsert\"  " + filePath).c_str());
            break;
        case 'Q':
        case 'q':
            cout << "Have a nice day ;)\n";
            return 0;
    }
}
