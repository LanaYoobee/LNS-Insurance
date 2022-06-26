// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I – CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector> 
using namespace std;

//***********************
//Struct definitions
//***********************

struct Account {
	string s_username, s_password;

	//constructor to initialize the variables of the struct
	Account(string s_u = "user1", string s_p = "pass1") {
		s_username = s_u;
		s_password = s_p;
	}
};

struct Policy {
	string s_username, s_carMake, s_carModel, s_carYear, s_insuredValue;

	//constructor to initialize the variables of the struct
	Policy(string s_u = "user1", string s_cMake = "Toyota", string s_cModel = "Corolla", string s_cY = "2021", string s_iV = "24500") {
		s_username = s_u;
		s_carMake = s_cMake;
		s_carModel = s_cModel;
		s_carYear = s_cY;
		s_insuredValue = s_iV;
	}
};

//***********************
//Function prototypes
//***********************

void mainMenuFunctions();
void displayMainMenu();
void displayAbout();
void displayPolicyMenu();
void displayLoggedInMenu();
void displayAdminMenu();
void loggedInFunctions();
void adminFunctions();
Account createAccount(Account&);
void viewPolicies();
void writeAccountToFile(Account);
void showPolicyDetails(string);
Policy createPolicy(string);
bool checkUserNameExists(string);
bool checkPassValidity(string);
vector <Account> readAccountFromFile();
void login(vector<Account>&);
void forgotPassword();



Account account;//data from the user
vector <Account> accountFromFile;//data from the file
Policy policy;//data from the user
vector <Policy> policyFromFile;//data from the file
string s_loggedInUser;

//***********************
//Functions
//***********************


//main function
int main()
{
	//using string literal instead of having each string on a new line
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Select an option from the menu below
)";
	mainMenuFunctions(); //start the application, expecting user input
}

//main program operation
void mainMenuFunctions()
{
	int i_menuSelection = 0;

	displayMainMenu(); //show menu
	bool b_runProgram = true;

	while (b_runProgram)
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				accountFromFile = readAccountFromFile();
				login(accountFromFile);
				break;
			case 2:
				createAccount(account);
				writeAccountToFile(account);
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
				cout << "Available policies" << endl;
				showPolicyDetails(s_loggedInUser);
				displayPolicyMenu();
				break;
			case 3:
				cout << "Submit a claim" << endl;
				break;
			case 4:
				cout << "Going back to the main menu" << endl;
				displayMainMenu();
				b_runLoggedMenu = false;
				break;
			default: //validation for other numbers
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the four numbers" << endl;
				displayLoggedInMenu();
				break;
			}
		}
		else //validation for non numeric input
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the four numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayLoggedInMenu();
		}
	}
}

void adminFunctions()
{
	int i_menuSelection = 0;

	bool b_runAdminMenu = true;

	while (b_runAdminMenu)
	{
		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				cout << "Below is the list of users and their passwords" << endl;
				break;
			case 2:
				cout << "Below is the list of all policies" << endl;
				break;
			case 3:
				cout << "Below is a list of all claims" << endl;
				break;
			case 4:
				cout << "Going back to the main menu" << endl;
				displayMainMenu();
				b_runAdminMenu = false;
				break;
			default: //validation for other numbers
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the four numbers" << endl;
				displayAdminMenu();
				break;
			}
		}
		else //validation for non numeric input
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the four numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayLoggedInMenu();
		}
	}
}


//****************************
//Menu and Sub Menu Functions
//****************************

//displays main menu
void displayMainMenu()
{
	cout << endl << "1. Log in" << endl;
	cout << "2. Create new user" << endl;
	cout << "3. About" << endl;
	cout << "4. Exit" << endl;
}

//menu for Admin users - allows managing existing accounts
void displayAdminMenu()
{
	cout << endl << "1. Manage users" << endl;
	cout << "2. Manage policies" << endl;
	cout << "3. Manage claims" << endl;
	cout << "4. Go back to the main menu" << endl;
	adminFunctions();
}

//menu visible to people who are logged in
void displayLoggedInMenu()
{
	cout << endl << "1. Show insurer details" << endl;
	cout << "2. Policies" << endl;
	cout << "3. Submit a claim" << endl;
	cout << "4. Go back to the main menu" << endl;
	loggedInFunctions();
}

//menu to view policies and create new policies
void displayPolicyMenu()
{
	cout << endl<<  "Would you like to add a new policy? " << endl;
	cout << "1. Yes." << endl;
	cout << "2. No. Return to the previous menu." << endl;
}


//the result of About selection
void displayAbout()
{
	cout << R"(Integrated Studio I - Assignment 2
***********************************************
Vehicle Insurance System
Developed by Lana Lankevich and Saadi Radcliffe
)";
}

//*************************************
//Account Creation and Logging In
//*************************************

//create new account
Account createAccount(Account& account) {
	cout << "Creating a new account." << endl;

	cout << "Please enter a user name: ";
	cin >> account.s_username;

	while (!checkUserNameExists(account.s_username))
	{
		cout << "Please enter a user name: ";
		cin >> account.s_username;
	}

	while (checkUserNameExists(account.s_username)) //check for unique user name
	{
		cout << "Please create a password. The password must be at least eight characters long and contain one upper case and one lower case letter: ";
		cin >> account.s_password;

		while (checkPassValidity(account.s_password) == false) //validating for password strength requirements
		{
			cout << "Please enter a new password: ";
			cin >> account.s_password;
		}

		cout << "User " << account.s_username << " created." << endl;
		displayLoggedInMenu();

		return (account);
	}
}

