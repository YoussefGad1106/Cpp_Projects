#pragma warning (disable : 4996)
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Bank Clients.txt";
const string UsersFileName = "Bank Users.txt";
const string delimiter = "#//#";

enum enMainMenuOptions { Exit = 0, ShowList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, SearchClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8};
enum enTransactionMenuOptions { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4 };
enum enManageUsersMenuOptions { ListUsers = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, SearchUser = 5, MainMenuScreen = 6};

struct stClientData
{
	string accountNumber, Name, Phone, pinCode;
	double accountBalance;
};

struct stUserData 
{
	string userName, userPassword;
	short userPermissions;
};

stUserData LoggedInUser;

int ReadPositiveNumber(string Message)
{
	int Number = 0;
	do
	{
		cout << "\n" << Message;
		cin >> Number;
	} while (Number < 0);
	return Number;
}

double ReadDoublePositiveNumber(string Message)
{
	double Number = 0;
	do
	{
		cout << "\n" << Message;
		cin >> Number;
	} while (Number <= 0);

	return Number;
}

bool IsNumber(string str)
{
	for (char x : str)
		if (!isdigit(x)) return false;

	return !str.empty();
}

int ValidateNumericInput(int num)
{
	string input = to_string(num);

	while (true)
	{
		if (IsNumber(input))
		{
			num = stoi(input);
			return num;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nWrong Input Please Try Again." << endl;
		}
	}

}

int ReadValidPositiveNumber(string Msg, short from = 0, int to = 999)
{
	int Num = ValidateNumericInput(ReadPositiveNumber(Msg));

	while (Num < from || Num > to)
	{
		cout << "\nPlease Enter a Number between " << from << " and " << to << endl;
		Num = ValidateNumericInput(ReadPositiveNumber(Msg));
	}

	return Num;
}

string ReadValidString(string Msg, short maxLength = 100, short minLength = 1)
{
	string input;

	do
	{
		cin.clear();
		cout << "\n" << Msg;
		getline(cin >> ws, input);

		if (input.length() > maxLength)
			cout << "\nWrong Input. Please Enter a String with max length : " << maxLength << " Characters \n";

		else if (input.length() < minLength)
			cout << "\nWrong Input. Please Enter a String with min length : " << minLength << " Characters \n";


	} while (cin.fail() || (input.length() > maxLength || input.length() < minLength));

	return input;
}

stClientData ReadClientData(string AccountNumber = "")
{
	stClientData client;

	cout << "\nPlease Enter Client Data:\n";

	if (AccountNumber == "")
		client.accountNumber = ReadValidString("Enter Account Number : ", 10);
	else
		client.accountNumber = AccountNumber;	

	client.pinCode = ReadValidString("Enter PinCode Number : ", 4, 4);
	client.Name = ReadValidString("Enter Client Name : ", 25);
	client.Phone = ReadValidString("Enter Phone Number : ", 12);
	client.accountBalance = ReadDoublePositiveNumber("Enter Account Balance : ");

	return client;
}

vector<string> SplitString(string str, string delimiter = " ")
{
	string word = "";
	short pos = 0;

	vector<string> stringWords;

	while ((pos = str.find(delimiter)) != str.npos)
	{
		word = str.substr(0, pos);

		if (word != "")
			stringWords.push_back(word);

		str.erase(0, pos + delimiter.length());
	}

	if (str != "")
		stringWords.push_back(str);

	return stringWords;
}

string JoinString(vector<string> vString, string Delim)
{
	string S1;
	for (string& s : vString)
	{
		S1 = S1 + s + Delim;
	}
	return S1.substr(0, S1.length() - Delim.length());
}

vector<string> ClientDataToStringVector(stClientData client)
{
	vector<string> vClientData;

	vClientData.push_back(client.accountNumber);
	vClientData.push_back(client.pinCode);
	vClientData.push_back(client.Name);
	vClientData.push_back(client.Phone);
	vClientData.push_back(to_string(client.accountBalance));

	return vClientData;
}

string ConvertRecordToLine(stClientData client, string delimiter)
{
	vector<string> vClientData = ClientDataToStringVector(client);
	return JoinString(vClientData, delimiter);
}

vector<string> LoadDataFromFileToVector(string FileName)
{
	fstream MyFile;
	string Line;
	vector<string> vFileContent;

	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			vFileContent.push_back(Line);
		}

		MyFile.close();
	}

	return vFileContent;
}

