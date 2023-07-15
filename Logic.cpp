#include "Logic.h"

unordered_map<string, Doctor>theDoctors;
unordered_map<string, Patient>thePatients;
unordered_map<int, Disease>theDiseases;
set<string>theSymptoms;
user theUser = unknown;
Doctor* doc;
Patient* pat;
int ID;

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
}

void Person::log_in()
{
	theUser = patient;
}

void Person::log_out()
{
}

void Person::delete_account()
{
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
}

void Doctor::remove_disease()
{
}

void Doctor::add_symptom()
{
}

void Doctor::remove_symptom()
{
}

void Doctor::display_diseases()
{
}

void Doctor::view_disease_patients()
{
}

void Doctor::doc_menu()
{
	string ans;
	while (true)
	{
		cout << "\n1-Add Disease\n2-Remove Disease\n3-Add Symptom\n4-Remove Symptom\n5-Display all Diseases\n6-View Disease Patients\n7-Log Out\n--> ";
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
}

void Patient::pat_menu()
{
	string ans;
	while (true)
	{
		cout << "\n1-Diagnosis\n2-Display Diseases Symptoms\n3-View Diagnosis History\n4-Clear Diagnosis History\n5-Log Out\n--> ";
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

