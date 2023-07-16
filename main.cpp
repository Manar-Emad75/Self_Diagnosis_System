#include"Logic.h"
#include<chrono>
#include <ctime>
#include<map>
#include <Windows.h>
#include<fstream>
#include <sstream>

void Start();
void End();

int main()
{
	Start();
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
	if (line != "#")
		theSymptoms = split(line, ';');
	readfile >> line; //<<<<<<<<<<<<<<<DISEASES>>>>>>>>>>>>>>>
	readfile >> sz;  // the number of diseases
	for (int i = 0; i < sz; i++)
	{
		Disease dis;
		readfile >> line; //--------------------------------------
		readfile >> dis.id >> dis.title;
		getline(readfile >> ws, dis.general_info);
		readfile >> line; // the disease symptoms
		if (line != "#")
			dis.symptoms = split(line, ';');
		readfile >> line; // the disease patients
		if (line != "#")
			dis.patients = split(line, ';');
		theDiseases[dis.id] = dis;
	}
	readfile >> line; //<<<<<<<<<<<<<<<DOCTORS>>>>>>>>>>>>>>>
	readfile >> sz; //the number of doctors
	for (int i = 0; i < sz; i++)
	{
		Doctor doctor;
		readfile >> line; //--------------------------------------
		getline(readfile >> ws, doctor.fullName);
		readfile >> doctor.account.username >> doctor.account.password;
		readfile >> line;
		if (line != "#")
			doctor.diseases_Added = split(line);
		theDoctors[doctor.account.username] = doctor;
	}
	readfile >> line; //<<<<<<<<<<<<<<<PATEINTS>>>>>>>>>>>>>>>
	readfile >> sz;  // the number of pateints
	for (int i = 0; i < sz; i++)
	{
		Patient patient;
		set<string>tempSet;
		readfile >> line; //--------------------------------------
		getline(readfile >> ws, patient.fullName);
		readfile >> patient.gender >> patient.age >> patient.account.username >> patient.account.password;
		readfile >> line; //title1,date1;title2,date2;title3,date3;
		if (line != "#")
		{
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
		}
		thePatients.insert({ patient.account.username, patient });
		patient.diseases_history.clear();
	}
	readfile >> line; //<<<<<<<<<<<<<<END>>>>>>>>>>>>>>
	readfile.close();
}

void End()
{
	fstream writefile("Data.txt", std::iostream::out);
	if (writefile.is_open() == false)return;


	writefile << "<<<<<<<<<<<<<<<<<<ID>>>>>>>>>>>>>>>>>>\n";
	writefile << disease_ID << '\n';

	writefile << "<<<<<<<<<<<<<<<SYMPTOMS>>>>>>>>>>>>>>>\n";
	if (theSymptoms.size() == 0)
		writefile << '#';
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
		//symp1;symp2;symp3;symp4
		if (dis.second.symptoms.size() == 0)
			writefile << '#';
		for (string symp : dis.second.symptoms) {
			writefile << symp << ';';
		}
		writefile << '\n';
		//pat1;pat2;pat3;pat4
		if (dis.second.patients.size() == 0)
			writefile << '#';
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
		if (doc.second.diseases_Added.size() == 0)
			writefile << '#';
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
		if (pat.second.diseases_history.size() == 0)
			writefile << '#';
		for (auto dis_his : pat.second.diseases_history)
		{
			writefile << dis_his.first << ',' << dis_his.second << ';';
		}
	}
	writefile << "\n<<<<<<<<<<<<<<<<<END>>>>>>>>>>>>>>>>>>";
	writefile.close();
}