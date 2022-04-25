#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#define STORAGE_LIMIT 2000
using namespace std;

static int wagon_count = 0;
void Train::create(){
    head = NULL;
}; 

int Train::sizeOfTrain(){

        int count = 0;
        wagonNode * tempWagon = head;


        while (tempWagon->next != NULL)
        {
           tempWagon = tempWagon->next;
            count++;
        }
        
    return count;
};

wagonNode * Train::getWagon(int wagon_id){
    int int_wagon_id;
    wagonNode * wagon2go = head;

    for (size_t i = 0; i < wagon_id; i++)
    {
        wagon2go = wagon2go->next;
    }
    
return wagon2go;
}


int Train::addMaterial2Wagon(int int_wagon_id,char material, int weight){
    
    wagonNode * p_wagon = getWagon(int_wagon_id);
    materialNode * p_material = p_wagon->material;
    bool found = false;
    while (p_material != NULL)
    {
        if ((p_material->id == material))
        {
            if (p_material->weight + weight <= STORAGE_LIMIT)
            {
                p_material->weight = p_material->weight + weight;
                return 0;  
            }
            else{
                int temp = (p_material->weight + weight)-STORAGE_LIMIT;
                p_material->weight = STORAGE_LIMIT;
                return temp;
            }
            
        }   
        if ((p_material->id < material) && ((p_material->next == NULL) || (p_material->next->id > material) ))
        {
            
            materialNode * newnode = new materialNode;
            newnode->id = material;
            newnode->next = p_material->next;
            p_material->next = newnode;
            if (weight <= STORAGE_LIMIT)
            {
                
                newnode->weight = weight;
                return 0;  
            }
            else{
                newnode->weight = STORAGE_LIMIT;
                return weight-STORAGE_LIMIT;
            }
             
        }   
        p_material = p_material->next;
    }
        // wagonNode * new_wagon = new wagonNode; // ?
        // head = new_wagon;
    if ((p_material == NULL))
    {
        materialNode * newnode = new materialNode;
        p_wagon->material = newnode;
        newnode->id = material;
        if (weight <= STORAGE_LIMIT)
        {
            newnode->weight = weight;
            return 0;  
        }
        else{
            newnode->weight = STORAGE_LIMIT;
            return weight-STORAGE_LIMIT;
        }
    }
    
        

};

int Train::findWagon(char material, int weight){ // found wagon which has room or make a new one

        wagonNode * tempWagon = head;
        bool found = false;
        while (tempWagon != NULL)
        {
            materialNode * tempMaterial = tempWagon->material;
            found = false;
            while ((tempMaterial != NULL) && !found) //&& (tempMaterial->weight == STORAGE_LIMIT)) (tempMaterial->id != material) &&
            {
                if ((tempMaterial->id == material) && (tempMaterial->weight < STORAGE_LIMIT))
                {
                    return tempWagon->wagonId;
                }
                else if ((tempMaterial->id == material) && (tempMaterial->weight == STORAGE_LIMIT))
                {
                    found = true;
                    break;
                }
                tempMaterial = tempMaterial->next; // burda siliyo

            }
            if (!found)
            {
                return tempWagon->wagonId;
            }
            
            tempWagon = tempWagon->next;
        }

        wagonNode * newtempWagon = new wagonNode;
        tempWagon = head;
        while (tempWagon->next != NULL)
        {
            tempWagon = tempWagon->next;

        }

        tempWagon->next = newtempWagon;
        newtempWagon->wagonId = wagon_count;
        wagon_count++;
        return newtempWagon->wagonId;



};


int Train::findWagonfromlast(char material, int weight){ // found wagon which has room or make a new one

        wagonNode * tempWagon = head;
        bool found = false;
        while (tempWagon != NULL)
        {
            materialNode * tempMaterial = tempWagon->material;
            found = false;
            while ((tempMaterial != NULL) && !found) //&& (tempMaterial->weight == STORAGE_LIMIT)) (tempMaterial->id != material) &&
            {
                if ((tempMaterial->id == material) && (tempMaterial->weight < STORAGE_LIMIT))
                {
                    return tempWagon->wagonId;
                }
                else if ((tempMaterial->id == material) && (tempMaterial->weight == STORAGE_LIMIT))
                {
                    found = true;
                    break;
                }
                tempMaterial = tempMaterial->next; // burda siliyo

            }
            if (!found)
            {
                return tempWagon->wagonId;
            }
            
            tempWagon = tempWagon->next;
        }

        wagonNode * newtempWagon = new wagonNode;
        tempWagon = head;
        while (tempWagon->next != NULL)
        {
            tempWagon = tempWagon->next;

        }

        tempWagon->next = newtempWagon;
        newtempWagon->wagonId = wagon_count;
        wagon_count++;
        return newtempWagon->wagonId;



};


void Train::addMaterial(char material, int weight){


    if (head == NULL){
        bool strlimit = false;
        wagonNode * new_wagon = new wagonNode;
        head = new_wagon;
        new_wagon->wagonId = wagon_count;

        materialNode * new_material = new materialNode;

        new_material->id = material;
        if (weight > STORAGE_LIMIT)
        {
            new_material->weight = STORAGE_LIMIT;
            weight = weight - STORAGE_LIMIT;
            strlimit = true;
        }
        else
        new_material->weight = weight;

        new_wagon->material = new_material;
        wagon_count++;

        if (strlimit)
        {
            int wagon_id = findWagon(material, weight);
            int remain = addMaterial2Wagon(wagon_id, material, weight);

            while (remain)
            {
                wagon_id = findWagon(material, weight);
                remain = addMaterial2Wagon(wagon_id, material, weight);        
            
            }
        }
        
    }
    else
    {

        int wagon_id = findWagon(material, weight);
        int remain = addMaterial2Wagon(wagon_id, material, weight);

        while (remain)
        {
            wagon_id = findWagon(material, remain);
            remain = addMaterial2Wagon(wagon_id, material, remain);        
        
        }

    }    
        //FILL THIS FUNCTION ACCORDINGLY
}; 


void Train::deleteFromWagon(char material, int weight){

    if (head == NULL)
    return;
    
        int wagon_id = findWagon(material, weight);


        //FILL THIS FUNCTION ACCORDINGLY
};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 