#pragma once
#include "String.hpp"

const size_t DAYS_OF_MONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const size_t EPOCH_START_YEAR = 1970;
const size_t DAYS_IN_YEAR = 365;
const size_t HOURS_IN_DAY = 24;
const size_t MINUETES_IN_HOUR = 60;
const size_t SECONDS_IN_MINUTE = 60;
const size_t SECONDS_IN_HOUR = MINUETES_IN_HOUR * SECONDS_IN_MINUTE; 

const char TO_UPPER_TRANSFORM = -'a' + 'A';
const char TO_LOWER_TRANSFORM = -'A' + 'a';

const size_t DOUBLE_STRING_PRECISION = 1000;

bool isLowercaseLetter(char c);
bool isUppercaseLetter(char c);
bool isLetter(char c);
bool isDigit(char c);
bool isAlphaNumericSymbol(char c);

size_t parseToUInt(const String& input);
double parseToDouble(const String& str);
String doubleToString(double d);

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