void SaveVectorToFile(string FileName, vector <string> vFileContent)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (string& Line : vFileContent)
		{
			if (Line != "") // indicator of a deleted record so if you want to delete a record just change its value to ""
			{
				MyFile << Line << endl;
			}
		}

		MyFile.close();
	}
}

void DeleteRecordFromFile(string FileName, string Record)
{
	vector <string> vFileContent = LoadDataFromFileToVector(FileName);

	for (string& Line : vFileContent)
	{
		if (Line == Record)
		{
			Line = "";
		}
	}

	SaveVectorToFile(FileName, vFileContent);
}

void UpdateRecordFromFile(string FileName, string OldRecord, string NewRecord)
{
	vector<string> FileContent = LoadDataFromFileToVector(FileName);

	for (string& line : FileContent)
	{
		if (line == OldRecord)
		{
			line = NewRecord;
			break;
		}
	}

	SaveVectorToFile(FileName, FileContent);
}

vector<stClientData> LoadClientsDataFromFileToVector(string FileName, string delimiter)
{
	vector<string> vFileRecords = LoadDataFromFileToVector(FileName);
	vector<stClientData> Clients;
	vector<string> vClientData;

	for (short i = 0; i < vFileRecords.size(); i++)
	{
		vClientData = SplitString(vFileRecords[i], delimiter);

		stClientData client;

		client.accountNumber = vClientData[0];
		client.pinCode = vClientData[1];
		client.Name = vClientData[2];
		client.Phone = vClientData[3];
		client.accountBalance = stod(vClientData[4]);

		Clients.push_back(client);


	}

	return Clients;
}

bool FindClientByAccountNumber(vector<stClientData>& Clients, string AccNumber, stClientData& FoundClient)
{
	for (stClientData& client : Clients)
		if (client.accountNumber == AccNumber)
		{
			FoundClient = client;
			return true;
		}

	return false;
}

int GetIndexOfClientUsingAccNumber(vector<stClientData>& Clients, string AccNumber)
{
	for (short i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].accountNumber == AccNumber)
		{
			return i;
		}
	}
	return -1;
}

void PrintClientData(stClientData Client)
{
	cout << "\nThe Following are the Clients details : \n\n";

	cout << "Account Number : " << Client.accountNumber << endl;
	cout << "Pin Code       : " << Client.pinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone Number   : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.accountBalance << endl;

}

void SearchClientMenu(vector<stClientData>& Clients, stClientData& FoundClient)
{
	system("cls");
	cout << "\n----------------------Searching for a Client Menu----------------------------\n";

	string AccNumber = ReadValidString("Enter the Client's Account Number : ");

	if (FindClientByAccountNumber(Clients, AccNumber, FoundClient))
		PrintClientData(FoundClient);
	else
		cout << "\nClient with Account Number (" << AccNumber << ") Not Found !" << endl;

	system("pause");
}

void ShowClientListMenu(vector<stClientData>& Client)
{
	system("cls");

	cout << "\n-------------------------------Client List (" << Client.size() << ") Client(s).-------------------------------\n\n" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	cout << left
		<< setw(18) << "| Account Number"
		<< setw(10) << "  | Pin"
		<< setw(25) << "  | Client Name"
		<< setw(15) << "   | Phone"
		<< right << setw(15) << " | Balance\t|" << endl;

	cout << "-----------------------------------------------------------------------------------------" << endl;

	for (const stClientData& client : Client) {
		cout << left
			<< "| " << setw(18) << client.accountNumber
			<< "| " << setw(8) << client.pinCode
			<< "| " << setw(24) << client.Name
			<< "| " << setw(14) << client.Phone
			<< "| " << setw(10) << client.accountBalance << "\t|"
			<< endl;
	}

	cout << "-----------------------------------------------------------------------------------------" << endl;

	system("pause");
}

bool DeleteConfirmation()
{
	char choice;

	cout << "\nAre you sure you want to delete this ? y/n : ";
	cin >> choice;

	return tolower(choice) == 'y';

}

void DeleteClientRecordByAccountNumber(bool confirmation, stClientData client, string delimiter)
{
	if (confirmation)
	{
		DeleteRecordFromFile("Bank Clients.txt", ConvertRecordToLine(client, delimiter));
		cout << "\nClient Deleted Successfully" << endl;
	}
	else
		cout << "\nClient Deletion has been Cancelled" << endl;
}

