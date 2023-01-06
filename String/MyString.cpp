// TODO: Implement this source file
#include "MyString.h"

#include <iostream>
#include <stdexcept>

using std::cout, std::endl;
using std::ofstream; 

MyString::MyString()
    :_size(0), _length(0), _capacity(1), Cstring(new char[1]) 
    {
        Cstring[0] = '\0';
    }

MyString::MyString(const MyString& str)
    : _size(str._size), _length(str._length), _capacity(str._capacity), Cstring(new char[str._size + 1])
{
    for(size_t i = 0; i < _size; i++){
        Cstring[i] = str.Cstring[i]; 
    }
    Cstring[_size] = '\0';
}

MyString::MyString(const char* c){
    size_t i = 0;
    while(c[i] != '\0'){
        i++; 
    }
    _size = i; 
    _length = _size; 
    _capacity = _size + 1; 
    Cstring = new char[_size + 1]; // plus one because of null pointer
    for( size_t i = 0; i < _size; i++){ 
        Cstring[i] = c[i]; 
    }
    Cstring[_size] = '\0';
}
MyString::~MyString(){
    delete[] Cstring; 
}
void MyString::resize(size_t n){
    _size = n;
}

size_t MyString::capacity() const{
    return _capacity; 
}
//size
//size of current number of elemtns in the array
size_t MyString::size()const {
    return _size; 
}

size_t MyString::length()const{
    return _length; 
}
//data
//This function returns the internal character array’s reference because it is actually a c-string on the inside, so remember the null terminator
const char* MyString::data() const{
    return Cstring; 
}

//empty
//Returns whether the string is empty (i.e. whether its length is 0).
bool MyString::empty() const{
    if(_length == 0 || _size == 0 || Cstring[0] == '\0'){
        return true; 
    }
    else{
        return false; 
    }
}

//front
//Returns a reference to the first character of the string.
const char& MyString::front() const{  
    return Cstring[0];
}

//at
//Returns a reference to the character at position pos in the string.
const char& MyString::at(size_t pos) const{
    if(pos >= _size){
        throw std::out_of_range("out of range");
    }
    char& element = Cstring[pos];
    return element; 
}

//clear
//Erases the contents of the string, which becomes an empty string (with a length of 0 characters).
void MyString::clear(){
    _size = 0; 
    _length = 0; 
    _capacity = 0; 
    delete[] Cstring; 
    Cstring = new char[1];
    Cstring[0] = '\0'; 
}

//operartor << 
//Inserts the sequence of characters that conforms value of str into os.
ostream& operator<<(std::ostream& os, const MyString& str){
    for(size_t i = 0; i < str.size(); i++){
        os << str.at(i);
    }
    return os; 
}

//operator =
MyString& MyString::operator=(const MyString& str){
    if(str.Cstring == Cstring){ 
        return *this; 
    }
    else{
        delete[] Cstring;
        Cstring = new char[str._size + 1];
        for(size_t i = 0; i < str._size; i++) {
            Cstring[i] = str.Cstring[i]; 
        }
        Cstring[str._size] = '\0';
        _size = str._size; 
        _capacity = str._capacity; 
        _length = str._length; 

    }
    return *this; 
}

//operator += 
MyString& MyString::operator+= (const MyString& str){
    size_t oldSize = _size;  
    _size = _size + str._size; 
    _capacity = _capacity +str._capacity; 
    _length = _size;
    char* temp = new char[_capacity]{};
    //get the old string
    for(size_t i = 0; i < oldSize; i++){
        temp[i] = Cstring[i];
    }
    //add in the new string
    int y = 0; 
    for(size_t i = oldSize; i < _size; i++){
        temp[i] = str.Cstring[y]; 
        y++;
    }
    temp[_size] = '\0';
    delete[] Cstring; 
    Cstring = temp;

    return *this; 
}

//find
//Searches the string for the first occurrence of the sequence specified by its arguments.
size_t MyString::find(const MyString& str, size_t pos ) const{
    size_t result = 0; 
    size_t tempSize = 0; 
    //start first loop 
    for(size_t i = pos; i < _size; i++){
        //start second loop
        if(Cstring[i] == str.Cstring[tempSize]){
            tempSize++;
            if(tempSize == str._size){
                result = i - tempSize + 1;
                return result; 
            }
        }
    }
    return -1; 
}
     //if you have an array that is 1 2 3 4, if you have a nested for loop, just don't assume 

bool operator== (const MyString& lhs, const MyString& rhs){
    bool equal = true; 
    if(lhs.size() == rhs.size()){
        for(size_t i = 0; i < lhs.size(); i++){
            if(lhs.at(i) != rhs.at(i)){
                equal = false; 
                break; 
            }
        }
    }
    else{
        return false; 
        
    }
    return equal; 
}
MyString operator+ (const MyString& lhs, const MyString& rhs){
    MyString newString = lhs;
    newString += rhs;
    return newString;
}