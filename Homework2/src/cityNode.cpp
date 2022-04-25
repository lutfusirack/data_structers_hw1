/* @Author
Student Name: Lütfü Sirac Küçükarabacıoğlu
Student ID: 504211521
E-mail: kucukarabaciogl@itu.edu.tr
Date: 28/12/2021
*/
#include <iostream> 
#include <stdlib.h>
#include<string.h>
#include <fstream>
#include "cityNode.h"

using namespace std;

cityNode::cityNode(){
    durationLeft=0;
    durationRight=0;
    left = NULL;
    right = NULL;
}

Map::Map(){
    this->head = NULL;
}
linkedCity::linkedCity(){
    this->total_duration = 0;
}

void Map::findNode(cityNode * p_head,string p_cityName, cityNode ** p_place){

    if (this->head == NULL)
    {
        *p_place = p_head;
        return;
    }
    
    if (p_head && (p_head->cityNumber == p_cityName) || (this->head->cityNumber.empty()))
    {
        *p_place = p_head;
        return;
    }
    if (p_head->left)
    {
        findNode(p_head->left,p_cityName,p_place);
    }
    if (p_head->right)
    {
        findNode(p_head->right,p_cityName,p_place);
    }

    
}

void Map::addNode2info(cityNode * p_node,string s_dataCity1,string s_dataCity,string s_dataDuration){

    if (this->head ==NULL)
    {
        cityNode * temp1 = new cityNode;
        temp1->cityNumber = s_dataCity1;
        temp1->cityNumberLeft = s_dataCity;
        sscanf(s_dataDuration.c_str(),"%d",&temp1->durationLeft);
        cityNode * temp2 = new cityNode;
        temp2->cityNumber = s_dataCity;
        temp1->left=temp2;
        this->head = temp1;
    }

    else if (p_node->durationLeft == 0)
    {
        cityNode * temp1 = new cityNode;
        findNode(this->head,s_dataCity,&temp1);
        p_node->cityNumberLeft = s_dataCity;
        // p_node->durationLeft = s_dataDuration;
        sscanf(s_dataDuration.c_str(),"%d",&p_node->durationLeft);
        if ((*temp1).cityNumber.empty())
        {
            // temp1 = new cityNode;
            temp1->cityNumber = s_dataCity;
        }
        p_node->left = temp1;
    }
    else if (p_node->durationRight == 0)
    {
        cityNode * temp1 = new cityNode;
        // findNode(this->head,s_dataCity,&temp1);
        p_node->cityNumberRight = s_dataCity;
        // p_node->durationLeft = s_dataDuration;
        sscanf(s_dataDuration.c_str(),"%d",&p_node->durationRight);
        if ((*temp1).cityNumber.empty())
        {
            // temp1 = new cityNode;
            temp1->cityNumber = s_dataCity;
        }
        p_node->right = temp1;
    }   
}

Map * Map::createMap(vector<string> * s_map){

    for (size_t i = 0; i < s_map->size(); i+=3)
    {
        cityNode * p_node = new cityNode;
        findNode(this->head,(*s_map)[i],&p_node);
        addNode2info(p_node,(*s_map)[i],(*s_map)[i+1],(*s_map)[i+2]);
    }
    
    // for (size_t i = 0; i < s_map->size(); i+=3)
    // {
    //     for (size_t j = 0; j < s_map->size(); j+=3)
    //     {
    //         cityNode * p_node1 = new cityNode;
    //         findNode(this->head,(*s_map)[i],&p_node1);
    //         cityNode * p_node2 = new cityNode;
    //         findNode(this->head,(*s_map)[j],&p_node2);
    //         if ((i != j) && ((*s_map)[i] == (*s_map)[j]))
    //         {
    //             cout<<(*s_map)[j]<<endl;
    //         }   
    //     }
    // }
    



    return this;
}

void Map::add2vector(cityNode * p_node,linkedCity l_s,int int_duration){

    if (p_node)
    {
        l_s.total_duration += int_duration;
        l_s.path.push_back(p_node->cityNumber);
        this->linked_cities.push_back(l_s);
    }
    if (p_node->left)
    {
        // l_s.total_duration += p_node->durationLeft;
        add2vector(p_node->left,l_s,p_node->durationLeft);
    }
    if (p_node->right)
    {
        // l_s.total_duration += p_node->durationRight; 
        add2vector(p_node->right,l_s,p_node->durationRight);
    }
}

void  Map::remove_long_path(vector<string> problem_path){

    cityNode * temp1;
    findNode(this->head,problem_path[problem_path.size()-2],&temp1);

    if (temp1->cityNumberLeft == problem_path.back())
    {
        temp1->cityNumberLeft.clear();
        temp1->left = NULL;
        temp1->durationLeft = 0;
    }
    else if (temp1->cityNumberRight == problem_path.back())
    {
        temp1->cityNumberRight.clear();
        temp1->right = NULL;
        temp1->durationRight = 0;
    }

}

Map * Map::restructer(){

    cityNode * temp = this->head;
    linkedCity * ls = new linkedCity;
    int duration = 0;

    add2vector(temp,*ls,duration);

    for (size_t i = 0; i < this->linked_cities.size(); i++)
    {
        for (size_t j = 0; j < this->linked_cities.size(); j++)
        {
            if ( (i != j) && (this->linked_cities[i].path.back() == this->linked_cities[j].path.back()))
            {
                if (this->linked_cities[i].total_duration > this->linked_cities[j].total_duration)
                {
                    remove_long_path(this->linked_cities[i].path);
                    this->linked_cities.erase(this->linked_cities.begin()+i);
                }
                else{
                    remove_long_path(this->linked_cities[j].path);
                    this->linked_cities.erase(this->linked_cities.begin()+j);
                }
                this->linked_cities.clear();
                add2vector(temp,*ls,duration);
            }
        }
    }
    



    // cout<<"exit"<<endl;
    return this;
}

void Map::print_preorder(cityNode * p_head){

    cout<<p_head->cityNumber<<" ";

    if (p_head->left)
    {
    print_preorder(p_head->left);
    }
    if (p_head->right)
    {
    print_preorder(p_head->right);
    }

}
