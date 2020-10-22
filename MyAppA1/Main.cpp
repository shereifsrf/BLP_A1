#include <iostream>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "Tools.h"
#include <time.h>
#include "md5.h"

using namespace std;

int main(int argc, char** argv)
{
	//showing the MD5 test
	cout << "MD5 (""This is a test"") = " << md5("This is a test");

	//cout << argv[1];
	//if user passed '-i' as parameter
	#pragma region Registration Part
	if (string(argv[1]) == "-i")
	{
		//cout << "inside";

		string userid = "";
		string password = "";
		string cnfPassword = "";
		string randNumber;

		int clearance;
		int isValidateOK = 0;
		int pswHasUpperCase = 0;
		int pswHasDigit = 0;
		int isOk = 0;

		char key;

		//prompt user to type username
		cout << "Username: ";
		cin >> userid;
		cout << endl;

		//check whether the user already exist in the file

		//promt user to type password
		while (!isOk)
		{
			password = "";
			cout << "Password: ";
			key = _getch();

			while (key != '\r')
			{
				password += key;
				cout << "*";
				key = _getch();
			}
			//cout << endl << password; 

			//validate user typed password whether contains atleast character, one Upper case and a Digit
			if (password.length() >= 8)
			{
				for (int i = 0; i < password.length(); i++)
				{
					if (pswHasDigit == 0)
					{
						if (isdigit(password[i]))
						{
							pswHasDigit = 1;
						}
					}
					if (pswHasUpperCase == 0)
					{
						if (isupper(password[i]))
						{
							pswHasUpperCase = 1;
						}
					}
				}

				if (pswHasDigit && pswHasUpperCase)
				{
					cout << " (password Ok)";
					cout << endl;
					isOk = 1;
				}
				else
				{
					cout << " (Password must contain a Digit and/or Upper case)";
					cout << endl;
					isOk = 0;
				}
			}
			else
			{
				cout << " (Password must be atleast 8 character long)";
				cout << endl;
				isOk = 0;
			}
		}

		//prompt user to type confirm password and validate match
		isOk = 0;

		while (!isOk)
		{
			cnfPassword = "";
			cout << "Confirm Password: ";
			key = _getch();

			while (key != '\r')
			{
				cnfPassword += key;
				cout << "*";
				key = _getch();
			}

			if (password == cnfPassword)
			{
				cout << " (password matched)";
				cout << endl;
				isOk = 1;
			}
			else
			{
				cout << " (password mismatched)";
				cout << endl;
				isOk = 0;
			}
		}

		//prompt user to type clearance level and validate whether the typed is within 0-3
		isOk = 0;

		while (!isOk)
		{
			cout << "User Clearance (0-3): ";
			cin >> clearance;
			cout << endl;

			if (clearance < 0 && clearance > 3)
			{
				cout << "Clearance must be within 0-3";
				cout << endl;
				isOk = 0;
				continue;
			}
			isOk = 1;
		}

		//create salt for the user (8 digits random generate)
		//read the file and check whether the user already existing
		string saltFile = "salt.txt";
		string shadowFile = "shadow.txt";

		vector<string> lineVector = ReadAFile(saltFile);

		for (string str : lineVector)
		{
			vector <string> stringLineArr = tokenizeString(str, ":");

			if (stringLineArr[0] == userid)
			{
				isOk = 0;
				break;
			}
		}

		if (!isOk)
		{
			cout << "User already exists";
			cout << endl;
		}
		else
		{
			// generate a random 8 digit number for salt
			srand(time(NULL));

			for (int i = 0; i < 8; i++)
			{
				int num = rand() % 9 + 1;

				randNumber += to_string(num);
			}

			//store the data in the salt file
			//save the data in salt.txt as <userid:salt>
			ofstream out(saltFile);
			out << userid << ":" << randNumber << endl;
			out.close();
		}



		//generate MD5 digest in a format such as <paassword><saltNumber>
		string md5Input = password + randNumber;
		string md5Output;
		md5Output = md5(md5Input);
		
		//save the data in shadow file as <userid:salthash:securityclearance>
		ofstream outS(shadowFile);
		outS << userid << ":" << md5Output << ":" << clearance << endl;
		outS.close();
		

	#pragma endregion 
	}
	//user want sto login
	else
	{
	#pragma region Logging in Part
	
	//load the file.store

	//prompt 

	#pragma endregion

	}
}