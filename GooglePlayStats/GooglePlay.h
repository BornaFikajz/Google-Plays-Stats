#pragma once
#include <string>
#include <vector>
#include "Date.h"


using namespace std;






class GooglePlay
{

private:

	string AppName;
	string Category;
	double Rating;
	int Reviews;
	double Size;
	int Installs;
	bool Paid;
	double Price;
	string ContentRating;
	vector<string> Genres;			//ZAMIJENI ZA VEKTOR
	Date LastUpdated;		//ZAMIJENI ZA KLASU DATE
	string CurrVersion;
	string AndVersion;

public:

	GooglePlay(string name, string cat, double rat, int rev, double siz, int ins, bool pay, double pric, string CR, vector<string> gen, Date dat, string ver, string andVer); //UNAPRIJEDI ZANR I DATUM
	GooglePlay();

	string get_AppName();
	void set_AppName(string name);
	string get_Category();
	void set_Category(string cat);
	double get_Rating();
	void set_Rating(double rat);
	int get_Reviews();
	void set_Reviews(int rev);
	double get_Size();
	void set_Size(double siz);
	int get_Installs();
	void set_Installs(int ins);
	bool get_Paid();
	void set_Paid(bool pay);

	double get_Price();
	void set_Price(double pric);

	string get_ContentRating();
	void set_ContentRating(string CR);

	//ZAMJENA ZA VEKTOR ZANROVA
	vector<string> get_Genres();
	void set_Genres(vector<string> gen);

	//ZAMJENA ZA KLASU  DATE
	Date get_LastUpdated();
	void set_LastUpdated(Date dat);

	string get_CurrVersion();
	void set_CurrVersion(string ver);
	string get_AndVersion();
	void set_AndVersion(string andVer);

	void incReviews(int rev);
	void decReviews(int rev);


	string to_string();



};

