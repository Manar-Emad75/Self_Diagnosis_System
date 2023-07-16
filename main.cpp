#include"Logic.h"
#include<chrono>
#include <ctime>
#include<map>
#include <Windows.h>
#include<fstream>
#include <sstream>

void Start();
void End();
void persontry()
{
	Doctor d1;
	d1.account.username = "nemo";
	d1.account.password = "nemo123";
	d1.fullName = "namanemo";
	d1.diseases_Added.insert(1);
	d1.diseases_Added.insert(2);
	theDoctors["nemo"] = d1;

	Doctor d2;
	d2.account.username = "uc";
	d2.account.password = "uc123";
	d2.fullName = "gus";
	d1.diseases_Added.insert(4);
	d1.diseases_Added.insert(3);
	theDoctors["uc"] = d2;

	Doctor d3;
	d3.account.username = "dory";
	d3.account.password = "dory123";
	d3.fullName = "doha";
	d1.diseases_Added.insert(5);
	d1.diseases_Added.insert(6);
	d1.diseases_Added.insert(7);
	theDoctors["dory"] = d3;

	//===========================================
	Disease dis1;
	dis1.id = 1;
	dis1.title = "dis1";
	dis1.general_info = "I am dis1";
	dis1.symptoms.insert("symp1");
	dis1.symptoms.insert("symp2");

	//==========================================

	Patient p1;
	p1.account.username = "marim";
	p1.account.password = "marim123";
	p1.age = 30;
	p1.gender = 'f';
	p1.fullName = "marim nabil";
	thePatients["marim"] = p1;

	Patient p2;
	p2.account.username = "hadeer";
	p2.account.password = "hadeer123";
	p2.age = 30;
	p2.gender = 'f';
	p2.fullName = "hadeer khald";
	thePatients["hadeer"] = p2;
}

void print()
{
	int ctr = 0;
	cout << "here\n";
	for (auto i : thePatients)
	{
		cout << "\nPatient" << ++ctr;
		cout << "\nUsername: " << i.second.account.username;
		cout << "\nPassword: " << i.second.account.password;
		cout << "\nAge: " << i.second.age;
		cout << "\nGender: " << i.second.gender;
		cout << "\nDisease History:\n";
		for (auto j : i.second.diseases_history)
		{
			cout << j.first << " " << j.second << endl;
		}
		cout << "-------------------------------------\n";
	}
}

int main()
{
	//persontry();
	Start();
	print();
	cout << "\n===================================*" << MAGENTA << " Welcome " << RESET << "*===================================\n";
	string ans;
	Person per;
	while (true)
	{
		cout << YELLOW << "\n1-Log in\n2-Register\n3-Exit" << RESET << "\n--> ";
		getline(cin, ans);
		if (ans == "1")
		{
			per.log_in();
		}
		else if (ans == "2")
		{
			per.Register();
		}
		else if (ans == "3")
		{
			break;
		}
		else
		{
			cout << RED << "\aInvalid choice.. please try again\n";
		}
	}
	End();
	return 0;
}

set<string> split(const string& line, char sign)
{
	string temp;
	set<string>tempSet;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != sign)
		{
			temp += line[i];
		}
		else
		{
			tempSet.insert(temp);
			temp = "";
		}
	}
	return tempSet;
}

set<int> split(const string& line)
{
	string temp;
	set<int>tempSet;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ';')
		{
			temp += line[i];
		}
		else
		{
			tempSet.insert(stoi(temp));
			temp = "";
		}
	}
	return tempSet;
}

