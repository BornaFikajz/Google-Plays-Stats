#include "GooglePlay.h"
#include <sstream>

GooglePlay::GooglePlay(string name, string cat, double rat, int rev, double siz, int ins, bool pay, double pric, string CR, vector<string> gen, Date dat, string ver, string andVer)
{

	set_AppName(name);
	set_Category(cat);
	set_Rating(rat);
	set_Reviews(rev);
	set_Size(siz);
	set_Installs(ins);
	set_Paid(pay);
	set_Price(pric);
	set_ContentRating(CR);
	set_Genres(gen);
	set_LastUpdated(dat);
	set_CurrVersion(ver);
	set_AndVersion(andVer);


}

GooglePlay::GooglePlay()
{
}

string GooglePlay::get_AppName()
{
	return AppName;
}

void GooglePlay::set_AppName(string name)
{
	AppName = name;
}

string GooglePlay::get_Category()
{
	return Category;
}

void GooglePlay::set_Category(string cat)
{
	Category = cat;
}

double GooglePlay::get_Rating()
{
	return Rating;
}

void GooglePlay::set_Rating(double rat)
{
	Rating = rat;
}

int GooglePlay::get_Reviews()
{
	return Reviews;
}

void GooglePlay::set_Reviews(int rev)
{
	Reviews = rev;
}

double GooglePlay::get_Size()
{
	return Size;
}

void GooglePlay::set_Size(double siz)
{
	Size = siz;
}

int GooglePlay::get_Installs()
{
	return Installs;
}

void GooglePlay::set_Installs(int ins)
{
	Installs = ins;
}

bool GooglePlay::get_Paid()
{
	return Paid;
}

void GooglePlay::set_Paid(bool pay)
{
	Paid = pay;
}

double GooglePlay::get_Price()
{
	return Price;
}

void GooglePlay::set_Price(double pric)
{
	Price = pric;
}

string GooglePlay::get_ContentRating()
{
	return ContentRating;
}

void GooglePlay::set_ContentRating(string CR)
{
	ContentRating = CR;
}

vector<string> GooglePlay::get_Genres()
{
	return Genres;
}

void GooglePlay::set_Genres(vector<string> gen)
{
	Genres = gen;
}

Date GooglePlay::get_LastUpdated()
{
	return LastUpdated;
}

void GooglePlay::set_LastUpdated(Date dat)
{
	LastUpdated = dat;
}

string GooglePlay::get_CurrVersion()
{
	return CurrVersion;
}

void GooglePlay::set_CurrVersion(string ver)
{
	CurrVersion = ver;
}

string GooglePlay::get_AndVersion()
{
	return AndVersion;
}

void GooglePlay::set_AndVersion(string andVer)
{
	AndVersion = andVer;
}

void GooglePlay::incReviews(int rev)
{

	Reviews += rev;
}

void GooglePlay::decReviews(int rev)
{
	Reviews -= rev;
}

string GooglePlay::to_string()
{
	stringstream ss;
	string typ;
	if (Paid)
	{
		typ = "Paid";
	}
	else
	{
		typ = "Free";
	}

	




	ss << "Naziv: " << AppName << " Kategorija: " << Category << " Korisnicka ocjena: " << Rating<<" Broj recenzija: "<<Reviews<< " Tip: " << typ;



	return ss.str();
}
