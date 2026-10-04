#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsBankClient.h"

using namespace std;


class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRegisterRecordLine(clsBankClient::stTransferLog TransferLogRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(8) << left << TransferLogRecord.ClientFromAccNum;
		cout << "| " << setw(8) << left << TransferLogRecord.ClienToAccNum;
		cout << "| " << setw(8) << left << TransferLogRecord.TransferAmount;
		cout << "| " << setw(10) << left << TransferLogRecord.ClientFromAccBalance;
		cout << "| " << setw(10) << left << TransferLogRecord.ClienToAccBalance;
		cout << "| " << setw(8) << left << TransferLogRecord.UserName;
	}




public:


	static void ShowTransferLogScreen()
	{
        vector <clsBankClient::stTransferLog> vTransferLogRecord = clsBankClient::GetTransferLogRegisterList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferLogRecord)
            {

                _PrintTransferLogRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

