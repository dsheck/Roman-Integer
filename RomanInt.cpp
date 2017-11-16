/********************************************************
 *				CRomanInt Implementation				*
 *					by Don Sheck						*
 *														*
 *	Function: Keeps track of roman numerals and converts*
 *	integers to its roman numeral counterpart			*
 ********************************************************/

#include "StdAfx.h"
#include ".\romanint.h"

/********************************************************
 *		CRomanInt Constructors							*
 *														*
 *	Decription: The constructors will accept an int,	*
 *	a CString or nothing at all and create a CRomanInt	*
 *	object.												*
 *														*
 *	History:											*
 *	Date			Author			Notes				*
 *	---------------------------------------------------	*
 *	09/27/2003		Don Sheck		Initial Spec		*
 *	09/28/2003		Don Sheck		Added the CString	*
 *										Constructor		*
 ********************************************************/

CRomanInt::CRomanInt(void)
: m_szRomanNum(_T("I"))
{
}

CRomanInt::CRomanInt(CString szValue)
{
	if( isRoman(szValue) )
		m_szRomanNum = szValue;
	else
		m_szRomanNum = "ERROR";
}

CRomanInt::CRomanInt(int nValue)
{
	intToRoman(nValue);
}

// Default Destructor
CRomanInt::~CRomanInt(void)
{
}

/****************************************************************************
 *		intToRoman															*
 *																			*
 *	Decription: Converts an integer to a roman numeral						*
 *																			*
 *	IN: nValue is the integer to convert									*
 *	OUT: N/A																*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 *	10/01/2003		Don				Fixed bugs that caused incorrect digits	*
 ****************************************************************************/

void CRomanInt::intToRoman(int nValue)
{
	int nLeftOver = nValue, nDigit, nCurrDivisor = ROMAN_M;
	nDigit = (int)( nLeftOver / nCurrDivisor );

	m_szRomanNum.Empty();

	while( nLeftOver != 0 )
	{
		int nDigCopy = nDigit;
		// Print out Roman Numerals
		while(nDigCopy != 0)
		{
			if(nCurrDivisor == ROMAN_M)
			{
				for(int i = 0; i < nDigit; i++)
					m_szRomanNum.Append("M");
				nDigCopy = 0;
			}
			else
			{
				if( nDigCopy == 9 )
				{
					// This is a Special Case
					switch(nCurrDivisor) {
						case ROMAN_D:
						case ROMAN_C: m_szRomanNum.Append("CM"); break;
						case ROMAN_L: 
						case ROMAN_X: m_szRomanNum.Append("XC"); break;
						case ROMAN_V: 
						case ROMAN_I: m_szRomanNum.Append("IX"); break;
					}
					nDigCopy -= 9;
				}
				else if( nDigCopy > 4 )
				{
					switch(nCurrDivisor) {
						case ROMAN_D: 
						case ROMAN_C: m_szRomanNum.Append("D"); break;
						case ROMAN_L: 
						case ROMAN_X: m_szRomanNum.Append("L"); break;
						case ROMAN_V: 
						case ROMAN_I: m_szRomanNum.Append("V"); break;
					}
					nDigCopy -= 5;
				}
				else
				{
					if(nDigCopy == 4)
					{
						// This is a Special Case
						switch(nCurrDivisor) {
							case ROMAN_D:
							case ROMAN_C: m_szRomanNum.Append("CD"); break;
							case ROMAN_L: 
							case ROMAN_X: m_szRomanNum.Append("XL"); break;
							case ROMAN_V: 
							case ROMAN_I: m_szRomanNum.Append("IV"); break;
						}
						nDigCopy -= 4;
					}
					else
					{
						for(int i = 0; i < nDigCopy; i++)
						{
							switch(nCurrDivisor) {
								case ROMAN_D: m_szRomanNum.Append("D"); break;
								case ROMAN_C: m_szRomanNum.Append("C"); break;
								case ROMAN_L: m_szRomanNum.Append("L"); break;
								case ROMAN_X: m_szRomanNum.Append("X"); break;
								case ROMAN_V: m_szRomanNum.Append("V"); break;
								case ROMAN_I: m_szRomanNum.Append("I"); break;
							}
						}
						nDigCopy = 0;
					}
					
				}
			}
		}

		// Update Loop Control Variables
		nLeftOver -= (int)(nDigit * nCurrDivisor);
		nCurrDivisor /= 10;
		if(nCurrDivisor > 0)
			nDigit = (int)( nLeftOver / nCurrDivisor );
	}
}

