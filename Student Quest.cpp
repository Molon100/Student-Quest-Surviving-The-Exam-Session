/**
*
* Solution to course project # 11
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Milen Karabadzhakov
* @idnumber 6MI0600662
* @compiler VC
*
* Main program file of the game.
*
*/


#include <iostream>
#include <fstream>
#include <random>

std::mt19937 randomGenerator(std::random_device{}());

const int CAPACITY = 1024;

//Returns the length of the passed string.
size_t myStrlen(const char* str)
{
	if (!str)
	{
		return 0;

	}

	unsigned result = 0;

	while (*str)
	{
		result++;
		str++;
	}

	return result;
}

//Copies the source string into the destination string and overrides the destination string.
void myStrcpy(char* dest, const char* source)
{
	if (!source)
	{
		return;

	}

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
}

//Adds the source string at the end of the destination string.
void myStrcat(char* dest, const char* source)
{
	if (!dest || !source)
	{
		return;
	}

	size_t firstLen = myStrlen(dest);
	dest += firstLen;
	myStrcpy(dest, source);
}

//Compares two strings
// - first < second
// 0 first == second
// + first > second
int myStrcmp(const char* str1, const char* str2)
{
	if (!str1 || !str2)
	{
		return 0;
	}

	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

//Returns the user input.
int userInput()
{
	std::cout << "> ";
	int choice;
	std::cin >> choice;
	return choice;
}

//Starts a new game and lets the user choose a difficulty
void newGame(int& knowledge, int& money, int& psyche, int& energy, int& difficulty)
{
	std::cout << "  [1] Easy         " << std::endl;
	std::cout << "  [2] Normal       " << std::endl;
	std::cout << "  [3] Hard         " << std::endl;
	std::cout << "Choose difficulty: ";
	int choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			knowledge = 80;
			money = 100;
			psyche = 100;
			energy = 100;
			difficulty = 1;
			break;
		}
		else if (choice == 2)
		{
			knowledge = 50;
			money = 80;
			psyche = 80;
			energy = 80;
			difficulty = 2;
			break;
		}
		else if (choice == 3)
		{
			knowledge = 35;
			money = 60;
			psyche = 60;
			energy = 40;
			difficulty = 3;
			break;
		}
		std::cout << "Invalid input!" << std::endl;
		std::cout << "Choose difficulty: ";
		choice = userInput();
	}
}

//Saves the game state with a name from the passed string fileName
void saveGame(char* fileName, int currentDay, int knowledge, int money, int psyche, int energy, int examNumber, int examDates[], int difficulty)
{
	myStrcat(fileName, ".txt");
	std::ofstream out(fileName);
	if (!out)
	{
		std::cout << "Failed to save game" << std::endl;
		return;
	}

	out << currentDay << ' ' << difficulty << std::endl;
	out << knowledge << ' ' << money << ' ' << psyche << ' ' << energy << std::endl;
	out << examNumber << ' ' << examDates[3] << std::endl;
	out.close();
	std::cout << "Game saved" << std::endl;
}

//Loads the game state from a file with a name from the passed string fileName
//If a file with a passed name cannot be opened, returns false. Else returns true.
bool loadGame(char* fileName, int& currentDay, int& knowledge, int& money, int& psyche, int& energy, int& examNumber, int examDates[], int& difficulty)
{
	myStrcat(fileName, ".txt");
	std::ifstream in(fileName);
	if (!in)
	{
		std::cout << "Failed to load game" << std::endl;
		return false;
	}
	in >> currentDay >> difficulty;
	in >> knowledge >> money >> psyche >> energy;
	in >> examNumber >> examDates[3];
	in.close();
	std::cout << "Game loaded" << std::endl;
	return true;
}

