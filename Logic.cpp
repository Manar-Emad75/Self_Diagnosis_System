#include "Logic.h"
#include <chrono>
#include <ctime>
unordered_map<string, Doctor>theDoctors;
unordered_map<string, Patient>thePatients;
unordered_map<int, Disease>theDiseases;
set<string>theSymptoms;
user theUser = unknown;
Doctor* doc = NULL;
Patient* pat = NULL;
int disease_ID = 0;

//============================== Person ===============================\\

Person::Person()
{
	fullName = "";
}

Person::~Person()
{
}

void Person::Register()
{
	string choice, fullname;
	cout << "Are you \n 1-Doctor \n 2-Patient \n -> ";
	getline(cin, choice);
	cout << "Enter your fullname -> ";
	getline(cin, fullname);

	if (choice == "1") {
		Doctor newDoc;
		newDoc.fullName = fullname;
		cout << "Enter your username -> ";
		getline(cin, newDoc.account.username);
		if (theDoctors.find(newDoc.account.username) == theDoctors.end())
		{
			cout << "Enter your password -> ";
			getline(cin, newDoc.account.password);
			theDoctors[newDoc.account.username] = newDoc;
			doc = &theDoctors[newDoc.account.username];
			cout << GREEN << "Your account has been created successfully\n" << RESET;
			doc->doc_menu();
		}
		else {
			cout << "This username is taken\n";
		}
	}
	else if (choice == "2") {
		Patient newPat;
		newPat.fullName = fullname;
		cout << "Enter your username -> ";
		getline(cin, newPat.account.username);
		if (thePatients.find(newPat.account.username) == thePatients.end())
		{
			cout << "Enter your password -> ";
			getline(cin, newPat.account.password);
			cout << "Enter your age -> ";
			cin >> newPat.age;
			cout << "Enter your gender -> ";
			cin >> newPat.gender;
			cin.ignore();
			thePatients[newPat.account.username] = newPat;
			pat = &thePatients[newPat.account.username];
			cout << GREEN << "Your account has been created successfully\n" << RESET;
			pat->pat_menu();
		}
		else {
			cout << "This username is taken\n";
		}
	}
	else {
		cout << RED << "\aInvalid choice\n";
	}
}

void Person::log_in()
{
	string choice;
	cout << YELLOW << "Are you \n 1-Doctor \n 2-Patient \n -> " << RESET;
	getline(cin, choice);
	string user_name, pass;
	if (choice == "1")
	{
		cout << CYAN << "Enter your username -> ";
		getline(cin, user_name);
		auto it = theDoctors.find(user_name);
		if (it != theDoctors.end())
		{
			cout << CYAN << "Enter your password -> ";
			getline(cin, pass);
			if (it->second.account.password == pass)
			{
				cout << GREEN << "You loged in successfully\n" << RESET;
				doc = &it->second;
				theUser = doctor;
				doc->doc_menu();
			}
			else
				cout << RED << "Password is wrong!\n" << RESET;
		}
		else
			cout << RED << "Username is wrong!\n" << RESET;
	}
	else if (choice == "2") {
		cout << CYAN << "Enter your username -> ";
		getline(cin, user_name);
		auto it = thePatients.find(user_name);
		if (it != thePatients.end())
		{
			cout << CYAN << "Enter your password -> ";
			getline(cin, pass);
			if (it->second.account.password == pass)
			{
				cout << GREEN << "You loged in successfully\n" << RESET;
				pat = &it->second;
				theUser = patient;
				pat->pat_menu();
			}
			else
				cout << RED << "\aPassword is wrong!\n" << RESET;
		}
		else
			cout << RED << "\aUsername is wrong!\n" << RESET;
	}
	else {
		cout << RED << "\aInvalid choice\n";
	}
}

void Person::log_out()
{
	cout << GREEN << "You loged out successfully\n" << RESET;
}

void Person::delete_account()
{
	string ans;
	cout << RED << "Are you sure you want to delete your account? (y)\n--> " << RESET;
	cin >> ans;
	cin.ignore();
	if (ans != "y")return;
	if (theUser == doctor) {
		theDoctors.erase(doc->account.username);
	}
	else if (theUser == doctor) {
		thePatients.erase(pat->account.username);
	}
	cout << GREEN << "Your accont has been deleted\n" << RESET;
}

//============================== Doctor ===============================\\

Doctor::Doctor()
{
	speciality = "";
}

Doctor::~Doctor()
{
}

void Doctor::add_disease()
{
	Disease dis;
	cout << CYAN << "Enter title for disease -> " << RESET;
	getline(cin, dis.title);
	cout << CYAN << "Enter General info for disease -> " << RESET;
	getline(cin, dis.general_info);
	doc->diseases_Added.insert(++disease_ID);
	dis.id = disease_ID;
	theDiseases[disease_ID] = dis;
	cout << GREEN << "The disease added successfully\n" << RESET;
}

