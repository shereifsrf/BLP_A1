#include <iostream>
#include <conio.h>

using namespace std;

int main(int argc, char** argv)
{
	//cout << argv[1];
	//if user passed '-i' as parameter
	if (string(argv[1]) == "-i")
	{
		//cout << "inside";

		string userid = "";
		string password = "";
		string cnfPassword = "";

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
			}
		}

		//create salt for the user (8 digits random generate)
		//save the data in salt.txt as <userid:salt>

		//generate MD5 digest in a format such as <paassword><saltNumber>
		//save the data in shadow file as <userid:salthash:securityclearance>

	}
	//user want sto login
	else
	{
		cout << "outside";
		//read the file.store file

	}
}