//Prints helpful information needed to understand how to play the game.
void helpMenu()
{
	std::cout << "Welcome to Student Quest!" << std::endl;
	std::cout << "Here's a brief breakdown of what you need to know." << std::endl;
	std::cout << std::endl;
	std::cout << "Every day you will be able to choose to do an action." << std::endl;
	std::cout << "In this game you have stats, which will be important to survive:" << std::endl;
	std::cout << "Money, Energy, Psyche, Knowledge" << std::endl;
	std::cout << "Your actions will change these stats." << std::endl;
	std::cout << std::endl;
	std::cout << "It's possible for your actions to not be fully effective, if you're too tired." << std::endl;
	std::cout << "If you run out of either Money or Psyche, the game will end." << std::endl;
	std::cout << "If you run out of Energy you will pass out and miss your action for the day." << std::endl;
	std::cout << std::endl;
	std::cout << "The main objective of this game is to pass all your 5 exams!" << std::endl;
	std::cout << "Passing your exams relies mainly on your Knowledge, but also your Energy and Psyche." << std::endl;
	std::cout << "If you fail an exam, the game ends!" << std::endl;
	std::cout << "If you pass all 5 exams, you win!" << std::endl;
	std::cout << std::endl;
	std::cout << "Exam dates: 1 - 8 day, 2 - 17 day, 3 - 26 day, 4 - random day bewteen exam 3 and 5, 5 - 45 day" << std::endl;
	std::cout << std::endl;
	std::cout << "It's also possible to get random events after each day and action." << std::endl;
	std::cout << "Some will have a positive effect and others - a negative effect!" << std::endl;
	std::cout << std::endl;
	std::cout << "Good luck!" << std::endl;
}

//Based on the rng, can fire a random event at the start of every day
//Returns false, if is not passing out event. Returns true, if is passing out event.
bool generalRandomEvent(int& psyche, int& money, int luck)
{
	if (luck < 3)
	{
		int eventNumber = luck % 4 + 1;
		switch (eventNumber)
		{
		case 1:
			std::cout << "Mom and dad sent you money!" << std::endl;
			std::cout << "+30 money" << std::endl;
			money += 30;
			return false;
		case 2:
			std::cout << "A friend treats you to some coffee!" << std::endl;
			std::cout << "+10 psyche" << std::endl;
			psyche += 10;
			return false;
		case 3:
			std::cout << "You got sick!" << std::endl;
			std::cout << "-20 energy" << std::endl;
			money -= 20;
			return false;
		case 4:
			std::cout << "You had a blackout on your block!" << std::endl;
			std::cout << "The day was skipped." << std::endl;
			money += 30;
			return true;
		default:
			std::cout << "Error with the general random event!" << std::endl;
			return false;
		}
	}
	return false;
}

//Based on the rng, can fire a random event when selecting different studying options
void studyRandomEvent(const char* eventSubType, int& psyche, int& knowledge, int luck)
{
	if (!myStrcmp(eventSubType, "lecture"))
	{
		if (luck < 10)
		{
			std::cout << "You understood the lecture extra hard!" << std::endl;
			std::cout << "+5 knowledge" << std::endl;
			std::cout << "+5 psyche" << std::endl;
			knowledge += 5;
			psyche += 5;
		}
	}
	else if (!myStrcmp(eventSubType, "home"))
	{
		if (luck < 10)
		{
			std::cout << "The neighbours made too much!" << std::endl;
			std::cout << "You couldn't concentrate!" << std::endl;
			std::cout << "-10 knowledge" << std::endl;
			std::cout << "-5 psyche" << std::endl;
			knowledge -= 20;
			psyche -= 5;
		}
	}
	else if (!myStrcmp(eventSubType, "friends"))
	{
		if (luck <= 1)
		{
			std::cout << "A friend showed you a leak of the exam!" << std::endl;
			std::cout << "+50 knowledge" << std::endl;
			std::cout << "+20 psyche" << std::endl;
			knowledge += 50;
			psyche += 20;
		}
	}
}

