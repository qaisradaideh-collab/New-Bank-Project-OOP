
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsLoginScreen.h"

int main()
{

    while (true)
    {

        clsLoginScreen::ShowLoginScreen();
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

    }

    system("pause>0");
    return 0;
}