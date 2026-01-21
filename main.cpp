#include <iostream>
#include "mech.hpp"
#include <stdlib.h>
#include <vector>
#include <tuple>
#include "sqlite3.h"

//do some setup
using std::cout;
using std::cin;
using std::endl;

//write a combat calculation function

int attack_calc(){
   //GATOR: Gunnery Skill, Attacker Movement Modifier, Targer Movement Modifier, Other Modifiers, Ranger Modifier
   int gunnery; 
   int attack_mod; 
   int target_mod; 
   int other_mod; 
   int range;
   int attack_sum;

   /*std::cout << "Input your G.A.T.O.R values, G to R order with spaces between values.\n\n";
   std::cin >> gunnery >> attack_mod >> target_mod >> other_mod >> range;
   attack_sum = gunnery + attack_mod + target_mod + other_mod + range; */ // removed while testing weapon hits 1.19.26
   attack_sum = 4;
   std::cout << "Your targer number modifier is: " << attack_sum << "\n\n";
    return attack_sum; 

   
}



int main(){
    bool quit = false;
    system("clear");
    system("color 09");
    
    //do some introductory text
    //system("color 0A");
    std::cout << "\n" << "WELCOME TO THE BATTLETECH FIELD COMPUTER \n\n";
    
    //-----------------------------------------------------------
    //cout << "INPUT MECH TO LOAD. USE MECH VARIANT NUMBER" << endl;
    //std::string mech_choice;
    std::vector<std::string> lance_choices = {"WSP-1A", "GRF-1N"};
    //cin >> mech_choice;
    //lance_choices.push_back(mech_choice);
    //cout << "Load one more mech please so they can fight each other!" << endl;
    //cin >> mech_choice;
    //lance_choices.push_back(mech_choice);
    cout << "Mech A: " << lance_choices[0] << " & Mech B: " << lance_choices[1] << endl;

    
    

    //open the database
    sqlite3* odb = openDB();

    //run a for loop to populate mech classes for each mech in lance_choices
    std::vector<Mech> lance;
    for (const auto& mech : lance_choices){
        Mech temp_mech;
        temp_mech.populate_mech_stats(odb, mech); //get mech basic stats and type
        temp_mech.populate_mech_armor(odb, mech); // get mech armor values
        temp_mech.populate_mech_struc(odb, mech); // get mech structure values
        temp_mech.get_mech_equipment(odb, mech); // get mech equipment (weapons and other)

        temp_mech.view_base_mech(); //print out some basic mech stats for debugging and user information
        
        //push back into Mech vector
        lance.push_back(temp_mech);
        
    }

    //load up a weapon class
    Weapon weapon_a;
    
    //pick a weapon to fire at the selected mech
    std::string weapon_choice;
    cout << "what weapon are you shooting?" << endl;
    cin >> weapon_choice;
    cout << "populating weapon values for user selection" << endl;
    weapon_a.populate_weapon_vals(odb, weapon_choice); //currently hard coded for PPC lookup
    weapon_a.debug_weapon_vals(); //prints all the values except crit slots and shots per ton
    
    //build the front hit table
    std::map<int, std::string> hit_table_fr = generate_lookup_table_fr();  //generate the hit location table


//set up the application loop
//notes to self 1/12/26 -
    //the mech shoots itself right now with the weapon chosen. Once I add multiple mech tracking this needs to switch over.
    while (quit != true) {
        char user_input;
        int user_roll;
        
        cout << "rolling dice for player \n";
        user_roll = dice_roll(); //roll the dice
        int to_hit = attack_calc(); //sum the gator vals to determine to hit number
        
        //check if you hit or miss 
        if (user_roll >= to_hit) {
            std::cout << "HIT!" << endl;
            cout << "Rolling to determine hit location" << endl;
            if (weapon_a.dmg_type == "MCS"){ //check for missile weapon
                int cluster_roll = dice_roll(); //roll for cluster table lookup
                int hits = Cluster_Table::get_hits(cluster_roll, Weapon_Size_Column::C4);
                cout << hits << " missiles hit the target" << endl;
                //add missile group hit logic


                return 0; //exit the program while I'm testing missile hits
            
            }
            user_roll = dice_roll();
            //user_roll = 12; //testing by hard setting hit location to 12
            std::string hit_location = hit_table_fr[user_roll]; //find the roll on the hit location table

            //check the hit locatin against weapon damage, if armor count goes negative, go to structure
            cout << "hit location is " << hit_location << " : " << lance[0].ArmorMap[hit_location] << " total armor" << endl; //print where the hit occurred
            if (lance[0].ArmorMap[hit_location] > weapon_a.dmg) {
            lance[0].ArmorMap[hit_location] -= weapon_a.dmg; //grab the weapon damage from the weapon class
            cout << "Remaining armor at " << hit_location << " : " << lance[0].ArmorMap[hit_location] << endl;
            } else {
                int remainder = weapon_a.dmg - lance[0].ArmorMap[hit_location];
                lance[0].StrucMap[hit_location] -= remainder; 
                lance[0].ArmorMap[hit_location] = 0;
                cout << "Remaining armor at " << hit_location << " : " << lance[0].ArmorMap[hit_location] << endl;
                cout << "Remaining struc at " << hit_location << " : " << lance[0].StrucMap[hit_location] << endl;
                //check for destroyed mech sections, if mech destroyed, continued damage into interior parts
            if (lance[0].StrucMap[hit_location] <= 0) {
                if (hit_location == "CT") {
                    cout << "mech is destroyed" << endl;
                } else {
                    cout << hit_location << " is destroyed" << endl;
                    remainder = lance[0].StrucMap[hit_location]; //new remainder to track damage into interior sections 
                }
            }
            }
        } else {
            std::cout << "MISS! GO NEXT" << endl;
        }



    std::cout << "Quit? y/n" << "\n";
        std::cin >> user_input;
        if (user_input == 'y') {
            quit = true;
        }
        
    }


return 0;


}


