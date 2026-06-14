#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
using namespace std;

vector<string> parseLine(string line);
string formatField(string field);

vector<vector<string>> readTXT(string filename);
void writeTXT(string filename, vector<string> header, vector<vector<string>> rows);
void appendTXT(string filename, vector<string> row);
vector<string> findRow(string filename, int colIndex, string value);
bool rowExists(string filename, int colIndex, string value);

#endif