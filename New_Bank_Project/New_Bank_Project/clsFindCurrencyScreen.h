#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{

private:

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		cout << "\nEnter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();
		return CurrencyCode;


	}

	static string _ReadCountryName()
	{
		string CountryName = "";
		cout << "\nEnter Country Name: ";
		CountryName = clsInputValidate::ReadString();

		return CountryName;


	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}


public:


	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");

		short Answer = 0;
		cout << "\nFind By: [1] Code or [2] Country ? ";
		Answer = clsInputValidate::ReadShortNumberBetween(1, 2);


		if (Answer == 1)
		{
			string CurrencyCode;
			CurrencyCode = _ReadCurrencyCode();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);

		}
		else
		{
			string Country;
			Country = _ReadCountryName();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}


	}


};

