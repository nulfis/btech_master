#include "mech.hpp"
#include <map>


//New cluster table lookup using std::map


const std::map<int, std::vector<int>> Cluster_Table::Cluster_table{
  //Size  Roll
  //      2,3,4,5,6,7,8,9,0,1,2   
    {2,  {1,1,1,1,1,1,2,2,2,2,2}},
    {4,  {1,2,2,2,2,3,3,3,3,4,4}},
    {5,  {1,2,2,3,3,3,3,4,4,5,5}},
    {6,  {2,2,3,3,4,4,4,5,5,6,6}}, 
    {10, {3,3,4,6,6,6,6,8,8,10,10}},
    {15, {5,5,6,9,9,9,9,12,12,15,15}},
    {20, {6,6,9,12,12,12,12,16,16,20,20}}

};

/* //CLUSTER TABLE DATA - PG 33 BT Manual - DEPRECATED 1.27.26
const std::array<std::array<int, (int)Weapon_Size_Column::COUNT> ,11> Cluster_Table::data {{
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
    */

    //cluster hit lookup function
    int Cluster_Table::get_hits(int roll, Weapon weapon){
        auto key = Cluster_table.find(weapon.size);
        return key->second[roll -2]; 

    }

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