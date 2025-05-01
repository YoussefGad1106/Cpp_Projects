#pragma once
#include "iostream"
#include "clsInputValidation.h"
#include <fstream>
#include <iomanip>
#include "clsPerson.h"
#include "clsGlobal.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsBankUser : public clsPerson
{
private :
	
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName, _UserPassword;
	short _Permissions;
	bool _MarkedForDelete = false;
	static const short encryptionKey = 4;


	static clsBankUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector<string> vUserData;

		vUserData = clsString::Split(Line, Separator);

		return clsBankUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5], encryptionKey), stof(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsBankUser User, string Separator = "#//#")
	{
		vector <string> vUserData;


		vUserData.push_back(User.FirstName);
		vUserData.push_back(User.LastName);
		vUserData.push_back(User.Email);
		vUserData.push_back(User.Phone);
		vUserData.push_back(User._UserName);
		vUserData.push_back(clsUtil::EncryptText(User.UserPassword,encryptionKey));
		vUserData.push_back(to_string(User.Permissions));

		return clsString::JoinString(vUserData, Separator);
	}

	static clsBankUser _GetEmptyUserObject()
	{
		return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankUser _GetNewUserObject(string UserName)
	{
		return clsBankUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector<clsBankUser> _LoadUsersDataFromFileToVector()
	{
		vector<clsBankUser> vUsers;
		fstream MyFile;
		string Line;

		MyFile.open("Bank Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vUsers.push_back(_ConvertLineToUserObject(Line));
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsBankUser>& vUsers)
	{
		fstream MyFile;
		MyFile.open("Bank Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankUser& User : vUsers)
			{
				if (!User._MarkedForDelete)
					MyFile << _ConvertUserObjectToLine(User) << endl;
			}

			MyFile.close();
		}
	}

	static void _AddNewDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Bank Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static void _DeleteUserFromFile(clsBankUser DeletedUser)
	{
		vector<clsBankUser> vUsers = _LoadUsersDataFromFileToVector();

		for (clsBankUser& User : vUsers)
		{
			if (DeletedUser._UserName == User._UserName)
			{
				User = _GetEmptyUserObject();
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _Add()
	{
		_AddNewDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _Update()
	{
		vector<clsBankUser> vUsers = _LoadUsersDataFromFileToVector();

		for (clsBankUser& User : vUsers)
		{
			if (User.GetUserName() == this->_UserName)
			{
				// update the same User in the file as the current modified User
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	string _ConvertLoggedInUserObjectToLine(string Separator = "#//#")
	{
		vector <string> vUserData;

		vUserData.push_back(GetUserName());
		vUserData.push_back(UserPassword);
		vUserData.push_back(to_string(Permissions));

		return clsString::JoinString(vUserData, Separator);
	}

	string _LoginRegisterLine()
	{
		return clsDate::DateTimeString() + "#//#" + _ConvertLoggedInUserObjectToLine();
	}

public :

	enum enMainMenuPermissions
	{
		enAll = -1, enListClient = 1, enAddClient = 2, enDeleteClient = 4,
		enUpdateClient = 8, enFindClient = 16, enTransactionMenu = 32, enManageUsersMenu = 64, enLoginRegister = 128
	};

	clsBankUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string UserPassword, short Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_UserPassword = UserPassword;
		_Permissions = Permissions;
	}

	struct stLoginRegisterData
	{
		string LoginTime;
		string UserName;
		string UserPassword;
		short Permissions;
	};

	void SetUserPassword(string UserPassword)
	{
		_UserPassword = UserPassword;
	}

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	string GetUserName()
	{
		return _UserName;
	}

	string GetUserPassword()
	{
		return _UserPassword;
	}

	short GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetUserPassword, put = SetUserPassword)) string UserPassword;
	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsBankUser Find(string UserName)
	{

		fstream MyFile;
		MyFile.open("Bank Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankUser User = _ConvertLineToUserObject(Line, "#//#");

				if (User._UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

		}

		return _GetEmptyUserObject();
	}

	static clsBankUser Find(string UserName, string UserPassword)
	{
		fstream MyFile;
		MyFile.open("Bank Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankUser User = _ConvertLineToUserObject(Line, "#//#");

				if (User._UserName == UserName && User.UserPassword == UserPassword)
				{
					MyFile.close();
					return User;
				}
			}

		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		return !(Find(UserName).IsEmpty());
	}

	static clsBankUser NewUserObject(string UserName)
	{
		return _GetNewUserObject(UserName);
	}

	bool Delete()
	{
		vector <clsBankUser> vUsers = _LoadUsersDataFromFileToVector();

		for (clsBankUser& User : vUsers)
		{
			if (User._UserName == _UserName)
			{
				User._MarkedForDelete = true;

				_SaveUsersDataToFile(vUsers);

				*this = _GetEmptyUserObject();

				return true;
			}
		}

		return false;
	}

	static vector<clsBankUser> GetUsersList()
	{
		return _LoadUsersDataFromFileToVector();
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSuccesseded = 1, svFailedUserNameExist = 2 };

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

		case enMode::AddNewMode:

			if (IsUserExist(_UserName))
				return svFailedUserNameExist;

			_Add();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSuccesseded;

		}
	}

	bool CheckAccessPermission(enMainMenuPermissions Permission)
	{
		if (this->Permissions == enMainMenuPermissions::enAll)
			return true;

		return (Permission & this->Permissions) == Permission;
	}

	void LoginRegisterOnFile()
	{
		fstream MyFile;
		MyFile.open("Login Register.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _LoginRegisterLine() << endl;
		}

		MyFile.close();
	}
};

