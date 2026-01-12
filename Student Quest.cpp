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

void mainMenu()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "| [1] Start new game. |" << std::endl;
    std::cout << "| [2] Load game.      |" << std::endl;
    std::cout << "| [3] Help            |" << std::endl;
    std::cout << "-----------------------";
}

int main()
{
    mainMenu();
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
