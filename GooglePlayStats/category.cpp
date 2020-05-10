#include "category.h"
#include <sstream>

category::category()
{
	price = 0.0;
	
}

category::category(string naziv)
{

	name = naziv;
	price = 0.0;

}



string category::getName()
{
	return name;
}

void category::setName(string kat)
{
	name = kat;
}

double category::getPrice()
{
	return price;
}

void category::setPrice(double pric)
{
	price += pric;
}

string category::to_string()
{

	stringstream ss;
	ss << "Kategorija: " << name << " Ukupna cijena: " << price<<endl;

	return ss.str();
}

void category::clearPrice()
{

	price = 0.0;

}