void Start()
{
	fstream readfile("Data.txt", std::iostream::in);
	if (readfile.is_open() == false) return;

	int sz;
	string line, temp;
	readfile >> line; //<<<<<<<<<<<<<<<<<<ID>>>>>>>>>>>>>>>>>>
	readfile >> disease_ID; //ID
	readfile >> line; //<<<<<<<<<<<<<<<SYMPTOMS>>>>>>>>>>>>>>>
	readfile >> line; //symp1;symp2;symp3;
	theSymptoms = split(line, ';');
	readfile >> line; //<<<<<<<<<<<<<<<DISEASES>>>>>>>>>>>>>>>
	readfile >> sz;  // the number of diseases
	Disease dis;
	for (int i = 0; i < sz; i++)
	{
		readfile >> line; //--------------------------------------
		readfile >> dis.id >> dis.title;
		getline(readfile >> ws,dis.general_info);
		readfile >> line; // the disease symptoms
		dis.symptoms = split(line, ';');
		readfile >> line; // the disease patients
		dis.patients = split(line, ';');
		theDiseases[dis.id] = dis;
	}
	readfile >> line; //<<<<<<<<<<<<<<<DOCTORS>>>>>>>>>>>>>>>
	readfile >> sz; //the number of doctors
	Doctor doctor;
	for (int i = 0; i < sz; i++)
	{
		readfile >> line; //--------------------------------------
		getline(readfile >> ws, doctor.fullName);
		readfile >> doctor.account.username >> doctor.account.password;
		readfile >> line;
		doctor.diseases_Added = split(line);
		theDoctors[doctor.account.username] = doctor;
	}
	readfile >> line; //<<<<<<<<<<<<<<<PATEINTS>>>>>>>>>>>>>>>
	readfile >> sz;  // the number of pateints
	Patient patient;
	set<string>tempSet;
	for (int i = 0; i < sz; i++)
	{
		readfile >> line; //--------------------------------------
		getline(readfile >> ws, patient.fullName);
		readfile >> patient.gender >> patient.age >> patient.account.username >> patient.account.password;
		readfile >> line; //title1,date1;title2,date2;title3,date3;
		tempSet = split(line, ';');
		for (string s : tempSet)  //s = title1,date1
		{
			string title = "", date = "";
			temp = "";
			for (int j = 0; j < s.size(); j++)
			{
				if (s[j] != ',')
				{
					temp += s[j];
				}
				else
				{
					title = temp;
					temp = "";
				}
			}
			date = temp;
			patient.diseases_history.push_back({ title, date });
		}
		thePatients.insert({ patient.account.username, patient });
		patient.diseases_history.clear();
	}
	readfile >> line; //<<<<<<<<<<<<<<I Love Nemo>>>>>>>>>>>>>>
	cout << "End\n";
	readfile.close();
}

void End()
{
	fstream writefile("Data.txt", std::iostream::out);
	if (writefile.is_open() == false)return;


	writefile << "<<<<<<<<<<<<<<<<<<ID>>>>>>>>>>>>>>>>>>\n";
	writefile << disease_ID << '\n';

	writefile << "<<<<<<<<<<<<<<<SYMPTOMS>>>>>>>>>>>>>>>\n";
	for (string symp : theSymptoms)
	{
		writefile << symp << ';';
	}
	writefile << "\n<<<<<<<<<<<<<<<DISEASES>>>>>>>>>>>>>>>\n";
	writefile << theDiseases.size();
	for (auto dis : theDiseases) {
		writefile << "\n--------------------------------------\n";
		writefile << dis.second.id << '\n';
		writefile << dis.second.title << '\n';
		writefile << dis.second.general_info << '\n';
		//symp1;symp2;symp3;symp4;
		for (string symp : dis.second.symptoms) {
			writefile << symp << ';';
		}
		writefile << '\n';
		//pat1;pat2;pat3;pat4
		for (string pat : dis.second.patients) {
			writefile << pat << ';';
		}
	}
	writefile << "\n<<<<<<<<<<<<<<<DOCTORS>>>>>>>>>>>>>>>>\n";
	writefile << theDoctors.size();
	for (auto doc : theDoctors)
	{
		writefile << "\n--------------------------------------\n";
		writefile << doc.second.fullName << "\n";
		writefile << doc.second.account.username << "\n";
		writefile << doc.second.account.password << "\n";
		//id1;id2;id3;id4;id5;id6;id7;
		for (int disId : doc.second.diseases_Added)
		{
			writefile << disId << ';';
		}
	}
	writefile << "\n<<<<<<<<<<<<<<<PATEINTS>>>>>>>>>>>>>>>\n";
	writefile << thePatients.size();
	for (auto pat : thePatients)
	{
		writefile << "\n--------------------------------------\n";
		writefile << pat.second.fullName << "\n";
		writefile << pat.second.gender << "\n";
		writefile << pat.second.age << "\n";
		writefile << pat.second.account.username << "\n";
		writefile << pat.second.account.password << "\n";
		//title1,date1;title2,date2;title3,date3;
		for (auto dis_his : pat.second.diseases_history)
		{
			writefile << dis_his.first << ',' << dis_his.second << ';';
		}
	}
	writefile << "\n<<<<<<<<<<<<<<I Love Nemo>>>>>>>>>>>>>>\n";
	writefile.close();
}