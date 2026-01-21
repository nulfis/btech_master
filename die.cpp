#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

int dice_roll(){

    srand((unsigned int) time(NULL)); //time returns current time with a type-cast to what srand wants

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

/*
//hit lookup table: front/rear
std::map<int, std::string> generate_lookup_table_fr(){
    std::map<int, std::string> hit_table;
    hit_table[2] = "CT - CRIT";
    hit_table[3] = "RA";
    hit_table[4] = "RA";
    hit_table[5] = "RL";
    hit_table[6] = "RT";
    hit_table[7] = "CT";
    hit_table[8] = "LT";
    hit_table[9] = "LL";
    hit_table[10] = "LA";
    hit_table[11] = "LA";
    hit_table[12] = "HD";

    return hit_table;
}

//hit lookup table: left side
std::map<int, std::string> generate_lookup_table_l(){
    std::map<int, std::string> hit_table;
    hit_table[2] = "CT - CRIT";
    hit_table[3] = "LL";
    hit_table[4] = "LA";
    hit_table[5] = "LA";
    hit_table[6] = "LL";
    hit_table[7] = "LT";
    hit_table[8] = "CT";
    hit_table[9] = "RT";
    hit_table[10] = "RA";
    hit_table[11] = "RL";
    hit_table[12] = "HD";

    return hit_table;
}

//hit lookup table: right side
std::map<int, std::string> generate_lookup_table_r(){
    std::map<int, std::string> hit_table;
    hit_table[2] = "CT - CRIT";
    hit_table[3] = "RL";
    hit_table[4] = "RA";
    hit_table[5] = "RA";
    hit_table[6] = "RL";
    hit_table[7] = "RT";
    hit_table[8] = "CT";
    hit_table[9] = "LT";
    hit_table[10] = "LA";
    hit_table[11] = "LL";
    hit_table[12] = "HD";

    return hit_table;
}
*/



