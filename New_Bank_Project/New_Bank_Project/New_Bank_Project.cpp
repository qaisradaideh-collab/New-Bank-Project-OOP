
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
    }

    system("pause>0");
    return 0;
}