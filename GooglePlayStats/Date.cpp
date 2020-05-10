#include "Date.h"
#include <sstream>
Date::Date(int D, int M, int Y)
{
	day = D;
	month = M;
	year = Y;
}

Date::Date() {

}

string Date::to_string()
{

	stringstream ss;
	ss << day << "/" << month << "/" << year;

	return ss.str();
}
