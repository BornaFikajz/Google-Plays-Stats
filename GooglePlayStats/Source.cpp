#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include "GooglePlay.h"
#include "category.h"

using namespace std;

template<typename T>
T convert(string& s) {

	stringstream c(s);
	T t;
	c >> t;
	return t;

}




void drawGP() {


	cout << R"(
                 _____                        __         ____  ___
	       / ____ / ___   ____    ____  _/ /__      / __ \/  /___ ___  __
	      / / __ / __  \ / __ \  / __  `/ / _ \    / /_/ /  / __ `/ / / /
	     / /_/  / /_/   / /_/ / /_/ /  /    __/   / ____/  / /_/ / /_/ /
	     \____ / \____ / \____ / \__, /_ /\___/  /_/   /_ / \__, _ /  /
	                            /____/                          /____ / 
	
)" << '\n';
	

}


void ChooseType() {

	int tip;
	cout << "S kojim aplikacijama zelite raditi?\n[ 0 ] Besplatnim\n[ 1 ] Aplikacija koje se naplacuju\nOdabir: ";
	cin >> tip;
	cin.ignore();

	if (tip != 0 && tip != 1)
	{

		cout << "Unijeli ste pogresan broj, molim probajte ponovo!\n";

	}

	else
	{


		ofstream out("type.bin", ios::out || ios::binary);
		if (out.is_open())
		{
			out.write((char*)(&tip), sizeof(int));
		}
		cout << "Postavke spremljene!\n";
		out.close();
	}

}


