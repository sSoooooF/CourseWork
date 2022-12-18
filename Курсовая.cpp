#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <sstream>
#include <map>

#define string std::string
#define cout std::cout
#define cin std::cin
#define ifstream std::ifstream
#define ofstream std::ofstream
#define endl std::endl

struct DateOfBirth {
	int day;
	int month;
	int year;
};

struct PatientNode {
	string first_name;
	string last_name;
	string patronymic;
	struct DateOfBirth date_of_birth;
	string phone_number;
	string policy_number;
	string blood_type;
	int number;
	struct PatientNode* left;
	struct PatientNode* right;
};

class PatientTree {
public:
	struct PatientNode* root;
	void deletePatientList(PatientNode* root) {
		if (root->left) deletePatientList(root->left);
		if (root->right) deletePatientList(root->right);
		delete root;
	}

	PatientNode* DeletePatientNode(PatientNode* root, int key) {
		if (root == NULL) return root;
		if (root->number < key) {
			root->right = DeletePatientNode(root->right, key);
		}
		else if (root->number > key) {
			root->left = DeletePatientNode(root->left, key);
		}
		else if (root->left != NULL && NULL != root->right) {
			root->number = FindMinNode(root->right)->number;
			root->right = DeletePatientNode(root->right, root->number);
		}
		else {
			if (root->left != NULL)
				root = root->left;
			else if (root->right != NULL)
				root =  root->right;
			else root =  NULL;
		}
		return root;
	}

	PatientTree() {
		root = NULL;
	}

	void insert(string first_name, string last_name, string patronymic, struct DateOfBirth date_of_birth, string phone_number, string policy_number, string blood_type) {
		root = doInsert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type, root);
	}

private:
	PatientNode* doInsert(string first_name, string last_name, string patronymic, struct DateOfBirth date_of_birth, string phone_number, string policy_number, string blood_type, PatientNode* tree) {
		if (tree == NULL) {
			tree = new PatientNode;
			tree->first_name = first_name;
			tree->last_name = last_name;
			tree->patronymic = patronymic;
			tree->date_of_birth = date_of_birth;
			tree->phone_number = phone_number;
			tree->policy_number = policy_number;
			tree->blood_type = blood_type;
			tree->left = NULL;
			tree->right = NULL;
		}
		if (last_name < tree->last_name || (last_name == tree->last_name && first_name < tree->first_name) || (last_name == tree->last_name && first_name == tree->first_name && patronymic < tree->patronymic)) {
			if (tree->left) doInsert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type, tree->left);
			else {
				tree->left = new PatientNode;
				tree->left->first_name = first_name;
				tree->left->last_name = last_name;
				tree->left->patronymic = patronymic;
				tree->left->date_of_birth = date_of_birth;
				tree->left->phone_number = phone_number;
				tree->left->policy_number = policy_number;
				tree->left->blood_type = blood_type;
				tree->left->left = NULL;
				tree->left->right = NULL;
			}
		}
		if (last_name > tree->last_name || (last_name == tree->last_name && first_name > tree->first_name) || (last_name == tree->last_name && first_name == tree->first_name && patronymic > tree->patronymic)) {
			if (tree->right) doInsert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type, tree->right);
			else {
				tree->right = new PatientNode;
				tree->right->first_name = first_name;
				tree->right->last_name = last_name;
				tree->right->patronymic = patronymic;
				tree->right->date_of_birth = date_of_birth;
				tree->right->phone_number = phone_number;
				tree->right->policy_number = policy_number;
				tree->right->blood_type = blood_type;
				tree->right->left = NULL;
				tree->right->right = NULL;
			}
		}
		return tree;
	}
public:
	void inorderPrint(struct PatientNode* root) {
		if (!root) {
			return;
		}
		inorderPrint(root->left);
		cout << root->number << "\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type << endl;
		inorderPrint(root->right);
	}

	PatientNode* FindMinNode(PatientNode* root) {
		PatientNode* minNode = new PatientNode;
		while (root->left) {
			root = root->left;
		}
		return root;
	}
};

void SearchByLastName(PatientNode* root, string search_by, string data_to_search, string filename) {
	ofstream fout(filename, std::ios::ate);
	if (!root) return;
	SearchByLastName(root->left, search_by, data_to_search, filename);
	if (root->last_name == data_to_search) {
		fout << "\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type << endl;
	}
	SearchByLastName(root->right, search_by, data_to_search, filename);
}

