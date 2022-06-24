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

    //constructor to initialize the variables of the structure
    //you can provide a default value to your variables
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
Account inputAccount(Account& account);
void writeToFile(Account);
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
}

//inputAccount to take user input
Account inputAccount(Account& account) {
    cout << "Creating a new account." << endl;
    cout << "Please enter a user name: ";
    cin >> account.username;
    cout << "Please enter a password: ";
    cin >> account.password;
    cout << "User " << account.username << " created.";
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

    int i_loggedIn = 0;
    //get the username and password from the user to login
    string uname, upassword;
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
        cout << "Invalid user name or password" << endl << endl;
        displayMainMenu();
    }
}

void forgot()
{

}