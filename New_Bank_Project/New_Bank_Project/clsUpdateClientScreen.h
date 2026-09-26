#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"]
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

private:

    static  void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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


   static void ShowUpdateClientScreen()
    {

       if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
       {
           return;// this will exit the function and it will not continue
       }


        _DrawScreenHeader("\t Update Client Screen");

        string AccNum = "";
        cout << "\nPlease Enter your Account Number: ";
        AccNum = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccNum))
        {
            cout << endl << "\nAccount number is not found, choose another one: ";
            AccNum = clsInputValidate::ReadString();

        }
        clsBankClient Client = clsBankClient::Find(AccNum);
        Client.Print();


        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client? Y/N? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {

            cout << "\n\nUpdate Client Info:\n";
            cout << "\n------------------\n";


            _ReadClientInfo(Client);

            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();



            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                Client.Print();
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
        }
};

