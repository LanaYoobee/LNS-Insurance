// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I – CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector> 
using namespace std;

/// Structs
struct Account {
    string username;
    string password;

    //constructor to initialize the variables of the struct
    Account(string u = "user1", string p = "pass1") {
        username = u;
        password = p;
    }
};

/// Function prototypes
void runProgram();
void displayMainMenu();
void displayAbout();
void displayLoggedInMenu();
void loggedInFunctions();
Account inputAccount(Account&);
void writeToFile(Account);
bool checkUserNameExists(string);
bool checkPassValidity(string);
vector <Account> readFromFile();
void login(vector<Account>&);
void forgotPassword();

//main function
int main()
{
	//using string literal instead of having each string on a new line
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Select an option from the menu below
)" << endl;
	runProgram(); //start the application, expecting user input
}

//main program operation
void runProgram()
{
	int i_menuSelection = 0;
	Account account;//data from the user
	vector <Account>accountFromFile;//data from the file
	displayMainMenu(); //show menu
	bool b_runProgram = true;

	while (b_runProgram)
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				accountFromFile = readFromFile();
				login(accountFromFile);
				break;
			case 2:
				inputAccount(account);
				writeToFile(account);
				break;
			case 3:
				displayAbout();
				displayMainMenu();
				break;
			case 4:
				b_runProgram = false; //false so let's get out of here
				break;
			default:
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the four numbers" << endl;
				displayMainMenu();
				break;
			}
		}
		else
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the four numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayMainMenu();
		}
	}
	cout << "Exiting application. Goodbye." << endl; //exit message
}

//displays main menu
void displayMainMenu()
{
	cout << "1. Log in" << endl;
	cout << "2. Create new user" << endl;
	cout << "3. About" << endl;
	cout << "4. Exit" << endl;
}

//the result of About selection
void displayAbout()
{
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Developed by Lana Lankevich and Saadi Radcliffe
)" << endl;
}

//menu visible to people who are logged in
void displayLoggedInMenu()
{
	cout << "1. Show insurer details" << endl;
	cout << "2. Show car details" << endl;
	cout << "3. Available policies" << endl;
	cout << "4. Submit a claim" << endl;
	cout << "5. Go back to the main menu" << endl;
	loggedInFunctions();
}

void loggedInFunctions() 
{
	int i_menuSelection = 0;

	bool b_runLoggedMenu = true;
	
	while (b_runLoggedMenu) 
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				cout << "Insurer details" << endl;
				break;
			case 2:
				cout << "Car details" << endl;
				break;
			case 3:
				cout << "Available policies" << endl;
				break;
			case 4:
				cout << "Submit a claim" << endl;
				break;
			case 5:
				cout << "Going back to the main menu" << endl;
				displayMainMenu();
				b_runLoggedMenu = false;
				break;
			default: //validation for other numbers
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the five numbers" << endl;
				displayLoggedInMenu();
				break;
			}
		}
		else //validation for non numeric input
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the five numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayLoggedInMenu();
		}
	} 
}

//inputAccount to take user input
Account inputAccount(Account& account) {
    cout << "Creating a new account." << endl;

    cout << "Please enter a user name: ";
    cin >> account.username;

	while (!checkUserNameExists(account.username))
	{
		cout << "Please enter a user name: ";
		cin >> account.username;
	}

	while (checkUserNameExists(account.username))
	{
		cout << "Please create a password. The password must be at least eight characters long and contain one upper case and one lower case letter: ";
		cin >> account.password;

		while (checkPassValidity(account.password) == false) //validating for password strength requirements
		{
			cout << "Please enter a new password: ";
			cin >> account.password;
		}

		cout << "User " << account.username << " created." << endl;
		displayLoggedInMenu();

		return (account);
	}
}

//checking that the account already exists
bool checkUserNameExists(string s_checkUserName)
{
	vector <Account>accountFromFile = readFromFile();

	for (int i = 0; i < accountFromFile.size(); i++)
	{
		if (accountFromFile[i].username == s_checkUserName)
		{
			cout << s_checkUserName << " is already taken. Please pick a different user name." << endl;
			return false;
		}
	}
	return true;
}

//writeToFile function to store login details
void writeToFile(Account account) {

    fstream loginDetails("loginDetails.csv", ios::app);
    loginDetails << account.username << "," << account.password << endl;
    loginDetails.close();
}

//readFromFile function to read data from the loginDetails.csv
vector <Account> readFromFile() {

    fstream loginDetails("loginDetails.csv", ios::in);
    vector<Account> tempAccount;

    Account a;
    string line;
    while (getline(loginDetails, line)) {

        istringstream linestream(line);//to split the row into columns/properties
        string item;
        //until the appearance of comma, everything is stored in item
        getline(linestream, item, ',');
        a.username = item;

        getline(linestream, item, ',');
        a.password = item;

        tempAccount.push_back(a);
    }
    loginDetails.close();
    return(tempAccount);
}

//login function to search for the username and password
void login(vector<Account>& accountFromFile) {

    int i_loggedIn = 0, i_attemptCount = 0;
    //get the username and password from the user to login
    string s_uname, s_upassword;

	while (i_attemptCount < 3 && (i_loggedIn == 0))
	{
		cout << "Enter user name: ";
		cin >> s_uname;
		cout << "Enter password: ";
		cin >> s_upassword;

		for (int i = 0; i < accountFromFile.size(); i++)
		{
			if (accountFromFile[i].username == s_uname && accountFromFile[i].password == s_upassword)
			{
				cout << s_uname << " logged in" << endl;
				displayLoggedInMenu();
				i_loggedIn = 1;
				return; //we are now logged in so return out of this function
			}
		}
		if (i_loggedIn != 1)
		{
			i_attemptCount++;

			if (i_attemptCount < 3) 
			{
				cout << "Invalid user name or password." << endl;
				cout << "Please try again." << endl;
			}
			else 
			{
				cout << "Log in attempts exceeded. Forgot password?" << endl;
				forgotPassword();
			}
		}
	}
	displayMainMenu();
}

void forgotPassword()
{
	string s_userName;
	cout << "Enter user name to search for the password: ";
	cin >> s_userName;


}

//checks for password strength requirements
bool checkPassValidity(string p) 
{
	int i_length = p.length();
	int i_lowerCount = 0, i_upperCount = 0;

	for (int i = 0; i < i_length; i++)
		{
			if (isupper(p[i]))
				i_upperCount++;
			if (islower(p[i]))
				i_lowerCount++;
		}
		if (i_length >= 8 && i_lowerCount >= 1 && i_upperCount >= 1)
			return true;
		if (i_length < 8)
			cout << "The password length must be at least eight characters." << endl;
		if (i_lowerCount < 1)
			cout << "The password must contain at least one lower case character." << endl;
		if (i_upperCount < 1)
			cout << "The password must contain at least one upper case character." << endl;
return false;
}