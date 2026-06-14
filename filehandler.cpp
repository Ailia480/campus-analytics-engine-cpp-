#include "filehandler.h"
#include <iostream>
#include <fstream>
using namespace std;

vector<string> parseLine(string line) {
    vector<string> fields;
    string current = "";
    bool inQuotes = false;

    for (int i = 0; i < line.length(); i++) {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            fields.push_back(current);
            current = "";
        }
        else {
            current += c;
        }
    }
    fields.push_back(current);

    return fields;
}

string formatField(string field) {
    bool needsQuotes = false;
    for (int i = 0; i < field.length(); i++) {
        if (field[i] == ',') {
            needsQuotes = true;
            break;
        }
    }

    if (needsQuotes) {
        return "\"" + field + "\"";
    }
    return field;
}

vector<vector<string>> readTXT(string filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: could not open " << filename << endl;
        return data;
    }

    string line;
    getline(file, line); // skip header row

    while (getline(file, line)) {
        if (line.length() == 0) continue;
        vector<string> row = parseLine(line);
        data.push_back(row);
    }

    file.close();
    return data;
}

void writeTXT(string filename, vector<string> header, vector<vector<string>> rows) {
    ofstream file(filename); // opening like this overwrites the file

    for (int i = 0; i < header.size(); i++) {
        file << formatField(header[i]);
        if (i != header.size() - 1) file << ",";
    }
    file << endl;

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            file << formatField(rows[i][j]);
            if (j != rows[i].size() - 1) file << ",";
        }
        file << endl;
    }

    file.close();
}

void appendTXT(string filename, vector<string> row) {
    ofstream file(filename, ios::app);

    for (int i = 0; i < row.size(); i++) {
        file << formatField(row[i]);
        if (i != row.size() - 1) file << ",";
    }
    file << endl;

    file.close();
}

vector<string> findRow(string filename, int colIndex, string value) {
    vector<vector<string>> data = readTXT(filename);

    for (int i = 0; i < data.size(); i++) {
        if (colIndex < data[i].size() && data[i][colIndex] == value) {
            return data[i];
        }
    }

    vector<string> empty;
    return empty;
}

bool rowExists(string filename, int colIndex, string value) {
    vector<string> result = findRow(filename, colIndex, value);
    return !result.empty();
}
