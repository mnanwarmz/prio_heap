#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

string gen_random(const int length) {

    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(length);

    for (int i = 0; i < length; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum)-1)];

    return tmp_s;
}

string gen_random1(const int length)
{
    string tmp_s;
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    tmp_s.reserve(length);

    for (int i = 0; i < length; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum)-1)];


    return tmp_s;

}

string gen_random2(const int length) {

    string tmp_s;
    static const char alphanum[] =
       "0123456789";

    tmp_s.reserve(length);

    for (int i = 0; i < length; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum)-1)];

    return tmp_s;
}

string gen_random3() {

	string tmp_s;
	const string arrayNum[3] = {"com", "org" ,"my"};

	int randIndex = rand() % 3;
	tmp_s = arrayNum[randIndex];



	return tmp_s;

}


int main(int argc, char *argv[]) {

    string data, data1, data2, data3, data4;
    ofstream myfile;

    //Set A
    cout << "Set A\n";
    myfile.open ("setA.txt");
    int itemA = 100;

    for (int i=0;i<itemA;i++)
    {
        //Capital[A-Z]
        data = gen_random1(4);

        //Number[0-9]
        data1 = gen_random2(4);

        //Alphanumerical [a-z,A-z,0-9]
    	data2 = gen_random(5);

        //Alphanumerical [a-z,A-z,0-9]
    	data3 = gen_random(4);

        //[com,org,net,my]
    	data4 = gen_random3();

        cout << i+1 << ". " << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
        myfile << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
    }
    myfile.close();

    //Set B
    cout << "\n";
    cout << "Set B\n";
    myfile.open ("setB.txt");
    int itemB = 1000000;

    for (int i=0;i<itemB;i++)
    {
        //Capital[A-Z]
        data = gen_random1(4);

        //Number[0-9]
        data1 = gen_random2(4);

        //Alphanumerical [a-z,A-z,0-9]
    	data2 = gen_random(5);

        //Alphanumerical [a-z,A-z,0-9]
    	data3 = gen_random(4);

        //[com,org,net,my]
    	data4 = gen_random3();

        cout << i+1 << ". " << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
        myfile << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
    }
    myfile.close();

    //Set C
    cout << "\n";
    cout << "Set C\n";
    myfile.open ("setC.txt");
    int itemC = 5000000;

    for (int i=0;i<itemC;i++)
    {
        //Capital[A-Z]
        data = gen_random1(4);

        //Number[0-9]
        data1 = gen_random2(4);

        //Alphanumerical [a-z,A-z,0-9]
    	data2 = gen_random(5);

        //Alphanumerical [a-z,A-z,0-9]
    	data3 = gen_random(4);

        //[com,org,net,my]
    	data4 = gen_random3();

        cout << i+1 << ". " << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
        myfile << data << "." << data1 << "." << data2 <<"@"<< data3 << "." << data4 << endl;
    }
    myfile.close();

    return 0;
}
