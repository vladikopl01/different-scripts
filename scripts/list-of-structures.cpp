#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>

using namespace std;

struct addressInfo {
	char city[50];
	char street[50];
	char building[50];
	char flat[10];
};

struct clientList {
	char name[50];
	char surname[50];
	char pantronimic[50];
	char number[50];
	addressInfo addressData;
	clientList *next = NULL;
	clientList *prev = NULL;
};

bool choice();
int menuChoice();

void insertEnd(clientList*&, clientList*&, clientList*&);

void initClient(clientList*);

void outputClient(clientList*);
void outputList(clientList*);

void removeClient(clientList*&, clientList*&, clientList*&);
bool searchClient(clientList*, clientList*&, char*);
void addClient(clientList*&, clientList*&, clientList*);

void nextClient(clientList*&);
void prevClient(clientList*&);

int countClients(clientList*);

void sortClients(clientList*&, clientList*&, clientList*&);
void swapClients(clientList*, clientList*);

void inputBinary(clientList*, clientList*);
void writeClient(ofstream&, clientList*);

void outputBinary(clientList*&, clientList*&, clientList*&);
void readClient(ifstream&, clientList*);

void clearList(clientList*&, clientList*&, clientList*&);

int main() {
	clientList *head = NULL;
	clientList *tail = NULL;
	clientList *current = NULL;

	do {
		system("cls");
		if (current) {
			outputClient(current);
			cout << endl;
		}
		else {
			cout << "List is empty!! First of all, create the list!!" << endl << endl;
		}

		cout << "1. Insert new item to the list" << endl
			<< "2. Editing the current list item" << endl
			<< "3. Removing current element from the list" << endl
			<< "4. Display the list" << endl
			<< "5. Searching the element by name" << endl
			<< "6. Insert new element before/after current item" << endl
			<< "7. Go to the next element" << endl
			<< "8. Go to the previous element" << endl
			<< "9. Counting items in the list " << endl
			<< "10. Sorting the list by the name" << endl
			<< "11. Writing the list into binary file" << endl
			<< "12. Reading the list from binary file" << endl
			<< "13. Exit" << endl;
		cout << "Your choice: ";

		switch (menuChoice()) {
		case 1: {
			//New item to list
			system("cls");
			insertEnd(head, tail, current);
			break;
		}

		case 2: {
			//Edit item of list
			system("cls");
			if (current) {
				initClient(current);
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 3: {
			//Delete item from list
			system("cls");
			if (current) {
				removeClient(head, tail, current);
				cout << "Removing is done!" << endl;
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 4: {
			//Output full list
			system("cls");
			if (head) {
				cout << "Full list:" << endl;
				outputList(head);
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 5: {
			//Search item by name in list
			system("cls");
			if (head) {
				char tempName[50];
				cout << "Enter name to search: ";
				cin.getline(tempName, 50);

				if (searchClient(head, current, tempName)) {
					cout << "Client was found:" << endl;
					outputClient(current);

					cout << "Do you want to change data? (1 - yes, 0 - no): ";
					if (choice()) {
						system("cls");
						initClient(current);
					}
				}
				else {
					cout << "No client with such name!!" << endl << endl;
				}
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 6: {
			//Input item before/after current
			system("cls");
			if (current) {
				addClient(head, tail, current);
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 7: {
			//Go to NEXT item
			if (!head) {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			else if (current == tail) {
				cout << "There is not next client!!" << endl << endl;
			}
			else {
				nextClient(current);
			}
			break;
		}

		case 8: {
			//Go to PREV item
			if (!head) {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			} else if (current == head) {
				cout << "There is not previous client!!" << endl << endl;
			}
			else {
				prevClient(current);
			}
			break;
		}

		case 9: {
			//Count items of list
			system("cls");
			if (head) {
				cout << "You have " << countClients(head)
					<< " clients in your list" << endl;
			}
			else {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			break;
		}

		case 10: {
			//Sorting list by name
			system("cls");
			if (!head) {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			else {
				cout << "Sorting..." << endl;
				sortClients(head, tail, current);
				cout << "Done!" << endl;
			}
			break;
		}

		case 11: {
			//Input binary file
			system("cls");
			if (!head) {
				cout << "List is empty!! First of all, create the list!!" << endl << endl;
			}
			else {
				cout << "Writing your list..." << endl;
				inputBinary(head, tail);
				cout << "Done!" << endl;
			}
			break;
		}

		case 12: {
			//Output binary file
			system("cls");
			cout << "Clear your list..." << endl;
			clearList(head, tail, current);
			cout << "Done! Reading file..." << endl;
			outputBinary(head, tail, current);
			cout << "Done!" << endl;
			break;
		}
		
		case 13: {
			//Exit
			system("pause");
			return 0;
		}
		}

		cout << "Continue? (1-yes, 0-no): ";
	} while (choice());

	system("pause");
	return 0;
}

//Choice (0 or 1)
bool choice() {
	int ch;
	do {
		cin >> ch;
		if (ch != 0 && ch != 1) {
			cout << "Incorrect input. Try again: ";
		}
	} while (ch != 0 && ch != 1);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (ch == 1) {
		return true;
	}
	return false;
}

//Menu choice (1 ... 13)
int menuChoice() {
	int num;
	do {
		cin >> num;
		if (num < 1 || num > 13) {
			cout << "Incorrect input! Try again: ";
		}
	} while (num < 1 || num > 13);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return num;
}

///1. Insert new item to list
void insertEnd(clientList *&head, clientList *&tail, clientList *&cur) {
	clientList *client = new clientList;
	initClient(client);

	if (head == NULL && tail == NULL) {
		head = client;
		tail = client;
		cur = client;
		return;
	}

	tail->next = client;
	client->prev = tail;
	tail = client;
}

///2. Initialization
void initClient(clientList* client) {
	cout << "Input client info:" << endl;
	cout << " Name: ";
	cin.getline(client->name, 50);//Для доступа к членам структуры с помощью указателя на структуру следует использовать оператор "стрелка"
	cout << " Surname: ";
	cin.getline(client->surname, 50);//через этот адрес к полю сернейм
	cout << " Pantronimic: ";
	cin.getline(client->pantronimic, 50);
	cout << " Phone number: ";
	cin.getline(client->number, 50);
	cout << " City: ";
	cin.getline(client->addressData.city, 50);
	cout << " Street: ";
	cin.getline(client->addressData.street, 50);
	cout << " Building: ";
	cin.getline(client->addressData.building, 50);
	cout << " Flat: ";
	cin.getline(client->addressData.flat, 10);
}

//Output data about client
void outputClient(clientList *client) {
	cout << "Client: "
		<< client->surname << " "
		<< client->name << " "
		<< client->pantronimic << endl;
	cout << " Phone number: "
		<< client->number << endl;
	cout << " Address: " 
		<< client->addressData.city << ", "
		<< client->addressData.street << ", "
		<< client->addressData.building << ", "
		<< client->addressData.flat << endl;
}

///4. Output full list
void outputList(clientList *head) {
	clientList *temp = head;

	do {
		outputClient(temp);
		cout << endl;
		temp = temp->next;
	} while (temp);
}

///3. Delete current element of the list
void removeClient(clientList *&head, clientList *&tail, clientList *&current) {
	clientList *temp = current;
	if (current == head) {
		head = current->next;
		head->prev = NULL;
		delete temp;
		current = head;
		return;
	}

	if (current == tail) {
		tail = current->prev;
		tail->next = NULL;
		delete temp;
		current = tail;
		return;
	}

	clientList *t1 = current->prev;
	clientList *t2 = current->next;
	t1->next = t2;
	t2->prev = t1;
	delete temp;
	current = t2;
}

///5. Search client by name (Return true if found)
bool searchClient(clientList *head, clientList *&current, char *str) {
	bool ind = true;
	clientList *temp = head;

	while (strcmp(str, temp->name) && temp != NULL) {
		ind = false;
		temp = temp->next;
		if (!strcmp(str, temp->name)) {
			ind = true;
		}
	}

	if (ind) {
		current = temp;
		return true;
	}

	return false;
}

///6. Adding client before/after current
void addClient(clientList *&head, clientList *&tail, clientList *current) {
	clientList *t1;
	clientList *newClient = new clientList;
	initClient(newClient);

	cout << "How to insert? (1 - before, 0 - after): ";
	if (choice()) {
		if (head == current) {
			newClient->next = head;
			head->prev = newClient;
			head = newClient;
			return;
		}

		if (tail == current) {
			t1 = tail->prev;
			t1->next = newClient;
			newClient->next = tail;
			tail->prev = newClient;
			newClient->prev = t1;
			return;
		}

		t1 = current->prev;
		t1->next = newClient;
		newClient->next = current;
	}
	else {
		if (head == current) {
			t1 = head->next;
			head->next = newClient;
			newClient->next = t1;
			t1->prev = newClient;
			newClient->prev = head;
			return;
		}

		if (tail == current) {
			tail->next = newClient;
			newClient->prev = tail;
			tail = newClient;
			return;
		}

		newClient->next = current->next;
		newClient->next->prev = newClient;
		current->next = newClient;
		newClient->prev = current;
	}
}

///7. Next client
void nextClient(clientList *&current) {
	current = current->next;
}

///8. Next client
void prevClient(clientList *&current) {
	current = current->prev;
}

///9. Count clients in the list
int countClients(clientList *head) {
	int counter = 0;

	clientList *temp = head;
	while (temp) {
		counter++;
		temp = temp->next;
	}

	return counter;
}

///10. Sort list by name
void sortClients(clientList *&head, clientList *&tail, clientList *&current) {
	bool swapped;

	clientList *ptr;
	clientList *temp = NULL;

	do {
		swapped = false;
		ptr = head;

		while (ptr->next != temp) {
			if (strcmp(ptr->name, ptr->next->name) > 0) {
				swapClients(ptr, ptr->next);
				swapped = true;
			}
			ptr = ptr->next;
		}
		temp = ptr;
	} while (swapped);
}

//Swap clients in the list
void swapClients(clientList *a, clientList *b) {
	char temp[50];

	//Name
	strcpy(temp, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp);

	//Surname
	strcpy(temp, a->surname);
	strcpy(a->surname, b->surname);
	strcpy(b->surname, temp);

	//Pantronimic
	strcpy(temp, a->pantronimic);
	strcpy(a->pantronimic, b->pantronimic);
	strcpy(b->pantronimic, temp);

	//Number
	strcpy(temp, a->number);
	strcpy(a->number, b->number);
	strcpy(b->number, temp);

	//City
	strcpy(temp, a->addressData.city);
	strcpy(a->addressData.city, b->addressData.city);
	strcpy(b->addressData.city, temp);

	//Street
	strcpy(temp, a->addressData.street);
	strcpy(a->addressData.street, b->addressData.street);
	strcpy(b->addressData.street, temp);

	//Building
	strcpy(temp, a->addressData.building);
	strcpy(a->addressData.building, b->addressData.building);
	strcpy(b->addressData.building, temp);

	//Flat
	strcpy(temp, a->addressData.flat);
	strcpy(a->addressData.flat, b->addressData.flat);
	strcpy(b->addressData.flat, temp);
}

///11. Input list into binary file
void inputBinary(clientList *head, clientList *tail) {
	ofstream outFile("data.bin", ios::binary);
	if (!outFile.is_open()) {
		cout << "Can not open the output file!!" << endl << endl;
		return;
	}

	clientList *temp = head;
	while (temp) {
		writeClient(outFile, temp);
		temp = temp->next;
	}

	outFile.close();
}

//Write data for one client from binary file
void writeClient(ofstream &file, clientList *client) {
	file.write(client->name, sizeof(client->name));
	file.write(client->surname, sizeof(client->surname));
	file.write(client->pantronimic, sizeof(client->pantronimic));

	file.write(client->number, sizeof(client->number));

	file.write(client->addressData.city, sizeof(client->addressData.city));
	file.write(client->addressData.street, sizeof(client->addressData.street));
	file.write(client->addressData.building, sizeof(client->addressData.building));
	file.write(client->addressData.flat, sizeof(client->addressData.flat));

	//file.write((char*)&client->next, sizeof(clientList*));
	//file.write((char*)&client->prev, sizeof(clientList*));
}

///12. Output list from binary file
void outputBinary(clientList *&head, clientList *&tail, clientList *&current) {
	ifstream inFile("data.bin", ios::binary);
	if (!inFile.is_open()) {
		cout << "Can not open the input file!!" << endl << endl;
		return;
	}

	inFile.seekg(0, inFile.end);
	int len = inFile.tellg();
	inFile.seekg(0, inFile.beg);

	while (len > inFile.tellg()) {
		clientList *newClient = new clientList;
		readClient(inFile, newClient);

		if (head == NULL) {
			head = newClient;
			tail = head;
			current = head;
			continue;
		}

		tail->next = newClient;
		newClient->prev = tail;
		tail = newClient;
		newClient = new clientList;
		len--;
	}

	inFile.close();
}

//Read data for one client from binary file
void readClient(ifstream &file, clientList *client) {
	file.read(client->name, sizeof(client->name));
	file.read(client->surname, sizeof(client->surname));
	file.read(client->pantronimic, sizeof(client->pantronimic));

	file.read(client->number, sizeof(client->number));

	file.read(client->addressData.city, sizeof(client->addressData.city));
	file.read(client->addressData.street, sizeof(client->addressData.street));
	file.read(client->addressData.building, sizeof(client->addressData.building));
	file.read(client->addressData.flat, sizeof(client->addressData.flat));

	//file.read((char*)&client->next, sizeof(clientList*));
	//file.read((char*)&client->prev, sizeof(clientList*));
}

//Clear full list
void clearList(clientList *&head, clientList *&tail, clientList *&current) {
	if (head == NULL) {
		return;
	}

	clientList *temp = head;
	clientList *ptr;
	while (temp) {
		ptr = temp;
		temp = temp->next;
		delete ptr;
	}

	head = NULL;
	tail = NULL;
	current = NULL;
}