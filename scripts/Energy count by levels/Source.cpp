#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct levelList {
	int height = 0;
	levelList *next = NULL;
	levelList *prev = NULL;

	static int amount;
};
int levelList::amount = 0;

int readFile(ifstream &, levelList *&, levelList *&);
void writeFile(ofstream &, const int &);

void inputLevels(levelList *&, levelList *&);
void outputLevels(levelList *);

void addLevel(levelList *&, levelList *&, int);

int energyToFinish(levelList *&, levelList *);

int main() {
	levelList *head = NULL;
	levelList *tail = NULL;
	int levelHeight;

	ifstream inFile("input.txt");
	ofstream outFile("output.txt");

	//Input
	if (inFile.is_open()) {
		readFile(inFile, head, tail);
	}
	else {
		inputLevels(head, tail);
	}

	//Output
	outputLevels(head);

	cout << "Needed energy: " << energyToFinish(head, tail) << endl;

	system("pause");
	return 0;
}

//Read data from file
int readFile(ifstream &file, levelList *&head, levelList *&tail) {
	int levelHeight;

	//Input amount of levels
	file >> levelList::amount;

	if (levelList::amount > 30000) {
		cout << "Input error!!\nIncorrect amount of levels!!!" << endl;
		return -1;
	}

	//Input heights of levels
	while (file >> levelHeight) {
		if (levelHeight > 30000) {
			cout << "Input error!!\nIncorrect height of level!!" << endl;
			return -2;
		}

		addLevel(head, tail, levelHeight);
	}
}

//Write result to file
void writeFile(ofstream &file, const int &energy) {
	file << energy << endl;
}

//Input data by console
void inputLevels(levelList *&head, levelList *&tail) {
	int levelHeight;

	//Input amount of levels
	cout << "Enter amount of levels: ";
	do {
		cin >> levelList::amount;

		if (levelList::amount > 30000) {
			cout << "Incorrect amount of levels!!" << endl;
			cout << "Try again: ";
		}
	} while (levelList::amount > 30000);

	//Input heights of levels
	for (int i = 0; i < head->amount; i++) {
		cout << "Enter height of " << i + 1 << "level: ";
		do {
			cin >> levelHeight;

			if (levelHeight > 30000) {
				cout << "Incorrect height of level!!" << endl;
				cout << "Try again: ";
			}
		} while (levelHeight > 30000);

		addLevel(head, tail, levelHeight);
	}
}

//Output all levels
void outputLevels(levelList *head) {
	if (head == NULL) {
		cout << "List of levels is empty!!!" << endl;
		return;
	}

	levelList *temp = head;
	cout << "Levels amount: " << temp->amount << endl;
	cout << "Levels height:" << endl;
	do {
		cout << setw(4) << temp->height;
		temp = temp->next;
	} while (temp);
	cout << endl;
}

//Add new level(item) to the list
void addLevel(levelList *&head, levelList *&tail, int levelHeight) {
	levelList *newLevel = new levelList;
	newLevel->height = levelHeight;

	if (head == NULL) {
		head = newLevel;
		tail = newLevel;
		return;
	}

	tail->next = newLevel;
	newLevel->prev = tail;
	tail = newLevel;
}

//Count energy to reach finish
int energyToFinish(levelList *&head, levelList *tail) {
	//Empty list
	if (head == NULL) {
		cout << "List of levels is empty!!!" << endl;
		return 0;
	}

	//Only one level
	if (head->next == NULL) {
		cout << "List has just one level" << endl;
		return 0;
	}

	int sumHeight = 0;
	levelList *current = head;
	levelList *temp = current->next;

	do {
		//If there are only two levels
		if (current->next->next == NULL) {
			return sumHeight += abs(current->next->height - current->height);
		}

		if (abs(temp->height - current->height) < 3 * abs(temp->next->height - current->height)) {
			//If |y2 - y1| less than 3*|y3-y1|
			sumHeight += abs(temp->height - current->height);

			//cout << "From " << current->height << " to " << temp->height << endl; 
			//cout << "Energy: " << sumHeight << endl;

			current = temp;
			temp = temp->next;
		}
		else {
			//If 3*|y3 - y1| less than |y2 - y1|
			sumHeight += 3 * abs(temp->next->height - current->height);

			//cout << "From " << current->height << " to " << temp->next->height << endl; 
			//cout << "Energy: " << sumHeight << endl;

			current = temp->next;
			temp = temp->next;
		}

	} while (current->next != NULL);

	return sumHeight;
}