bool isPaid() {

	ifstream in("type.bin", ios::in || ios::binary);
	if (!in)
	{
		cout << "Greska pri citanju bin datoteke!\n";
		return 0;
	}

	int temp;
	if (in.is_open())
	{
		in.seekg(0, ios::end);
		int size = (int)in.tellg();
		in.seekg(0, ios::beg);
		while (in.tellg() < size)
		{
			in.read((char*)(&temp), sizeof(temp));
		}

	}
	in.close();

	if (temp == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


int getMonth(string& s) {

	if (s == "January")
	{
		return 1;
	}

	else if (s == "February")
	{
		return 2;
	}

	else if (s == "March")
	{
		return 3;
	}

	else if (s == "April")
	{
		return 4;
	}

	else if (s == "May")
	{
		return 5;
	}

	else if (s == "June")
	{
		return 6;
	}

	else if (s == "July")
	{
		return 7;
	}

	else if (s == "August")
	{
		return 8;
	}

	else if (s == "September")
	{
		return 9;
	}

	else if (s == "October")
	{
		return 10;
	}

	else if (s == "November")
	{
		return 11;
	}
	else
	{
		return 12;
	}

}


Date FormDate(string s) {

	int d;
	int m;
	int y;
	s.erase(remove(s.begin(), s.end(), '\"'), s.end());

	stringstream ss(s);
	string temp;
	string MonthDay;
	getline(ss, MonthDay, ',');

	size_t space = MonthDay.find_first_of("123456789");
	string day = MonthDay.substr(space, 2);
	string month = MonthDay.substr(0, space - 1);

	d = convert<int>(day);

	m = getMonth(month);

	getline(ss, temp);
	y = convert<int>(temp);



	Date datum(d, m, y);


	return datum;
}


int getInstalls(string& s) {

	s.erase(remove(s.begin(), s.end(), '\"'), s.end());
	
	s.erase(remove(s.begin(), s.end(), ','), s.end());

	int ins = convert<int>(s);

	return ins;

}


double getPrice(string& s) {

	s.erase(remove(s.begin(), s.end(), '$'), s.end());

	double pric = convert<double>(s);

	return pric;

}


vector<string> getGenres(string& s) {

	vector<string> Zanrovi;
	stringstream ss(s);
	string temp;
	getline(ss, temp,';');
	Zanrovi.push_back(temp);

	getline(ss, temp, ';');
	if (!temp.empty() && temp !=Zanrovi[0] )
	{
		Zanrovi.push_back(temp);
	}



	return Zanrovi;
}


void ReadCSV(vector<GooglePlay>& apps) {


	bool type = isPaid();



	ifstream in("SPA_PROJ_007_GOOGLE_PLAY_data.csv");
	if (!in)
	{
		cout << "Greska pri citanju datoteke\n";
		return;
	}

	string line;
	getline(in, line);

	while (getline(in,line))
	{

		GooglePlay aplikacija;

		stringstream ss(line);
		string temp;

		getline(ss, temp,',');
		aplikacija.set_AppName(temp);

		getline(ss, temp,',');
		aplikacija.set_Category(temp);

		getline(ss, temp, ',');
		aplikacija.set_Rating(convert<double>(temp));

		getline(ss, temp, ',');
		aplikacija.set_Reviews(convert<int>(temp));

		getline(ss, temp, ',');
		aplikacija.set_Size(convert<double>(temp));

		
		getline(ss, temp, '+');

		aplikacija.set_Installs(getInstalls(temp));
	
		getline(ss, temp, ',');

		getline(ss, temp, ',');
		if (temp =="Free")
		{
			aplikacija.set_Paid(0);
		}
		else if(temp=="Paid")
		{
			aplikacija.set_Paid(1);
		}

		if (aplikacija.get_Paid()!=type)
		{
			continue;
		}
		
		getline(ss, temp, ',');

		if (type)
		{

			aplikacija.set_Price(getPrice(temp));
		}

		else
		{

		aplikacija.set_Price(0.0);
		}
		
		getline(ss, temp, ',');
		aplikacija.set_ContentRating(temp);
		//////////////////////////////////////////////////////////////////

		getline(ss, temp, ',');


		aplikacija.set_Genres(getGenres(temp));

		//////////////////////////////////////////////////////////////////
		getline(ss, temp, '\"');

		getline(ss, temp, '\"');
		aplikacija.set_LastUpdated(FormDate(temp));


		getline(ss, temp, ',');
		getline(ss, temp, ',');
		aplikacija.set_CurrVersion(temp);

		getline(ss, temp);
		aplikacija.set_AndVersion(temp);


		apps.push_back(aplikacija);

		if (apps.size()==8459)
		{
			break;
		}

	}

	in.close();
	cout<<"Ucitavanje uspjesno zavrseno!"<<endl;
}


void findMax(vector<category>& v) {

	category max = v[0];
	for (unsigned i = 0; i < v.size(); i++)
	{

		if (v[i].getPrice()>max.getPrice())
		{
			max = v[i];
		}


	}

	cout << max.to_string();

	for (unsigned i = 0; i < v.size(); i++)
	{
		if (max.getName()==v[i].getName())
		{
			v[i].clearPrice();
		}

	}

}


void TopCat(vector<GooglePlay>& apps) {


		vector<category> v;

		for (int i = 0; i < apps.size(); i++)
		{

			if (i==0)
			{
				category v1(apps[i].get_Category());
				v.push_back(v1);
			}

			for (int j = 0; j < v.size(); j++)
			{

				

				if (apps[i].get_Category()==v[j].getName())
				{
					v[j].setPrice(apps[i].get_Price());
				}

				if (apps[i].get_Category() != v[j].getName() && j==v.size()-1)
				{

					v.emplace_back(category(apps[i].get_Category()));
					v[j+1].setPrice(apps[i].get_Price());
				}

			}

		}


		for (unsigned i = 0; i < 5; i++)
		{

			cout << i + 1 << ". ";
			findMax(v);

		}
	


	
}


void PrintRegular() {

	ifstream in("SPA_PROJ_007_GOOGLE_PLAY_data.csv");
	ofstream out("output.txt");
	if (!in || !out)
	{
		cout << "Greska pri otvaranju datoteke\n";
		return;
	}

	queue<string> red;

	string line;

	while (getline(in,line))
	{

		red.push(line);


	}
	in.close();

	while (!red.empty())
	{
		out << red.front() << endl;
		red.pop();
	}

	out.close();

	cout << "Prepisivanje uspjesno zavrseno, rezultate pogledajte u output.txt" << endl;




}


void PrintReverse() {

	ifstream in("SPA_PROJ_007_GOOGLE_PLAY_data.csv");
	ofstream out("output.txt");
	if (!in || !out)
	{
		cout << "Greska pri otvaranju datoteke\n";
		return;
	}
	stack<string> stog;

	string line;

	while (getline(in, line))
	{

		stog.push(line);


	}
	in.close();

	while (!stog.empty())
	{
		out << stog.top() << endl;
		stog.pop();
	}

	out.close();

	cout << "Prepisivanje uspjesno zavrseno, rezultate pogledajte u output.txt" << endl;



}


bool fewIns(GooglePlay& g) {

	if (g.get_Installs()<1000000)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CatObrada(vector <GooglePlay>& apps) {


	cout << "Unesite naziv zeljene kategorije: ";
	string target;
	getline(cin, target);

	list<GooglePlay> l;

	for (unsigned i = 0; i < apps.size(); i++)
	{

		if (apps[i].get_Category()==target)
		{
			l.push_back(apps[i]);
		}

	}

	l.remove_if(fewIns);
	l.reverse();

	for (auto it = l.begin();it != l.end();++it)
	{
		cout << it->to_string()<<endl;
	}


}


int countSamoglasnici(string& s) {

	int counter = 0;

	for (int i = 0; i < s.length(); i++)
	{

		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i]=='A' || s[i]=='E' || s[i]=='I' || s[i]=='O' || s[i]=='U')
		{
			counter++;
		}


	}

	return counter;
}


void Samoglasnici(vector<GooglePlay>& v) {

	stack<GooglePlay> stog;

	for (auto it = v.rbegin(); it != v.rend(); ++it) {

		string s = it->get_AppName();

		if (countSamoglasnici(s)>3)
		{
			stog.push(*it);
		}
		else if (countSamoglasnici(s)<=3)
		{
			if (stog.empty())
			{
				cout << "Stog je prazan!" << endl;
			}

			else
			{
				cout << stog.top().to_string() << endl;
				stog.pop();
			}
		}

	}

	cout << "Ispis preostalih: " << endl;
	if (stog.empty())
	{
		cout << "Na stogu nema nicega!" << endl;
	}
	else
	{
		while (!stog.empty())
		{
			cout << stog.top().to_string() << endl;
			stog.pop();
		}
	}


	
}


void PrintStats(vector<GooglePlay>& apps) {

	int smallSize = 0;
	int mediumSize = 0;
	int largeSize = 0;
	int ultraSize = 0;
	
	for (int i = 0; i < apps.size(); i++)
	{

		if (apps[i].get_Size() > 200.0  )
		{
			ultraSize++;
		}


		else if (apps[i].get_Size() >= 100.0 && apps[i].get_Size() <= 199)
		{
			largeSize++;
		}


		else if (apps[i].get_Size() >= 50.0 && apps[i].get_Size() <= 99.0)
		{
			mediumSize++;
		}


		else if (apps[i].get_Size()<=49.0 )
		{
			smallSize++;
		}
	}

	cout << "0-49 Mb: " << smallSize << endl;
	cout << "50-99 Mb: " << mediumSize << endl;
	cout << "100-199 Mb: " << largeSize << endl;
	cout << "200+ Mb: " << ultraSize << endl;

}


void SimTrans(vector<GooglePlay>& apps) {

	stack<int> rollback;
	bool nastavi = 1;
	cout << "TRANSACTION TERMINAL" << endl;
	bool trans = 0;
	do
	{
		cout << "Command:";
		string unos;
		getline(cin, unos);

		

		 if (trans)
		 {

			  if (unos=="ROLLBACK")
			 {

				 while (!rollback.empty())
				 {
					 int decrement = rollback.top();
					 for (int i = 0; i < apps.size(); i++)
					 {
						 apps[i].decReviews(decrement);
					 }
					 rollback.pop();

				 }
				 cout << "Rollback complete\n";
				 continue;
			 }

			 else if (unos=="COMMIT")
			 {
				 nastavi = 0;
				 cout << "Changes saved, printing results:" << endl;
				 for (int i = 0; i < apps.size(); i++)
				 {
					 cout<<apps[i].to_string()<<endl;
				 }
				 continue;
			 }
			 size_t location = unos.find_first_of("123456789");
			 string difference = unos.substr(location, 12);
			 int promjena = convert<int>(difference);

			  if (unos=="UPDATE GOOGLE_PLAY SET Reviews += " + difference)
			 {
				 for (int i = 0; i < apps.size(); i++)
				 {
					 apps[i].incReviews(promjena);

				 }
				 cout << "Reviews increased" << endl;
				 rollback.push(promjena);
			 }

		 }


		 if (unos=="BEGIN TRAN")
		{
			cout << "Transaction initiated\n";
			trans = 1;

		}

		 else if (!trans)
		 {

			 cout << "Unknown command, try again\n";
		 }




	} while (nastavi);







}


int main() {

	bool running = 1;
	vector<GooglePlay> apps;

	do
	{
		system("CLS");
		drawGP();
		int choice;

		cout << "\n \nDobrodosli u izbornik usluga! Zelite li :\n" << "[ 1 ] Odabrati tip aplikacija \n"<<"[ 2 ] Ucitati podatke iz tablice\n" 
			<< "[ 3 ] Ispisati top kategorije\n"<<"[ 4 ] Kopirati datoteku\n"<<"[ 5 ] Obradu po kategorijama\n"
			<<"[ 6 ] Prebrojavati samoglasnike\n"<<"[ 7 ] Prikazati statistiku velicina\n"<<"[ 8 ] Simulirati transakciju\n"<<"[ 0 ] Zatvoriti program\n";

		cout << "Unesite brojku Zeljene opcije: ";
		cin >> choice;
		cin.ignore();

		switch (choice)
		{

		default:
			cout << "Unijeli ste pogresnu brojku, molim pokusajte ponovo!\n";
			system("pause");
			break;

		case 0:

			running = 0;

			break;

		case 1:
			system("CLS");
			ChooseType();
			system("pause");
			break;

		case 3: 

			system("cls");

			if (isPaid())
			{
				TopCat(apps);
			}
			else
			{
				cout << "Sortiranje po cijeni nema smisla s besplatnim aplikacijama" << endl;
			}


			system("pause");

			break;


		case 4:

			system("cls");

			cout << "Zelite li datoteku kopirati: 1) Standardno 2) Obrnuto\nUnos:";
			int unos;
			cin >> unos;
			cin.ignore();


			switch (unos)
			{
			default:

				cout << "Unijeli ste pogresan broj!" << endl;

				break;

			case 1:

				PrintRegular();

				break;


			case 2:

				PrintReverse();

				break;

			}

			system("pause");

			break;

		case 5:

			system("CLS");

			CatObrada(apps);

			system("pause");

			break;


		case 6:

			system("CLS");

			Samoglasnici(apps);

			system("pause");
			break;


		case 7:

			system("CLS");

			PrintStats(apps);

			system("pause");

			break;


		case 8:

			system("CLS");

			SimTrans(apps);

			system("pause");


			break;

		
		case 2:

			auto begin = std::chrono::high_resolution_clock::now();
			
			ReadCSV(apps);

			auto end = std::chrono::high_resolution_clock::now();

			cout << "Trajanje ucitavanja datoteke : " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " sekundi"<<endl;

			
			system("pause");

			break;

			}

	} while (running);

	


	return 0;
 }