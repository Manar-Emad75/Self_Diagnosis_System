#pragma once
#include<iostream>
#include<set>
#include<vector>
#include<unordered_map>
#include<string>
using namespace std;

enum user {
	doctor,
	patient,
	unknown
};

class Account
{
public:
	string username;
	string password;
};

class Person
{
public:
	string fullName;
	Account account;

public:
	Person();
	~Person();
	void Register();
	void log_in();
	void log_out();
	void delete_account();
};

class Doctor : public Person
{
public:
	string speciality;
	set<int>diseases_Added;

public:
	Doctor();
	~Doctor();
	void add_disease();
	void remove_disease();
	void add_symptom();
	void remove_symptom();
	void display_diseases();
	void view_disease_patients();
	void doc_menu();
};

class Patient : public Person
{
public:
	int age;
	char gender;
	vector<pair<int, string>>diseases_history;

public:
	Patient();
	~Patient();
	void diagnosis();
	void display_disease_symptoms();
	void view_diagnosis_history();
	void clear_diagnosis_history();
	void pat_menu();
};

class Disease
{
public:
	int id;
	string title;
	string general_info;
	set<string>symptoms;
	set<string>patients;

public:
	Disease();
	~Disease();
};

extern unordered_map<string, Doctor>theDoctors;
extern unordered_map<string, Patient>thePatients;
extern unordered_map<int, Disease>theDiseases;
extern user theUser;