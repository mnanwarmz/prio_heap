#include <iostream>
#include <chrono>
#include <fstream>
#include "program_3.cpp"
#include <sstream>

using namespace std;;

int main()
{
	stringstream intValue("hello");
	int number = 5;
	intValue >> number;
	cout<<intValue;
	// insert("Hello");
	// insert("How");
	// insert("Are");
	// insert("You");
}