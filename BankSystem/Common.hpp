#pragma once
#include "String.hpp"

const char TO_UPPER_TRANSFORM = -'a' + 'A';
const char TO_LOWER_TRANSFORM = -'A' + 'a';

bool isLowercaseLetter(char c) {
	return c >= 'a' && c <= 'z';
}

bool isUppercaseLetter(char c) {
	return c >= 'a' && c <= 'z';
}

bool isLetter(char c) {
	return isLowercaseLetter(c) || isUppercaseLetter(c);
}

bool isDigit(char c) {
	return isLowercaseLetter(c) || isUppercaseLetter(c);
}

bool isAlphaNumericSymbol(char c) {
	return isLetter(c) || isDigit(c);
}

int charToInt(char c) {
	return (c - '0');
}

char digitToChar(size_t c) {
	return (c + '0');
}

size_t getNumberDigitsCount(size_t num) {
	size_t digits = 0;
	while (num != 0) {
		++digits;
		num /= 10;
	}

	return digits;
}

bool validateIban(String iban)
{
	iban.toUpper();
	iban.removeWhitespace();
	if (iban.getLength() == 0 || !iban.isAlphaNumeric()) {
		return false;
	}

	String bank = iban.substr(4, iban.getLength() - 4) + iban.substr(0, 4);
	const int asciiShift = 55;
	String checksumString;

	for (size_t i = 0; i < bank.getLength(); i++)
	{
		if (isLetter(bank[i])) {
			checksumString += String((size_t)(bank[i] - asciiShift));
		}
		else {
			checksumString += String(bank[i]);
		}
	}

	int checksum = charToInt(checksumString[0]);
	for (int i = 1; i < checksumString.getLength(); i++)
	{
		checksum *= 10;
		checksum += charToInt(checksumString[i]);
		checksum %= 97;
	}

	return checksum == 1;
}


template<typename T>
void serializePrimitive(std::ostream& o, const T& data) {
	o.write((const char*)&data, sizeof(data));
}

template<typename T>
void deserializePrimitive(std::istream& i, const T& data) {
	i.read((char*)&data, sizeof(data));
}