//find a password for a given user name
void forgotPassword()
{
	string s_userName;
	cout << "Forgot your password? Enter your user name to search for the password: ";
	cin >> s_userName;
	vector <Account>accountFromFile = readAccountFromFile();

	for (int i = 0; i < accountFromFile.size(); i++) //iterate through the file looking for the user
	{
		if (accountFromFile[i].s_username == s_userName)
		{
			cout << "User " << s_userName << " exists. Your password is " << accountFromFile[i].s_password << endl;
			return;
		}
	}
	cout << "No such user name found. Try creating a new user account." << endl;
}

//writeAccountToFile function to store login details
void writeAccountToFile(Account account) {

	fstream loginDetails("loginDetails.csv", ios::app);
	loginDetails << account.s_username << "," << account.s_password << endl;
	loginDetails.close();
}

//readAccountFromFile function to read data from the loginDetails.csv
vector <Account> readAccountFromFile() {

	fstream loginDetails("loginDetails.csv", ios::in);
	vector<Account> tempAccount;

	Account a;
	string line;
	while (getline(loginDetails, line)) {

		istringstream linestream(line);//to split the row into columns/properties
		string item;
		//until the appearance of comma, everything is stored in item
		getline(linestream, item, ',');
		a.s_username = item;

		getline(linestream, item, ',');
		a.s_password = item;

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
			if (accountFromFile[i].s_username == s_uname && accountFromFile[i].s_password == s_upassword)
			{
				cout << s_uname << " logged in" << endl;
				s_loggedInUser = s_uname;
				if (s_uname == "Admin")
					displayAdminMenu();
				else
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
				cout << "Log in attempts exceeded." << endl;
				forgotPassword();
			}
		}
	}
	displayMainMenu();
}


//***********************
//Validation Functions
//***********************

//checking that the account already exists
bool checkUserNameExists(string s_checkUserName)
{
	vector <Account>accountFromFile = readAccountFromFile();

	for (int i = 0; i < accountFromFile.size(); i++)
	{
		if (accountFromFile[i].s_username == s_checkUserName)
		{
			cout << s_checkUserName << " is already taken. Please pick a different user name." << endl;
			return false;
		}
	}
	return true;
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

//****************************
//Logged In Functions
//****************************


//view policies
void viewPolicies() {
	int i_menuSelection = 0;

	bool b_policyMenu = true;

	cout << "You currently have the following policies. " << endl;
	showPolicyDetails(s_loggedInUser);
	displayPolicyMenu();
	cin >> i_menuSelection;

	if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				b_policyMenu = true;
				createPolicy(s_loggedInUser);
				displayPolicyMenu();
				break;
			case 2:
				cout << "Going back to the previous menu" << endl;
				b_policyMenu = false;
				displayLoggedInMenu();
				break;
			default: //validation for other numbers
				cout << "Invalid selection." << endl;
				cout << "Please enter one of the two numbers" << endl;
				displayPolicyMenu();
				break;
			}
		}
		else //validation for non numeric input
		{
			cout << "Invalid selection." << endl;
			cout << "Please select one of the two numbers" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayPolicyMenu();
		}

}

Policy createPolicy(string s_loggedInUser) {
	cout << "Creating a new Policy." << endl;

	policy.s_username = s_loggedInUser;
	cout << "Please enter your car make: ";
	cin >> policy.s_carMake;
	cout << "Please enter your car model: ";
	cin >> policy.s_carModel;
	cout << "Please enter your car year of manufacture: ";
	cin >> policy.s_carYear;
	cout << "Please enter the value you'd like to ensure your car for: ";
	cin >> policy.s_insuredValue;

	fstream policyDetails("policyDetails.csv", ios::app);
	policyDetails << policy.s_username << "," << policy.s_carMake << "," << policy.s_carModel << "," << policy.s_carYear << "," << policy.s_insuredValue << endl;
	policyDetails.close();

	return(policy);
}

//readPolicyFromFile function to read data from the policyDetails.csv
vector <Policy> readPolicyFromFile() {

	fstream policyDetails("policyDetails.csv", ios::in);
	vector<Policy> tempPolicy;

	Policy p;
	string line;
	while (getline(policyDetails, line)) {

		istringstream linestream(line);//to split the row into columns/properties
		string s_item;

		//until the appearance of comma, everything is stored in item
		getline(linestream, s_item, ',');
		p.s_username = s_item;

		getline(linestream, s_item, ',');
		p.s_carMake = s_item;

		getline(linestream, s_item, ',');
		p.s_carModel = s_item;

		getline(linestream, s_item, ',');
		p.s_carYear = s_item;

		getline(linestream, s_item, ',');
		p.s_insuredValue = s_item;

		tempPolicy.push_back(p);
	}
	policyDetails.close();
	return(tempPolicy);
}

//show all policies for a given user name
void showPolicyDetails(string s_loggedInUser)
{
	policyFromFile = readPolicyFromFile();

	cout << "Policies for " << s_loggedInUser << endl;

	for (int i = 0; i < policyFromFile.size(); i++)
	{
		if (policyFromFile[i].s_username == s_loggedInUser) {
			for (int i = 0; i < policyFromFile.size(); i++) //iterate through the file listing all policies for the given user 
			{
				cout << "Policy " << i + 1;
				cout << "Car Make " << policyFromFile[i].s_carMake << endl;
				cout << "Car Model " << policyFromFile[i].s_carModel << endl;
				cout << "Car Year " << policyFromFile[i].s_carYear << endl;
				cout << "Insured Value " << policyFromFile[i].s_insuredValue << endl;
			}
		}
		else {
			cout << "No policies found." << endl;
			break;
		}
	}
	return;
}