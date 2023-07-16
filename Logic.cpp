#include "Logic.h"

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
			cout << GREEN << "You loged in successfully\n" << RESET;
			doc->doc_menu();
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
			thePatients[newPat.account.username] = newPat;
			pat = &thePatients[newPat.account.username];
			cout << GREEN << "You loged in successfully\n" << RESET;
			pat->pat_menu();
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
	theDiseases[disease_ID] = dis;
}

void Doctor::remove_disease()
{
	if (doc->diseases_Added.size() > 0)
	{
		string ans;
		int cnt=0;
		for (auto it = doc->diseases_Added.begin(); it != doc->diseases_Added.end(); it++)
		{
			cout <<++cnt<<'-'<< ORANGE << theDiseases[*it].title << endl;
		}
		cout << CYAN << "Enter number of disease which you want to remove\n-> ";
		getline(cin, ans);
	    auto it = doc->diseases_Added.begin();
		advance(it,stoi(ans) - 1);
		int id = *it;
		theDiseases.erase(id);
		doc->diseases_Added.erase(it);
		cout << GREEN << "Disease is removed successfully\n"<<RESET;
	}
}   

void Doctor::add_symptom()
{
}

void Doctor::remove_symptom()
{
}

void Doctor::display_diseases()
{
	if(theDiseases.size() == 0){
		cout <<RED<< "\aThere isn't any diseases\n"<<RESET;
		return;
	}

	cout <<YELLOW<< "The diseases are:\n";
	int ctr = 0;
	for(auto& dis:theDiseases)
	{
		cout << ++ctr << "- "<<ORANGE << dis.second.title;
		cout << "\n\tGeneral Info: " <<ORANGE<< dis.second.general_info;
		cout << "\n\tThe Symptoms: ";
		for(const string& symp: dis.second.symptoms){
			cout <<ORANGE<< symp << " ";
		}
		cout << "\n\tPatients number: " <<ORANGE<< dis.second.patients.size() << endl<<RESET;
	}
}

void Doctor::view_disease_patients()
{
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
	//this->pat_menu();
}

Patient::~Patient()
{
}

void Patient::diagnosis()
{
}

void Patient::display_disease_symptoms()
{
}

void Patient::view_diagnosis_history()
{
}

void Patient::clear_diagnosis_history()
{
	cout << "Are you sure you want to clear the diagnosis history? (y) \n--> ";
	string ans;
	getline(cin, ans);
	if(ans == "y"){
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

