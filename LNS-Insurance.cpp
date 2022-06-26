// LNS-Insurance.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Integrated Studio I – CS103 | ASSIGNMENT 2 | Lana Lankevich and Saadi Radcliffe | Student ID 270164718 and 270206492

#include <iostream>
#include <fstream>
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

struct Claim {
	string s_username, s_policyID, s_claimType, s_claimStatus;

	//constructor to initialize the variables of the struct
	Claim(string s_u = "user1", string s_pID = "1", string s_cType = "Stolen", string s_cStatus = "Submitted") {
		s_username = s_u;
		s_policyID = s_pID;
		s_claimType = s_cType;
		s_claimStatus = s_cStatus;
	}
};

//***********************
//Function prototypes
//***********************

void mainMenuFunctions();
void displayMainMenu();
void displayAbout();
void displayInsurerDetails();
void displayPolicyMenu();
void displayLoggedInMenu();
void displayAdminMenu();

void loggedInFunctions();
void adminFunctions();
Account createAccount(Account&);
void viewPolicies();
void viewClaims();
void writeAccountToFile(Account);
void writePolicyToFile(Policy);
void showPolicyDetails(string);
void showClaimDetails(string);
Policy createPolicy(string);
bool checkUserNameExists(string);
bool checkPassValidity(string);
vector <Account> readAccountFromFile();
vector <Policy> readPolicyFromFile();
vector <Claim> readClaimFromFile();
void login(vector<Account>&);
void forgotPassword();
Claim createClaim(string);
void writeClaimToFile(Claim);

Account account;//data from the user
vector <Account> accountFromFile;//data from the file
Policy policy;//data from the user
vector <Policy> policyFromFile;//data from the file
Claim claim;//data from the user
vector <Claim> claimFromFile;//data from the file
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
				return;
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
				displayInsurerDetails();
				displayLoggedInMenu();
				break;
			case 2:
				viewPolicies();
				displayLoggedInMenu();
				break;
			case 3:
				viewClaims();
				displayLoggedInMenu();
				break;
			case 4:
				cout << "Going back to the main menu" << endl;
				displayMainMenu();
				b_runLoggedMenu = false;
				return;
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
				showPolicyDetails(s_loggedInUser);
				displayAdminMenu();
				break;
			case 3:
				showClaimDetails(s_loggedInUser);
				displayAdminMenu();
				break;
			case 4:
				cout << "Going back to the main menu" << endl;
				displayMainMenu();
				b_runAdminMenu = false;
				return;
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
}

//menu visible to people who are logged in
void displayLoggedInMenu()
{
	cout << endl << "1. Show insurer details" << endl;
	cout << "2. Policies" << endl;
	cout << "3. Claims" << endl;
	cout << "4. Go back to the main menu" << endl;
}

//menu to view policies and create new policies
void displayPolicyMenu()
{
	cout << endl<<  "Would you like to add a new policy? " << endl;
	cout << "1. Yes." << endl;
	cout << "2. No. Return to the previous menu." << endl;
}

