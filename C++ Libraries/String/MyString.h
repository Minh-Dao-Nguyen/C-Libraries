// TODO: Implement this header file
#ifndef _MYSTRING_H
#define _MYSTRING_H
#include <iostream>

using std::ostream; 
class MyString {
private: 
    size_t _size; 
    size_t _length; 
    size_t _capacity; 
    char* Cstring; 
public:
    //constructor
    MyString(); 
    MyString(const MyString& str); 
    MyString(const char* c);
    //destructor
    ~MyString(); 
    //resize
    void resize(size_t n); 
    //capacity
    size_t capacity() const;
    size_t size() const; //size of current number of elemtns in the array
    size_t length() const; 
    const char* data() const; //This function returns the internal character array’s reference because it is actually a c-string on the inside, so remember the null terminator
    bool empty() const; //Returns whether the string is empty (i.e. whether its length is 0).
    const char& front() const; //Returns a reference to the first character of the string.
    const char& at(size_t pos) const; //Returns a reference to the character at position pos in the string.
    void clear(); //Erases the contents of the string, which becomes an empty string (with a length of 0 characters).
    MyString& operator=(const MyString& str); 
    MyString& operator+= (const MyString& str);
    size_t find (const MyString& str, size_t pos = 0 ) const; //Searches the string for the first occurrence of the sequence specified by its arguments.
};

ostream& operator<< (ostream& os, const MyString& str); //Inserts the sequence of characters that conforms value of str into os.

bool operator== (const MyString& lhs, const MyString& rhs);
MyString operator+ (const MyString& lhs, const MyString& rhs);
#endif