//Based on the rng, can fire a random event when selecting different food options
void foodRandomEvent(const char* eventSubType, int& psyche, int& energy, int& knowledge, int luck)
{
	if (!myStrcmp(eventSubType, "canteen"))
	{
		if (luck < 10)
		{
			std::cout << "A friend tutored you while eating!" << std::endl;
			std::cout << "+5 knowledge" << std::endl;
			std::cout << "+5 psyche" << std::endl;
			knowledge += 5;
			psyche += 5;
		}
	}
	else if (!myStrcmp(eventSubType, "doner"))
	{
		if (luck < 10)
		{
			std::cout << "The doner was rotten!" << std::endl;
			std::cout << "-20 energy" << std::endl;
			std::cout << "-5 psyche" << std::endl;
			energy -= 20;
			psyche -= 5;
		}
	}
	else if (!myStrcmp(eventSubType, "pizza"))
	{
		if (luck < 10)
		{
			std::cout << "You ate too much pizza!" << std::endl;
			std::cout << "-10 energy" << std::endl;
			std::cout << "+5 psyche" << std::endl;
			energy -= 10;
			psyche += 5;
		}
	}
}

//Based on the rng, can fire a random event when selecting different party options
void partyRandomEvent(const char* eventSubType, int& psyche, int& energy, int& money, int luck)
{
	if (luck < 30)
	{
		std::cout << "You got way too drunk!" << std::endl;
		std::cout << "You got a bad hungover!" << std::endl;
		std::cout << "-10 energy" << std::endl;
		std::cout << "-5 psyche" << std::endl;
		energy -= 10;
		psyche -= 5;
	}
	if (!myStrcmp(eventSubType, "bar"))
	{
		if (luck < 10)
		{
			std::cout << "The waiters messed up your order!" << std::endl;
			std::cout << "You got a partial refund!" << std::endl;
			std::cout << "+10 money" << std::endl;
			money += 10;
		}
	}
	else if (!myStrcmp(eventSubType, "club"))
	{
		if (luck < 10)
		{
			std::cout << "You got into a fight!" << std::endl;
			std::cout << "You did not win!  ;(" << std::endl;
			std::cout << "-30 psyche" << std::endl;
			std::cout << "-10 energy" << std::endl;
			psyche -= 20;
			energy -= 10;
		}
	}
}

//Based on the rng, can fire a random event when taking a break/sleeping
void sleepRandomEvent(int& psyche, int& energy, int luck)
{
	if (luck < 30)
	{
		std::cout << "You had a nightmare!" << std::endl;
		std::cout << "-15 energy" << std::endl;
		std::cout << "-10 psyche" << std::endl;
		energy -= 15;
		psyche -= 10;
	}
}

//Based on the rng, can fire a random event when working
void workRandomEvent(int& psyche, int& money, int luck)
{
	if (luck < 20)
	{
		std::cout << "You messed up something on the job!" << std::endl;
		std::cout << "Your pay got deducted!" << std::endl;
		std::cout << "-20 money" << std::endl;
		std::cout << "-10 psyche" << std::endl;
		money -= 25;
		psyche -= 10;
	}
}

//Prints a textbox with the user's current stats
void statsText(int currentDay, int money, int energy, int psyche, int knowledge, int examNumber)
{
	const int LAST_DAY = 45;
	std::cout << " -------------------" << std::endl;
	std::cout << "| Day " << currentDay << '/' << LAST_DAY << "         |" << std::endl;
	std::cout << "| Money: " << money << " euro   |" << std::endl;
	std::cout << "| Energy: " << energy << "       |" << std::endl;
	std::cout << "| Psyche: " << psyche << "       |" << std::endl;
	std::cout << "| Knowledge: " << knowledge << "    |" << std::endl;
	std::cout << "| Passed exams: " << examNumber - 1 << "  |" << std::endl;
	std::cout << " -------------------" << std::endl;
}

//Prints a menu with the possible study options.
void studyMenuText()
{
	std::cout << "| How will you study today?" << std::endl;
	std::cout << "| [1] Go to lecture" << std::endl;
	std::cout << "| [2] Study at home" << std::endl;
	std::cout << "| [3] Study with friends" << std::endl;
}

