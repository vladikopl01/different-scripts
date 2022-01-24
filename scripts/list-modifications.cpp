#include <iostream>
#include <iomanip>

using namespace std;

struct singleList {
	int data;
	singleList *next = NULL;
};

struct doubleList {
	int data;
	doubleList *next = NULL;
	doubleList *prev = NULL;
};

void insertNode(singleList*&, int); //Insert node to the end of single linked list
void insertNode(doubleList*&, doubleList*&, int); //Insert node to the end of double linked list

template <class listType>
void outputList(listType*); //Display full list

void delByKey(singleList*&, int); //Delete node by a key value in single linked list
void delByKey(doubleList*&, doubleList*&, int); //Delete node by a key value in double linked list

template <class listType>
double arithmeticMean(listType*); //Return arithmetic mean of 1 to 6 node's values

template <class listType>
void clearList(listType**, doubleList **tail = NULL); //Clear full list

int main() {
	int nodesAmount;
	int key;

	///Single linked list///
	singleList *singleHead = NULL;

	//Enter amount of nodes to create
	cout << "Enter number of nodes: ";
	do {
		cin >> nodesAmount;

		if (nodesAmount < 0) {
			cout << "Error!! Enter number >= 0!!" << endl;
			cout << "Try again: ";
		}
	} while (nodesAmount < 0);
	

	//Creating list of 10 nodes
	for (int i = 0; i < nodesAmount; i++) {
		insertNode(singleHead, rand() % 10);
	}

	//Display full list
	cout << "Single linked list:" << endl;
	outputList(singleHead);

	//Delete node by a key value
	cout << "Enter key: ";
	cin >> key;

	delByKey(singleHead, key);
	cout << "New list: " << endl;
	outputList(singleHead);

	//TASK | Arithmetic mean of nodes from 1 to 6
	cout << "Arithmetic mean: " << arithmeticMean(singleHead) << endl;
	
	cin.ignore();
	getchar();
	system("cls");

	///Double linked list///
	doubleList *doubleHead = NULL;
	doubleList *doubleTail = NULL;

	//Enter amount of nodes to create
	cout << "Enter number of nodes: ";
	do {
		cin >> nodesAmount;

		if (nodesAmount < 0) {
			cout << "Error!! Enter number >= 0!!" << endl;
			cout << "Try again: ";
		}
	} while (nodesAmount < 0);

	//Creating list of 10 nodes
	for (int i = 0; i < nodesAmount; i++) {
		insertNode(doubleHead, doubleTail, rand() % 10);
	}

	//Display full list
	cout << "Double linked list:" << endl;
	outputList(doubleHead);

	//Delete node by a key value
	cout << "Enter key: ";
	cin >> key;

	delByKey(doubleHead, doubleTail, key);
	cout << "New list: " << endl;
	outputList(doubleHead);

	//TASK | Arithmetic mean of nodes from 1 to 6
	cout << "Arithmetic mean: " << arithmeticMean(doubleHead) << endl;

	//Clearing lists
	clearList(&singleHead);
	clearList(&doubleHead, &doubleTail);

	system("pause");
	return 0;
}

//Insert node to the end of single linked list
void insertNode(singleList *&head, int num) {
	singleList *newNode = new singleList;
	newNode->data = num;

	//If list is empty, creates HEAD
	if (head == NULL) {
		head = newNode;
		return;
	}

	singleList *temp = head;

	//Iterate up to last node of list
	while (temp->next) {
		temp = temp->next;
	}

	//Creating link to new node from last node
	temp->next = newNode;
}

//Insert node to the end of double linked list
void insertNode(doubleList *&head, doubleList *&tail, int num) {
	doubleList *newNode = new doubleList;
	newNode->data = num;

	if (head == NULL && tail == NULL) {
		head = newNode;
		tail = newNode;
		return;
	}

	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
}

//Display full list
template <class listType>
void outputList(listType *head) {
	if (head == NULL) {
		cout << "List is empty..." << endl;
		return;
	}

	listType *temp = head;
	while (temp) {
		cout << setw(3) << temp->data;
		temp = temp->next;
	}
	cout << endl;
}

//SINGLE - Delete node by a key value
void delByKey(singleList *&head, int key) {
	if (head == NULL) {
		cout << "List is empty..." << endl;
		return;
	}

	int temp;
	singleList *t = head;

	if (t->data == key) {
		head = t->next;
		delete t;
		t = head;

		//If there are two nodes to swap
		if (t != NULL && t->next != NULL) {
			temp = t->data;
			t->data = t->next->data;
			t->next->data = temp;
		}
	}

	singleList *t1 = (t != NULL) ? t->next : NULL;

	//Delete all other nodes with key value
	while (t1) {
		if (t1->data == key) {
			t->next = t1->next;
			delete t1;
			t1 = t->next;

			if (t1 != NULL && t1->next != NULL) {
				temp = t1->data;
				t1->data = t1->next->data;
				t1->next->data = temp;
			}
			continue;
		}
		t = t1;
		t1 = t1->next;
	}
}

//DOUBLE - Delete node by a key value
void delByKey(doubleList *&head, doubleList *&tail, int key) {
	if (head == NULL) {
		cout << "List is empty..." << endl;
		return;
	}

	doubleList *current = head;

	while (current) {
		if (current->data == key) {
			if (current == head) {
				head = current->next;
				head->prev = NULL;
				delete current;
				current = head;
			}
			else if (current == tail) {
				tail = current->prev;
				tail->next = NULL;
				delete current;
				current = tail;
			}
			else {
				doubleList *t1 = current->prev;
				doubleList *t2 = current->next;
				t1->next = t2;
				t2->prev = t1;
				delete current;
				current = t2;
			}
			continue;
		}
		current = current->next;
	}
}

//Calculate arithmetic mean of nodes btw 1 and 6 values
template <class listType>
double arithmeticMean(listType *head) {
	int sum = 0;
	int count = 0;

	listType *t = head;
	while (t) {
		if (t->data >= 1 && t->data <= 6) {
			sum += t->data;
			count++;
		}
		t = t->next;
	}

	return head ? (double)sum / count : 0;
}

//Clear full list
template <class listType>
void clearList(listType **head, doubleList **tail) {
	if (head == NULL) {
		return;
	}

	listType *ptr = *head;
	listType *t;

	while (ptr) {
		t = ptr;
		ptr = ptr->next;
		delete t;
	}

	*head = NULL;
	if (tail) 	*tail = NULL;
	cout << "List was cleared!" << endl;
}