#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:\n";
		cout << "\n-------------------------\n";
		cout << endl << "Full Name   :   " << Client.FullName();
		cout << endl << "Acc. Number :   " << Client.AccountNumber();
		cout << endl << "Balance     :   " << Client.AccountBalance;
		cout << "\n-------------------------\n";

	}

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient)
	{
		float Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

	static void _PerformTransfer()
	{
		string AccNum = _ReadAccountNumber();
		clsBankClient ClientFrom = clsBankClient::Find(AccNum);
		_PrintClientCard(ClientFrom);



		 AccNum = _ReadAccountNumber();
		clsBankClient ClientTo = clsBankClient::Find(AccNum);
		_PrintClientCard(ClientTo);



		float TransferAmount = 0;
		TransferAmount = ReadAmount(ClientFrom);


		cout << "\nAre you sure you want to perform this Opertion? Y/N? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (ClientFrom.Transfer(TransferAmount,ClientTo))
			{
				cout << "\nTransfer Done Successfully\n";
				_PrintClientCard(ClientFrom);
				_PrintClientCard(ClientTo);

			}
			else
			{
				cout << "\nOperation Failed.\n";

			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}




	}


public:


	static void ShowTransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");
		_PerformTransfer();

	}


};

