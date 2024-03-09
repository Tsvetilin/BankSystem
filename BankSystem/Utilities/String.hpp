#pragma once
#include "../Contracts/ISerializable.hpp"
#include "../Contracts/IPrintable.hpp"
#include <iostream>

class String : public ISerializable, public IPrintable{
	char* string;
	size_t length;

	void setString(const char* const);

public:
	String() : String(nullptr) {}
	String(const char* const);
	explicit String(char);
	explicit String(size_t);
	String(const String&);

	String& operator=(const String&);
	String& operator=(const char* const);

	String(String&&) noexcept;
	String& operator=(String&&) noexcept;

	~String();

	const char* c_str() const;
	size_t getLength() const;
	String substr(size_t, size_t) const;
	int indexOf(char c) const;
	bool isAlphaNumeric() const;

	String& trim();
	String& removeWhitespace();
	String& toUpper();
	String& toLower();
	String& concat(const String&);

	String& operator+=(const String&);
	String operator+(const String&) const;

	bool operator== (const String&) const;
	bool operator< (const String&) const;
	bool operator> (const String&) const;
	bool operator>= (const String&) const;
	bool operator<= (const String&) const;
	bool operator!= (const String&) const;

	const char& operator[](size_t) const;

	virtual void print(std::ostream&) const override;

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);

	friend void getline(std::istream&, String&);

	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
};

String getline(std::istream&);