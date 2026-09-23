#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients2.txt";

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2 , DeleteMode = 3};
    enMode _Mode;
    bool _MarkedForDelete = false;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vClientsData;
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClientsData.push_back(Client);
            }

            MyFile.close();

        }

        return vClientsData;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient& C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
                }
            MyFile.close();
        }
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _Update()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
  }


public:

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    //void Print()
    //{
    //    cout << "\nClient Card:";
    //    cout << "\n___________________";
    //    cout << "\nFirstName   : " << FirstName;
    //    cout << "\nLastName    : " << LastName;
    //    cout << "\nFull Name   : " << FullName();
    //    cout << "\nEmail       : " << Email;
    //    cout << "\nPhone       : " << Phone;
    //    cout << "\nAcc. Number : " << _AccountNumber;
    //    cout << "\nPassword    : " << _PinCode;
    //    cout << "\nBalance     : " << _AccountBalance;
    //    cout << "\n___________________\n";

    //}

    static clsBankClient Find(string AccountNumber)
        {


            fstream MyFile;
            MyFile.open(ClientsFileName, ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }

            return _GetEmptyClientObject();
        }

    static clsBankClient Find(string AccountNumber, string PinCode)
        {



            fstream MyFile;
            MyFile.open(ClientsFileName, ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }
            return _GetEmptyClientObject();
        }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2 };

    enSaveResults Save()
     {
        if (_Mode == enMode::EmptyMode)
            {
                return svFaildEmptyObject;
            }
            
        else if (_Mode == enMode::UpdateMode)
            {
                _Update();

                return svSucceeded;
            }
        else if (_Mode == enMode::AddNewMode)
        {
            if (IsClientExist(_AccountNumber))
            {
                return svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                return svSucceeded;
            }
        }



     }
 
    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }

   static  clsBankClient GetAddNewClientObject(string AccountNumber)
    {
       clsBankClient NewClient(enMode::AddNewMode,"","","","", AccountNumber,"", 0);
       return NewClient;
    }

   bool Delete()
   {
       vector <clsBankClient> _vClients;
       _vClients = _LoadClientsDataFromFile();

       for (clsBankClient& C : _vClients)
       {
           if (C.AccountNumber() == _AccountNumber)
           {
               C._MarkedForDelete = true;
               break;
           }

       }

       _SaveCleintsDataToFile(_vClients);

       *this = _GetEmptyClientObject();

       return true;

   }

   static vector <clsBankClient> GetClientsList()
   {
       return _LoadClientsDataFromFile();
   }

   static double GetTotalBalances()
   {
       vector <clsBankClient>   _vClients = _LoadClientsDataFromFile();
       double TotalBalances = 0;

       for (clsBankClient& Client : _vClients)
       {
           TotalBalances += Client.AccountBalance;
       }
       return TotalBalances;

   }

};