#include <iostream>
#include <string>
#include <fstream>

#define string std::string
#define cout std::cout
#define cin std::cin

struct DateOfBirth {
	int day;
	int month;
	int year;
};

struct Patient {
	string first_name;
	string last_name;
	string patronymic;
	struct DateOfBirth date_of_birth;
	unsigned int phone_number[11];
	string registration_area;
	double policy_number;
	string blood_type;
	Patient* next_patient;
	Patient* rear_patient;
};


class PatientList {
private:
	Patient* first_patient;
	Patient* last_patient;
public:
	Patient* add(string name, string sername, string patr, struct DateOfBirth date, unsigned int phone[11], string reg, double policy, string blood) {
		Patient* p = new Patient;
		if (p) {
			p->first_name = name;
			p->last_name = sername;
			p->patronymic = patr;
			p->date_of_birth = date;
			p->phone_number[11] = phone[11];
			p->registration_area = reg;
			p->policy_number = policy;
			p->blood_type = blood;
			p->next_patient = NULL;
			p->rear_patient = NULL;

			if (first_patient == NULL) {
				first_patient = last_patient = p;
			}
			else {
				last_patient = last_patient->next_patient = p;
			}
		}
		return p;
	}
};


struct Reffer {
	string reffer;
	PatientList* patient_list;
	Reffer* next_reffer;
	Reffer* rear_reffer;
};

struct RefferList {
	Reffer* first_reffer;
	Reffer* last_reffer;
};

struct Adress{
	string adress;
	RefferList* reffer_list;
	Adress* next_adress;
	Adress* rear_adress;
};

struct AdressList {
	Adress* first_adress;
	Adress* last_adress;
};
