
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Tools.h"

using namespace std;


vector<string> ReadAFile(string fileName)
{
	fstream inputFile(fileName.c_str(), fstream::in);
	vector<string> lineVector;

	string aLine;

	while (getline(inputFile, aLine))
	{
		if (aLine.find("//") != string::npos || aLine == "")
			continue;

		lineVector.push_back(aLine);
	}
	return lineVector;
}

vector<string> tokenizeString(string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos)
	{
		token = input.substr(0, pos);
		result.push_back(token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back(input);

	return (result);
}

string findUsernameExists(string filename, string username)
{
	vector<string> lineVector = ReadAFile(filename);

	for (string str : lineVector)
	{
		vector <string> stringLineArr = tokenizeString(str, ":");

		if (stringLineArr[0] == username)
		{
			return stringLineArr[1];
		}
	}
	return "";
}


HashNClearance getHashValue(string filename, string username)
{
	vector<string> lineVector = ReadAFile(filename);
	HashNClearance output;

	for (string str : lineVector)
	{
		vector <string> stringLineArr = tokenizeString(str, ":");

		if (stringLineArr[0] == username)
		{
			output.hash = stringLineArr[1];
			output.clearance = stoi(stringLineArr[2]);
			return output;
		}
	}
	return output;
}