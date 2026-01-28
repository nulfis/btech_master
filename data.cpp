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