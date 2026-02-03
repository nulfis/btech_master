#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include "mech.hpp"
#include "utilities.hpp"


//define some text colors to help with debugging the program


Dice::Dice()
    : gen(std::random_device{}()), d6(1,6) {} //seeding our random number to a d6 normal distribution


/*int dice_roll(){ //deprecated 2.3.26

    

    int roll_1 = 0;
    int roll_2 = 0;

    roll_1 = (rand() % 6) + 1;
    roll_2 = (rand() % 6) + 1;
    
    int two_d_six = roll_1 + roll_2;

    //std::cout << "Dice 1: " << roll_1 << std::endl;
    //std::cout << "Dice 2: " << roll_2 << "\n\n";
    //std::cout << Color::YELLOW << "2D6 Total: " << two_d_six << Color::RESET << "\n\n";

    return two_d_six;

} */

int Dice::one_d_six() { //simple 1d6roll
    return d6(gen);
    
}

int Dice::two_d_six(){
    return d6(gen) + d6(gen);
}


