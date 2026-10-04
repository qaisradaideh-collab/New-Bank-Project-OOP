
#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{

public:

	template <typename UnkownDataType> 
		
	static bool	IsNumberBetween(UnkownDataType Number, UnkownDataType From, UnkownDataType To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}


	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	template <typename UnkownDataType>

	static UnkownDataType ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		UnkownDataType Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	template <typename UnkownDataType>

	static short ReadNumberBetween(UnkownDataType From, UnkownDataType To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		UnkownDataType Number = ReadNumber<UnkownDataType>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<UnkownDataType>();
		}
		return Number;
	}


	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}


};