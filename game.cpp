#include<iostream>
#include<cstdlib>
#include<ctime>
#include<time.h>
using namespace std;


class helper {
public:
	static int stringlength(const char* str);
	static void stringcopy(char* str1, int str2len, const char* str2);
};
int helper::stringlength(const char* str) {
	int len;
	for (len = 0; str[len] != '\0'; len++);
	return len;
}
void helper::stringcopy(char* str1, int str2len, const char* str2) {
	for (int i = 0; i < str2len - 1 && str1[i]; i++)
	{
		*(str1 + i) = *(str2 + i);
	}*(str1 + str2len - 1) = '\0';
}

class Participant {
	int Score;
public:
	Participant() :Score(0) {}
	virtual int makeChoice() = 0;
	void incrementScore();
	int getScore();
	void resetScore();
	virtual ~Participant() {}


};
void Participant::incrementScore() {
	Score++;
}
int Participant::getScore() {
	return Score;
}
void Participant::resetScore() {
	Score = 0;
}


class Player :public Participant {
public:
	virtual int makeChoice();

};
int Player::makeChoice() {
	int choice;
	cout << "Enter 1{Rock), 2(Paper), 3(Scissors).\n";
	cin >> choice;
	while (choice < 1 || choice>3)
	{
		cout << "Invalid Choice. Try Again!\n";
		cin >> choice;

	}
	return choice;
}

class Computer :public Participant {
	int comp;
public:
	virtual int makeChoice();


};
int Computer::makeChoice() {

	int x = time(0);
	srand(x);
	return (rand() % 3) + 1;

}
class Game {
	Player player;
	Computer computer;
	char* object;

	int playerScore;
	int computerScore;
	int round;


public:
	Game();
	Game(const char* obj);
	~Game();
	const char* ConvertChoiceToString(int choice);
	int determineWinner(int playerChoice, int computerChoice);
	void play();

};
Game::Game() {
	object = nullptr;
	playerScore = 0;
	computerScore = 0;
	round = 0;

}
Game::Game(const char* obj) {

	int length = helper::stringlength(obj);
	object = new char[length + 1];
	helper::stringcopy(object, length + 1, obj);

}
Game::~Game() {
	delete[] object;
	object = nullptr;
}

const char* Game::ConvertChoiceToString(int choice) {

	const char* obj = nullptr;
	if (choice == 1)
	{
		obj = "Rock";
	}
	else if (choice == 2)
	{
		obj = "Paper";
	}
	else if (choice == 3)
	{
		obj = "scissors";
	}

	int length = helper::stringlength(obj);
	delete[]object;
	object = new char[length + 1];
	helper::stringcopy(object, length + 1, obj);
	return object;

}
int Game::determineWinner(int playerChoice, int computerChoice) {

	if (playerChoice == computerChoice)
	{
		return 0;
	}
	if ((playerChoice == 1 && computerChoice == 3) || (playerChoice == 2 && computerChoice == 1) || (playerChoice == 3 && computerChoice == 2))
	{
		return 1;
	}
	return -1;
}
void Game::play() {

	int x = time(0);
	srand(x);

	cout << "==========================================\n";
	cout << " WELCOME TO ROCK, PAPER, SCISSORS GAME\n";
	cout << "==========================================\n";
	cout << "First to score 3 points wins the match!\n\n";

	while (playerScore < 3 && computerScore < 3)
	{
		cout << "--------------------Round: " << round++ << "--------------------" << endl;


		int pChoice = player.makeChoice();
		int cChoice = computer.makeChoice();

		cout << "You chose: " << ConvertChoiceToString(pChoice) << endl;
		cout << "Computer chose: " << ConvertChoiceToString(cChoice) << endl;


		int result = determineWinner(pChoice, cChoice);

		if (result == 1) {
			player.incrementScore();
			cout << "You win this round!\n";
		}
		else if (result == -1) {
			computer.incrementScore();
			cout << "Computer wins this round!\n";
		}
		else {
			cout << "It's a tie!\n";
		}

		cout << "Score => You: " << player.getScore()
			<< " | Computer: " << computer.getScore() << "\n";


		if (player.getScore() == 3 || computer.getScore()==3)
		{

			if (player.getScore() == 3)
				cout << "\nCongratulations! You won the game.\n\n";
			else
				cout << "\nComputer won the game. Better luck next time!\n\n";
			char furtherPlay;
			cout << "If you want new match press 'Y':";
			cin >> furtherPlay;
			if (furtherPlay == 'Y' || furtherPlay == 'y')
			{
				round = 0;
				player.resetScore();
				computer.resetScore();
				
			}
			else {
				return;
			}
		}

	}

}


int main() {


	int x = time(0);
	srand(x);

	Game g("Rock Paper Scissors");
	g.play();
	return 0;

}