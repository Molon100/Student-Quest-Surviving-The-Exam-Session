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

int currentDay = 1;
int knowledge = 0;
int money = 0;
int psyche = 0;
int energy = 0;
//going to implement randomness later
int luck = 0;
int examNumber = 0;

void mainMenu()
{
    std::cout << " -----------------------" << std::endl;
    std::cout << "| [1] Start new game.   |" << std::endl;
    std::cout << "| [2] Load game.        |" << std::endl;
    std::cout << "| [3] Help              |" << std::endl;
    std::cout << " -----------------------" << std::endl;
}

void helpMenu()
{

}

void actionMenu()
{
    std::cout << " Day " << currentDay << std::endl;
    std::cout << " --------------------------" << std::endl;
    std::cout << "| What action will         |   Knowledge: " << knowledge << std::endl;
    std::cout << "| you choose?              |   Energy:    " << knowledge<< std::endl;
    std::cout << "| [1] Study                |   Psyche:    " << knowledge << std::endl;
    std::cout << "| [2] Eat                  |   Money:     " << knowledge << std::endl;
    std::cout << "| [3] Go out               |" << std::endl;
    std::cout << "| [4] Take a break         |" << std::endl;
    std::cout << "| [5] Go to part-time work |" << std::endl;
    std::cout << "| [6] Quit game            |" << std::endl;
    std::cout << " --------------------------" << std::endl;
}


void newGame()
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
        break;
    case 2:
        knowledge = 50;
        money = 80;
        psyche = 80;
        energy = 80;
        break;
    case 3:
        knowledge = 35;
        money = 60;
        psyche = 60;
        energy = 40;
        break;
    default:
        break;
    }
}

void loadGame()
{

}

void gameloop()
{
    while (currentDay <= 45)
    {
        actionMenu();
        int choice;
        std::cin >> choice;
        currentDay++;
    }
}

int main()
{
    mainMenu();
    while (true)
    {
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            newGame();
            gameloop();
        }
        else if (choice == 2)
        {
            loadGame();
            gameloop();
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
