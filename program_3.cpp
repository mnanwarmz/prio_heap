#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>
#define SET_SIZE 5000000
#define FILENAME "SetC.txt"
#define STR_SIZE 24

using namespace std;

struct Node
{
    string data;
    int index;
};
Node H[SET_SIZE];
int size = -1;
int polynomials[STR_SIZE];
int parent(int i)
{
    return (i - 1) / 2;
}

// get left child of a given node
int leftChild(int i)
{

    return ((2 * i) + 1);
}

// get right child of a given node
int rightChild(int i)
{

    return ((2 * i) + 2);
}

// Function to shift up the node in order
// to maintain the heap property
void shiftUp(int i)
{
    while (i > 0 && H[parent(i)].index < H[i].index)
    {
        // Swap parent and current node
        swap(H[parent(i)], H[i]);

        // Update i to parent of i
        i = parent(i);
    }
}

// Function to shift down the node in
// order to maintain the heap property
void shiftDown(int i)
{
    int maxIndex = i;
    // Left Child
    int l = leftChild(i);
    if (l <= size && H[l].index > H[maxIndex].index)
    {
        maxIndex = l;
    }
    // Right Child
    int r = rightChild(i);
    if (r <= size && H[r].index > H[maxIndex].index)
    {
        maxIndex = r;
    }
    if (i != maxIndex)
    {
        swap(H[i], H[maxIndex]);
        shiftDown(maxIndex);
    }
}

// Function to insert a new element
// in the Binary Heap
void insert(string p, int index)
{
    size = size + 1;
    Node n = {p, index};
    H[size] = n;

    // Shift Up to maintain heap property
    shiftUp(size);
}

// Function to extract the element with
// maximum priority
Node extractMax()
{
    Node result = H[0];
    // Replace the value at the root
    // with the last leaf
    H[0] = H[size];
    size = size - 1;

    // Shift down the replaced element
    // to maintain the heap property
    shiftDown(0);
    return result;
}

void initializePolynomials()
{
    for (int i = 0; i < STR_SIZE; i++)
    {
        polynomials[i] = pow(2, i);
    }
}

// Inserts the setData into the heap
void getAndInsertData(string setName)
{
    fstream file;

    file.open(setName, ios::in);
    if (file.is_open())
    {
        string data;
        int size = 0;
        while (!file.eof())
        {
            while (getline(file, data))
            {
                int total = 0;
                for (int i = 0; data[i] != '\0'; i++)
                    total += data[i] * polynomials[i];
                insert(data, total);
            }
        }
        file.close();
    }
}

void display()
{
    for (int i = 0; i < size; i++)
    {
        cout << H[i].data << " " << endl;
    }
    cout << endl;
}

// Main Function
int main()
{
    initializePolynomials();
    // Insertion
    cout << "Inserting Values in the Priority Queue\n";
    clock_t start = clock();
    getAndInsertData(FILENAME);
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken to insert values into queue is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    cout << "Extracting the 10\% from the Priority Queue\n";

    // Extracting 10%
    start = clock();
    for (int i = 0; i < SET_SIZE * 0.1; i++)
        extractMax();
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken to extract 10\% from the queue is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;

    // Displaying the heap
    cout << "Would you like to display the data in the heap? (y/n)";
    char choice;
    cin >> choice;
    if (choice == 'y')
    {
        cout << "Displaying the data in the heap\n";
        display();
    }
    else
    {
        cout << "Exiting the program\n";
    }
}