void Doctor::remove_disease()
{
	if (doc->diseases_Added.size() > 0)
	{
		string ans;
		int cnt = 0;
		for (auto it = doc->diseases_Added.begin(); it != doc->diseases_Added.end(); it++)
		{
			cout << ++cnt << '-' << ORANGE << theDiseases[*it].title << endl;
		}
		cout << CYAN << "Enter number of disease which you want to remove\n-> ";
		getline(cin, ans);
		auto it = doc->diseases_Added.begin();
		advance(it, stoi(ans) - 1);
		int id = *it;
		theDiseases.erase(id);
		doc->diseases_Added.erase(it);
		cout << GREEN << "Disease is removed successfully\n" << RESET;
	}
	else
		cout << RED << "NO disease has been added\n" << RESET;
}

void Doctor::add_symptom()
{
	if (doc->diseases_Added.size() > 0)
	{
		string ans, symp;
		int cnt = 0;
		for (auto it = doc->diseases_Added.begin(); it != doc->diseases_Added.end(); it++)
		{
			cout << ++cnt << '-' << ORANGE << theDiseases[*it].title << endl;
		}
		cout << CYAN << "Enter number of disease which you want to add symptom\n-> ";
		getline(cin, ans);
		auto it = doc->diseases_Added.begin();
		advance(it, stoi(ans) - 1);
		int id = *it;
		cout << CYAN << "Enter symptom which you want to add -> ";
		getline(cin, symp);
		theDiseases[id].symptoms.insert(symp);
		theSymptoms.insert(symp);
		cout << GREEN << "Your symptom has been added successfully\n" << RESET;
	}
	else
		cout << RED << "NO disease has been added\n" << RESET;
}

void Doctor::remove_symptom()
{
	if (doc->diseases_Added.size() > 0)
	{
		string ans1, ans2;
		int cnt1 = 0, cnt2 = 0;
		for (auto it = doc->diseases_Added.begin(); it != doc->diseases_Added.end(); it++)
		{
			cout << ++cnt1 << '-' << ORANGE << theDiseases[*it].title << endl;
		}
		cout << CYAN << "Enter number of disease which you want to remove symptom\n-> ";
		getline(cin, ans1);
		auto it = doc->diseases_Added.begin();
		advance(it, stoi(ans1) - 1);
		int id = *it;
		if (theDiseases[id].symptoms.size() == 0) {
			cout << RED << "This disease doesn't has any symptoms yet\n" << RESET;
			return;
		}
		for (auto it = theDiseases[id].symptoms.begin(); it != theDiseases[id].symptoms.end(); it++)
		{
			cout << ++cnt2 << '-' << ORANGE << *it << endl;
		}
		cout << CYAN << "Enter number of symptom which you want to remove";
		getline(cin, ans2);
		auto itt = theDiseases[id].symptoms.begin();
		advance(itt, stoi(ans2) - 1);
		theDiseases[id].symptoms.erase(*itt);
		//theSymptoms
		cout << GREEN << "Your symptom has been removed successfully\n" << RESET;
	}
	else
		cout << RED << "NO disease has been added\n" << RESET;
}

void Doctor::display_diseases()
{
	if (theDiseases.size() == 0) {
		cout << RED << "\aThere isn't any diseases\n" << RESET;
		return;
	}

	cout << YELLOW << "The diseases are:\n";
	int ctr = 0;
	for (auto& dis : theDiseases)
	{
		cout << ++ctr << "- " << ORANGE << dis.second.title;
		cout << "\n\tGeneral Info: " << ORANGE << dis.second.general_info;
		cout << "\n\tThe Symptoms: ";
		for (const string& symp : dis.second.symptoms) {
			cout << ORANGE << symp << " ";
		}
		cout << "\n\tPatients number: " << ORANGE << dis.second.patients.size() << endl << RESET;
	}
}

void Doctor::view_disease_patients()
{
	if (doc->diseases_Added.size() == 0) {
		cout << RED << "You didn't add any disease yet\n";
		return;
	}
	cout << "Choose the disease number:\n";
	int ctr = 0, ans;
	for (auto dis : doc->diseases_Added) {
		cout << ++ctr << "-" << theDiseases[dis].title << endl;
	}
	cout << "--> ";
	cin >> ans;
	cin.ignore();
	if (ans == 0 || ans > ctr) {
		cout << RED << "\aInvalid choice.. please try again\n";
		return;
	}
	auto it = doc->diseases_Added.begin();
	advance(it, ans - 1);
	if (theDiseases[*it].patients.size() == 0) {
		cout << "This disease doesn't has any patients yet\n";
		return;
	}
	cout << theDiseases[*it].title << " patients are: ";
	for (const string& patient : theDiseases[*it].patients) {
		cout << patient << " ";
	}
	cout << endl;
}