//The user inputs a number to choose one study options.
void studyMenuChoice(int partialSuccessDivider, int& knowledge, int& psyche, int& energy, int luck)
{
	int choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			int knowledgeIncrease = 20 / partialSuccessDivider;
			knowledge += knowledgeIncrease;
			energy -= 20;
			psyche -= 10;
			std::cout << "+" << knowledgeIncrease << " knowledge" << std::endl;
			std::cout << "-20 energy" << std::endl;
			std::cout << "-10 psyche" << std::endl;
			studyRandomEvent("lecture", psyche, knowledge, luck);
			break;
		}
		else if (choice == 2)
		{
			int knowledgeIncrease = 15 / partialSuccessDivider;
			knowledge += knowledgeIncrease;
			energy -= 15;
			psyche -= 20;
			std::cout << "+" << knowledgeIncrease << " knowledge" << std::endl;
			std::cout << "-15 energy" << std::endl;
			std::cout << "-20 psyche" << std::endl;
			studyRandomEvent("home", psyche, knowledge, luck);
			break;
		}
		else if (choice == 3)
		{
			int knowledgeIncrease = 5 / partialSuccessDivider;
			int psycheIncrease = 10 / partialSuccessDivider;
			knowledge += knowledgeIncrease;
			energy -= 10;
			psyche += psycheIncrease;
			std::cout << "+" << knowledgeIncrease << " knowledge" << std::endl;
			std::cout << "-10 energy" << std::endl;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			studyRandomEvent("friends", psyche, knowledge, luck);
			break;
		}
		std::cout << "Invalid input!" << std::endl;
		choice = userInput();
	}
}

//Prints a menu with the possible food options.
void eatMenuText()
{
	std::cout << "| Where will you eat today?" << std::endl;
	std::cout << "| [1] At the canteen (10 euro)" << std::endl;
	std::cout << "| [2] Doner kebap (15 euro)" << std::endl;
	std::cout << "| [3] Get a pizza (20 euro)" << std::endl;
}

//The user inputs a number to choose one food option.
void eatMenuChoice(int partialSuccessDivider, int& knowledge, int& psyche, int& money, int& energy, int luck)
{
	int choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			int energyIncrease = 20 / partialSuccessDivider;
			int psycheIncrease = 5 / partialSuccessDivider;
			energy += energyIncrease;
			money -= 10;
			psyche += psycheIncrease;
			std::cout << "+" << energyIncrease << " energy" << std::endl;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			foodRandomEvent("canteen", psyche, energy, knowledge, luck);
			break;
		}
		else if (choice == 2)
		{
			int energyIncrease = 25 / partialSuccessDivider;
			int psycheIncrease = 10 / partialSuccessDivider;
			energy += energyIncrease;
			money -= 15;
			psyche += psycheIncrease;
			std::cout << "+" << energyIncrease << " energy" << std::endl;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			foodRandomEvent("doner", psyche, energy, knowledge, luck);
			break;
		}
		else if (choice == 3)
		{
			int energyIncrease = 30 / partialSuccessDivider;
			int psycheIncrease = 15 / partialSuccessDivider;
			energy += energyIncrease;
			money -= 20;
			psyche += psycheIncrease;
			std::cout << "+" << energyIncrease << " energy" << std::endl;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			foodRandomEvent("pizza", psyche, energy, knowledge, luck);
			break;
		}
		std::cout << "Invalid input!" << std::endl;
		choice = userInput();
	}
}

//Prints a menu with the possible party options.
void partyMenuText()
{
	std::cout << "| Where will you go out today?" << std::endl;
	std::cout << "| [1] To the bar (20 euro)" << std::endl;
	std::cout << "| [2] To the club (25 euro)" << std::endl;
}

