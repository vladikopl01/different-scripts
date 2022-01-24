#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

bool isPrime(int);

void calcE(int, vector<int>*, vector<int>*);
int gcd(int, int);
int calcD(int, int);

int encryption(int, int, int);
int decryption(int, int, int);

void writeResult(
	ofstream&, 
	const map<string, int>&, 
	const vector<int>&, const vector<int>&, 
	const string&, const string&
);

int main() {
	//Method data
	int p, q, n, t;
	bool primeFlag;

	string msg;
	string encryptedText;
	string decryptedText;

	ifstream textFile, valuesFile;

	//Opening input files
	valuesFile.open("TP_92_Gorokhovska_mkr2.dat");
	textFile.open("TP_92_Gorokhovska_mkr2.rsa");

	//Input p and q values
	if (!valuesFile.is_open()) {
		//cout << "Error!! There are not such .dat file!!" << endl;
		cout << "Enter prime values for p and q: " << endl;

		//Input p value
		cout << "p: ";
		do {
			cin >> p;

			if (!isPrime(p)) {
				cout << "Wrong input!! This number is not Prime!" << endl;
				cout << "Try again: ";
			}
		} while (!isPrime(p));

		//Input q value
		cout << "q: ";
		do {
			cin >> q;

			if (!isPrime(q)) {
				cout << "Wrong input!! This number is not Prime!" << endl;
				cout << "Try again: ";
			}
		} while (!isPrime(q));
	}
	else {
		cout << "Reading .dat file..." << endl;
		valuesFile >> p;
		valuesFile >> q;
		cout << "Reading complete!" << endl;
		cout << "Data from file: " << endl << endl;
		cout << "p: " << p << endl;
		cout << "q: " << q << endl << endl;
	}

	//Input coding text
	if (!textFile.is_open()) {
		//cout << "Error!! There are not such .rsa file!!" << endl;
		cout << "Enter coding text: ";
		cin >> msg;
	}
	else {
		cout << "Reading .rsa file..." << endl;
		textFile >> msg;
		cout << "Reading complete!" << endl;
		cout << "Data from file: " << endl << endl;
		cout << "Text: " << msg << endl;
	}

	//Calculate modulus - n
	n = p * q;
	cout << "\nn: " << n << endl;

	//Calculate Euler totient function - t
	t = (p - 1) * (q - 1);
	cout << "t: " << t << endl << endl;

	//Calculation of the:
	//	open exponent - e
	//	hidden exponent - d
	vector<int> e;
	vector<int> d;
	calcE(t, &e, &d);

	//Output all possible values of E and D
	cout << "All possible values of E and D:" << endl;
	for (int i = 0; i < e.size(); i++) {
		cout << "e: " << setw(4) << e[i] << "  d: " << setw(4) << d[i] << endl;
	}
	cout << endl;

	//Public RSA key
	cout << "Public RSA key: [e = " << e[0] << ", n = " << n << "]" << endl;

	//Private RSA key
	cout << "Private RSA key: [d = " << d[0] << ", n = " << n << "]" << endl << endl;

	//Encryption
	for (int i = 0; i < msg.length(); i++) {
		encryptedText += (char)encryption(msg[i], e[0], n);
	}

	//Decryption
	for (int i = 0; i < msg.length(); i++) {
		decryptedText += (char)decryption(encryptedText[i], d[0], n);
	}

	//Result
	cout << "Encrypted message: " << encryptedText << endl;
	cout << "Decrypted message: " << decryptedText << endl;

	//Output info to file
	ofstream outFile("TP_92_Gorokhovska_mkr2.txt");
	map<string, int> list = { {"p", p}, {"q", q}, {"n", n}, {"t", t} };
	writeResult(outFile, list, e, d, encryptedText, decryptedText);

	system("pause");
	return 0;
}

//Check for prime number
bool isPrime(int num) {
	int j = sqrt((double)num);

	for (int i = 2; i <= j; i++) {
		if (num % i == 0) {
			return false;
		}
	}

	return true;
}

//Calculation of the open exponent - e
void calcE(int t, vector<int> *eList, vector<int> *dList) {
	//Calcualte all possible e
	for (int e = 2; e < t; e++) {
		if (gcd(e, t) == 1 && isPrime(e)) {
			eList->push_back(e);
		}
	}
	
	//Calculte d from e
	for (int i = 0; i < eList->size(); i++) {
		dList->push_back(calcD((*eList)[i], t));
	}
}

int gcd(int e, int t) {
	int temp;
	while (e > 0) {
		temp = e;
		e = t % e;
		t = temp;
	}
	return t;
}

//Calculation of the hidden exponent - d
int calcD(int e, int t) {
	int d;
	int k = 1;

	while (true) {
		k += t;

		if (k % e == 0) {
			d = k / e;
			return d;
		}
	}
}

//Encryption
int encryption(int symbol, int e, int n) {
	int current, result;

	current = symbol - 96;
	result = 1;

	for (int i = 0; i < e; i++) {
		result *= current;
		result %= n;
	}

	return result;
}

//Decryption
int decryption(int symbol, int d, int n) {
	int current, result;

	current = symbol;
	result = 1;

	for (int i = 0; i < d; i++) {
		result *= current;
		result %= n;
	}

	return result + 96;
}

//Write all info to file
void writeResult(ofstream& file, const map<string, int>& list, const vector<int>& e, const vector<int>& d, const string& encText, const string& decText) {
	for (auto it = list.begin(); it != list.end(); it++) {
		file << it->first << ": " << it->second << endl;
	}

	file << "All possible values of E and D:" << endl;
	for (int i = 0; i < e.size(); i++) {
		file << "e: " << setw(4) << e[i] << "  d: " << setw(4) << d[i] << endl;
	}

	file << "Public RSA key: [e = " << e[0] << ", n = " << list.find("n")->second << "]" << endl;
	file << "Private RSA key: [d = " << d[0] << ", n = " << list.find("n")->second << "]" << endl;

	file << "Encryption: " << encText << endl
		<< "Decryption: " << decText << endl;
}
