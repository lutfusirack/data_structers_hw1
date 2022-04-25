/* @Author
Student Name: Lütfü Sirac Küçükarabacıoğlu
Student ID: 504211521
E-mail: kucukarabaciogl@itu.edu.tr
Date: 28/12/2021
*/
#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

class Map;
class cityNode;
class linkedCity;

class cityNode{
    public:
        string cityNumber;
        string cityNumberLeft;
        string cityNumberRight;
        int durationLeft;
        int durationRight;
        cityNode* right;
        cityNode* left;
        friend class Map;
        cityNode();

};

class Map{

    public:
    cityNode * head;
    vector<linkedCity> linked_cities;
    friend class cityNode;
    friend class linkedCity;
    Map();
    Map * createMap(vector<string> * s_map);
    void findNode(cityNode * p_head,string p_cityName, cityNode ** p_place);
    void addNode2info(cityNode * p_node,string s_dataCity1,string s_dataCity,string s_dataDuration);
    Map * restructer();
    void  add2vector(cityNode * p_node,linkedCity l_s,int int_duration);
    void  remove_long_path(vector<string> problem_path);
    void print_preorder(cityNode * p_head);
};


class linkedCity{
    public:
        vector<string> path;
        int total_duration;
        friend class Map;
        friend class cityNode;
        linkedCity();
        // void createLinkedcity(Map * p_map);
};



#endif