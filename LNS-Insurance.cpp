// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I � CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

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
Account inputAccount(Account& account);
void writeToFile(Account);
bool checkPassValidity(string p);
vector <Account> readFromFile();
void login(vector<Account>&);
void forgot();



//main function
int main()
{
	//using string literal instead of having each string on a new line
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Select an option from the menu below
)" << endl;

	displayMainMenu(); //show menu
	runProgram(); //start the application, expecting user input
}


//main program operation
void runProgram() {
	int i_menuSelection = 0;
    Account account;//data from the user
    vector <Account>accountFromFile;//data from the file

    do //application continues until the user requests to exit
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection) {
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
			case 4: //exit condition
				break;
			default: //validation for other numbers
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the four numbers" << endl;
				displayMainMenu();
				break;
			}
		}
		else //validation for non numeric input
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the four numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayMainMenu();
		}

	} while (i_menuSelection != 4); //monitoring for exit request

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

	do 
	{
	if (cin >> i_menuSelection)
		{
			switch (i_menuSelection) {
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

	} while (i_menuSelection != 5); //monitoring for request to return to the main menu
}

//inputAccount to take user input
Account inputAccount(Account& account) {
    cout << "Creating a new account." << endl;
    cout << "Please enter a user name: ";
    cin >> account.username;

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

//writeToFile function facilitates the storing of account details
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
    string uname, upassword;

	while (i_attemptCount < 3)
	{
		cout << "Enter user name: ";
		cin >> uname;
		cout << "Enter password: ";
		cin >> upassword;

		for (int i = 0; i < accountFromFile.size(); i++)
		{
			if (accountFromFile[i].username == uname && accountFromFile[i].password == upassword)
			{
				cout << uname << " logged in" << endl;
				displayLoggedInMenu();
				i_loggedIn = 1;
			}
		}
		if (i_loggedIn != 1)
		{
			i_attemptCount++;

			if (i_attemptCount <= 2) 
			{
				cout << "Invalid user name or password." << endl;
				cout << "Please try again." << endl;
			}
			else 
			{
				cout << "Log in attempts exceeded. Forgot password?" << endl;
				forgot();
			}
		}
	}
	displayMainMenu();
}

void forgot()
{

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