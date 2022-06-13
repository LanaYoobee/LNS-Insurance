// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I – CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

#include <iostream>
using namespace std;


void displayMainMenu() 
{
	cout << "1. Log in" << endl;
	cout << "2. Create new user" << endl;
	cout << "3. About" << endl;
	cout << "4. Exit" << endl;
}

void displayLoggedInMenu()
{
	cout << "1. Show insurer details" << endl;
	cout << "2. Show car details" << endl;
	cout << "3. Available policies" << endl;
	cout << "4. Submit a claim" << endl;
}

void displayAbout()
{
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Developed by Lana Lankevich and Saadi Radcliffe
)" << endl;
}

int main()
{
	//using string literal instead of having each string on a new line
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Select an option from the menu below
)" << endl;

	displayMainMenu(); //show menu

	int menuSelection = 0;

	do //application continues until the user requests to exit
	{
		if (cin >> menuSelection)
		{
			switch (menuSelection) {
			case 1:
				// Log in function will be called here
				break;
			case 2:
				// create mew iser function will be called here
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

	} while (menuSelection != 4); //monitoring for exit request

	cout << "Exiting application. Goodbye." << endl; //exit message
}
