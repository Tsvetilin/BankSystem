#pragma warning(disable:4996)

#include "String.hpp"
#include "Common.hpp"
#include <iostream>

const size_t BUFF_LENGTH = 4096;

String::String(const char* data) : string(nullptr)
{
	if (data == nullptr)
	{
		setString("");
		return;
	}

	setString(data);
}

String::String(const String& other) : string(nullptr)
{
	setString(other.string);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		setString(other.string);
	}
	return *this;
}

String& String::operator=(const char* const data)
{
	setString(data);
	return *this;
}

String::~String()
{
	delete[] string;
}


size_t String::getLength() const
{
	return length;
}

String& String::concat(const String& other)
{
	length += other.length;

	char* temp = new char[length + 1];
	strcpy(temp, string);
	strcat(temp, other.string);

	delete[] string;
	string = temp;
	return *this;
}

String String::substr(size_t index, size_t length = 0) const {
	if (index + length > this->length) {
		length = this->length - index;
	}
	else if (index + length == this->length) {
		return String(string + index);
	}

	char* data = new char[length + 1];
	for (size_t i = 0; i < length; i++)
	{
		data[i] = string[i + index];
	}

	data[length] = '\0';

	String result(data);

	delete[] data;
	return result;
}

const char* String::c_str() const
{
	return string;
}

String& String::operator+=(const String& other)
{
	concat(other);
	return *this;
}

String String::operator+(const String& other) const
{
	String left(*this);
	left += other;
	return left;
}

std::ostream& operator<<(std::ostream& o, const String& string)
{
	string.print(o);
	return o;
}

void String::print(std::ostream& stream) const {
	stream << string;
}

std::istream& operator>>(std::istream& i, String& string)
{
	delete[] string.string;
	char buff[BUFF_LENGTH];
	i >> buff;
	string.setString(buff);
	return i;
}

bool String::operator==(const String& other) const
{
	return strcmp(string, other.c_str()) == 0;
}

bool String::operator>(const String& other) const
{
	return strcmp(string, other.c_str()) > 0;
}
bool String::operator>=(const String& other) const
{
	return strcmp(string, other.c_str()) >= 0;
}

bool String::operator<(const String& other) const
{
	return strcmp(string, other.c_str()) < 0;
}

bool String::operator<=(const String& other) const
{
	return strcmp(string, other.c_str()) <= 0;
}

bool String::operator!=(const String& other) const
{
	return strcmp(string, other.c_str()) != 0;
}

void getline(std::istream& i, String& str) {
	char buff[BUFF_LENGTH];
	i.getline(buff, BUFF_LENGTH);
	str.setString(buff);
}

String getline(std::istream& i) {
	char buff[BUFF_LENGTH];
	i.getline(buff, BUFF_LENGTH);
	return String(buff);
}

void String::setString(const char* const str) {
	delete[] string;
	length = strlen(str);
	string = new char[length + 1];
	strcpy(string, str);
}

void String::serialize(std::ostream& stream) const {
	stream.write((const char*)&length, sizeof(length));
	stream.write((const char*)string, length);
}

void String::deserialize(std::istream& stream) {
	stream.read((char*)&length, sizeof(length));
	char* temp = new char[length + 1];
	stream.read(temp, length);
	temp[length] = '\0';
	delete[] string;
	string = temp;
}

const char& String::operator[](size_t index) const {
	if (index > length) {
		throw "Index out of range exception!";
	}

	return string[index];
}

String& String::trim() {
	size_t leadingSpaces = 0;
	while (string[leadingSpaces] == ' ') {
		++leadingSpaces;
	}

	size_t followingSpaces = 0;
	while (string[length - 1 - followingSpaces] == ' ') {
		++followingSpaces;
	}

	*this = substr(leadingSpaces, length - leadingSpaces - followingSpaces);

	return *this;
}

int String::indexOf(char c) const {
	for (size_t i = 0; i < length; i++)
	{
		if (string[i] == c) {
			return i;
		}
	}

	return -1;
}


String::String(String&& other) noexcept {
	string = other.string;
	length = other.length;
	other.string = nullptr;
}

String& String::operator=(String&& other) noexcept {
	delete[] string;
	string = other.string;
	length = other.length;
	other.string = nullptr;

	return *this;
}

String& String::removeWhitespace() {
	size_t countSpaces = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (string[i] == ' ') {
			++countSpaces;
		}
	}

	if (countSpaces == 0) {
		return *this;
	}

	char* newString = new char[length + 1 - countSpaces];
	size_t ind = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (string[i] != ' ') {
			newString[ind++] = string[i];
		}
	}

	newString[length - countSpaces] = '\0';

	delete[] string;
	string = newString;
	return *this;
}

String& String::toUpper() {
	for (size_t i = 0; i < length; i++)
	{
		if (isLowercaseLetter(string[i])) {
			string[i] += TO_UPPER_TRANSFORM;
		}
	}
	return *this;
}

String& String::toLower() {
	for (size_t i = 0; i < length; i++)
	{
		if (isUppercaseLetter(string[i])) {
			string[i] += TO_LOWER_TRANSFORM;
		}
	}
	return *this;
}

bool String::isAlphaNumeric() const {
	for (size_t i = 0; i < length; i++)
	{
		if (!isAlphaNumericSymbol(string[i])) {
			return false;
		}
	}

	return true;
}

String::String(char c) {
	length = 1;
	string = new char[length + 1];
	string[0] = c;
	string[1] = '\0';
}

String::String(size_t num) :string(nullptr) {
	if (num == 0) {
		setString("0");
		return;
	}

	length = getNumberDigitsCount(num);
	string = new char[length + 1];
	size_t i = length - 1;
	while (num != 0) {
		string[i] = digitToChar(num % 10);
		num /= 10;
		--i;
	}

	string[length] = '\0';
}