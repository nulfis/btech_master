#include <iostream>
#include <map>
#include <vector>
#include "sqlite3.h"


//define the class


class Mech {
    private:
        //attributes
        std::string name;
        
        //movement points
        int walk;
        int run;
        int jump;
        int tonnage;
        std::string tech_base;
        std::string weapon_1;
        std::string weapon_2;

    public:
        //attributes
        //std::vector<int> armorvals;
        std::map<std::string, int> StrucMap;
        std::map<std::string, int> ArmorMap;
        //methods
        //create a mech constructor with name and basic attributes , removed constructor 1/13/26
        //Mech(std::string new_name, int new_walk, int new_run, int new_jump, int new_tonnage, std::string new_tech_base);

        //get values from the class
        std::string view_base_mech(); 
        //fill in the mech values  
        std::map<std::string, int> populate_mech_armor(sqlite3* db, std::string mech_choice);
        std::map<std::string, int> populate_mech_struc(sqlite3* db, std::string mech_choice);
        //get mech weapons and equipment
        void get_mech_equipment(sqlite3* db, std::string mech_choice);
        void populate_mech_stats(sqlite3* db, std::string mech_choice);


};

class Weapon { //container for mech weapons
    private:
    //attributes
    std::string weapon_type;
    int heat;
    int min_range;
    int sht_range;
    int med_range;
    int lng_range;
    int weight;
    int crit_slots;
    int shots_per_ton;


    public:
    std::string dmg_type;
    std::vector<int> weapon_vals;
    void populate_weapon_vals(sqlite3* db, std::string weapon_choice);
    int dmg; //moved to public variable for testing with
    void get_weapon_name();
    void debug_weapon_vals();
    

};


//sqlite3 functions
sqlite3* openDB(); 
int callback(void* mech_data, int argc, char** argv, char** azColName);

//die rolling functions and lookupt tables
int dice_roll();
std::map<int, std::string> generate_lookup_table_fr();

//build the cluster hits table
enum class Weapon_Size_Column { //WS cluster columns
    C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, 
    C19, C20, C21, C22, C23, C24, C25, C26, C27, C28, C29, C30, C40, COUNT};

struct Cluster_Table {
    
    static constexpr std::array<std::array<int, (int)Weapon_Size_Column::COUNT> ,11> data {{
    //C2, C4, C10, C40 and so on
    {1,1,1,1,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,12}, //roll 2
    {1,1,2,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,12}, //roll 3
    {1,1,2,2,3,3,4,4,4,5,5,5,6,6,7,7,8,8,9,9,9,10,10,10,11,11,11,12,12,18}, //roll 4
    {1,2,2,3,3,4,4,5,6,7,8,8,9,9,10,10,11,11,12,13,14,15,16,16,17,17,17,18,18,24}, //roll 5
    {1,2,2,3,4,4,5,5,6,7,8,8,9,9,10,10,11,11,12,13,14,15,16,16,17,17,17,18,18,24}, //roll 6
    {1,2,3,3,4,4,5,5,6,7,8,8,9,9,10,10,11,11,12,13,14,15,16,16,17,17,17,18,18,24}, //roll 7
    {2,2,3,3,4,4,5,5,6,7,8,8,9,9,10,10,11,11,12,13,14,15,16,16,17,17,17,18,18,24}, //roll 8
    {2,2,3,4,5,6,6,7,8,9,10,11,11,12,13,14,14,15,16,17,18,19,20,21,21,22,23,23,24,32}, //roll 9
    {2,3,3,4,5,6,6,7,8,9,10,11,11,12,13,14,14,15,16,17,18,19,20,21,21,22,23,23,24,32}, //roll 10
    {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,40}, //roll 11
    {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,40} //roll 12

    }};
    
    //add a hit lookup function
    static int get_hits(int roll, Weapon_Size_Column col){
        return data[roll][(int)col];
    };

};