void SearchByFirstName(PatientNode* root, string search_by, string data_to_search, string filename) {
	if (!root) return;
	SearchByFirstName(root->left, search_by, data_to_search, filename);
	SearchByFirstName(root->right, search_by, data_to_search, filename);
	ofstream fout;
	fout.open(filename, std::ios::ate);
	if (root->first_name == data_to_search) {
		fout << "\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type << endl;
	}
	fout.close();
}

void SearchByBloodType(PatientNode* root, string search_by, string data_to_search, string filename) {
	ofstream fout(filename, std::ios::ate);
	if (!root) return;
	SearchByBloodType(root->left, search_by, data_to_search, filename);
	if (root->blood_type == data_to_search) {
		fout << "\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type << endl;
	}
	SearchByBloodType(root->right, search_by, data_to_search, filename);
}

void SearchByPolicyNumber(PatientNode* root, string search_by, string data_to_search, string filename) {
	ofstream fout(filename, std::ios::ate);
	if (!root) return;
	SearchByPolicyNumber(root->left, search_by, data_to_search, filename);
	if (root->policy_number == data_to_search) {
		fout << "\n\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type;
	}
	SearchByPolicyNumber(root->right, search_by, data_to_search, filename);
}

void SearchInTree(PatientNode* root,string search_by, string data_to_search, string filename) {
	if (search_by == "last name") {
		SearchByLastName(root, search_by, data_to_search, filename);
	}
	else if (search_by == "first name") {
		SearchByFirstName(root, search_by, data_to_search, filename);
	}
	else if (search_by == "blood type") {
		SearchByBloodType(root, search_by, data_to_search, filename);
	}
	else if (search_by == "policy number") {
		SearchByPolicyNumber(root, search_by, data_to_search, filename);
	}
	else {
		cout << "\n\tIncorrect input!\n";
		system("pause");
		return;
	}
}

void InterfaceSearchInTree(PatientNode* root) {
	cout << "\nSearch by ___(first name, last name, policy number, blood type):> ";
	cin.ignore(1, '\n');
	string search_by, data_to_search;
	getline(cin, search_by);
	cout << "\nWrite " << search_by << " to search:\n> ";
	cin >> data_to_search;
	cout << "\nWrite the name of the file in which to write the data:\n> ";
	string filename;
	ofstream fout;
	cin >> filename;
	fout.open(filename, std::ios::ate);
	while (!fout.is_open()) {
		cout << "\nError: file does not exist! Try another time:\n> ";
		cin >> filename;
		fout.close();
		fout.open(filename);
	}
	fout << "Patients with " << search_by << " " << data_to_search << ":\n";
	SearchInTree(root, search_by, data_to_search, filename);
}

PatientNode* inorderNumber(struct PatientNode* root, int& number) {
	PatientNode* new_root = root;
	if (new_root) {
		inorderNumber(new_root->left, number);
		new_root->number = number++;
		inorderNumber(new_root->right, number);
	}
	return new_root;
}

// List of adresses
struct Adress{
	string adress;
	class PatientTree* PatientTree = NULL;
	struct Adress* next_adress{};
};

class AdressList {
public:
	struct Adress* firstAdress_;
	struct Adress* lastAdress_;
	AdressList() {
		firstAdress_ = NULL;
		lastAdress_ = NULL;
	}
	void AddAdress(string adress);
	void DelAdress(int index);
	void DelAllAdresses();
	void PrintAdressList();
	int KnowLength();
};

int AdressList::KnowLength() {
	int counter = 0;
	Adress* a = new Adress;
	a = firstAdress_;
	do {
		counter++;
		a = a->next_adress;
	} while (a != firstAdress_);
	return counter;
}

void AdressList::AddAdress(string adress) {
	Adress* a = new Adress;
	a->PatientTree = new PatientTree;
	a->PatientTree->root = NULL;
	a->adress = adress;
	if (firstAdress_==NULL) {
		firstAdress_ = lastAdress_ = a;
		lastAdress_->next_adress = firstAdress_;
		return;
	}
	lastAdress_->next_adress = a;
	a->next_adress = firstAdress_;
	lastAdress_ = a;
}