void DeleteClientMenu(vector<stClientData>& Clients, stClientData& FoundClient)
{
	system("cls");
	cout << "\n----------------------Deleting a Client Menu--------------------------\n";

	string AccNumber = ReadValidString("Enter Client's Account Number : ");

	if (FindClientByAccountNumber(Clients, AccNumber, FoundClient))
	{
		PrintClientData(FoundClient);
		DeleteClientRecordByAccountNumber(DeleteConfirmation(), FoundClient, delimiter);
	}
	else
		cout << "\nClient with Account Number (" << AccNumber << ") Not Found !" << endl;

	system("pause");
}

bool UpdateConfirmation()
{
	char choice;

	cout << "\nAre you sure you want to Update this ? y/n : ";
	cin >> choice;

	return tolower(choice) == 'y';

}

void UpdateClientRecordByAccountNumber(bool confirmation, stClientData client, string delimiter)
{
	if (confirmation)
	{
		string OldRecord = ConvertRecordToLine(client, delimiter);
		string NewRecord = ConvertRecordToLine(ReadClientData(client.accountNumber), delimiter);

		UpdateRecordFromFile("Bank Clients.txt", OldRecord, NewRecord);
		cout << "\nClient Updated Successfully" << endl;
	}
	else
		cout << "\nClient Update has been Cancelled" << endl;
}

void UpdateClientMenu(vector<stClientData>& Clients, stClientData& FoundClient)
{
	system("cls");
	cout << "\n----------------------Updating a Client----------------------\n";

	string AccNumber = ReadValidString("Enter Client's Account Number : ");

	if (FindClientByAccountNumber(Clients, AccNumber, FoundClient))
	{
		PrintClientData(FoundClient);
		UpdateClientRecordByAccountNumber(UpdateConfirmation(), FoundClient, delimiter);
	}
	else
		cout << "\nClient with Account Number (" << AccNumber << ") Not Found !" << endl;

	system("pause");
}

bool AddingClient(vector<stClientData>& Clients)
{
	fstream MyFile;
	stClientData Client;

	MyFile.open(ClientsFileName, ios::out | ios::app);
	if (!MyFile.is_open())
	{
		cout << "Error: Unable to open file.\n";
		return false;
	}

	Client = ReadClientData();

	if (FindClientByAccountNumber(Clients, Client.accountNumber, Client))
	{
		cout << "\nClient with Same Account Number already exists\n";
		MyFile.close();
		return false;
	}
	else
	{
		MyFile << ConvertRecordToLine(Client, "#//#") << endl;
		MyFile.close();
		return true;
	}
}

void AddClientMenu(vector<stClientData>& Clients)
{
	system("cls");

	fstream MyFile;
	char choice = 'y';

	MyFile.open(ClientsFileName, ios::out | ios::app);

	while (tolower(choice) != 'n' && MyFile.is_open())
	{
		system("cls");
		cout << "\n----------------------Adding new Client Menu---------------------------\n";

		if (AddingClient(Clients))
		{
			cout << "\nClient Added Successfully, Do you want to add more Clients ? y/n : ";
			cin >> choice;
		}
		else
		{
			MyFile.close();
		}
	}

	MyFile.close();

	system("pause");
}

bool ProcessConfirmation()
{
	char choice;

	cout << "\nAre you sure you want to perform this process ? y/n : ";
	cin >> choice;

	return tolower(choice) == 'y';

}

