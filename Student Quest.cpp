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
* <main program file of the game>
*
*/


#include <iostream>
#include <fstream>
#include <random>

std::mt19937 randomGenerator(std::random_device{}());

const int CAPACITY = 1024;

size_t myStrlen(const char* str)
{
    if (!str)
        return 0;

    unsigned result = 0;

    while (*str)
    {
        result++;
        str++;
    }

    return result;
}

void myStrcpy(char* dest, const char* source)
{
    if (!source)
        return;

    while (*source)
    {
        *dest = *source;
        dest++;
        source++;
    }

    *dest = '\0';
}

void myStrcat(char* dest, const char* source)
{
    if (!dest || !source)
        return;

    size_t firstLen = myStrlen(dest);
    dest += firstLen;
    myStrcpy(dest, source);
}

int myStrcmp(const char* str1, const char* str2)
{
    if (!str1 || !str2)
        return 0;

    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void mainMenu()
{
    std::cout << " -----------------------" << std::endl;
    std::cout << "| [1] Start new game.   |" << std::endl;
    std::cout << "| [2] Load game.        |" << std::endl;
    std::cout << "| [3] Help              |" << std::endl;
    std::cout << " -----------------------" << std::endl;
}

void newGame(int &knowledge, int &money, int &psyche, int &energy, int &difficulty)
{
    std::cout << "  [1] Easy         " << std::endl;
    std::cout << "  [2] Normal       " << std::endl;
    std::cout << "  [3] Hard         " << std::endl;
    std::cout << "Choose difficulty: ";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        knowledge = 80;
        money = 100;
        psyche = 100;
        energy = 100;
        difficulty = 1;
        break;
    case 2:
        knowledge = 50;
        money = 80;
        psyche = 80;
        energy = 80;
        difficulty = 2;
        break;
    case 3:
        knowledge = 35;
        money = 60;
        psyche = 60;
        energy = 40;
        difficulty = 3;
        break;
    default:
        break;
    }
}


void saveGame(char* fileName, int &currentDay, int &knowledge, int &money, int &psyche, int &energy, int &examNumber, int examDates[], int &difficulty)
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

bool loadGame(char* fileName, int &currentDay, int &knowledge, int &money, int &psyche, int &energy, int &examNumber, int examDates[], int& difficulty)
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

void helpMenu()
{

}

void studyMenu(int partialSuccessDivider, int &knowledge, int &psyche, int &money, int &energy)
{
    std::cout << " --------------------------" << std::endl;
    std::cout << "| How will you study       |   Knowledge: " << knowledge << std::endl;
    std::cout << "| today?                   |   Energy:    " << energy << std::endl;
    std::cout << "| [1] Go to lecture        |   Psyche:    " << psyche << std::endl;
    std::cout << "| [2] Study at home        |   Money:     " << money << std::endl;
    std::cout << "| [3] Study with friends   |" << std::endl;
    std::cout << " --------------------------" << std::endl;

    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        knowledge += 20 / partialSuccessDivider;
        energy -= 20;
        psyche -= 10;
        break;
    case 2:
        knowledge += 15 / partialSuccessDivider;
        energy -= 15;
        psyche -= 20;
        break;
    case 3:
        knowledge += 5 / partialSuccessDivider;
        energy -= 10;
        psyche += 10 / partialSuccessDivider;
        break;
    default:
        break;
    }
}

void eatMenu(int partialSuccessDivider, int &knowledge, int &psyche, int &money, int &energy)
{
    std::cout << " --------------------------" << std::endl;
    std::cout << "| Where will you eat       |   Knowledge: " << knowledge << std::endl;
    std::cout << "| today?                   |   Energy:    " << energy << std::endl;
    std::cout << "| [1] At the canteen       |   Psyche:    " << psyche << std::endl;
    std::cout << "| [2] Doner kebap          |   Money:     " << money << std::endl;
    std::cout << "| [3] Get a pizza          |" << std::endl;
    std::cout << " --------------------------" << std::endl;

    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        energy += 20 / partialSuccessDivider;
        money -= 10;
        psyche += 5 / partialSuccessDivider;
        break;
    case 2:
        energy += 25 / partialSuccessDivider;
        money -= 15;
        psyche += 10 / partialSuccessDivider;
        break;
    case 3:
        energy += 30 / partialSuccessDivider;
        money -= 20;
        psyche += 10 / partialSuccessDivider;
        break;
    default:
        break;
    }
}

void partyMenu(int partialSuccessDivider, int &knowledge, int &psyche, int &money, int &energy)
{
    std::cout << " --------------------------" << std::endl;
    std::cout << "| Where will you go out    |   Knowledge: " << knowledge << std::endl;
    std::cout << "| today?                   |   Energy:    " << energy << std::endl;
    std::cout << "| [1] To the bar           |   Psyche:    " << psyche << std::endl;
    std::cout << "| [2] To the club          |   Money:     " << money << std::endl;
    std::cout << " --------------------------" << std::endl;

    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        psyche += 30 / partialSuccessDivider;
        energy -= 10;
        money -= 20;
        break;
    case 2:
        psyche += 40 / partialSuccessDivider;
        energy -= 15;
        money -= 25;
        break;
    default:
        break;
    }
}

bool actionIsPartialSucces(int &energy, int &luck)
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

void actionMenuText(int &knowledge, int &psyche, int &money, int &energy)
{
    std::cout << " --------------------------" << std::endl;
    std::cout << "| What action will         |   Knowledge: " << knowledge << std::endl;
    std::cout << "| you choose?              |   Energy:    " << energy << std::endl;
    std::cout << "| [1] Study                |   Psyche:    " << psyche << std::endl;
    std::cout << "| [2] Eat                  |   Money:     " << money << std::endl;
    std::cout << "| [3] Go out               |" << std::endl;
    std::cout << "| [4] Take a break         |" << std::endl;
    std::cout << "| [5] Go to part-time work |" << std::endl;
    std::cout << "| [6] Quit game            |" << std::endl;
    std::cout << " --------------------------" << std::endl;
}