void AdressList::DelAdress(int index) {
	Adress* now = new Adress;
	now = firstAdress_;
	int length = KnowLength();
	if (index > length || index < 1) return;

	if (firstAdress_ == NULL) return;	// hollow list
	else if (firstAdress_ == lastAdress_ && index == 1) {	// one element list
		firstAdress_ = NULL;
		lastAdress_ = NULL;
	}
	else if (index == 1) {			// delete first element
		firstAdress_ = now->next_adress;
		lastAdress_->next_adress = firstAdress_;
	}
	else if (index == length) {		// delete last element
		if (firstAdress_ == lastAdress_) {
			delete firstAdress_;
			return;
		}
		while (now->next_adress != lastAdress_) {
			now = now->next_adress;
		}
		now->next_adress = firstAdress_;
		delete lastAdress_;
		lastAdress_ = now;
	}
	else {							// delete any other element
		for (int i = 2; i < index; i++) {
			now = now->next_adress;
		}
		now->next_adress = now->next_adress->next_adress;
	}
}

void AdressList::DelAllAdresses() {
	while (lastAdress_ != firstAdress_) {
		firstAdress_ = firstAdress_->next_adress;
		delete lastAdress_->next_adress;
		lastAdress_->next_adress = firstAdress_;
	}
	delete firstAdress_;
	firstAdress_ = NULL;
}

void AdressList::PrintAdressList() {
	Adress* a = new Adress;
	a = firstAdress_;
	int counter = 0;
	cout << "Index" << "\tAdress\n";
	do {
		cout <<++counter<< "\t" << a->adress << endl;
		a = a->next_adress;
	} while (a != firstAdress_);

}

