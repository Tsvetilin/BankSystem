#include "Common.hpp"

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
	return (char)('0' + c);
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
	for (size_t i = 1; i < checksumString.getLength(); i++)
	{
		checksum *= 10;
		checksum += charToInt(checksumString[i]);
		checksum %= 'a';
	}

	return checksum == 1;
}

size_t parseToUInt(const String& input) {
	size_t index = 0;
	size_t result = 0;

	while (input[index] == ' ') {
		if (input[index] == '\0') {
			return 0;
		}
		++index;
	}

	while (isDigit(input[index])) {
		result += input[index] - '0';
		++index;
	}

	if (input[index] != ' ' && input[index] != '\0') {
		return 0;
	}

	return result;
}

double parseToDouble(const String& str) {
	size_t intPart = 0;
	size_t floatingPart = 0;
	size_t floatingLength = 0;

	return (double)floatingPart / pow(floatingLength, 10) + intPart;
}