void Doctor::doc_menu()
{
	string ans;
	while (true)
	{
		cout << "\n1-Add Disease\n2-Remove Disease\n3-Add Symptom\n4-Remove Symptom\n5-Display all Diseases\n6-View Disease Patients\n7-Log Out\n8-Delete Account\n--> ";
		getline(cin, ans);

		if (ans == "1")
		{
			this->add_disease();
		}
		else if (ans == "2")
		{
			this->remove_disease();
		}
		else if (ans == "3")
		{
			this->add_symptom();
		}
		else if (ans == "4")
		{
			this->remove_symptom();
		}
		else if (ans == "5")
		{
			this->display_diseases();
		}
		else if (ans == "6")
		{
			this->view_disease_patients();
		}
		else if (ans == "7")
		{
			this->log_out();
			break;
		}
		else if (ans == "8")
		{
			this->delete_account();
			break;
		}
		else {
			cout << "\aInvalid choice.. please try again";
		}
	}
}

//============================== Patient ===============================\\

Patient::Patient()
{
	age = -1;
	gender = 'n';
}

Patient::~Patient()
{
}

string calculateTime()
{
	auto currentTime = std::chrono::system_clock::now();
	std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
	char currentTimeStr[11];
	std::tm currentTimeStruct;
	localtime_s(&currentTimeStruct, &currentTimeT);
	std::strftime(currentTimeStr, sizeof(currentTimeStr), "%d-%m-%Y", &currentTimeStruct);
	return currentTimeStr;
}

void Patient::diagnosis()
{
	vector<string>symptoms;
	string choice;
	for (const string& symp : theSymptoms)
	{
		cout << symp << endl;
		cout << "Enter (y) if you have this diseasne or (n) if not or (0) to stop -> ";
		getline(cin, choice);
		if (choice == "y")
		{
			symptoms.push_back(symp);
		}
		else if (choice == "n")
		{
			continue;
		}
		else if (choice == "0")
		{
			break;
		}
		else
			cout << RED << "Invalide choice..try agine\n" << RESET;
	}

	bool found = true;
	for (auto& dis : theDiseases)
	{
		found = true;
		for (const string& symp : symptoms)
		{
			if (dis.second.symptoms.find(symp) == dis.second.symptoms.end()) {
				found = false;
				break;
			}
		}
		if (found) {
			cout << MAGENTA << "You are suffering from " << dis.second.title << endl;
			pat->diseases_history.push_back({ dis.second.title, calculateTime() });
			dis.second.patients.insert(pat->account.username);
			break;
		}
	}
	if (found == false) {
		cout << RED << "No valid disease was found\n";
	}
}

void Patient::display_disease_symptoms()
{
	if (theDiseases.size() == 0) {
		cout << RED << "There is no diseases\n";
		return;
	}
	cout << "Choose the disease number:\n";
	int ctr = 0, ans;
	for (auto dis : theDiseases) {
		cout << ++ctr << "-" << dis.second.title << endl;
	}
	cout << "--> ";
	cin >> ans;
	cin.ignore();
	if (ans == 0 || ans > ctr) {
		cout << RED << "\aInvalid choice.. please try again\n";
		return;
	}
	auto it = theDiseases.begin();
	advance(it, ans - 1);
	if (it->second.symptoms.size() == 0) {
		cout << "This disease doesn't has any symptoms yet\n";
		return;
	}
	cout << it->second.title << " symptoms are: ";
	for (const string& symp : it->second.symptoms) {
		cout << symp << " ";
	}
	cout << endl;
}

void Patient::view_diagnosis_history()
{
	if (pat->diseases_history.size() == 0) {
		cout << RED << "Your don't have diagnosis history\n";
	}
	for (auto i : pat->diseases_history) {
		cout << "\n\t" << i.first << " " << i.second;
	}
}

void Patient::clear_diagnosis_history()
{
	cout << "Are you sure you want to clear the diagnosis history? (y) \n--> ";
	string ans;
	getline(cin, ans);
	if (ans == "y") {
		pat->diseases_history.clear();
		cout << "The diagnosis history has been cleared\n";
	}
}

void Patient::pat_menu()
{
	string ans;
	while (true)
	{
		cout << "\n1-Diagnosis\n2-Display Diseases Symptoms\n3-View Diagnosis History\n4-Clear Diagnosis History\n5-Log Out\n6-Delete Account\n--> ";
		getline(cin, ans);

		if (ans == "1")
		{
			this->diagnosis();
		}
		else if (ans == "2")
		{
			this->display_disease_symptoms();
		}
		else if (ans == "3")
		{
			this->view_diagnosis_history();
		}
		else if (ans == "4")
		{
			this->clear_diagnosis_history();
		}
		else if (ans == "5")
		{
			this->log_out();
			break;
		}
		else if (ans == "6")
		{
			this->delete_account();
			break;
		}
		else {
			cout << "\aInvalid choice.. please try again";
		}
	}
}

//============================== Disease ===============================\\

Disease::Disease()
{
	id = -1;
}

Disease::~Disease()
{
}

