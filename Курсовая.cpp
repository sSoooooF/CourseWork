#include <iostream>		// стандартный ввод-вывод
#include <string>		// работа со string
#include <fstream>		// файловый ввод-вывод	
#include <sstream>		// потоковая работа со string

#define string std::string
#define cout std::cout
#define cin std::cin
#define ifstream std::ifstream
#define ofstream std::ofstream
#define endl std::endl
#define setfill std::setfill
#define setw std::setw
#define setprecision std::setprecision


// дата рождения пациента
struct DateOfBirth {
	int day;
	int month;
	int year;
};


// структура данных пациента
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


// бинарное дерево поиска, каждый элемент которого является объектом структуры PatientNode
class PatientTree {
public:
	struct PatientNode* root;		// вершина дерева

	// функция удаления дерева пациентов
	void deletePatientTree(PatientNode* root) {
		if (root->left) deletePatientTree(root->left);
		if (root->right) deletePatientTree(root->right);
		delete root;
	}

	// удаление одного из пациентов из дерева
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

	// вставка пациента в дерево
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
	
	// функция симметричной печати дерева
	void inorderPrint(struct PatientNode* root);

	// функция нахождения минимального узла
	PatientNode* FindMinNode(PatientNode* root) {
		PatientNode* minNode = new PatientNode;
		while (root->left) {
			root = root->left;
		}
		return root;
	}
};


void PatientTree::inorderPrint(struct PatientNode* root) {
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

// функция для нумерации узлов дерева в порядке возрастания
PatientNode* inorderNumber(struct PatientNode* root, int& number) {
	PatientNode* new_root = root;
	if (new_root) {
		inorderNumber(new_root->left, number);
		new_root->number = number++;
		inorderNumber(new_root->right, number);
	}
	return new_root;
}

// функция поиска в дереве
bool SearchInTree(PatientNode* root,string last_name, string first_name, string patronymic, string filename) {
	bool flag = false;
	if (!root) return flag;
	SearchInTree(root->left, last_name, first_name, patronymic, filename);
	if (root->last_name == last_name && root->first_name == first_name && root->patronymic == patronymic) {
		ofstream fout(filename, std::ios::app);
		fout << "\n\t" << root->last_name << "\t\t" << root->first_name << "\t\t" << root->patronymic << "\t"
			<< root->date_of_birth.day << "." << root->date_of_birth.month << "."
			<< root->date_of_birth.year << "\t+" << root->phone_number
			<< "\t" << root->policy_number << "\t" << root->blood_type;
		fout.close();
		flag = true;
		return flag;
	}
	SearchInTree(root->right, last_name, first_name, patronymic, filename);
}

// структура адреса больницы
struct Adress{
	string adress;
	class PatientTree* PatientTree = NULL;
	struct Adress* next_adress{};
};

// односвязный список адресов больниц
class AdressList {
public:
	struct Adress* firstAdress_;
	struct Adress* lastAdress_;
	AdressList() {
		firstAdress_ = NULL;
		lastAdress_ = NULL;
	}

	// добавление адреса в конец списка
	void AddAdress(string adress);

	// удаление адреса под номером index
	void DelAdress(int index);

	// удаление всех адресов из списка
	void DelAllAdresses();

	// печать списка адресов
	void PrintAdressList();

	// найти длину списка
	int knowLength();

	// найти пациента в списке
	void SearchPatient();
};

int AdressList::knowLength() {
	int counter = 0;	// счетчик длины
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
	int length = knowLength();
	if (index > length || index < 1) return;

	if (firstAdress_ == NULL) return;	// пустой список
	else if (firstAdress_ == lastAdress_ && index == 1) {	// список из 1 элемента
		firstAdress_ = NULL;
		lastAdress_ = NULL;
	}
	else if (index == 1) {			// удаление первого элемента
		firstAdress_ = now->next_adress;
		lastAdress_->next_adress = firstAdress_;
	}
	else if (index == length) {	// удаления второго элемента
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
	else {							// остальные случаи
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

void AdressList::SearchPatient() {
	string first_name, last_name, patronymic;
	Adress* current = new Adress;
	cout << "\nEnter first name: ";
	cin >> first_name;		// имя пациента
	cout << "\nEnter last name: ";
	cin >> last_name;		// фамилия пациента
	cout << "\nEnter patronymic: ";
	cin >> patronymic;		// отчество пациента
	cout << "\nWrite the name of the file in which to write the data:\n> ";
	string filename;		// файл для вывода результата
	ofstream fout;
	cin >> filename;
	fout.open(filename, std::ios::app);

	while (!fout.is_open()) {		// файл открыт?
		cout << "\nError: file does not exist! Try another time:\n> ";
		cin >> filename;
		fout.close();
		fout.open(filename, std::ios::app);
	}

	bool flag;
	// печать в файл данных о искомом пациенте
	fout << "\nPatient to search: " << last_name << " " << first_name << " " << patronymic;
	fout.close();
	current = firstAdress_;

	// очистка файла
	fout.open("input.txt", std::ios::out | std::ios::in);	
	fout.close();

	do {		// обход списка с поиском в нем нужного пациента
		fout.open(filename, std::ios::app);
		fout << "\n\n\t\tAdress: " << current->adress;
		fout.close();
		if (current->PatientTree) {
			//поиск пациента в дереве
			flag = SearchInTree(current->PatientTree->root, last_name, first_name, patronymic, filename);
			if (!flag) {
				fout.open(filename, std::ios::app);
				fout << "\n\tThere are no matching patients at this address!\n";
				fout.close();
			}
		}
		current = current->next_adress;
	} while (current != firstAdress_);
}

// реализация меню
void menuReaization() {
	setlocale(LC_ALL, "rus");
	AdressList* adress_list = new AdressList;	// инициализвация списка адресов
	int variant;
	int variant2;
	string adress;			// адрес ольницы
	string first_name;		// имя пациента
	string last_name;		// фамилия пациента
	string patronymic;		// отчество пациента
	struct DateOfBirth date_of_birth {};	// дата рождения пациента
	string phone_number{};		// номер телефона пациента
	string policy_number{};		// номер полиса поциента
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
			cout << "Options:\n1. Add adress into adress list manually\n2. Add adress into adress list from file\n3. Show patients by adress\n4. Find patients\n5. Delete adress by index\n6. Delete all adressess\n7. Exit the program\nYour choise:\n>  ";
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
						cout << "\nOptions:\n1. Add new patient manually\n2. Add new patients from file\n3. Delete patient by index\n4. Delete all patients\n5. Return to adress list\nYour choise:\n> ";
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
							cout << "Enter patient index to delete\n> ";
							cin >> index;	
							patient_tree->root = patient_tree->DeletePatientNode(patient_tree->root, index);
							break;
						case 4:
							patient_tree->deletePatientTree(patient_tree->root);
							patient_tree->root = NULL;
							break;
						case 5:
							current->PatientTree = patient_tree;
							break;
						default:
							cout << "\nIncorrect input. Try another time.\n";
							system("pause");
							break;
						}
					}
				} while (variant2 != 3 && !patient_tree->root || patient_tree->root && variant2 != 5);
				break;
			case 4:
				adress_list->SearchPatient();
				break;
			case 5:
				cout << "\nEnter the index of the address to delete\n> ";
				cin >> index;
				adress_list->DelAdress(index);
				break;
			case 6:
				adress_list->DelAllAdresses();
				break;
			case 7:
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
	system("color F0");
	menuReaization();
}