//============================================================================
// Name        : advanced_cpp1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <exception>
#include <fstream> // file stream library

using namespace std;

///////to write this struct to a binary file
//// wrap the struct with #pragma
#pragma pack(push, 1) //remove padding

struct Person {

	char name[50];
	int age;
	double weight;
};

#pragma pack(pop)
////

class MyException: public exception {
public:
	// the const throw() part means it won't throw an exception
	virtual const char* what() const throw () {
		return "Something happened";
	}
	;
};

class Test {
public:
	void goesWrong() {
		throw MyException();
	}
};

class CanGoWrong {
public:
	CanGoWrong() {
		char *pmemory = new char[99999999999999999];
		delete[] pmemory;
	}
};

void mightGoWrong() {
	bool error = false;
	bool error2 = true;
	if (error) {
		throw "something went wrong"; // throw error and btw this is consider char so to catch it you need to use char *e
	}

	if (error2) {
		throw string("Something else went wrong");
	}
}

int main() {

	//------------Exception-------------
	try {
		mightGoWrong();
	} catch (int e) {
		cout << "error occured: " << e << endl;
	} catch (char const *e) { // for the string error message
		cout << "Error message: " << e << endl;
	} catch (string &e) { // normally you don't want to return a reference but exception is different
		cout << "string error message: " << e << endl;
	}

	try {
		CanGoWrong wrong;
		// bad_alloc is from std, a sub error class
	} catch (std::bad_alloc &e) {
		cout << "Caught exception: " << e.what() << endl;
	}

	Test test;
	try {
		test.goesWrong();
	} catch (MyException &e) {
		cout << "Caught my custom exception: " << e.what() << endl;
	};
	cout << "still running" << endl;

//-----------------file handling-------------
	// writing text file

//	fstream outFile;
	ofstream outFile; //output file stream

	string fileName = "text.txt";

//	outFile.open(outputFileName, ios::out);
	outFile.open(fileName);

	if (outFile.is_open()) {
		outFile << "hello there" << endl;
		outFile << "123" << endl;
		outFile.close();
	} else {
		cout << "could not create file" << fileName << endl;
	}

	// reading text file
	ifstream inFile; // input file stream
	inFile.open(fileName);
	if (inFile.is_open()) {

		// loop thru each line to get whole content
		while (inFile) { // eof = end of file
			string line;
			getline(inFile, line);

			cout << line << endl;
		}
		inFile.close();
	} else {
		cout << "can't open file" << endl;
	}

	// parse string from a file
	ifstream input_file;
	string file_name = "parse.txt";

	input_file.open(file_name);

	if (!input_file.is_open()) {
		return 1; // error code
	}

	while (input_file) {
		string line;
		getline(input_file, line, ':'); //: as delimiter

		int population;
		input_file >> population;
		//input_file.get(); //get the next charector
		input_file >> ws; // read white space (c++ 11)

		if (!input_file) {
			break;
		}
		cout << "'" << line << "'" << "------ '" << population << "'" << endl;
	}

	input_file.close();

	// ------write and read binary file-----

	// write binary file
	//instantiate person struct
	Person someone = { "Hsin", 38, 100 };

	string file_name_bi = "test.bin";

	ofstream out_file;

	out_file.open(file_name_bi, ios::binary);

	if (out_file.is_open()) {
		// write expects char type pointer and size of byte you need to write
		//out_file.write((char *)&someone, sizeof(Person)); //old way

		//new way considered best practice
		out_file.write(reinterpret_cast<char *>(&someone), sizeof(Person));
		out_file.close();
	} else {
		cout << "Could not create file " + file_name_bi;
	}

	// read binary file

	Person someone_else = {};
	ifstream in_file;

	in_file.open(file_name_bi, ios::binary);

	if (in_file.is_open()) {
		// write expects char type pointer and size of byte you need to write
		//out_file.write((char *)&someone, sizeof(Person)); //old way

		//new way considered best practice
		in_file.read(reinterpret_cast<char *>(&someone_else), sizeof(Person));
		in_file.close();
	} else {
		cout << "Could not read file " + file_name_bi;
	}

	cout << someone_else.name << ", " << someone_else.age << ", " << someone_else.weight << endl;

	return 0;
}