void DepoistAndWithdrawMenu(vector<stClientData>& Clients, string AccNumber, bool choice) // deposit = true, withdraw = false
{
	system("cls");
	int ClientIndex = GetIndexOfClientUsingAccNumber(Clients, AccNumber);

	if (ClientIndex != -1)
	{
		stClientData NewClient = Clients[ClientIndex];
		string OldClientDataRecord = ConvertRecordToLine(Clients[ClientIndex], delimiter);

		if (choice)
		{
			cout << "\n===========================================================================";
			cout << "\n====================== Deposit Screen =====================================";
			cout << "\n===========================================================================";

			PrintClientData(Clients[ClientIndex]);

			double amount = ReadDoublePositiveNumber("\nEnter the amount of the Deposit from 1 to 100000 : ");

			if (ProcessConfirmation())
			{
				NewClient.accountBalance += amount;
				UpdateRecordFromFile(ClientsFileName, OldClientDataRecord, ConvertRecordToLine(NewClient, delimiter));
				cout << "\nThe Process has been done Successfully !!" << endl;
			}
			else
				cout << "\nThe Process has been Cancelled" << endl;

		}

		else
		{
			cout << "\n===========================================================================";
			cout << "\n====================== Withdraw Screen ====================================";
			cout << "\n===========================================================================";

			PrintClientData(Clients[ClientIndex]);

			double amount = ReadDoublePositiveNumber("\nEnter the amount of the Withdraw from 1 to 100000 : ");

			if (Clients[ClientIndex].accountBalance - amount >= 0)
			{
				if (ProcessConfirmation())
				{
					NewClient.accountBalance -= amount;
					UpdateRecordFromFile(ClientsFileName, OldClientDataRecord, ConvertRecordToLine(NewClient, delimiter));
					cout << "\nThe Process has been done Successfully !!" << endl;
				}
				else
					cout << "\nThe Process has been Cancelled" << endl;
			}
			else
				cout << "\nInsufficient Balance for the Withdraw Process. You can withdraw up to " << Clients[ClientIndex].accountBalance << endl;
		}
	}
	else
		cout << "\nClient with Account Number (" << AccNumber << ") Not Found !" << endl;

	system("pause");

}

void TotalBalancesMenu(vector<stClientData>& Clients, stClientData& FoundClient)
{
	system("cls");
	double TotalBalances = 0;

	for (stClientData& Client : Clients)
		TotalBalances += Client.accountBalance;

	cout << "\n========================================================================================";
	cout << "\n=========================== Total Balances Screen ======================================";
	cout << "\n========================================================================================";

	cout << "\n\n---------------------------Client List (" << Clients.size() << ") Client(s).-------------------------------\n\n" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	cout << left
		<< setw(18) << "| Account Number"
		<< setw(25) << "  | Client Name"
		<< right << setw(15) << "| Balance\t|" << endl;

	cout << "-----------------------------------------------------------------------------------------" << endl;

	for (const stClientData& client : Clients) {
		cout << left
			<< "| " << setw(18) << client.accountNumber
			<< "| " << setw(24) << client.Name
			<< " | " << setw(12) << client.accountBalance << "\t|"
			<< endl;
	}
	cout << "\n-----------------------------------------------------------------------------------------" << endl;

	cout << "\n\n\t\t Total Balances = " << TotalBalances << endl;

	cout << "\n-----------------------------------------------------------------------------------------" << endl;

	system("pause");
}

vector<string> UserDataToStringVector(stUserData user)
{
	vector<string> vUserData;

	vUserData.push_back(user.userName);
	vUserData.push_back(user.userPassword);
	vUserData.push_back(to_string(user.userPermissions));

	return vUserData;
}

string ConvertRecordToLine(stUserData user, string delimiter)
{
	vector<string> vUserData = UserDataToStringVector(user);
	return JoinString(vUserData, delimiter);
}

vector<stUserData> LoadUsersDataFromFileToVector(string FileName, string delimiter)
{
	vector<string> vFileRecords = LoadDataFromFileToVector(FileName);
	vector<stUserData> Users;
	vector<string> vUserData;

	for (short i = 0; i < vFileRecords.size(); i++)
	{
		vUserData = SplitString(vFileRecords[i], delimiter);

		stUserData user;

		user.userName = vUserData[0];
		user.userPassword = vUserData[1];
		user.userPermissions = stoi(vUserData[2]);

		Users.push_back(user);


	}

	return Users;
}

bool FindUserByUserName(vector<stUserData>& Users, string userName, stUserData& FoundUser)
{
	for (stUserData& user : Users)
		if (user.userName == userName)
		{
			FoundUser = user;
			return true;
		}

	return false;
}

int GetIndexOfUserUsingUserName(vector<stUserData>& Users, string userName)
{
	for (short i = 0; i < Users.size(); i++)
	{
		if (Users[i].userName == userName)
		{
			return i;
		}
	}
	return -1;
}

bool Confirmation(char c)
{
	return (tolower(c) == 'y') ? true : false;
}

vector<bool> ReadAccessPermission()
{
	vector<bool> Permission;
	Permission.push_back(false); // for the 0 index
	char choice;

	cout << "\nApply access to Show Clients List ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Add new Client ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Delete Client ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Update Client ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Search for a Client ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Transactions Menu ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	cout << "\nApply access to Manage Users Menu ? y/n ? : ";
	cin >> choice;
	Permission.push_back(Confirmation(choice));

	return Permission;
}

