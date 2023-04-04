#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"

myString::myString() : buffer(nullptr), size(0), capacity(STRING_BUFFER) {
    buffer = new char[capacity];
    buffer[0] = '\0';
}

myString::myString(const char* str) : buffer(nullptr), size(0), capacity(STRING_BUFFER) {
    size_t strLength = strlen(str);
    if (strLength > capacity) {
        capacity = strLength + STRING_BUFFER;
    }
    buffer = new char[capacity];
    strcpy(buffer, str);
    size = strLength;
}

myString::myString(const myString& other) : buffer(nullptr), size(0), capacity(other.size + STRING_BUFFER) {
    *this = other;
}

myString::~myString() {
    delete[] buffer;
}


myString& myString::operator=(const myString& other) {
    size = other.size;
    capacity = other.capacity;
    delete[] buffer;
    buffer = new char[capacity];
    strcpy(buffer, other.buffer);
    return *this;
}

myString& myString::operator+=(const myString& other) {
    size_t newsize = size + other.size;
    if (newsize + 1 > capacity) {
        capacity = newsize + STRING_BUFFER;
        char* newBuffer = new char[capacity];
        strcpy(newBuffer, buffer);
        delete[] buffer;
        buffer = newBuffer;
    }
    strcat(buffer, other.buffer);
    size = newsize;
    return *this;
}

myString& myString::operator+=(const char& character) {
    if (size + 2 > capacity) {
        capacity += STRING_BUFFER;
        char* newBuffer = new char[capacity];
        strcpy(newBuffer, buffer);
        delete[] buffer;
        buffer = newBuffer;
    }
    buffer[size++] = character;
    buffer[size] = '\0';
    return *this;
}

myString& myString::operator+=(const int& number) {
    char numberInChar[INT_TO_CHAR_BUFFER];
    sprintf(numberInChar, "%d", number);

    *this += numberInChar;

    return *this;
}

myString& myString::operator+=(const char* str) {
    size_t strLength = strlen(str);
    if (size + strLength + 1 > capacity) {
        capacity = size + strLength + STRING_BUFFER;
        char* newBuffer = new char[capacity];
        strcpy(newBuffer, buffer);
        delete[] buffer;
        buffer = newBuffer;
    }
    strcat(buffer, str);
    size += strLength;
    return *this;
}

bool myString::operator!=(myString& stringObjectToCompare) {
    return strcmp(buffer, stringObjectToCompare.buffer);
}

bool myString::operator==(const char* arr) {
    return strcmp(buffer, arr) == 0;
}

bool myString::operator==(myString& str) {
    return strcmp(buffer, str.buffer) == 0;
}

size_t myString::length() const {
    return size;
}

const char* myString::str() const {
    return buffer;
}
const char myString::operator[](const int index) {
    return this->buffer[index];
}

std::ostream& operator<<(std::ostream& cout, const myString& obj) {
    cout << obj.str();
    return cout;
}

void myString::removeSpacesFromBeginningAndEndFromString() {
    myString newStr = { "" };
    int start = 0, end = length() - 1;

    for (size_t i = 0; i < length(); i++) {
        if (buffer[i] > ' ') { start = i; break; };
    }
    for (int i = length() - 1; i >= 0; i--) {
        if (buffer[i] > ' ') { end = i; break; };
    }
    for (int i = start; i <= end; i++) {
        newStr += buffer[i];
    }
    *this = newStr;
}

int const myString::amountOfComasInString() {
    int counter = 0;
    for (size_t i = 0; i < length(); i++) {
        if (buffer[i] == ',') counter++;
    }
    return counter;
}