#ifndef Read_H
#define Read_H

#include <string>
#include <vector>

using namespace std;

vector<string> ReadAFile(string filename);
vector<string> tokenizeString(string input, string delimiter);

#endif