short PermissionKey()
{
	char choice;
	short Key = 0;

	cout << "\nDo you Want to Give Full Access ? y/n ? ";
	cin >> choice;

	if (Confirmation(choice)) return -1;

	vector<bool> Permission = ReadAccessPermission();

	for (short i = 0; i < Permission.size(); i++)
	{
		if (Permission[i])
			Key = Key | (short)pow(2, i);
	}

	return Key;
}

vector<short> AccessibleMenus(short PermissionKey)
{
	short optionsArrayValues[] = { 0,2,4,8,16,32,64,128 };
	vector<short> AccessibleMenusVector;

	for (short i = 7; i > 0; i--)
	{
		if (PermissionKey >= optionsArrayValues[i])
		{
			AccessibleMenusVector.push_back(i);
			PermissionKey -= optionsArrayValues[i];
		}
	}

	return AccessibleMenusVector;
}

bool IsOptionInVector(short option, vector<short> vector)
{
	for (short s : vector)
	{
		if (s == option)
			return true;
	}

	return false;
}

void AccessDenied()
{
	system("cls");
	cout << "\n================================";
	cout << "\nYour Access has been denied";
	cout << "\nYou can not access this menu";
	cout << "\nPlease contact your admin";
	cout << "\n================================\n";

	system("pause");
}

stUserData ReadUserData(string UserName = "")
{
	system("cls");
	stUserData user;
	vector<stUserData> Users = LoadUsersDataFromFileToVector(UsersFileName, delimiter);
	
	cout << "\nPlease Enter the User's Details : \n";

	if (UserName != "")
		user.userName = UserName;
	else
	{
		user.userName = ReadValidString("Enter the User's Name : ", 25);

		while (FindUserByUserName(Users, user.userName, user))
		{
			cout << "\nUser with User Name [" << user.userName << "] is already exists.\n";
			user.userName = ReadValidString("Enter a new User Name : ");
		}
	}
	user.userPassword = ReadValidString("Enter the User's Password : ", 4);

	user.userPermissions = PermissionKey();	

	return user;
}

void PrintUserData(stUserData User)
{
	cout << "\nThe Following are the User's details : \n\n";

	cout << "User's Name         : " << User.userName << endl;
	cout << "User's Password     : " << User.userPassword << endl;
	cout << "User's Permissions  : " << User.userPermissions << endl;
	cout << endl;
}

void SearchUserMenu(vector<stUserData>& Users, stUserData& FoundUser)
{
	system("cls");
	cout << "\n----------------------Searching for a User Menu----------------------------\n";

	string userName = ReadValidString("Enter the User's Name : ");

	if (FindUserByUserName(Users, userName, FoundUser))
		PrintUserData(FoundUser);
	else
		cout << "\nUser with User Name (" << userName << ") Not Found !" << endl;

	system("pause");
}

void ShowUsersListMenu(vector<stUserData>& Users)
{
	system("cls");

	cout << "\n-------------------------------Users List (" << Users.size() << ") User(s).-------------------------------\n\n" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	cout << left
		<< setw(18) << "| User Name"
		<< setw(10) << "  | User Password"
		<< right << setw(15) << " | User Permissions\t|" << endl;

	cout << "-----------------------------------------------------------------------------------------" << endl;

	for (const stUserData& user : Users) {
		cout << left
			<< "| " << setw(18) << user.userName
			<< "| " << setw(14) << user.userPassword
			<< "| " << setw(15) << user.userPermissions << "\t|"
			<< endl;
	}

	cout << "-----------------------------------------------------------------------------------------" << endl;

	system("pause");
}

void DeleteUserRecordByUserName(bool confirmation, stUserData user, string delimiter)
{
	if (confirmation)
	{
		DeleteRecordFromFile("Bank Users.txt", ConvertRecordToLine(user, delimiter));
		cout << "\nUser Deleted Successfully" << endl;
	}
	else
		cout << "\nDeletion has been Cancelled" << endl;
}

