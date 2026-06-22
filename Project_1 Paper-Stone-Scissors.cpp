#include <iostream>
#include<limits>
#include <cstdlib>
#include <ctime>
#define NOMINMAX
#include<windows.h>
using namespace std;

enum enGame { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { User_Win = 1, Comp_Win = 2, Draw = 3 };
enum enRepeat_Game { Yes = 1, No = 0 };

struct stRoundInfo {
	enGame Player_Choice;
	enGame Computer_Choice;
	enWinner Winner;
};


struct stGameResults {
	short GameRounds = 0;
	short PlayerScore = 0;
	short ComputerScore = 0;
	short DrawTimes = 0;
	enWinner Winner;
};

struct stGameInfo {
	short Round = 0;
	stRoundInfo roundInfo[10];
	stGameResults GameResults;
};


static int ReadIntNumbers(const string& str) {
	while (true) {
		int num = 0;
		cout << str;
		cin >> num;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
		}
		else {
			return num;
		}
	}
}

void SetColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

static int ReadIntWithMaxLimit(const string& str, int Min,int Max) {
	int num = 0;
	do {
		num = ReadIntNumbers(str);
		if (num <= Max&&num>=Min) return num;
		cout << "Follow instructions, Please! (Max " << Max << ")\n";
	} while (true);
}


static int RandomNumber(int from, int to) {
	return  rand() % (to - from + 1) + from;
}

enGame getCompChoice() {
	return enGame(RandomNumber(1, 3));
} 

enGame getPlayerChoice() {
	return enGame(ReadIntWithMaxLimit("Enter Your Choice:\t", 1, 3));;
}


static void Logic_Compare(stRoundInfo &round) {
	if (round.Player_Choice == round.Computer_Choice) {
		round.Winner = Draw; return;
	}
	round.Winner = (round.Player_Choice == enGame::Stone && round.Computer_Choice == enGame::Paper)||
		 (round.Player_Choice == enGame::Paper && round.Computer_Choice == enGame::Scissor)||
		 (round.Player_Choice == enGame::Scissor && round.Computer_Choice == enGame::Stone)? 
		  Comp_Win : User_Win;
	return;
}
static void Separate() {
	cout << "\n--------------------------------------------------\n";
}

static void GameMenue() {
	cout << "\n*** C H O I C E S ***\n\n";
	cout << "1.\tStone\n";
	cout << "2.\tPaper\n";
	cout << "3.\tScissor\n\n";

}
string enGameToString(const enGame &Choice) {

	string arrChoices[3] = {"Stone","Paper","Scissor"};
	return arrChoices[Choice - 1];
}
string enWinnerToString(const enWinner& Choice) {

	switch (Choice) {
	case enWinner::User_Win: return "You:-)";
	case enWinner::Comp_Win: return "Computer:-(";
	case enWinner::Draw:     return "Draw!";
	default: return "Undefined!!";
	}
}

void ChooseTheSuitableColor(const enWinner &Choice) {
	switch (Choice) {
	case enWinner::User_Win:
		SetColor(10);
		break;
	case enWinner::Comp_Win:
		SetColor(12);
		break;
	case enWinner::Draw:
		SetColor(14);
		break;
	default:
		SetColor(7);
	}
}

void ShowResultForSingleRound(const stRoundInfo &round) {
	cout << "Player 1 Choice:\t[" << enGameToString(round.Player_Choice) << "].\n";
	cout << "Computer Choice:\t[" << enGameToString(round.Computer_Choice) << "].\n";
	ChooseTheSuitableColor(round.Winner);
	cout << "Round Winner:\t[" << enWinnerToString(round.Winner)<<"].\n";
	SetColor(7);
}


static void GameRound(stRoundInfo &round) {
	
		round.Player_Choice= getPlayerChoice();
		round.Computer_Choice = getCompChoice();
		

}

void GameWinner(stGameResults &GameResults) {
	GameResults.Winner=(GameResults.PlayerScore > GameResults.ComputerScore) ? enWinner::User_Win : (GameResults.PlayerScore < GameResults.ComputerScore) ? enWinner::Comp_Win : enWinner::Draw;
}

void StoreGameResults(const stRoundInfo &round,stGameResults &GameResults) {
	
	switch (round.Winner) {
	case enWinner::User_Win:
		GameResults.PlayerScore++;
		break;
	case enWinner::Comp_Win:
		GameResults.ComputerScore++;
		break;
	case enWinner::Draw:
		GameResults.DrawTimes++;
		break;
	}GameResults.GameRounds++;
}

static void TheCompleteGame(stGameInfo &GameInfo) {
	GameMenue();
	for (int i = 0; i < GameInfo.Round; i++) {
		cout << "---------- [Round " << i+1 << "] ----------\n";
		GameRound(GameInfo.roundInfo[i]);
		Logic_Compare(GameInfo.roundInfo[i]);
		ShowResultForSingleRound(GameInfo.roundInfo[i]);
		StoreGameResults(GameInfo.roundInfo[i],GameInfo.GameResults);
	}
	GameWinner(GameInfo.GameResults);

}
void Title(const string &title) {
	Separate();
	cout << "\n             +++ ";
	for (int i = 0; i < title.length(); i++) {
		cout << char(toupper(title[i])) << " ";
	}
	cout << "+++             \n";
	Separate();
}

void ShowResultsForAllGame(const stGameInfo &GameInfo) {
	Title("Game Over");
	cout << "\n------------------ Game Results ------------------\n";
	cout << "Total Rounds:\t[" << GameInfo.Round << "]\n";
	cout << "Player Score:\t[" << GameInfo.GameResults.PlayerScore << "]\n";
	cout << "Computer Score:\t[" << GameInfo.GameResults.ComputerScore << "]\n";
	cout << "Draw Times:\t[" << GameInfo.GameResults.DrawTimes << "]\n";

	if (GameInfo.GameResults.PlayerScore > GameInfo.GameResults.ComputerScore) {
		SetColor(10);
		cout << "\nCongratulations, you have won!\n\n";
		SetColor(7);
	}
	else if (GameInfo.GameResults.PlayerScore < GameInfo.GameResults.ComputerScore) {
		SetColor(11);
		cout << "\nGood luck next time!\n\n";
		SetColor(7);
	}
	else {
		SetColor(14);
		cout << "\nDraw, no winner!\n\n";
		SetColor(7);
	}

}






static void Start_Game(stGameInfo &GameInfo) {
	
		Title("Welcome to the Game");
	    GameInfo.Round = ReadIntWithMaxLimit("How many Rounds form 1 to 10:\t", 1,10);
		TheCompleteGame(GameInfo);
		Separate();
	
}
void Start_EndGame() {
	stGameInfo GameInfo{};

	Start_Game(GameInfo);
	ShowResultsForAllGame(GameInfo);
}

int main()
{

	srand((unsigned)time(NULL));
	enRepeat_Game choice ;
	do {
		system("cls");
		Start_EndGame();

		choice = enRepeat_Game(ReadIntWithMaxLimit("\nDo you want to play again? [1]: Yes, [0]: No?\t", 0,1));

	} while (choice == enRepeat_Game::Yes);

	cout << "Goodbye!" << endl;
	return 0;
}

