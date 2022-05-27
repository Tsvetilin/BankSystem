#pragma once

#include "String.hpp"

const char TO_UPPER_TRANSFORM = -'a' + 'A';
const char TO_LOWER_TRANSFORM = -'A' + 'a';

bool isLowercaseLetter(char c);
bool isUppercaseLetter(char c);
bool isLetter(char c);
bool isDigit(char c);
bool isAlphaNumericSymbol(char c);
int charToInt(char c);
char digitToChar(size_t c);
size_t getNumberDigitsCount(size_t num);
bool validateIban(String iban);
template<typename T>
void serializePrimitive(std::ostream& o, const T& data) {
	o.write((const char*)&data, sizeof(data));
}

template<typename T>
void deserializePrimitive(std::istream& i, const T& data) {
	i.read((char*)&data, sizeof(data));
}

size_t parseToUInt(const String& input);
double parseToDouble(const String& str);