//The user inputs a number to choose one party option.
void partyMenuChoice(int partialSuccessDivider, int& psyche, int& money, int& energy, int luck)
{
	int choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			int psycheIncrease = 30 / partialSuccessDivider;
			psyche += psycheIncrease;
			energy -= 10;
			money -= 20;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			std::cout << "-10 energy" << std::endl;
			partyRandomEvent("bar", psyche, energy, money, luck);
			break;
		}
		else if (choice == 2)
		{
			int psycheIncrease = 40 / partialSuccessDivider;
			psyche += psycheIncrease;
			energy -= 15;
			money -= 25;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			std::cout << "-15 energy" << std::endl;
			partyRandomEvent("club", psyche, energy, money, luck);
			break;
		}
		std::cout << "Invalid input!" << std::endl;
		choice = userInput();
	}
}

//Determines if the action wil have partial effect, depending on the level of energy.
//Partial success means halving the increase of user stats.
bool actionIsPartialSuccess(int energy, int luck)
{
	if (energy >= 80)
	{
		return false;
	}
	else if (energy >= 40)
	{
		return luck > 75 ? true : false;
	}
	else
	{
		return luck > 50 ? true : false;
	}
}

//Prints a menu with the different options a user can take each day.
void actionMenuText()
{
	std::cout << "| What action will you choose?" << std::endl;
	std::cout << "| [1] Study" << std::endl;
	std::cout << "| [2] Eat" << std::endl;
	std::cout << "| [3] Go out" << std::endl;
	std::cout << "| [4] Take a break" << std::endl;
	std::cout << "| [5] Go to part-time work" << std::endl;
	std::cout << "| [6] Save and quit game" << std::endl;
}

//Lets the user input which action he wants take from the action menu.
//Returns true if saving game, returns false if anything else.
bool actionMenuChoice(int currentDay, int& knowledge, int& money, int& psyche, int& energy, int luck, int examNumber, int examDates[], int difficulty)
{
	bool isPartialSucces = actionIsPartialSuccess(energy, luck);
	int partialSuccessDivider = 1 + isPartialSucces;

	int  choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			studyMenuText();
			studyMenuChoice(partialSuccessDivider, knowledge, psyche, energy, luck);
			return false;
		}
		else if (choice == 2)
		{
			eatMenuText();
			eatMenuChoice(partialSuccessDivider, knowledge, psyche, money, energy, luck);
			return false;
		}
		else if (choice == 3)
		{
			partyMenuText();
			partyMenuChoice(partialSuccessDivider, knowledge, psyche, energy, luck);
			return false;
		}
		else if (choice == 4)
		{
			int energyIncrease = 30;
			int psycheIncrease = 5;
			energy += energyIncrease;
			psyche += psycheIncrease;
			std::cout << "+" << energyIncrease << " energy" << std::endl;
			std::cout << "+" << psycheIncrease << " psyche" << std::endl;
			sleepRandomEvent(psyche, energy, luck);
			return false;
		}
		else if (choice == 5)
		{
			int moneyIncrease = 40 / partialSuccessDivider;
			int energyDecrease = 20;
			int psycheDecrease = 10;
			money += moneyIncrease;
			energy -= energyDecrease;
			psyche -= psycheDecrease;
			std::cout << "+" << moneyIncrease << " money" << std::endl;
			std::cout << "-" << energyDecrease << " energy" << std::endl;
			std::cout << "-" << psycheDecrease << " psyche" << std::endl;
			workRandomEvent(psyche, money, luck);
			return false;
		}
		else if (choice == 6)
		{
			std::cout << "Set a name for your save(without whitespace): ";
			char name[CAPACITY];
			std::cin >> name;
			saveGame(name, currentDay, knowledge, money, psyche, energy, examNumber, examDates, difficulty);
			return true;
		}
		std::cout << "Invalid input!" << std::endl;
		choice = userInput();
	}
}

