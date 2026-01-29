#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "mech.hpp"
#include "utilities.hpp"
#include "sqlite3.h"

//removed mech constructor 1/13/26 - not needed for right now
 /*Mech::Mech(std::string new_name, int new_walk, int new_run, int new_jump, int new_tonnage, std::string new_tech_base){
        name = new_name;
        walk = new_walk;
        run = new_run;
        jump = new_jump;
        tonnage = new_tonnage;
        tech_base = new_tech_base;
 }*/



void Mech::populate_mech_stats(sqlite3* db, std::string mech_choice){
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, name, tonnage, walk, run, jump FROM mech WHERE id = ? ";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //convert the sql statement to bytes
    sqlite3_bind_text(stmt, 1, mech_choice.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt); //execute the stmt
   if (rc == SQLITE_ROW){
        //const unsigned char* mech_raw = sqlite3_column_text(stmt, 1);
        //const char* mech_selected = reinterpret_cast<const char*>(mech_raw); //convert mech selected to c text
        //std::cout << "Mech found - populating mech values from data sheet" << std::endl;
        //if the mech is found, create a MECH_A object
        const unsigned char* name_raw = sqlite3_column_text(stmt, 1);
        name = reinterpret_cast<const char*>(name_raw);
        tonnage = sqlite3_column_int(stmt, 2);
        walk = sqlite3_column_int(stmt, 3);
        run = sqlite3_column_int(stmt, 4);
        jump = sqlite3_column_int(stmt, 5);
   } else {
    std::cerr << "No mech by that ID found, or there is another error." << std::endl;
   }
}

 std::string Mech::get_mech_name() const {
    return name; //print the mech's name
 }

 std::string Mech::view_base_mech() {
          std::vector<std::string> mech_base;
          mech_base.push_back(name);
          mech_base.push_back(tech_base);
          mech_base.push_back(std::to_string(tonnage));

          return "Loaded Mech is: " +  mech_base[0] + " " + mech_base[1] + " " + mech_base[2] + " tons" +"\n";

}

void Mech::print_armorStruc_vals(std::string location){
    std::cout << "Armor/Structure at " << location << " : " << ArmorMap[location] << "|" <<
    StrucMap[location] << "\n";
}

std::map<std::string, int> Mech::populate_mech_armor(sqlite3* db, std::string mech_choice){ 
    sqlite3_stmt* stmt;
    const char* sql = "SELECT HD, LA, LT, CT, RT, RA, LL, RL, LTR, CTR, RTR FROM armor WHERE id = ? "; //get the armor
    int rc = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL); //convert the sql statement to bytes
    rc = sqlite3_bind_text(stmt, 1, mech_choice.c_str(),-1, SQLITE_STATIC);
    rc = sqlite3_step(stmt); //execute the stmt
   if (rc == SQLITE_ROW){
    //create an armor map and seed it with the values.
    ArmorMap["HD"] = sqlite3_column_int(stmt, 0);
    ArmorMap["LA"] = sqlite3_column_int(stmt, 1);
    ArmorMap["LT"] = sqlite3_column_int(stmt, 2);
    ArmorMap["CT"] = sqlite3_column_int(stmt, 3);
    ArmorMap["RT"] = sqlite3_column_int(stmt, 4);
    ArmorMap["RA"] = sqlite3_column_int(stmt, 5);
    ArmorMap["LL"] = sqlite3_column_int(stmt, 6);
    ArmorMap["RL"] = sqlite3_column_int(stmt, 7);
    } else {
        std::cout << "SQL query for armor map failed" << std::endl;
    }

    return ArmorMap;    
} 

std::map<std::string, int> Mech::populate_mech_struc(sqlite3* db, std::string mech_choice){
    sqlite3_stmt* stmt;
    const char* sql = "SELECT HD, LA, LT, CT, RT, RA, LL, RL FROM structure WHERE id = ? "; //get the armor
    int rc = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL); //convert the sql statement to bytes
    rc = sqlite3_bind_text(stmt, 1, mech_choice.c_str(),-1, SQLITE_STATIC);
    rc = sqlite3_step(stmt); //execute the stmt
   if (rc == SQLITE_ROW){
    StrucMap["HD"] = sqlite3_column_int(stmt, 0);
    StrucMap["LA"] = sqlite3_column_int(stmt, 1);
    StrucMap["LT"] = sqlite3_column_int(stmt, 2);
    StrucMap["CT"] = sqlite3_column_int(stmt, 3);
    StrucMap["RT"] = sqlite3_column_int(stmt, 4);
    StrucMap["RA"] = sqlite3_column_int(stmt, 5);
    StrucMap["LL"] = sqlite3_column_int(stmt, 6);
    StrucMap["RL"] = sqlite3_column_int(stmt, 7);
    } else {
        std::cout << "SQL query for struc map failed" << std::endl;
    }
    return StrucMap;     
} 

