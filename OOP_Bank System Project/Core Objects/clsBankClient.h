#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidation.h"
#include "clsGlobal.h"
using namespace std;


class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;

	string _AccountNumber, _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClientData;

		vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
							vClientData[4], vClientData[5], stof(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		vector <string> vClientData;


		vClientData.push_back(Client.FirstName);
		vClientData.push_back(Client.LastName);
		vClientData.push_back(Client.Email);
		vClientData.push_back(Client.Phone);
		vClientData.push_back(Client._AccountNumber);
		vClientData.push_back(Client.PinCode);
		vClientData.push_back(to_string(Client.AccountBalance));

		return clsString::JoinString(vClientData, Separator);
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "",0);
	}

	static clsBankClient _GetNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFileToVector()
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		string Line;

		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient>& vClients)
	{
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient &Client : vClients)
			{
				if (!Client._MarkedForDelete)
					MyFile << _ConvertClientObjectToLine(Client) << endl;
			}

			MyFile.close();
		}
	}

	static void _AddNewDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static void _DeleteClientFromFile(clsBankClient DeletedClient)
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFileToVector();
		
		for (clsBankClient& Client : vClients)
		{
			if (DeletedClient._AccountNumber == Client._AccountNumber)
			{
				Client._MarkedForDelete = true;
				Client = _GetEmptyClientObject();
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _Add()
	{
		_AddNewDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	
	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFileToVector();

		for (clsBankClient& Client : vClients)
		{
			if (Client.GetAccountNumber() == this->_AccountNumber)
			{
				// update the same client in the file as the current modified client
				Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	string _TransferLogLine(clsBankClient SenderClient, clsBankClient AccepterClient, double TransferAmount, string Separator = "#//#")
	{
		return clsDate::DateTimeString() + Separator + SenderClient._AccountNumber + Separator + AccepterClient._AccountNumber
			+ Separator + to_string(TransferAmount) + Separator + to_string(SenderClient._AccountBalance) + Separator +
			to_string(AccepterClient._AccountBalance) + Separator + LoggedInUser.GetUserName();
	}

	void _TransferRegisterOnFile(clsBankClient AccepterClient, double TransferAmount, string Separator = "#//#")
	{
		fstream MyFile;
		MyFile.open("Transfer Log.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _TransferLogLine(*this, AccepterClient, TransferAmount) << endl;
		}

		MyFile.close();
	}


public :

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogData
	{
		string DateTime;
		string SenderClientAccountNumber;
		string AccepterClientAccountNumber;
		double TransferAmount;
		float SenderClientAccountBalance;
		float AccepterClientAccountBalance;
		string UserName;
	};
	
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}
		
	string GetPinCode()
	{
		return _PinCode;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");

				if (Client._AccountNumber == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");

				if (Client._AccountNumber == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		return !(Find(AccountNumber).IsEmpty());
	}

	static clsBankClient NewClientObject(string AccountNumber)
	{
		return _GetNewClientObject(AccountNumber);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToVector();

		for (clsBankClient& client : vClients)
		{
			if (client._AccountNumber == _AccountNumber)
			{
				client._MarkedForDelete = true;

				_SaveClientsDataToFile(vClients);

				*this = _GetEmptyClientObject();

				return true;
			}
		}

		return false;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFileToVector();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSuccesseded = 1, svFailedAccountNumberExist = 2 };

	void Deposit(double Amount)
	{
		AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > AccountBalance)
			return false;

		AccountBalance -= Amount;
		Save();
		return true;
	}

	void Transfer(clsBankClient &AccepterClient, double TransferAmount)
	{
		Withdraw(TransferAmount);
		AccepterClient.Deposit(TransferAmount);
		_TransferRegisterOnFile(AccepterClient, TransferAmount);

	}

	
	 
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;

		case enMode::UpdateMode:

			_Update();
			return enSaveResults::svSuccesseded;

		case enMode::AddNewMode :

			if (IsClientExist(_AccountNumber))
				return svFailedAccountNumberExist;

			_Add();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSuccesseded;

		}
	}	

};