
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