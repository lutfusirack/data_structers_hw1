/* @Author
Student Name: Lütfü Sirac Küçükarabacıoğlu
Student ID : 504211521
Date: 04.1.2022 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include<string.h>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;

string file_path;
vector<string> data_v;
map<string, double> data_map;
multimap<double,string> sorted_data_map;

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();
void parse_data(string str);
void map_data();
void order_map();

int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        // cout<<"exit"<<endl;
        break;
    case 'E':
    case 'e':
        terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
// *********************Fill this method 
    string temp_char;
    ifstream InputReadFile1(file_path);

    while (getline(InputReadFile1, temp_char))
    {
        parse_data(temp_char);
        // cout<<temp_char<<endl;
    }
    map_data();
    order_map();
    cout<<"5 products with the highest revenue for total are:"<<endl;
    int i=0;
    for (auto itt = sorted_data_map.cend(); itt != sorted_data_map.cbegin(); --itt)
    {   
        i++;
        if (i == 1)
        {
            continue;
        }
        if (i == 7)
        {
            break;
        }
        // cout.precision(3);
        cout<<itt->second<<" ";
        // cout<<setprecision(5)<<itt->first<<endl;
        printf("%.2f",itt->first);
        cout<<endl;
    }
    

}

void parse_data(string str){
 
    // Returns first token
    char *token = strtok(&str.front(), " ");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        // printf("%s\n", token);
        data_v.push_back(token);
        token = strtok(NULL, " ");
    }
}

void map_data(){

    string product_name;
    double price=0,quantity=0;

    for (size_t i = 4; i < data_v.size(); i+=4)
    {
        product_name = data_v[i];
        price = stod(data_v[i+1]);
        quantity = stod(data_v[i+2]);
        if (data_map.count(product_name) < 0)
        {
            data_map.insert(pair<string,double>(product_name,(price*quantity)));
        }
        else
        {
            double old_data = data_map[product_name];
            old_data += (quantity*price);
            data_map[product_name] = old_data;
        }
    }

}

void order_map(){

    for (auto itt = data_map.cbegin(); itt != data_map.cend(); ++itt)
    {
        
        sorted_data_map.insert(pair<double,string>(itt->second,itt->first));
        
    }
}