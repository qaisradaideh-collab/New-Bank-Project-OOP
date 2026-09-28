#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsString.h"
#include "Global.h"
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients2.txt";
const string TransferLogFileName = "TransferLog.txt";


class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2 };
    enMode _Mode;
    bool _MarkedForDelete = false;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
      struct stTransferLog;



    static stTransferLog _ConvertTransferLogLineToRecord(string LoginLine, string Seperator = "#//#")
    {
        vector<string> vLoginData = clsString::Split(LoginLine, Seperator);

        stTransferLog LoginRecord;
        LoginRecord.DateTime = vLoginData[0];
        LoginRecord.ClientFromAccNum = vLoginData[1];
        LoginRecord.ClienToAccNum = vLoginData[2];
        LoginRecord.ClientFromAccBalance = stof(vLoginData[3]);
        LoginRecord.ClienToAccBalance = stof(vLoginData[4]);
        LoginRecord.UserName = vLoginData[5];

        return LoginRecord;
    }

    string _PrepareTransferLogRecord( clsBankClient ClientTo, float TransferAmount, string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _AccountNumber + Seperator;
        LoginRecord += ClientTo.AccountNumber() + Seperator;
        LoginRecord += to_string(TransferAmount) + Seperator;
        LoginRecord += to_string(_AccountBalance) + Seperator;
        LoginRecord += to_string(ClientTo.AccountBalance) + Seperator;
        LoginRecord += CurrentUser.UserName;

        return LoginRecord;

    }
   
    void _RegisterTransferLog( clsBankClient ClientTo, float TransferAmount)
    {
        string  stDataLine = _PrepareTransferLogRecord( ClientTo, TransferAmount);
        fstream MyFile;
        MyFile.open(TransferLogFileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }



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

    static  struct stTransferLog
    {
        string DateTime;
        string ClientFromAccNum;
        string ClienToAccNum;
        float ClientFromAccBalance = 0;
        float ClienToAccBalance = 0;
        float TransferAmount = 0;
        string UserName;


    };

    static  vector <stTransferLog> GetTransferLogRegisterList()
    {

        vector <stTransferLog> vTransferLogRecords;

        fstream MyFile;
        MyFile.open(TransferLogFileName, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                vTransferLogRecords.push_back(_ConvertTransferLogLineToRecord(Line));
            }

            MyFile.close();

        }

        return vTransferLogRecords;

    }



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
            if (IsEmpty())
            {
                return svFaildEmptyObject;
            }
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
                _Mode = enMode::UpdateMode;

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

   void Deposit(double Amount)
   {
       _AccountBalance += Amount;
       Save();
   }
   
   bool Withdraw(double Amount)
   {
       if (Amount > _AccountBalance)
           return false;
       else
       {
           _AccountBalance -= Amount;
           Save();
           return true;
       }

   }

   bool Transfer(float Amount , clsBankClient& DestinationClient)
   {
       if (Withdraw(Amount))
       {
           DestinationClient.Deposit(Amount);
           _RegisterTransferLog(DestinationClient, Amount);
           return true;
       }
       else
       {
           return false;
       }


   }

};