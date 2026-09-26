#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"]
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:


    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }



public:

   static  void ShowDeleteClientScreen()
    {

       if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
       {
           return;// this will exit the function and it will not continue
       }


       _DrawScreenHeader("\t Delete Client Screen");

        string AccNum = "";
        cout << "\nPlease Enter your Account Number: ";
        AccNum = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccNum))
        {
            cout << endl << "\nAccount number is not found, choose another one: ";
            AccNum = clsInputValidate::ReadString();

        }
        clsBankClient Client = clsBankClient::Find(AccNum);
        _PrintClient(Client);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client? Y/N? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {

            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }



        }

    }





};