void actionMenuChoice(int choice, int &currentDay, int &knowledge, int &money, int &psyche, int &energy, int &luck, int &examNumber, int examDates[], int &difficulty)
{
    bool isPartialSucces = actionIsPartialSucces(energy, luck);
    int partialSuccessDivider = 1 + isPartialSucces;
    switch (choice)
    {
        case 1:
            studyMenu(partialSuccessDivider, knowledge, psyche, money, energy);
            break;
        case 2:
            eatMenu(partialSuccessDivider, knowledge, psyche, money, energy);
            break;
        case 3:
            partyMenu(partialSuccessDivider, knowledge, psyche, money, energy);
            break;
        case 4:
            energy += 50;
            psyche += 10;
            break;
        case 5:
            money += 40 / partialSuccessDivider;
            energy -= 20;
            psyche -= 10;
            break;
        case 6:
            std::cout << "Set a name for your save: ";
            char name[CAPACITY];
            std::cin >> name;
            saveGame(name, currentDay, knowledge, money, psyche, energy, examNumber, examDates, difficulty);
            exit(0);
            break;
    default:
        break;
    }
}

bool randomEvent(const char* eventType, int &psyche, int &money, int &luck)
{
    if (!myStrcmp(eventType,"general"))
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
                break;
            case 2:
                std::cout << "A friend treats you to some coffee!" << std::endl;
                std::cout << "+10 psyche" << std::endl;
                psyche += 10;
                return false;
                break;
            case 3:
                std::cout << "You got sick!" << std::endl;
                std::cout << "-20 energy" << std::endl;
                money -= 20;
                return false;
                break;
            case 4:
                std::cout << "You had a blackout on your block!" << std::endl;
                std::cout << "The day was skipped." << std::endl;
                money += 30;
                return true;
                break;
            default:
                break;
            }
        }
    }
    return false;
}

bool loseConditions(int &money, int &psyche)
{
    if (money <= 0)
    {
        std::cout << "You ran out of money and moved back in with your parents." << std::endl;
        return true;
    }
    if (psyche <= 0)
    {
        std::cout << "You lost your mind and decided university isn't for you." << std::endl;
        return true;
    }
    return false;
}

bool takeExam(int &knowledge, int &psyche, int &energy, int &luck, int &examNumber, int &difficulty)
{
    int penalty = (examNumber - 1) * 5;
    double examPoints = (knowledge * 0.75) + (psyche * 0.1) + (energy * 0.1) + (luck * 0.2) - penalty;
    if (examPoints >= 75)
    {
        std::cout << "Exam #" << examNumber << " has been succesfully passed!" << std::endl;
        examNumber++;
        energy -= 20;
        psyche += 20;
        knowledge -= 25 + 20 * difficulty;
        return true;
    }
    else
    {
        std::cout << "Exam #" << examNumber << " has been failed!" << std::endl;
        return false;
    }
}

void gameloop(int &currentDay, int &knowledge, int &money, int &psyche, int &energy, int &luck, int &examNumber, int examDates[], int &difficulty)
{
    const int FIRST_EXAM_DATE = examDates[0];
    const int SECOND_EXAM_DATE = examDates[1];
    const int THIRD_EXAM_DATE = examDates[2];
    const int FOURTH_EXAM_DATE = examDates[3];
    const int FIFTH_EXAM_DATE = examDates[4];
    while (currentDay <= 45)
    {
        char autosaveStr[CAPACITY] = "autosave";
        saveGame(autosaveStr, currentDay, knowledge, money, psyche, energy, examNumber, examDates, difficulty);
        std::cout << " Day " << currentDay << std::endl;
        if (currentDay == FIRST_EXAM_DATE || currentDay == SECOND_EXAM_DATE || currentDay == THIRD_EXAM_DATE
            || currentDay == FOURTH_EXAM_DATE || currentDay == FIFTH_EXAM_DATE)
        {
            if (!takeExam(knowledge, psyche, energy, luck, examNumber, difficulty))
            {
                return;
            }
        }
        else if(energy > 0)
        {
            if (randomEvent("general", psyche, money, luck))
            {
                currentDay++;
                randomGenerator.seed(std::random_device{}());
                luck = randomGenerator() % 101;
                continue;
            }
            int choice;
            actionMenuText(knowledge, psyche, money, energy);
            std::cout << "Next exam is in " << examDates[examNumber - 1] - currentDay << "days." << std::endl;
            std::cin >> choice;
            actionMenuChoice(choice, currentDay, knowledge, money, psyche, energy, luck, examNumber, examDates, difficulty);
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
        knowledge -= (knowledge / 100) * (knowledge % 100);
        psyche -= (psyche / 100) * (psyche % 100);
        energy -= (energy / 100) * (energy % 100);

        currentDay++;
        randomGenerator.seed(std::random_device{}());
        luck = randomGenerator() % 101;
    }
    std::cout << "Congratulations! You passed all 5 exams! And won! Yay";
}

int main()
{
    int currentDay = 1;
    int knowledge = 0;
    int money = 0;
    int psyche = 0;
    int energy = 0;
    int luck = randomGenerator() % 101;
    int examNumber = 1;
    int difficulty = 1;

    int fourthExamDate = luck % 18 + 27;
    int examDates[5] = { 8, 17, 26, fourthExamDate, 45 };

    mainMenu();
    while (true)
    {
        int choice;
        std::cin >> choice;
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

        }
    }
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
