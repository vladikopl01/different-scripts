#include <iostream>

using namespace std;

struct addressInfo {
	char city[50];
	char street[50];
	char building[50];
	char flat[10];
};

struct clientInfo {
	char name[50];
	char surname[50];
	char pantronimic[50];
	char number[50];
	addressInfo addressData;
	int id;
};

bool choice();

bool findClient(clientInfo*, int);

int inputId();

void initClient(clientInfo*, int);
void showClientData(clientInfo*, int);
clientInfo* createClient(clientInfo*, int&, int&);

int main() {
	int id = 0;
	int clientsAmount = 1;

	clientInfo* clients = new clientInfo[clientsAmount];

	clientInfo Christina = { "Christina", "Gorokhovska", "Leonidivna", "067-492-44-65",
	{"Brovary", "Symonenka", "2b"} , 0 };

	*clients = Christina;

	do {
		system("cls");
		cout << "Are you in our database? (0 = no, 1 = yes): ";
		if (choice()) {
			system("cls");
			id = inputId();
			if (findClient(clients, id)) {
				showClientData(clients, id);
				cout << "Do you want to refresh your information? (0 = no, 1 = yes): ";
				if (choice()) {
					system("cls");
					initClient(&clients[id], id);
				}
			}
			else {
				cout << "There aren`t any client with such ID!!" << endl;
				cout << "Do you want to create a new client? (0 = no, 1 = yes): ";
				if (choice()) {
					system("cls");
					id = clientsAmount;
					clients = createClient(clients, id, clientsAmount);
				}
			}
		}
		else {
			system("cls");
			cout << "Do you want to create a new client? (0 = no, 1 = yes): ";
			if (choice()) {
				system("cls");
				id = clientsAmount;
				clients = createClient(clients, id, clientsAmount);
			}
		}
		cout << "Continue? (0 = no, 1 = yes): ";
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
	cin.get();
	if (ch == 1) {
		return true;
	}
	return false;
}

//Find client by id
bool findClient(clientInfo* client, int identifier) {
	if (client[identifier].id == identifier) {
		return true;
	}
	return false;
}

//Input id
int inputId() {
	int id;
	cout << "Enter your ID: ";
	do {
		cin >> id;
		if (id < 0) {
			cout << "Incorrect input. Try again: ";
		}
	} while (id < 0);
	return id;
}

//Initialization
void initClient(clientInfo* client, int id) {
	cout << "Input client info:" << endl;
	cout << " Name: ";
	cin.getline(client->name, 50);
	cout << " Surname: ";
	cin.getline(client->surname, 50);
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
	client->id = id;
}

//Output data
void showClientData(clientInfo* clients, int id) { 
	cout << "Client: "
		<< clients[id].surname << " "
		<< clients[id].name << " "
		<< clients[id].pantronimic << endl;
	cout << " Phone number: "
		<< clients[id].number << endl;
	cout << " Address: " << clients[id].addressData.city << ", "
		<< clients[id].addressData.street << ", "
		<< clients[id].addressData.building << ", "
		<< clients[id].addressData.flat << endl;
	cout << " Client ID: " << clients[id].id << endl;
}

//Create data
clientInfo* createClient(clientInfo* clients, int& id, int& ownersAmount) {
	clientInfo client;
	initClient(&client, id);
	clientInfo* newArr = new clientInfo[ownersAmount + 1];
	cout << "Your id: " << client.id << endl;
	for (int i = 0; i < ownersAmount; i++) {
		newArr[i] = clients[i];
	}
	newArr[ownersAmount] = client;
	ownersAmount++;
	delete[]clients;
	return newArr;
}