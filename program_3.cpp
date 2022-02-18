#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#define SET_SIZE 100
#define STR_SIZE 24

using namespace std;
int H[SET_SIZE];
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
    while (i > 0 && H[parent(i)] < H[i])
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

    if (l <= size && H[l] > H[maxIndex])
    {
        maxIndex = l;
    }

    // Right Child
    int r = rightChild(i);

    if (r <= size && H[r] > H[maxIndex])
    {
        maxIndex = r;
    }

    // If i not same as maxIndex
    if (i != maxIndex)
    {
        swap(H[i], H[maxIndex]);
        shiftDown(maxIndex);
    }
}

// Function to insert a new element
// in the Binary Heap
void insert(int p)
{
    size = size + 1;
    H[size] = p;

    // Shift Up to maintain heap property
    shiftUp(size);
}

// Function to extract the element with
// maximum priority
int extractMax()
{
    int result = H[0];

    // Replace the value at the root
    // with the last leaf
    H[0] = H[size];
    size = size - 1;

    // Shift down the replaced element
    // to maintain the heap property
    shiftDown(0);
    return result;
}

// Return the highest value
int getMax()
{
    return H[0];
}

void initializePolynomials()
{
    for (int i = 0; i < STR_SIZE; i++)
    {
        polynomials[i] = pow(2, i);
    }
}

// Inserts the setData into the heap
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
                i = 0;
                value = 0;
                while (data[i] != '\0')
                {
                    value += data[i] * polynomials[i];
                    i++;
                }
                insert(value);
                size++;
            }
        }
        file.close();
    }
}

void display()
{
    for (int i = 0; i < SET_SIZE; i++)
    {
        cout << H[i] << " " << endl;
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
    convertStringToPolynomial("SetA.txt");
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken to insert values into queue is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    cout << "Extracting the 10\% from the Priority Queue\n";

    // Extracting 10%
    start = clock();
    for (int i = 0; i < 10; i++)
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