void Weapon::populate_weapon_vals(sqlite3* db, std::string weapon_choice){ //in the future you can combine this all into a single function?
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM weapons WHERE type = ? ";
    int rc = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL); //convert the sql statement to bytes
    rc = sqlite3_bind_text(stmt, 1, weapon_choice.c_str(),-1, SQLITE_STATIC);
    rc = sqlite3_step(stmt); //execute the stmt
   if (rc == SQLITE_ROW){
        const unsigned char* weapon_type_raw = sqlite3_column_text(stmt, 0);
        weapon_type = reinterpret_cast<const char*>(weapon_type_raw);
        
        heat = sqlite3_column_int(stmt, 1);
        dmg = sqlite3_column_int(stmt, 2);
        grouping = sqlite3_column_int(stmt, 3);
        size = sqlite3_column_int(stmt, 4);
        const unsigned char* dmg_type_raw = sqlite3_column_text(stmt, 5);
        dmg_type = reinterpret_cast<const char*>(dmg_type_raw);
        min_range = sqlite3_column_int(stmt, 6);
        sht_range = sqlite3_column_int(stmt, 7);
        med_range = sqlite3_column_int(stmt, 8);
        lng_range = sqlite3_column_int(stmt, 9);
        crit_slots = sqlite3_column_int(stmt, 10);
        shots_per_ton = sqlite3_column_int(stmt, 11); 
    } else {
       std::cout << "Your SQL query has an issue" << std::endl;
    }    
    sqlite3_finalize(stmt);
} 

void Weapon::debug_weapon_vals(){ //print all the weapon class variables
    std::cout << weapon_type << "|" << heat << "|" << dmg << "|" << dmg_type 
    << "|" << min_range << "|" << sht_range << "|" << med_range << "|" << lng_range 
    << "|" << crit_slots << "|" << shots_per_ton << std::endl;
} 

void Mech::get_mech_equipment(sqlite3* db, std::string mech_choice){
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM equipment WHERE mech = ? ";
    int rc = sqlite3_prepare_v2(db,sql, -1, &stmt, NULL); //convert the sql statement to bytes
    rc = sqlite3_bind_text(stmt, 1, mech_choice.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt); //execute the stmt
   if (rc == SQLITE_ROW){
        const unsigned char* weapon_raw = sqlite3_column_text(stmt, 1);
        weapon_1 = reinterpret_cast<const char*>(weapon_raw);
        weapon_raw = sqlite3_column_text(stmt, 2);
        weapon_2 = reinterpret_cast<const char*>(weapon_raw);
        //std::cout << weapon_1 << " | " << weapon_2 << std::endl;
   } else {
    std::cout << "your sql is fucked bro" << std::endl;
   }
}

//sqlite stuff
sqlite3* openDB() {

    //open the database
    sqlite3* db;
    int connection = sqlite3_open("btech.db", &db);
    if (connection) { 
        std::cout << "ERROR - database cannot be opened\n\n";
    } else {
        std::cout << "Database connection opened\n\n";
    }
    return db;
}

std::string get_hit_location(std::map<int, std::string>& hit_table){
    int roll_result = dice_roll();
    std::string  hit_location= hit_table[roll_result]; //find the roll on the hit location table
    return hit_location;
}

void dmg_alloc(std::string location, int weapon_dmg, Mech& target_mech, std::map<std::string, std::string> transfer){ //damage allocation logic for mech armor and structure
    //check the hit location against weapon damage, if armor count goes negative, go to structure, if structure goes negative dmg goes inward to next module 
    int remainder;
    
    //infinite loop check for recursion
    if (weapon_dmg <= 0 || location == "") return;

    //debug console output
    std::cout << Color::CYAN_B << "Applying Hit(s)" << Color::RESET << "\n";
    std::cout << Color::GREEN << "Hit location: " << target_mech.get_mech_name()  << "-> " << location << "-> ";
    target_mech.print_armorStruc_vals(location);
    std::cout << Color::RED << "Wpn Dmg: " << weapon_dmg << "->" << Color::GREEN << " "; //print where the hit occurred and the damage to be done
    
    //Phase 1 - apply hits to armor
    if (target_mech.ArmorMap[location] > weapon_dmg) {
        target_mech.ArmorMap[location] -= weapon_dmg; //grab the weapon damage from the weapon class
        return;
    } 
    
    //Phase 2 - apply remaning damage to structure
    remainder = weapon_dmg - target_mech.ArmorMap[location];
    target_mech.ArmorMap[location] = 0;
    target_mech.StrucMap[location] -= remainder; 
    
    //debug console output the remaining armor/struc after dmg has been applied
    target_mech.print_armorStruc_vals(location);
    std::cout << "\n";

    //Phase 3 - check for location destruction/mech destroyed conditions
    if (target_mech.StrucMap[location] <= 0) { //you have overage
        remainder = std::abs(target_mech.StrucMap[location]);
        target_mech.StrucMap[location] = 0;

        std::cout << Color::RED <<  location << " is destroyed, remainder Dmg: " << remainder << Color::RESET << "\n\n";

        //any other parts fall off along with the destroyed location?
        if(location == "LT" & target_mech.StrucMap["LA"] > 0) {
            target_mech.ArmorMap["LT"]; target_mech.StrucMap["LT"] = 0;  //destroy the outward arm
            std::cout << Color::RED << "Left arm is destroyed" << Color::RESET << "\n\n"; } 
        if(location == "RT" & target_mech.StrucMap["RA"] > 0) {
            target_mech.ArmorMap["RT"]; target_mech.StrucMap["RT"] = 0; //destroy the outward arm
            std::cout << Color::RED << "Right arm destroyed" << Color::RESET << "\n\n"; } 
        if (location == "CT") {
            target_mech.StrucMap["CT"] = 0;
            std::cout << Color::RED << "Mech is destroyed" << Color::RESET << "\n\n";
            return;
        }
      
        //Recursion time: check transfer direction and run function again
        std::string transfer_loc = transfer[location];
        dmg_alloc(transfer_loc, remainder, target_mech, transfer);
        
    }

 
}
 