//menu to view claims and create new claims
void displayClaimMenu()
{
	cout << endl << "Would you like to submit a new claim? " << endl;
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

//the result of Insurer Details selection
void displayInsurerDetails()
{
	cout << R"(You are insured with LNS Insurance
***********************************************
for any problems or concerns, please contact Insurance Admin
email: admin@lnsinsurance.fake.com
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
				if (s_uname == "Admin") {
					displayAdminMenu();
					adminFunctions();
				}
				else
				{
					displayLoggedInMenu();
					loggedInFunctions();
				}
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

	showPolicyDetails(s_loggedInUser);

	displayPolicyMenu();

	while (b_policyMenu) {

		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				b_policyMenu = true;
				createPolicy(s_loggedInUser);
				writePolicyToFile(policy);
				displayPolicyMenu();
				break;
			case 2:
				cout << "Going back to the previous menu" << endl;
				b_policyMenu = false;
				return;
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
}

//take user input to create a new policy
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

	return(policy);
}

// writePolicyToFile function to store policy details
void writePolicyToFile(Policy policy) {

	fstream policyDetails("policyDetails.csv", ios::app);
	policyDetails << policy.s_username << "," << policy.s_carMake << "," << policy.s_carModel << "," << policy.s_carYear << "," << policy.s_insuredValue << endl;
	policyDetails.close();
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

	for (int i = 0; i < policyFromFile.size(); i++)
	{
		if (s_loggedInUser == "Admin")
		{
			cout << "Below is the list of all existing policies" << endl;
			for (int i = 0; i < policyFromFile.size(); i++) //iterate through the file listing all policies for all users
			{
					cout << endl << policyFromFile[i].s_username << endl;
					cout << "Policy ID " << i << endl;
					cout << "Car Make " << policyFromFile[i].s_carMake << endl;
					cout << "Car Model " << policyFromFile[i].s_carModel << endl;
					cout << "Car Year " << policyFromFile[i].s_carYear << endl;
					cout << "Insured Value " << policyFromFile[i].s_insuredValue << endl;
			}
			return;
		}
		else if (policyFromFile[i].s_username == s_loggedInUser)
		{
			cout << "User " << s_loggedInUser << " has these policies:" << endl;
			for (int i = 0; i < policyFromFile.size(); i++) //iterate through the file listing all policies for the given user
			{
				if (policyFromFile[i].s_username == s_loggedInUser)

				{
					cout << endl << "Policy ID " << i << endl;
					cout << "Car Make " << policyFromFile[i].s_carMake << endl;
					cout << "Car Model " << policyFromFile[i].s_carModel << endl;
					cout << "Car Year " << policyFromFile[i].s_carYear << endl;
					cout << "Insured Value " << policyFromFile[i].s_insuredValue << endl;
				}
			}
			return;
		}
		else 
		{
			cout << "No policies found." << endl;
			return;
		}
	}	
}



//readClaimFromFile function to read data from the claimDetails.csv
vector <Claim> readClaimFromFile() {

	fstream claimDetails("claimDetails.csv", ios::in);
	vector<Claim> tempClaim;

	Claim c;
	string line;
	while (getline(claimDetails, line)) {

		istringstream linestream(line);//to split the row into columns/properties
		string s_item;

		//until the appearance of comma, everything is stored in item
		getline(linestream, s_item, ',');
		c.s_username = s_item;

		getline(linestream, s_item, ',');
		c.s_policyID = s_item;

		getline(linestream, s_item, ',');
		c.s_claimType = s_item;

		getline(linestream, s_item, ',');
		c.s_claimStatus = s_item;

		tempClaim.push_back(c);
	}
	claimDetails.close();
	return(tempClaim);
}

//view Claims
void viewClaims() {
	int i_menuSelection = 0;

	bool b_claimMenu = true;

	showClaimDetails(s_loggedInUser);

	displayClaimMenu();

	while (b_claimMenu) {

		if (cin >> i_menuSelection)
		{
			switch (i_menuSelection)
			{
			case 1:
				b_claimMenu = true;
				createClaim(s_loggedInUser);
				writeClaimToFile(claim);
				displayClaimMenu();
				return;
			case 2:
				cout << "Going back to the previous menu" << endl;
				b_claimMenu = false;
				return;
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
}

//take user input to create a new claim
Claim createClaim(string s_loggedInUser) {
	cout << "Creating a new Claim." << endl;

	claim.s_username = s_loggedInUser;

	showPolicyDetails(s_loggedInUser);

	cout << "Which Policy ID would you like to make a claim for? ";
	cin >> claim.s_policyID;
	cout << "What is the claim for? (eg, stolen, fire, car accident)";
	cin >> claim.s_claimType;

	claim.s_claimStatus = "Submitted";

	cout << "Your claim has been submitted." << endl;

	return(claim);
}

// writeClaimToFile function to store claim details
void writeClaimToFile(Claim claim) {

	fstream claimDetails("claimDetails.csv", ios::app);
	claimDetails << claim.s_username << "," << claim.s_policyID << "," << claim.s_claimType << "," << claim.s_claimStatus << endl;
	claimDetails.close();
}

//show all claims for a given user name
void showClaimDetails(string s_loggedInUser)
{
	claimFromFile = readClaimFromFile();

	for (int i = 0; i < claimFromFile.size(); i++)
	{

		if (s_loggedInUser == "Admin")
		{
			cout << "Below is the list of all existing claims" << endl;
			for (int i = 0; i < claimFromFile.size(); i++) //iterate through the file listing all claims for all users
			{
				cout << endl << "User " << claimFromFile[i].s_username << endl;
				cout << endl << "Policy ID " << claimFromFile[i].s_policyID << endl;
				cout << "Car Make " << claimFromFile[i].s_claimType << endl;
				cout << "Car Model " << claimFromFile[i].s_claimStatus << endl;

			}
			return;
		}
		else if (claimFromFile[i].s_username == s_loggedInUser)
		{
			cout << "User " << s_loggedInUser << " has these claims:" << endl;
			for (int i = 0; i < claimFromFile.size(); i++) //iterate through the file listing all claims for the given user
			{
				if (claimFromFile[i].s_username == s_loggedInUser)

				{
					cout << endl << "Policy ID " << claimFromFile[i].s_policyID << endl;
					cout << "Car Make " << claimFromFile[i].s_claimType << endl;
					cout << "Car Model " << claimFromFile[i].s_claimStatus << endl;
				}
			}
			return;
		}
		else
		{
			cout << "No claims found." << endl;
			return;
		}
	}
}