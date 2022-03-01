#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iterator>
#include <chrono>
#include <vector>
#define FILENAME "setC.txt"
#define SET_SIZE 5000000
#define STR_SIZE 24
using namespace std;
// Inserts the setData into the heap
const int TABLE_SIZE = SET_SIZE * 1.5;
string *HashTable = new string[TABLE_SIZE];
int polynomials[STR_SIZE];

int getIndex(string data)
{
	int total = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		total += data[i] * polynomials[i];
	}
	// simple hash function
	int index = total % TABLE_SIZE;
	return index;
}

void insert(int index, string data)
{
	if (HashTable[index] == "")
		HashTable[index] = data;
	else
	{
		while (HashTable[index] == "")
		{
			index++;
		}
		HashTable[index] = data;
	}
}

void convertStringToPolynomial(string setName)
{
	fstream file;

	file.open(setName, ios::in);
	if (file.is_open())
	{
		string data;
		int value, i, size = 0;
		while (!file.eof())
		{
			while (getline(file, data))
			{
				int index = getIndex(data);
				insert(index, data);
			}
		}
		file.close();
	}
}

void initializePolynomials()
{
	for (int i = 0; i < STR_SIZE; i++)
	{
		polynomials[i] = pow(2, i);
	}
}

void search(string data)
{
	int index = getIndex(data);
	if (HashTable[index] == data)
		cout << "Found" << endl;
	else
	{
		while (HashTable[index] != data && index <= TABLE_SIZE)
		{
			index++;
		}
		if (HashTable[index] == data)
			cout << "Found" << index << endl;
		else
			cout << "Not Found" << endl;
	}
}

bool exists(string a[], string data)
{
	for (int i = 0; i < 10; i++)
	{
		if (a[i] == data)
			return true;
	}
	return false;
}

string *generateRandomStrings()
{
	string *randoms = new string[10];
	for (int i = 0; i < 10; i++)
	{
		// get random unique value ranging from 0 to TABLE_SIZE
		srand(unsigned(time(0)));
		int index = (int)rand() % TABLE_SIZE;
		while (HashTable[index] == "" || exists(randoms, HashTable[index]) == true)
			index++;
		randoms[i] = HashTable[index];
	}
	return randoms;
}

void display()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (HashTable[i] != "")
			cout << i << "\t -> " << HashTable[i] << endl;
	}
}

int main()
{
	string *findString = new string[10];
	initializePolynomials();
	// Data insertion start
	cout << "Inserting data into the hash table\n";
	cout << "\n";
	clock_t start = clock();
	convertStringToPolynomial(FILENAME);
	clock_t end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken to insert data into the hash table: " << time_taken << " seconds\n";
	// Data insertion end
	cout << "Fetching 10 randoms string to search" << endl;
	findString = generateRandomStrings();
	// Searching start
	cout << "Searching for the strings" << endl;
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		cout << "Searching for " << findString[i] << endl;
		search(findString[i]);
	}
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken to search for the strings: " << time_taken << " seconds\n";
	// Searching end
	// Searching for unavailable data
	cout << "Searching for unavailable data" << endl;
	start = clock();
	for (int i = 0; i < 10; i++)
	{
		cout << "Searching for "
			 << "Unavailable String" << endl;
		search("askdjfalskdjfasldkjf");
	}
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken to search for unavailable data: " << time_taken << " seconds\n";
	// Searching for unavailable data end
	cout << "Would you like to display the dataset? (y/n)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'y')
		display();
	return 0;
}