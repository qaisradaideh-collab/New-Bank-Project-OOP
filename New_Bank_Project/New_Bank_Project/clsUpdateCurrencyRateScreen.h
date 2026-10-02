#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();
		return CurrencyCode;


	}

	static float _ReadRate()
	{
		float NewRate = 0;

		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;


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


	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t Update Currency Rate Screen");

		string CurrencyCode = _ReadCurrencyCode();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";

			 CurrencyCode = _ReadCurrencyCode();

		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		char Answer = 'n';
		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
		cin >> Answer;


		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Currency Rate: \n";
			cout << "-----------------------\n";

			float NewRate = _ReadRate();
			Currency.UpdateRate(NewRate);

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);

		}
	}


};

