#pragma warning (disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileName = "Bank Clients.txt";
const string delimiter = "#//#";

enum enMainMenuOptions{ ShowList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, SearchClient = 5, Transactions = 6, Exit = 7};
enum enTransactionMenuOptions { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4};

struct stClientData
{
	string accountNumber, Name, Phone, pinCode;
	double accountBalance;
};

int ReadPositiveNumber(string Message)
{
	int Number = 0;
	do
	{
		cout << "\n" << Message;
		cin >> Number;
	} while (Number <= 0);
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
	int Num = 0;

	while (Num < from || Num > to)
	{
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

		else if(input.length() < minLength)
			cout << "\nWrong Input. Please Enter a String with min length : " << minLength << " Characters \n";


	} while (cin.fail() || (input.length() > maxLength || input.length() < minLength));

	return input;
}

stClientData ReadClientData()
{
	stClientData client;

	cout << "\nPlease Enter Client Data:\n";
	
	client.accountNumber = ReadValidString("Enter Account Number : ", 10);
	client.pinCode = ReadValidString("Enter PinCode Number : ",4,4);
	client.Name = ReadValidString("Enter Client Name : ",25);
	client.Phone = ReadValidString("Enter Phone Number : ",12);
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

	cout << "\nAre you sure you want to delete this Client ? y/n : ";
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

void DeleteClientMenu(vector<stClientData>& Clients, string AccNumber, stClientData& FoundClient)
{
	system("cls");
	cout << "\n----------------------Deleting a Client Menu--------------------------\n";

	if (FindClientByAccountNumber(Clients,AccNumber,FoundClient))
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

	cout << "\nAre you sure you want to Update this Client ? y/n : ";
	cin >> choice;

	return tolower(choice) == 'y';

}

void UpdateClientRecordByAccountNumber(bool confirmation, stClientData client, string delimiter)
{
	if (confirmation)
	{
		string OldRecord = ConvertRecordToLine(client, delimiter);
		string NewRecord = ConvertRecordToLine(ReadClientData(), delimiter);

		UpdateRecordFromFile("Bank Clients.txt", OldRecord, NewRecord);
		cout << "\nClient Updated Successfully" << endl;
	}
	else
		cout << "\nClient Update has been Cancelled" << endl;
}

void UpdateClientMenu(vector<stClientData>& Clients, string AccNumber, stClientData& FoundClient)
{
	system("cls");
	cout << "\n----------------------Updating a Client----------------------\n";

	if (FindClientByAccountNumber(Clients,AccNumber,FoundClient))
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

	MyFile.open(fileName, ios::out | ios::app);
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

	MyFile.open(fileName, ios::out | ios::app);

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
				UpdateRecordFromFile(fileName, OldClientDataRecord, ConvertRecordToLine(NewClient, delimiter));
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
					UpdateRecordFromFile(fileName, OldClientDataRecord, ConvertRecordToLine(NewClient, delimiter));
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
	cout << "\n\t 7- Exit the Program";
}

void DisplayTransactionMenu();

void DisplayMainMenu()
{	
	system("cls");
	MainMenuOptions();
	enMainMenuOptions choice = (enMainMenuOptions)ReadValidPositiveNumber("\nEnter an Option from 1 to 6 : ", 1, 7);
	vector<stClientData> Clients = LoadClientsDataFromFileToVector(fileName, delimiter);
	stClientData Client;

	switch (choice)
	{
	case ShowList:
		ShowClientListMenu(Clients);
		DisplayMainMenu();
		break;

	case AddClient:
		AddClientMenu(Clients);
		DisplayMainMenu();
		break;

	case DeleteClient:
		DeleteClientMenu(Clients, ReadValidString("Enter the Client's Account Number : "), Client);
		DisplayMainMenu();
		break;

	case UpdateClient:
		UpdateClientMenu(Clients, ReadValidString("Enter the Client's Account Number : "), Client);
		DisplayMainMenu();
		break;

	case SearchClient:
		SearchClientMenu(Clients, Client);
		DisplayMainMenu();
		break;
	
	case Transactions:
		DisplayTransactionMenu();
		break;

	case Exit:
		system("cls");
		cout << "\nThanks for using our Services :) \n";
		break;
	}
}

void DisplayTransactionMenu()
{
	system("cls");
	TranscationMenuOptions();
	enTransactionMenuOptions choice = (enTransactionMenuOptions)ReadValidPositiveNumber("\nEnter an Option from 1 to 4 : ", 1, 4);
	vector<stClientData> Clients = LoadClientsDataFromFileToVector(fileName, delimiter);
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
		DisplayMainMenu();
		break;
	}
}

int main()
{
	DisplayMainMenu();
}