//Checks if any of the lose conditions are met.
//If one or more are met, returns true and prints lose message.
bool loseConditions(int money, int psyche)
{
	if (money <= 0)
	{
		std::cout << " --------------------------------" << std::endl;
		std::cout << "|          Game over!            |" << std::endl;
		std::cout << "|                                |" << std::endl;
		std::cout << "|  You ran out of money          |" << std::endl;
		std::cout << "|  and moved back in with        |" << std::endl;
		std::cout << "|  your parents! (and quit uni)  |" << std::endl;
		std::cout << " --------------------------------" << std::endl;
		return true;
	}
	if (psyche <= 0)
	{
		std::cout << " --------------------------------" << std::endl;
		std::cout << "|          Game over!            |" << std::endl;
		std::cout << "|                                |" << std::endl;
		std::cout << "|  Your psyche could not handle  |" << std::endl;
		std::cout << "|  all this torture and          |" << std::endl;
		std::cout << "|  you quit university!          |" << std::endl;
		std::cout << " --------------------------------" << std::endl;
		return true;
	}
	return false;
}

//Prints win message.
void winMessage()
{
	std::cout << " -------------------------------" << std::endl;
	std::cout << "|   Congratulations! Victory!   |" << std::endl;
	std::cout << "|                               |" << std::endl;
	std::cout << "|  You passed all 5 exams and   |" << std::endl;
	std::cout << "|  lived to tell the tale!      |" << std::endl;
	std::cout << " -------------------------------" << std::endl;
}

//Returns true, if exam is passed, and returns false, if exam is not passed.
//If passed, prints that it's passed. If not, prints that the game is over.
bool takeExam(int& knowledge, int& psyche, int& energy, int luck, int& examNumber, int difficulty)
{
	const int PASSING_EXAM_POINTS = 75;
	int penalty = (examNumber - 1) * 5;
	double examPoints = (knowledge * 0.75) + (psyche * 0.1) + (energy * 0.1) + (luck * 0.2) - penalty;
	if (examPoints >= PASSING_EXAM_POINTS)
	{
		std::cout << "Exam #" << examNumber << " has been succesfully passed!" << std::endl;
		examNumber++;
		int energyDecrease = 20;
		int psycheIncrease = 20;
		int knowledgeDecrease = 25 + 20 * difficulty;
		energy -= energyDecrease;
		psyche += psycheIncrease;
		knowledge -= knowledgeDecrease;
		std::cout << "-" << energyDecrease << " energy" << std::endl;
		std::cout << "+" << psycheIncrease << " psyche" << std::endl;
		std::cout << "Remaining knowledge: " << knowledge << std::endl;
		return true;
	}
	else
	{
		std::cout << " -------------------------------" << std::endl;
		std::cout << "|          Game over!           |" << std::endl;
		std::cout << "|                               |" << std::endl;
		std::cout << "|  You failed to pass           |" << std::endl;
		std::cout << "|  exam #" << examNumber << " !                    | " << std::endl;
		std::cout << " -------------------------------" << std::endl;
		return false;
	}
}

//Increases the current day with one.
//Randomly resets luck.
void nextDay(int& currentDay, int& luck)
{
	currentDay++;
	randomGenerator.seed(std::random_device{}());
	luck = randomGenerator() % 100 + 1;
}

//Resets stats, if they're over a 100, with the remainder of dividing by 100.
void resetIfOver100(int& knowledge, int& psyche, int& energy)
{
	knowledge -= (knowledge / 100) * (knowledge % 100);
	psyche -= (psyche / 100) * (psyche % 100);
	energy -= (energy / 100) * (energy % 100);
}

