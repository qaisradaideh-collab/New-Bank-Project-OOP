#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{


private:


    static  bool _Login()
    {
        bool LoginFaild = false;
        short FailedLoginCount = 3;

        string Username, Password;

        do
        {


            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
                FailedLoginCount--;
                cout << "\nYou have " << FailedLoginCount << " Trial(s) to login\n\n";

            }

            if (FailedLoginCount == 0)
            {
                cout << "Enter Username? ";
                cin >> Username;

                cout << "Enter Password? ";
                cin >> Password;

                CurrentUser = clsUser::Find(Username, Password);

                LoginFaild = CurrentUser.IsEmpty();
            }
            else
            {
                cout << "\n\nYou are Locked after 3 failed trails\n";
                return false;
            }


        } while (LoginFaild);

        clsMainScreen::ShowMainMenu();

    }

public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
        

    }

};






