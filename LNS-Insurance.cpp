// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I – CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

#include <iostream>
#include <fstream>
using namespace std;

/// Function prototypes
void runProgram();
void displayMainMenu();
void displayAbout();
void displayLoggedInMenu();
void login();
void newUserRegistration();
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

	do //application continues until the user requests to exit
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection) {
			case 1:
				login();
				break;
			case 2:
				newUserRegistration();
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

void login()
{
	string s_enteredUserID, s_enteredPassword, s_fileUserID, s_filerUserPassword;
	cout << "Please enter a user name:" << endl;
	cin >> s_enteredUserID;
	cout << "Please enter your password:" << endl;
	cin >> s_enteredPassword;
	
	ifstream loginDetails;
	loginDetails.open("loginDetails.csv", ios::in);

	if (loginDetails.is_open())
	{
		while (loginDetails >> s_fileUserID >> s_filerUserPassword)
		{
			if (s_fileUserID == s_enteredUserID && s_filerUserPassword == s_enteredPassword)
			{
				cout << s_enteredUserID << " successfully logged in" << endl;
				displayLoggedInMenu();
			}
			else
			{
				cout << "Incorrect Login" << endl;
				displayMainMenu();
			}
		}
	}
	loginDetails.close();	
}

void newUserRegistration()
{
	string s_enteredUserID, s_enteredPassword;
	cout << "Creating a new user account" << endl;
	cout << "Please enter a user name:" << endl;
	cin >> s_enteredUserID;
	cout << "Please enter your password:" << endl;
	cin >> s_enteredPassword;

	ofstream loginDetails;
	loginDetails.open("loginDetails.csv", ios::app); //write to the csv file
	loginDetails << s_enteredUserID << ',' << s_enteredPassword << endl;
	cout << "Created a new user " << s_enteredUserID << endl;
	displayMainMenu();
}

void forgot()
{

}