void menuReaization() {
	setlocale(LC_ALL, "rus");
	AdressList* adress_list = new AdressList;
	int variant;
	int variant2;
	string adress;
	string first_name;
	string last_name;
	string patronymic;
	struct DateOfBirth date_of_birth {};
	string phone_number{};
	string policy_number{};
	string blood_type;
	ifstream fin;
	string filename;
	string search_by;
	string data_to_search;
	int index;
	PatientTree* patient_tree = new PatientTree;
	Adress* current = new Adress;
	do {
		if (!adress_list->firstAdress_) {
			system("cls");
			cout << "\tAdress list is not created!\nOptions:\n1. Create adress list\n2. Read adress list from file\n3. Exit the program\nYour choise:\n> ";
			cin >> variant;
			switch (variant) {
			case 1:
				cout << "Enter adress\n> ";
				cin.ignore(1, '\n');
				getline(cin, adress);
				adress_list->AddAdress(adress);
				break;
			case 2:
				cout << "Enter filename\n> ";
				cin >> filename;
				fin.open(filename);
				if (!fin.is_open()) {
					cout << "\nError: file does not exist!";
					system("pause");
					break;
				}
				while (!fin.eof()) {
					getline(fin, adress);
					adress_list->AddAdress(adress);
				}
				fin.close();
				break;
			case 3:
				break;
			default:
				cout << "\nIncorrect input. Try another time.\n";
				system("pause");
				break;
			}
		}
		else {
			system("cls");
			cout << "\tAdress list is created!\n";
			
			adress_list->PrintAdressList();
			cout << "Options:\n1. Add adress into adress list manually\n2. Add adress into adress list from file\n3. Show patients by adress\n4. Delete adress by index\n5. Delete all adressess\n6. Exit the program\nYour choise:\n>  ";
			cin >> variant;
			switch (variant) {
			case 1:
				cout << "Enter adress\n> ";
				cin.ignore(1, '\n');
				getline(cin, adress);
				adress_list->AddAdress(adress);
				break;
			case 2:
				cout << "Enter filename\n> ";
				cin >> filename;
				fin.open(filename);
				if (!fin.is_open()) {
					cout << "\nError: file does not exist!";
					system("pause");
					break;
				}
				while (!fin.eof()) {
					getline(fin, adress);
					adress_list->AddAdress(adress);
				}
				fin.close();
				break;
			case 3:
				cout << "Enter the index of adress to show patient list\n> ";
				cin >> index;
				current = new Adress;
				current = adress_list->firstAdress_;
				for (int i = 1; i < index; i++) {
					current = current->next_adress;
				}
				patient_tree = current->PatientTree;
				do {
					if (!patient_tree->root) {
						system("cls");
						cout <<"\tCurrent adress: " << current->adress << endl;
						cout << "\tPatient list is not created!\nOptions:\n1. Create patient list\n2. Read patient list from file\n3. Return to adress list\nYour choise:\n> ";
						cin >> variant2;
						switch (variant2) {
						case 1:
							cout << "Enter patient date: first name, last name, patronymic, date of birth, phone number, policy number, blood type\n> ";
							cin >> first_name >> last_name >> patronymic >> date_of_birth.day >> date_of_birth.month >> date_of_birth.year >> phone_number >> policy_number >> blood_type;
							patient_tree->insert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type);
							break;
						case 2:
							cout << "Enter filename\n> ";
							cin >> filename;
							fin.open(filename);
							if (!fin.is_open()) {
								cout << "\nError: file does not exist!";
								system("pause");
								break;
							}
							while (!fin.eof()) {
								fin >> first_name >> last_name >> patronymic >> date_of_birth.day >> date_of_birth.month >> date_of_birth.year >> phone_number >> policy_number >> blood_type;
								patient_tree->insert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type);
							}
							fin.close();
							break;
						case 3:
							break;
						default:
							cout << "\nIncorrect input. Try another time.\n";
							system("pause");
							break;
						}
					}
					else {
						system("cls");
						cout << "\tCurrent adress: " << current->adress << endl;
						cout << "\tPatient list is created!\n";
						int number = 1;
						patient_tree->root = inorderNumber(patient_tree->root, number);
						cout << "Index\tLast name\tFirst name\tPatronymic\tDate of birth\tPhone number\tPolicy number\t\tBlood type\n";
						patient_tree->inorderPrint(patient_tree->root);
						cout << "\nOptions:\n1. Add new patient manually\n2. Add new patients from file\n3. Search patients and write them to file\n4. Delete patient by index\n5. Delete all patients\n6. Return to adress list\nYour choise:\n> ";
						cin >> variant2;
						switch (variant2) {
						case 1:
							cout << "Enter patient date: first name, last name, patronymic, day, month, year of birth, phone number, policy number, blood type\n> ";
							cin >> first_name >> last_name >> patronymic >> date_of_birth.day >> date_of_birth.month >> date_of_birth.year >> phone_number >> policy_number >> blood_type;
							patient_tree->insert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type);
							break;
						case 2:
							cout << "Enter filename\n> ";
							cin >> filename;
							fin.open(filename);
							if (!fin.is_open()) {
								cout << "\nError: file does not exist!";
								system("pause");
								break;
							}
							while (!fin.eof()) {
								fin >> first_name >> last_name >> patronymic >> date_of_birth.day >> date_of_birth.month >> date_of_birth.year >> phone_number >> policy_number >> blood_type;
								patient_tree->insert(first_name, last_name, patronymic, date_of_birth, phone_number, policy_number, blood_type);
							}
							fin.close();
							break;
						case 3:
							InterfaceSearchInTree(patient_tree->root);
							break;
						case 4:
							cout << "Enter patient index to delete\n> ";
							cin >> index;	
							patient_tree->root = patient_tree->DeletePatientNode(patient_tree->root, index);
							break;
						case 5:
							patient_tree->deletePatientList(patient_tree->root);
							patient_tree->root = NULL;
							break;
						case 6:
							current->PatientTree = patient_tree;
							break;
						default:
							cout << "\nIncorrect input. Try another time.\n";
							system("pause");
							break;
						}
					}
				} while (variant2 != 3 && !patient_tree->root || patient_tree->root && variant2 != 6);
				break;
			case 4:
				cout << "\nEnter the index of the address to delete\n> ";
				cin >> index;
				adress_list->DelAdress(index);
				break;
			case 5:
				adress_list->DelAllAdresses();
				break;
			case 6:
				exit(0);
			default:
				cout << "\nIncorrect input. Try another time.\n";
				system("pause");
				break;
			}
		}
	}while (variant != 3 && !adress_list->firstAdress_ || variant!= 6 && adress_list->firstAdress_);
}


int main() {
	
	menuReaization();
}