#include <iostream>
#include <map>
#include <vector>
#include "sqlite3.h"
#include <random>



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
        std::string get_mech_name() const; 
        void print_armorStruc_vals(std::string location);
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
    int grouping;
    int size; //how many munitions a cluster weapon fires in a single shot
    std::vector<int> weapon_vals;
    void populate_weapon_vals(sqlite3* db, std::string weapon_choice);
    int dmg; //moved to public variable for testing with
    void get_weapon_name();
    void debug_weapon_vals();
    

};

class Dice {//container for the random number engine and dice rolling functions.
    private:
        std::mt19937 gen;
        std::uniform_int_distribution<int> d6;

    public:
        Dice();
        int dice_roll();
        int one_d_six();
        int two_d_six();


};

std::string get_hit_location(std::map<int, std::string>& hit_table, Dice dice);

void dmg_alloc(std::string hit_location, int weapon_dmg, Mech& target_mech, std::map<std::string, std::string> transfer, Dice dice);
void crit_alloc(int crit_hits, std::string location, Mech& mech, Dice dice);

//sqlite3 functions
sqlite3* openDB(); 


//die rolling functions and lookupt tables
int dice_roll();
std::map<int, std::string> generate_lookup_table_fr();



struct Cluster_Table { //see page 33 in rulebook
    
    static const std::map<int, std::vector<int>> Cluster_table;
    
    //add a hit lookup function
    static int get_hits(int roll, Weapon weapon);

};

static const std::map<std::string, std::string> dmg_transfer_map = { //map containting the direction over dmg does to the next internal part
    {"LA", "LT"},
    {"LT", "CT"},
    {"RA", "RT"},
    {"RT", "CT"},
    {"LL", "LT"},
    {"RL", "RT"}
};