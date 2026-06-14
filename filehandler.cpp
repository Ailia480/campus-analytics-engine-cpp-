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
