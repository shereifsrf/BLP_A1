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

	//cout << argv[1];
	//if user passed '-i' as parameter
#pragma region Registration Part
	if (argc > 1 && string(argv[1]) == "-i")
	{
		//cout << "inside";

		string username = "";
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
		cin >> username;
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
		string saltValue;

		saltValue = findUsernameExists(saltFile, username);

		if (saltValue != "")
		{
			cout << "User already exists";
			cout << endl;
			return 0;
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
			//save the data in salt.txt as <username:salt>
			ofstream out(saltFile, ios_base::app);
			out << username << ":" << randNumber << endl;
			out.close();
		}



		//generate MD5 digest in a format such as <paassword><saltNumber>
		string md5Input = password + randNumber;
		string md5Output;
		md5Output = md5(md5Input);

		//save the data in shadow file as <username:salthash:securityclearance>
		ofstream outS(shadowFile, ios_base::app);
		outS << username << ":" << md5Output << ":" << clearance << endl;
		outS.close();


#pragma endregion 
	}
	//user want sto login
	else
	{

		//showing the MD5 test
		cout << "MD5 (""This is a test"") = " << md5("This is a test") << endl;

#pragma region Logging in Part

		string username = "";
		string password = "";
		string saltValue;
		string hashValue;

		int isOk;
		int clearance;

		//structure for the files.store file
		struct MyStruct
		{
			string filename;
			string username;
			int clearance;
			string status;
		};

		//load the files.store
		string saltFile = "salt.txt";
		string shadowFile = "shadow.txt";
		string filesStore = "files.store";

		char key;

		HashNClearance hNCStruct;

		vector<string> lineVector = ReadAFile(filesStore);
		vector <MyStruct> filesVector;

		for (string str : lineVector)
		{
			vector <string> stringLineArr = tokenizeString(str, ":");

			filesVector.push_back({ stringLineArr[0], stringLineArr[1], stoi(stringLineArr[2]), "exisiting" });
		}

		/*for (int i = 0; i < filesVector.size(); i++)
		{
			cout << filesVector[i].filename << filesVector[i].username << filesVector[i].clearance << filesVector[i].status;
		}*/

		//prompt username and password
		cout << "Username: ";
		cin >> username;
		cout << endl;

		password = "";
		cout << "Password: ";
		key = _getch();

		while (key != '\r')
		{
			password += key;
			cout << "*";
			key = _getch();
		}
		cout << endl;

		//use md5 and check whether the username is valid and password is correct
		//check whether user exists in the salt.txt
		saltValue = findUsernameExists(saltFile, username);

		if (saltValue != "")
		{
			cout << username << " found in the salt.txt" << endl;

			//get the salt value
			cout << "salt retrieved: " << saltValue << endl;

			//hash the value and show it
			string md5Input = password + saltValue;
			string md5Output;

			cout << "hashing ..." << endl;

			md5Output = md5(md5Input);

			hNCStruct = getHashValue("shadow.txt", username);

			hashValue = hNCStruct.hash;
			clearance = hNCStruct.clearance;

			cout << "hash value: " << hashValue << endl;

			//check whether user password is correct
			if (hashValue == md5Output)
			{
				cout << "Authentication for user " << username << " complete" << endl;
				cout << "The clearance for " << username << " is " << clearance << endl << endl;

				//show the options after successfull login
				cout << "Options: (C)reatem (A)ppend, (R)ead, (W)rite, (L), (S)ave or (E)xit" << endl;

			}
			else
			{
				cout << "User password is not correct!!" << endl;
				return 0;
			}


		}
		else
		{
			cout << " (Username not found)";
			return 0;
		}



#pragma endregion

	}
}