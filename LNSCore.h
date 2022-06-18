#ifndef LNSCORE_H
#define LNSCORE_H

#include <string>
using namespace std;

//This file contains core data structures and maybe functions that the application requires
//Each struct is defined and populated with the date it requires

struct sDate
{
	int day;
	int month;
	int year;
};

struct sAddress
{
	
	string s_streetName;
	string s_city;
	int i_postCode;
	string s_country;

};
struct sCustomer
{
	string s_customerName;
	int i_age;
	string s_emailAddress;
	sAddress st_customerAddress;
	int i_phoneNumber;


};

struct sCar
{

};

//enumerated type - claim can be either a stolen car or damaged car (which is everything other than stolen) and a default "noclaim"
enum claimtype 
{
	noclaim,
	stolen, 
	damgaged
};

struct sInsuranceClaim
{
	sCar st_car; //the car that was damaged or stolen
	claimtype claim_type; //either stolen or damaged

};

struct sPolicy
{

};










#endif LNSCORE_H
