#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsUser.h"


class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LogInRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LogInRecord.DateTime;
		cout << "| " << setw(20) << left << LogInRecord.UserName;
		cout << "| " << setw(20) << left << LogInRecord.Password;
		cout << "| " << setw(10) << left << to_string(LogInRecord.Permissoins);
	}



public:

	static void ShowLoginRegisterScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }

        vector <clsUser::stLoginRegisterRecord> vLoginRecords = clsUser::GetLoginRegisterList();

		string SubTitle = "(" + to_string(vLoginRecords.size())+") Record(s)";
		_DrawScreenHeader("Login Register List Screen", SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRecords.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord  Record : vLoginRecords)
            {

                _PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

