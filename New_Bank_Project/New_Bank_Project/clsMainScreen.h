#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"

using namespace std;
class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,eLoginRegister = 8,eExit = 9
    };

    static short _ReadMainMenuOption()
    { 
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
    short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 9? ");
    return Choice;
}

    static void _GoBackToMainMenu()
    {
        cout << "\n\n\n\tPress any Key to go back to Main Menu....";
        system("pause>0");
        system("cls");
        ShowMainMenu();

    }

    static void _ShowAllClientsScreen()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
 }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");

    }



    static void _PerfromMainMenueOption(enMainMenueOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enMainMenueOptions::eListClients:
        {
             system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
         break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;


        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            break;
        }


    }


public:

	static void ShowMainMenu()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenuOption());
	}

};

