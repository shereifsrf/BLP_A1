#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	//if user passed '-i' as parameter
	if (argv[1] == "-i")
	{

		char userid[] = "";

		//prompt user to type username
		cout << "username: ";
		cin >> userid;
		cout << endl;

		//promt user to type password
		cout << "password: ";
		cin >> userid;
		cout << endl; //checking

		//validate user typed password whether contains atleast character, one Upper case and a Digit
		//prompt user to type confirm password and validate match

		//prompt user to type clearance level and validate whether the typed is within 0-3

		//create salt for the user (8 digits random generate)
		//save the data in salt.txt as <userid:salt>

		//generate MD5 digest in a format such as <paassword><saltNumber>
		//save the data in shadow file as <userid:salthash:securityclearance>

	}
	//user want sto login
	else
	{
		//read the file.store file

	}
}