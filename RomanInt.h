#pragma once

#include <iostream>
using namespace std;

// Define the Letter Values
#define ROMAN_M	1000
#define	ROMAN_D	 500
#define ROMAN_C	 100
#define ROMAN_L	  50
#define	ROMAN_X	  10
#define ROMAN_V	   5
#define ROMAN_I	   1

class CRomanInt
{
public:
	CRomanInt(void);
	~CRomanInt(void);
private:
	CString m_szRomanNum;
	void intToRoman(int nValue);
	bool isRoman(CString szString);

public:
	CRomanInt(CString szValue);
	CRomanInt(int nValue);
	
	CString getRoman(void);
	int getIntValue(void);
	bool setRoman(int nValue);
	bool setRoman(CString szRomanString);

	// Overloaded Operators
	friend ostream& operator<<( ostream& os, CRomanInt &myRoman );
	friend istream& operator>>( istream& is, CRomanInt &myRoman );
	CRomanInt operator++(int);
	CRomanInt operator--(int);
	CString operator+(CRomanInt&);
	CString operator-(CRomanInt&);
};