//Main game loop function of the game.
void gameloop(int& currentDay, int& knowledge, int& money, int& psyche, int& energy, int& luck, int& examNumber, int examDates[], int difficulty)
{
	const int FIRST_EXAM_DATE = examDates[0];
	const int SECOND_EXAM_DATE = examDates[1];
	const int THIRD_EXAM_DATE = examDates[2];
	const int FOURTH_EXAM_DATE = examDates[3];
	std::cout << FOURTH_EXAM_DATE << std::endl;
	const int FIFTH_EXAM_DATE = examDates[4];
	while (currentDay <= FIFTH_EXAM_DATE)
	{
		char autosaveStr[CAPACITY] = "autosave";
		saveGame(autosaveStr, currentDay, knowledge, money, psyche, energy, examNumber, examDates, difficulty);
		statsText(currentDay, money, energy, psyche, knowledge, examNumber);
		if (currentDay == FIRST_EXAM_DATE || currentDay == SECOND_EXAM_DATE || currentDay == THIRD_EXAM_DATE
			|| currentDay == FOURTH_EXAM_DATE || currentDay == FIFTH_EXAM_DATE)
		{
			if (!takeExam(knowledge, psyche, energy, luck, examNumber, difficulty))
			{
				return;
			}
		}
		else if (energy > 0)
		{
			if (generalRandomEvent(psyche, money, luck))
			{
				nextDay(currentDay, luck);
				continue;
			}
			std::cout << "Next exam is in " << examDates[examNumber - 1] - currentDay << " days." << std::endl;
			actionMenuText();
			if (actionMenuChoice(currentDay, knowledge, money, psyche, energy, luck, examNumber, examDates, difficulty))
			{
				return;
			}
		}
		else
		{
			std::cout << "No energy. You passed out!" << std::endl;
			std::cout << "Your action was skipped today!" << std::endl;
			energy = 40;
			psyche -= 10;
		}
		if (loseConditions(money, psyche))
		{
			return;
		}
		resetIfOver100(knowledge, psyche, energy);

		nextDay(currentDay, luck);
	}
	winMessage();
}

//Prints the main menu options and lets the user input an option
void mainMenu(int& currentDay, int& knowledge, int& money, int& psyche, int& energy, int& luck, int& difficulty, int& examNumber, int examDates[])
{
	std::cout << " Student Quest: Surviving the exam session" << std::endl;
	std::cout << " -----------------------" << std::endl;
	std::cout << "| [1] Start new game.   |" << std::endl;
	std::cout << "| [2] Load game.        |" << std::endl;
	std::cout << "| [3] Help              |" << std::endl;
	std::cout << " -----------------------" << std::endl;
	int choice = userInput();
	while (true)
	{
		if (choice == 1)
		{
			newGame(knowledge, money, psyche, energy, difficulty);
			gameloop(currentDay, knowledge, money, psyche, energy, luck, examNumber, examDates, difficulty);
			break;
		}
		else if (choice == 2)
		{
			std::cout << "Load file with name(without whitespace): ";
			char name[1024];
			std::cin >> name;
			while (!loadGame(name, currentDay, knowledge, money, psyche, energy, examNumber, examDates, difficulty))
			{
				std::cout << "Load file with name(without whitespace): ";
				std::cin >> name;
			}
			gameloop(currentDay, knowledge, money, psyche, energy, luck, examNumber, examDates, difficulty);
			break;
		}
		else if (choice == 3)
		{
			helpMenu();
		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
		choice = userInput();
	}
}

//Main function.
//The program starts here.
int main()
{
	int currentDay = 1;
	int knowledge = 0;
	int money = 0;
	int psyche = 0;
	int energy = 0;
	int luck = randomGenerator() % 100 + 1;

	int examNumber = 1;
	int difficulty = 1;

	const int FIRST_EXAM_DATE = 8;
	const int SECOND_EXAM_DATE = 17;
	const int THIRD_EXAM_DATE = 26;
	const int FIFTH_EXAM_DATE = 45;
	const int DAYS_BETWEEN_THIRD_AND_FIFTH_EXAM = 27;
	int fourthExamDate = luck % 18 + DAYS_BETWEEN_THIRD_AND_FIFTH_EXAM;

	int examDates[5] = { FIRST_EXAM_DATE, SECOND_EXAM_DATE, THIRD_EXAM_DATE, fourthExamDate, FIFTH_EXAM_DATE };

	mainMenu(currentDay, knowledge, money, psyche, energy, luck, difficulty, examNumber, examDates);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
