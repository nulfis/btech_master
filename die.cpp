#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

int dice_roll(){

    

    int roll_1 = 0;
    int roll_2 = 0;

    roll_1 = (rand() % 6) + 1;
    roll_2 = (rand() % 6) + 1;
    
    int two_d_six = roll_1 + roll_2;

    //std::cout << "Dice 1: " << roll_1 << std::endl;
    //std::cout << "Dice 2: " << roll_2 << "\n\n";
    std::cout << "2D6 Total: " << two_d_six << std::endl;

    return two_d_six;

}

