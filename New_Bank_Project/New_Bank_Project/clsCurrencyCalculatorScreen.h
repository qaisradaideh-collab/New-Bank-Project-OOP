#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static string _ReadCurrencyCode()
    {

        string Code = clsInputValidate::ReadString();
        return Code;

    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }

    static clsCurrency _GetCurrency( string CurrencyMessage)
    {
        cout <<  endl << CurrencyMessage << endl;

        string Code1 = _ReadCurrencyCode();
        while (!clsCurrency::IsCurrencyExist(Code1))
        {
            cout << endl << CurrencyMessage << endl;
            Code1 = _ReadCurrencyCode();
        }
        clsCurrency Currency = clsCurrency::FindByCode(Code1);

        return Currency;

    }

    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");
        float AmountAfter = 0;
        AmountAfter = Currency1.ConvertCurrencyToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountAfter << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }
        else
        {
 
           _PrintCurrencyCard(Currency2, "Convert from USD To:");


           AmountAfter = Currency1.ConvertToAnotherCurrency(Amount, Currency2);


            cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountAfter << " " << Currency2.CurrencyCode();


        }


    }

public:


    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tConvert Currencies Screen");

            clsCurrency Currency1 = _GetCurrency("Please Enter Currency 1 Code:");
        
            clsCurrency Currency2 = _GetCurrency("Please Enter Currency 2 Code:");

            float Amount = 0;
            Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, Currency1, Currency2);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;


        }

    }


};
