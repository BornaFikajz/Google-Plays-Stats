#pragma once
#include <string>

using namespace std;

class category
{

private :

	string name;
	double price;

public:

	category();

	category(string naziv);

	string getName();
	void setName(string kat);

	double getPrice();
	void setPrice(double pric);

	string to_string();

	void clearPrice();


};

