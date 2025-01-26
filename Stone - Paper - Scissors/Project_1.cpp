#include <iostream>
#include <cstdlib>
using namespace std;

enum enChoices{Stone = 1, Paper = 2, Scissors = 3};

struct strGame
{
	short noOfRounds=0, playerChoice=0, computerChoice=0, computerWinsTimes=0, playerWinsTimes=0, drawTimes=0;
	bool restartChoice=true;
};

strGame Game;

short ReadPositiveNumber(string Message, short MaxValue) {
	short Number = 0;
	do {
		cout << Message << endl;
		cin >> Number;

		if (Number <= 0 || Number > MaxValue)
			cout << "Please enter a number between 1 and " << MaxValue << ".\n";

	} while (Number <= 0 || Number > MaxValue);
	return Number;
}

short RandomNumber(short From, short To)  // Take the computer choice
{
	//Function to generate a random number 
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string ChoiceToString(enChoices choice) {
	switch (choice) {
	case Stone: return "Stone";
	case Paper: return "Paper";
	case Scissors: return "Scissors";
	}
	return "Unknown"; 
}

void StartGameRound(short roundNumber)
{
	cout << "\n---------------Round " << roundNumber << " ---------------\n";
	Game.playerChoice = ReadPositiveNumber("What is your choice ? 1- Stone 2- Paper 3- Scissors",3);
	Game.computerChoice = RandomNumber(1, 3);
}

void GameRules(strGame& Game)
{
	enChoices playerChoice = (enChoices)Game.playerChoice;
	enChoices computerChoice = (enChoices)Game.computerChoice;

	if ((playerChoice == enChoices::Stone && computerChoice == enChoices::Scissors) || (playerChoice == enChoices::Paper && computerChoice == enChoices::Stone) || (playerChoice == enChoices::Scissors && computerChoice == enChoices::Paper))
	{
		system("color 2F");
		cout << "Player Choice : " << ChoiceToString(playerChoice) << endl;
		cout << "Computer Choice : " << ChoiceToString(computerChoice) << endl;
		cout << "Winner is [Player]";
		Game.playerWinsTimes++;
	}
	else if (playerChoice == computerChoice)
	{
		system("color 6F");
		cout << "Player Choice : " << ChoiceToString(playerChoice) << endl;
		cout << "Computer Choice : " << ChoiceToString(computerChoice) << endl;
		cout << "Winner is [No Winner it's a Draw]";
		Game.drawTimes++;
	}
	else
	{
		cout << "\a";
		system("color 4F");
		cout << "Player Choice : " << ChoiceToString(playerChoice) << endl;
		cout << "Computer Choice : " << ChoiceToString(computerChoice) << endl;
		cout << "Winner is [Computer]";
		Game.computerWinsTimes++;
	}
}

void ShowRoundResults()
{
	cout << "\n------------------------------\n";	
	GameRules(Game);
	cout << "\n------------------------------\n";
}

void ShowGameResults()
{
	cout << "\n------------------------------------------------------------\n";
	cout << "\t\tGame Over\t\t\n";
	cout << "\n------------------------------------------------------------\n";

	cout << "Number of Player Wins Times : " << Game.playerWinsTimes << endl;
	cout << "Number of Computer Wins Times : " << Game.computerWinsTimes << endl;
	cout << "Number of Draw Times : " << Game.drawTimes << endl;


	if (Game.computerWinsTimes > Game.playerWinsTimes)
		cout << "The Overall Winner is [Computer]\n";
	else if (Game.computerWinsTimes < Game.playerWinsTimes)
		cout << "The Overall Winner is [Player]\n";
	else
		cout << "The Game Result is Draw\n";

	cout << "\n------------------------------------------------------------\n";
}

void StonePaperScissorsGame()
{
	char choice;
	
	while (Game.restartChoice) 
	{
		Game.noOfRounds = ReadPositiveNumber("How many Rounds you want to play ? (1-10)",10);
		for (int i = 0; i < Game.noOfRounds; i++)
		{
			StartGameRound(i + 1);
			ShowRoundResults();
		}
		ShowGameResults();

		cout << "Do you want to Play Again Y/N : ";
		cin >> choice;

		if (choice == 'N' || choice == 'n')
		{
			Game.restartChoice = false;
			break;
		}			
		else
			system("cls");

	}
}

int main()
{
	srand((unsigned)time(NULL));

	StonePaperScissorsGame();
}