void DeleteUserMenu(vector<stUserData>& Users, stUserData& FoundUser)
{
	system("cls");
	cout << "\n----------------------Deleting an User Menu--------------------------\n";

	string userName = ReadValidString("Enter User's Name : ");

	if (userName != "Admin")
	{
		if (FindUserByUserName(Users, userName, FoundUser))
		{
			PrintUserData(FoundUser);	
			DeleteUserRecordByUserName(DeleteConfirmation(), FoundUser, delimiter);
		}
		else
			cout << "\nUser with User Name (" << userName << ") Not Found !" << endl;
	}
	else
		cout << "\nThe Admin User cannot be deleted.\n\n";
	
	system("pause");
}

void UpdateUserRecordByUserName(bool confirmation, stUserData user, string delimiter)
{
	if (confirmation)
	{
		string OldRecord = ConvertRecordToLine(user, delimiter);
		string NewRecord = ConvertRecordToLine(ReadUserData(user.userName), delimiter);

		UpdateRecordFromFile("Bank Users.txt", OldRecord, NewRecord);
		cout << "\nUser Updated Successfully" << endl;
	}
	else
		cout << "\nUser Update has been Cancelled" << endl;
}

void UpdateUserMenu(vector<stUserData>& Users, stUserData& FoundUser)
{
	system("cls");
	cout << "\n----------------------Updating an User----------------------\n";

	string userName = ReadValidString("Enter User's Name : ");

	if (userName != "Admin")
	{
		if (FindUserByUserName(Users, userName, FoundUser))
		{
			PrintUserData(FoundUser);
			UpdateUserRecordByUserName(UpdateConfirmation(), FoundUser, delimiter);
		}
		else
			cout << "\nUser with Account Number (" << userName << ") Not Found !" << endl;
	}
	else
		cout << "\nThe Admin User cannot be Updated.\n\n";

	system("pause");
}

bool AddingUser(vector<stUserData>& Users)
{
	fstream MyFile;
	stUserData User;

	MyFile.open(UsersFileName, ios::out | ios::app);
	if (!MyFile.is_open())
	{
		cout << "Error: Unable to open file.\n";
		return false;
	}

	User = ReadUserData();

	MyFile << ConvertRecordToLine(User, "#//#") << endl;
	MyFile.close();
	return true;
}	

void AddUserMenu(vector<stUserData>& Users)
{
	system("cls");

	fstream MyFile;
	char choice = 'y';

	MyFile.open(UsersFileName, ios::out | ios::app);

	while (tolower(choice) != 'n' && MyFile.is_open())
	{
		system("cls");
		cout << "\n----------------------Adding new User Menu---------------------------\n";

		if (AddingUser(Users))
		{
			cout << "\nUser Added Successfully, Do you want to add more Users ? y/n : ";
			cin >> choice;
		}
		else
		{
			MyFile.close();
		}
	}

	MyFile.close();

	system("pause");
}

void ManageUsersMenuOptions()
{
	cout << "\n-------------------------------------------------------------------------";
	cout << "\n---------------- Manage Users Menu --------------------------------------";
	cout << "\n-------------------------------------------------------------------------";
	cout << "\n\t 1- List All Users";
	cout << "\n\t 2- Add New User";
	cout << "\n\t 3- Delete User";
	cout << "\n\t 4- Update User";
	cout << "\n\t 5- Find User";
	cout << "\n\t 6- Main Menu";
}

void TranscationMenuOptions()
{
	cout << "\n------------------------------------------------------------------------";
	cout << "\n---------------- Transaction Menu --------------------------------------";
	cout << "\n------------------------------------------------------------------------";
	cout << "\n\t 1- Deposit";
	cout << "\n\t 2- Withdraw";
	cout << "\n\t 3- Total Balance";
	cout << "\n\t 4- Main Menu";
}

void MainMenuOptions()
{
	cout << "\n------------------------------------------------------------------------";
	cout << "\n---------------------- Main Menu  --------------------------------------";
	cout << "\n------------------------------------------------------------------------";
	cout << "\n\t 1- Show Clients List";
	cout << "\n\t 2- Add new Client";
	cout << "\n\t 3- Delete Client";
	cout << "\n\t 4- Update Client";
	cout << "\n\t 5- Search for a Client";
	cout << "\n\t 6- Transactions Menu";
	cout << "\n\t 7- Manage Users Menu";
	cout << "\n\t 8- Logout";
	cout << "\n\t 0- Exit the Program";
}

void DisplayUsersMainMenu();

