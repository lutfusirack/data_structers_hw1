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

vector<string> s_map1;
vector<string> s_map2;

using namespace std;

void read_maps(string smap1,string smap2);
void parse_data(string str,vector<string>*sp_map);
void find_min_duration(Map * p_map1,Map * p_map2);
void print_preorder_tree(Map * p_map1,Map * p_map2);

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows
    string dirOfmap1 = string(argv[1]);
    string dirOfmap2 = string(argv[2]);
    // cout<<dirOfmap1<<endl;
    // cout<<dirOfmap1<<endl;

    read_maps(dirOfmap1,dirOfmap2);

    Map * m_map1 = new Map;
    Map * m_map2 = new Map;


    m_map1 = m_map1->createMap(&s_map1);
    m_map2 = m_map2->createMap(&s_map2);

    m_map1 = m_map1->restructer();
    m_map2 = m_map2->restructer();

    print_preorder_tree(m_map1,m_map2);

    find_min_duration(m_map1,m_map2);


return EXIT_SUCCESS;
}
void print_preorder_tree(Map * p_map1,Map * p_map2){
    
    cout<<"FRIEND-1:";
    p_map1->print_preorder(p_map1->head);
    cout<<endl;
    cout<<"FRIEND-2:";
    p_map2->print_preorder(p_map2->head);
    cout<<endl;
}

void find_min_duration(Map * p_map1,Map * p_map2){

    int min_duration = INT32_MAX;
    int min_d_x=0, min_d_y=0;
    int duration_arr[p_map1->linked_cities.size()][p_map2->linked_cities.size()] = {0};

    for (size_t i = 0; i < p_map1->linked_cities.size(); i++)
    {
       for (size_t j = 0; j < p_map2->linked_cities.size(); j++)
       {
           if (p_map1->linked_cities[i].path.back() == p_map2->linked_cities[j].path.back())
           {
                duration_arr[i][j] = p_map2->linked_cities[j].total_duration + p_map1->linked_cities[i].total_duration;
                if (min_duration > duration_arr[i][j])
                {
                    min_duration = duration_arr[i][j];
                    min_d_x = i;
                    min_d_y = j;
                }
           }  
       }  
    }

    cout<<"MEETING POINT : "<<p_map1->linked_cities[min_d_x].path.back()<<endl;
    cout<<"TOTAL DURATION COST : "<<min_duration<<endl;

}


void read_maps(string smap1,string smap2){

    string temp_char;
    ifstream InputReadFile1(smap1);
    ifstream InputReadFile2(smap2);

    while (getline(InputReadFile1, temp_char))
    {
        // cout<<temp_char<<endl;
        if (memcmp(temp_char.c_str(),"SOURCE_CITY",11) == 0)
        {

            continue;
        }
        parse_data(temp_char,&s_map1);
        // s_map1.push_back(temp_char);
    }

    while (getline(InputReadFile2, temp_char))
    {
        // cout<<temp_char<<endl;
        if (memcmp(temp_char.c_str(),"SOURCE_CITY",11) == 0)
        {
            continue;
        }
        
        parse_data(temp_char,&s_map2);
    }

}

void parse_data(string str,vector<string>*sp_map){
 
    // Returns first token
    char *token = strtok(&str.front(), " ");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        // printf("%s\n", token);
        sp_map->push_back(token);
        token = strtok(NULL, " ");
    }


}
