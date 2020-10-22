#ifndef Read_H
#define Read_H

#include <string>
#include <vector>

using namespace std;

struct HashNClearance
{
	string hash;
	int clearance;
};

vector<string> ReadAFile(string filename);
vector<string> tokenizeString(string input, string delimiter);
string findUsernameExists(string filename, string username);
HashNClearance getHashValue(string filename, string username);

#endif