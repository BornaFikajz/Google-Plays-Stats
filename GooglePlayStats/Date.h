#pragma once
#include <string>
using namespace std;
class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date(int D, int M, int Y);
	Date();
	string to_string();

};