void DisplayTransactionMenu()
{
	system("cls");
	TranscationMenuOptions();
	enTransactionMenuOptions choice = (enTransactionMenuOptions)ReadValidPositiveNumber("\nEnter an Option from 1 to 4 : ", 1, 4);
	vector<stClientData> Clients = LoadClientsDataFromFileToVector(ClientsFileName, delimiter);
	stClientData Client;

	switch (choice)
	{
	case Deposit:
		DepoistAndWithdrawMenu(Clients, ReadValidString("Enter the Client's Account Number : "), 1);
		DisplayTransactionMenu();
		break;

	case Withdraw:
		DepoistAndWithdrawMenu(Clients, ReadValidString("Enter the Client's Account Number : "), 0);
		DisplayTransactionMenu();
		break;

	case TotalBalances:
		TotalBalancesMenu(Clients, Client);
		DisplayTransactionMenu();
		break;

	case MainMenu:
		DisplayUsersMainMenu();
		break;
	}
}

void DisplayManageUsersMenu()
{
	system("cls");
	ManageUsersMenuOptions();
	enManageUsersMenuOptions choice = (enManageUsersMenuOptions)ReadValidPositiveNumber("\nEnter an Option from 1 to 6 : ", 1, 6);
	vector<stUserData> Users = LoadUsersDataFromFileToVector(UsersFileName, delimiter);
	stUserData User;

	switch (choice)
	{
	case ListUsers:
		ShowUsersListMenu(Users);
		DisplayManageUsersMenu();
		break;

	case AddUser:
		AddUserMenu(Users);
		DisplayManageUsersMenu();
		break;

	case DeleteUser:
		DeleteUserMenu(Users, User);
		DisplayManageUsersMenu();
		break;

	case UpdateUser:
		UpdateUserMenu(Users, User);
		DisplayManageUsersMenu();
		break;

	case SearchUser:
		SearchUserMenu(Users, User);
		DisplayManageUsersMenu();
		break;

	case MainMenuScreen:
		DisplayUsersMainMenu();
		break;
	}
}

bool UsersLogInScreen()
{	
	stUserData user, foundUser;
	vector<stUserData> Users = LoadUsersDataFromFileToVector(UsersFileName, delimiter);

	user.userName = ReadValidString("Enter User's Name : ");
	user.userPassword = ReadValidString("Enter User's Password : ");

	if (FindUserByUserName(Users, user.userName, foundUser) && user.userPassword == foundUser.userPassword)
	{
		LoggedInUser = foundUser;
		return true;
	}
	else
		return false;	
}

void LogIn()
{
	system("cls");
	cout << "\n------------------------- Log In Screen -------------------------\n";
	while (true)
	{
		if (UsersLogInScreen())
			break;
		else
			cout << "\nInvalid UserName or Password\n";
	}

	DisplayUsersMainMenu();
}

void DisplayUsersMainMenu()
{
	system("cls");
	MainMenuOptions();
	enMainMenuOptions choice = (enMainMenuOptions)ReadValidPositiveNumber("\nEnter an Option from 0 to 8 : ", 0, 8);
	vector<stClientData> Clients = LoadClientsDataFromFileToVector(ClientsFileName, delimiter);
	stClientData Client;

	switch (choice)
	{
	case ShowList:
		if (IsOptionInVector(ShowList, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			ShowClientListMenu(Clients);
			DisplayUsersMainMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}
		
	case AddClient:
		if (IsOptionInVector(AddClient, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			AddClientMenu(Clients);
			DisplayUsersMainMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case DeleteClient:
		if (IsOptionInVector(DeleteClient, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			DeleteClientMenu(Clients,Client);
			DisplayUsersMainMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case UpdateClient:
		if (IsOptionInVector(UpdateClient, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			UpdateClientMenu(Clients,Client);
			DisplayUsersMainMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case SearchClient:
		if (IsOptionInVector(SearchClient, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			SearchClientMenu(Clients,Client);
			DisplayUsersMainMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case Transactions:
		if (IsOptionInVector(Transactions, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			DisplayTransactionMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case ManageUsers:
		if (IsOptionInVector(ManageUsers, AccessibleMenus(LoggedInUser.userPermissions)) || LoggedInUser.userPermissions == -1)
		{
			DisplayManageUsersMenu();
			break;

		}
		else
		{
			AccessDenied();
			DisplayUsersMainMenu();
			break;
		}

	case Logout:
		LogIn();
		break;

	case Exit:
		system("cls");
		cout << "\nThanks for using our Services :) \n";
		break;
	}
}

int main()
{
	LogIn();
}