/****************************************************************************
 *		getRoman															*
 *																			*
 *	Decription: Returns the Roman Numeral as a CString						*
 *																			*
 *	IN: N/A																	*
 *	OUT: Returns a roman numeral as a CString								*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 ****************************************************************************/

CString CRomanInt::getRoman(void)
{
	return m_szRomanNum;
}

/****************************************************************************
 *		Overloaded operator<<												*
 *																			*
 *	Decription: Allows the roman numeral to be displayed with cout			*
 *																			*
 *	IN: os is the ostream (ie: cout) and CRomanInt is a reference to the	*
 *		object that needs to be displayed.									*
 *	OUT: Returns the ostream object to allow cout << roman1 << roman2;		*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 ****************************************************************************/

ostream& operator<<( ostream& os, CRomanInt &myRoman )
{
	os << myRoman.m_szRomanNum;
	return os;
}

/****************************************************************************
 *		Overloaded operator>>												*
 *																			*
 *	Decription: Allows Roman numerals to be read from cin					*
 *																			*
 *	IN: is is the istream (cin) and myRoman is a reference to the roman		*
 *		numeral to read into												*
 *	OUT: returns the istream												*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 *	10/04/2003		Don				Took out the ability to read numbers	*
 ****************************************************************************/

istream& operator>>( istream &is, CRomanInt &myRoman )
{
	char* temp = new char[256];
	int nValue = 0;
	bool bAlpha = true;

	is >> temp;
	
	CString theString(temp);
	if( myRoman.isRoman(theString) )
		myRoman.m_szRomanNum = theString;

	return is;
}

/****************************************************************************
 *		isRoman																*
 *																			*
 *	Decription: Returns true if the inputted string is a roman numeral.		*
 *		Returns false if the numeral is improperly syntaxed or wrong.		*
 *																			*
 *	IN: szString is the string to check										*
 *	OUT: Returns true if szString is a roman numeral						*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/28/2003		Don Sheck		Initial Spec							*
 *	10/07/2003		Don				Refinements to check the order			*
 ****************************************************************************/

bool CRomanInt::isRoman(CString szString)
{
	bool bRValue = true;
	char cLast = szString[0];
	int nCharCount = 0;

	for(int i = 0; i < szString.GetLength(); i++)
	{
		// see if the character at position i is one of the allowed values
		if( szString[i] == 'M' || szString[i] == 'D' ||
			szString[i] == 'C' || szString[i] == 'L' ||
			szString[i] == 'X' || szString[i] == 'V' || szString[i] == 'I' )
		{
			// Check to see if the current character is the same as the last character
			if(szString[i] == cLast)
			{
				nCharCount++;
				// if the character isn't an M, we need to check to make sure there are only the correct multiples
				if(szString[i] != 'M')
				{
					if( (szString[i] == 'D' || szString[i] == 'L' || szString[i] == 'V') 
						&& nCharCount >= 2)
						return false;
					else if( (szString[i] == 'C' || szString[i] == 'X' || szString[i] == 'I') 
						&& nCharCount >= 4)
						return false;
				}
			}
			else
			{
				// new character, reset the variables to reflect this
				cLast = szString[i];
				nCharCount = 1;
			}
			bRValue = true;
		}
		else	// character was not an allowed value
			return false;
	}
	return bRValue;
}

/****************************************************************************
 *		getIntValue															*
 *																			*
 *	Decription: Returns the integer value of a roman numeral				*
 *																			*
 *	IN: N/A																	*
 *	OUT: Returns the Roman Numeral as an integer							*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 *	09/27/2003		Don				Added ability to check for IX, CD, etc.	*
 ****************************************************************************/

