#ifndef LNSCORE_H
#define LNSCORE_H

//This file contains core data structures and maybe functions that the application requires
//Each struct is defined and populated with the date it requires

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

struct sInsuranceClaim
{

};

struct sPolicy
{

};










#endif LNSCORE_H
