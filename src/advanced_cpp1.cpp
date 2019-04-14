//============================================================================
// Name        : advanced_cpp1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <exception>
using namespace std;

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
	} catch(MyException &e){
		cout << "Caught my custom exception: " << e.what() << endl;
	};
	cout << "still running" << endl;

	return 0;
}