int CRomanInt::getIntValue(void)
{
	int nValue = 0;

	// Fatal Error in Constructor
	if( m_szRomanNum == "ERROR" )
	{
		return -1;
	}

	// we need to parse the string and compute the integer value
	for(int i = 0; i < m_szRomanNum.GetLength(); i++)
	{
		// Add our Ms
		if( m_szRomanNum[i] == 'M' )
			nValue += ROMAN_M;
		
		// Add the Ds
		if( m_szRomanNum[i] == 'D' )
			nValue+= ROMAN_D;

		// C is a special case
		if( m_szRomanNum[i] == 'C' )
		{
			// if next num is an M, we have 900
			if( m_szRomanNum[i+1] == 'M' )
			{
				nValue += ROMAN_M - ROMAN_C;
				i++;
			}
			else if( m_szRomanNum[i+1] == 'D' ) // if next num is D, we have 400
			{
				nValue += ROMAN_D - ROMAN_C;
				i++;
			}
			else
				nValue += ROMAN_C; // else we have 100
		}

		if( m_szRomanNum[i] == 'L' )
			nValue += ROMAN_L;

		// X is a Special Case
		if( m_szRomanNum[i] == 'X' )
		{
			if( m_szRomanNum[i+1] == 'C' ) // if next num is C, we have 90
			{
				nValue += ROMAN_C - ROMAN_X;
				i++;
			}
			else if( m_szRomanNum[i+1] == 'L' ) // if next num is L, we have 40
			{
				nValue += ROMAN_L - ROMAN_X;
				i++;
			}
			else
				nValue += ROMAN_X;	// else we have 10
		}

		if( m_szRomanNum[i] == 'V' )
			nValue += ROMAN_V;
		
		// I is a Special Case
		if( m_szRomanNum[i] == 'I' )
		{
			if( m_szRomanNum[i+1] == 'X' ) // if next num is X, we have 9
			{
				nValue += ROMAN_X - ROMAN_I;
				i++;
			}
			else if( m_szRomanNum[i+1] == 'V' ) // if next num is V, we have 4
			{
				nValue += ROMAN_V - ROMAN_I;
				i++;
			}
			else
				nValue += ROMAN_I;	// else we have 1
		}
	}
	return nValue;
}

/****************************************************************************
 *		setRoman															*
 *																			*
 *	Decription: Sets the roman numeral to the provided integer value		*
 *																			*
 *	IN: nValue is the integer set the roman numeral too						*
 *	OUT: N/A																*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/27/2003		Don Sheck		Initial Spec							*
 ****************************************************************************/

bool CRomanInt::setRoman(int nValue)
{
	intToRoman(nValue);
	return true;
}

/****************************************************************************
 *		setRoman (Overloaded)												*
 *																			*
 *	Decription: Sets the roman numeral to the supplied CString				*
 *																			*
 *	IN: szRomanString is the string to set the roman numeral to				*
 *	OUT: Returns true if it worked, false if it failed						*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	09/28/2003		Don Sheck		Initial Spec							*
 ****************************************************************************/

bool CRomanInt::setRoman(CString szRomanString)
{
	if( isRoman( szRomanString ) )
	{
		m_szRomanNum = szRomanString;
		return true;
	}
	else
		return false;
}

/****************************************************************************
 *		Overloaded addition/subtraction operators							*
 *																			*
 *	Decription: Adds or subtracts CRomanInts from CRomanInts				*
 *																			*
 *	IN: other is a reference to other CRomanInts							*
 *	OUT: N/A																*
 *																			*
 *	History:																*
 *	Date			Author			Notes									*
 *	---------------------------------------------------						*
 *	10/04/2003		Don Sheck		Initial Spec							*
 ****************************************************************************/

CRomanInt CRomanInt::operator++( int )
{
	CRomanInt temp = *this; // save instance of this
	int nCurrVal = getIntValue(); // get the value of this
	
	setRoman(nCurrVal + 1); // increase the value by 1
	
	return temp;
}

CRomanInt CRomanInt::operator--( int )
{
	CRomanInt temp = *this; // save instance of this
	int nCurrVal = getIntValue(); // get the value of this
	
	setRoman(nCurrVal - 1); // decrease the value by 1
	
	return temp;
}

CString CRomanInt::operator+(CRomanInt& other)
{
	int nTempValue;
	CRomanInt temp;

	nTempValue = getIntValue() + other.getIntValue(); // add the values together
	
	temp.setRoman(nTempValue); // set this roman numerals value to the temporary
	return temp.getRoman();
}

CString CRomanInt::operator-(CRomanInt& other)
{
	int nTempValue;
	CRomanInt temp;
	
	nTempValue = getIntValue() - other.getIntValue(); // subtract the two values
	
	temp.setRoman(nTempValue); // set this roman numeral's value to the temporary
	return temp.getRoman();
}
