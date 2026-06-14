#include <iostream>
#include "filehandler.h"
using namespace std;

int main() {
    vector<vector<string>> students = readTXT("students.txt");

    cout << "Loaded " << students.size() << " students:" << endl;
    for (int i = 0; i < students.size(); i++) {
        for (int j = 0; j < students[i].size(); j++) {
            cout << students[i][j] << " | ";
        }
        cout << endl;
    }

    return 0;
}
