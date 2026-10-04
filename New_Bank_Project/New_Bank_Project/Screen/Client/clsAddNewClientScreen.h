#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"]
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
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
   static  void ShowAddNewClientScreen()
    {

       if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
       {
           return;// this will exit the function and it will not continue
       }



        _DrawScreenHeader("\t  Add New Client Screen");


        string AccNum = "";

        cout << "\nPlease Enter your Account Number: ";
        AccNum = clsInputValidate::ReadString();



        while (clsBankClient::IsClientExist(AccNum))
        {
            cout << endl << "\nAccount Number Already Exists, Enter Another one: ";
            AccNum = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccNum);

 

        _ReadClientInfo(NewClient);


        clsBankClient::enSaveResults SaveResult = NewClient.Save();


        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }

    }



};

