#include <iostream>
#include <fstream>
#include "Rover.h"
#include "MyString.h"
using std::cin, std::cout, std::endl, std::ifstream, std::istream;


// helper function "stoi" to converts MyString to int, works a lot like number slicing in reverse
int stoi(const MyString& str, size_t* pos = nullptr, int base = 10) { // just doing base 10 here
	int result = 0;
	for (unsigned int i = 0; i < str.size(); i++) { // MyString: size()
		if (str.at(i) >= '0' && str.at(i) <= '9') { // MyString: at()
			result *= 10; // increase digit (reverse of number slicing)
			result += str.at(i) - 48; // using ascii for conversion
		}
	}
	return result;
}

// helper function for insertion allows reading from input stream to MyString
istream& operator>>(istream& is, MyString& str) {
	str.clear();
	while (!is.eof()) {
		char c;
		is >> std::noskipws >> c; // use the noskipws manipulator
		if (isspace(c) || is.fail()) break; // if whitespace, can stop adding to string
		const char* newstr = new char[2] {c, '\0'};
		MyString newc = MyString(newstr); // MyString: copy constructor
		delete[] newstr;
		str += newc; // MyString: operator+=()
	}
	return is;
}

/*
// helper function for insertion allows reading from input stream to MyString
istream& operator>>(istream& is, MyString& str) {
    cout << std::boolalpha;
    
    str.clear();
    {
        cout << "--- testing: cleared MyString object ---" << endl;

        cout << "expected cout: ||" << endl;
        cout << "actual cout: |" << str << "|" << endl << endl;

        cout << "expected size: 0" << endl;
        cout << "actual size: " << str.size() << endl << endl;

        cout << "expected capacity > 0:" << true << endl;
        cout << "actual capacity > 0: " << (str.capacity() > 0) << endl << endl;

        const char* actual_data = str.data();
        cout << "expected data[0] == null char: " << true << endl;
        cout << "actual data[0] == null char: " << (actual_data[0] == 0) << endl << endl;

        cout << "expected data: ||" << endl;
        cout << "actual data: |" << str.data() << "|" << endl << endl;
    }

    cout << "enter filename: ";
    while (!is.eof()) {
        char c;
        is >> std::noskipws >> c; // use the noskipws manipulator
        if (isspace(c) || is.fail()) break; // if whitespace, can stop adding to string
        const char* newstr = new char[2] {c, '\0'};
		
        MyString newc = MyString(newstr); // MyString: C-string constructor
        {
            cout << "--- testing: MyString C-string constructor ---" << endl;

            cout << "expected cout: |" << newstr << "|" << endl;
            cout << "actual cout: |" << newc << "|" << endl << endl;

            cout << "expected size: 1" << endl;
            cout << "actual size: " << str.size() << endl << endl;

            cout << "expected capacity > 1: " << true << endl;
            cout << "actual capacity > 1: " << (str.capacity() > 1) << endl << endl;

            const char* actual_data = newc.data();
            cout << "expected data != nullptr: " << false << endl;
            cout << "actual data != nullptr: " << (actual_data == nullptr) << endl << endl;

            cout << "expected data[1] == null char: " << true << endl;
            cout << "actual data[1] == null char: " << (actual_data[1] == 0) << endl << endl;

            char c1 = -1;
            char c2 = -1;
            size_t i = 0;
            while (c1 != 0 || c2 != 0) {
                c1 = newstr[i];
                c2 = actual_data[i];
                cout << "@ index " << i << ": ";
                cout << "   expected char: " << c1 << endl;
                cout << "   actual char: " << c2 << endl;
                ++i;
            }
            cout << endl;

            cout << "expected data: |" << newstr << "|" << endl;
            cout << "actual data: |" << actual_data << "|" << endl << endl;
        }

        delete[] newstr;
        str += newc; // MyString: operator+=()
        {
            cout << "--- testing: MyString operator+= ---" << endl;
            cout << "object: |" << str << "|" << endl << endl;

            cout << "object size: " << str.size() << endl;
            cout << "object capacity: " << str.capacity() << endl;
            
            const char* actual_data = str.data();
            cout << "data: |" << actual_data << "|" << endl << endl;
			
			char c1 = -1;
            size_t i = 0;
            while (c1 != 0) {
                c1 = actual_data[i];
                cout << "@ index " << i << ": " << c1 << endl;
                ++i;
            }
            cout << endl << endl;
        }
    }
    return is;
}
*/
int main () {

	// open command file
	MyString filename; // MyString: default constructor

	cin >> filename; // operator>> is provided above

	ifstream commands(filename.data()); // MyString: data() return const char* type (otherwise, have to implement ifstream constructor for MyString type)

	if (!commands.is_open()) {
		cout << "Unable to open file" << endl;
		return 1;
	}

	// setup test rover
	Rover testRover;

	// read commands
	MyString comm;
	MyString data;
	while (!commands.eof()) {
		commands >> comm;

		if (comm.front() == 'P') { // MyString: front()
			testRover.print();
			continue;
		}

		if (comm.front() == 'C') {
			testRover.clear();
			continue;
		}

		commands >> data;

		switch (comm.front()) {
			case 'S':
				testRover.setSMILE(data);
				break;
			case 'R':
				testRover.read(stoi(data)); // stoi is provided above
				break;
			case 'J':
				testRover.join(data);
				break;
			case 'T':
				cout << testRover.test(data) << endl;
				break;
			case 'F':
				cout << data << " "; // MyString: operator<<()
				if (testRover.find(data)) {
					cout << "was found" << endl;
				} else {
					cout << "was not found" << endl;
				}
				break;
			default:
				continue;
		}
	}
	
	return 0;
}
