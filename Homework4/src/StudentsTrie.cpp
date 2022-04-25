#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

TrieNode * find_child_node(char a);

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD BELOW
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   // IMPLEMENT THIS METHOD

   TrieNode * temp = root;
   string temp_string = student_id;
   int id_int;

   for (size_t i = 0; i < temp_string.size(); i++)
   {
      id_int = temp_string[i] - '0';
      // TrieNode * parent =  find_child_node(student_id[i]);
      if(temp->children[id_int] == NULL){

         TrieNode *new_node = new TrieNode(temp_string[i]);
         temp->children[id_int] = new_node;
      }
      temp = temp->children[id_int];

   }

}; 

// Check existence of a student ID in the StudentsTrie
bool StudentsTrie::in_the_trie ( const string& student_id ) {
   // IMPLEMENT THIS METHOD

   TrieNode * temp = root;
   int id_int;

   for (size_t i = 0; i < student_id.size(); i++)
   {
      id_int = student_id[i] - '0';
      // TrieNode * parent =  find_child_node(student_id[i]);
      if(temp->children[id_int] == NULL){

         return false;

      }
      temp = temp->children[id_int];

   }


   // IN ORDER NOT TO GET COMPILER ERROR, I RETURN A DUMMY VALUE
   return true; 
}; 

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

// TrieNode * StudentsTrie::find_child_node(char a){

//       TrieNode * temp = root;

//       for (size_t i = 0; i < MAX_CHILDREN; i++)
//       {
//          if (temp->children[i]->digit == a)
//          {
//             return temp->children[i-1];
//          }
         
//       }
      


// return NULL;
// }

