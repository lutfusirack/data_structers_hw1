#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

#define DIFF_CHARS 10

char char_a[DIFF_CHARS] = {0};
int freq_a[DIFF_CHARS] = {0};
int countOfChar = 0;
void add2array(string s){

    char temp;
    memcpy(&temp,s.c_str(),1);

    for (size_t i = 0; i < DIFF_CHARS; i++)
    {
        if (temp == char_a[i])
        {
            freq_a[i]++;
            return;
        }
    }

    char_a[countOfChar] = temp;
    freq_a[countOfChar]++;
    countOfChar++;


}

void Huffman::add2PQ(){

    for (int i = 0; i < countOfChar; i++)
    {
        Node * temp = new Node;
        temp->token.symbol = char_a[i];
        temp->token.count = freq_a[i];

        this->priority_queue.push(temp);

    }

}

int Huffman::findindex(Token *arr,string elem){
	// YOU HAVE TO COMPLETE THIS PART
	// THIS FUNCTION RETURNS THE INDEX OF STRING ON TOKEN ARRAY, IF STRING IS NOT IN TOKEN ARRAY, RETURNS -1

    // for (size_t i = 0; i < 10; i++)
    // {
    //     /* code */
    //     token_array[i].symbol += (char_a[i]);
    //     token_array[i].count = freq_a[i];
    // }
    for (size_t i = 0; i < 100; i++)
    {
        if (strcmp(token_array[i].symbol.c_str(),elem.c_str()) == 0) 
        {
            return i;
        }
    }
return -1;
    
}

void Huffman::find_frequencies()
{
    // int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
        // cout<<s;
        add2array(s);
        // YOU HAVE TO COMPLETE THIS PART
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
    if (this->token_count == 0)
    {
        head = newnode;
        this->token_count++;
    }
    else{

        Node * temp = this->head;
        Node * prev = this->head;
        while (temp != NULL)
        {
            if (temp->token.count > newnode->token.count)
            {
                break;
            }   
            prev = temp;
            temp = temp->next;
        }                
        if ((prev == this->head) && temp == this->head)
        {
            newnode->next = this->head;
            this->head = newnode;
        }
        else{
        newnode->next = prev->next;
        prev->next = newnode;}
        this->token_count++;
    }

}

Node* PriorityQueue::pop()
{
    // YOU HAVE TO COMPLETE THIS PART
    Node * temp = this->head;
    this->head = this->head->next;
    this->token_count--;
    temp->next =NULL;
    return temp;
}

void Huffman::get_priority_queue()
{
    // YOU HAVE TO COMPLETE THIS PART  
    add2PQ();

}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    // YOU HAVE TO COMPLETE THIS PART
    Node * temp3 = new Node;

        temp3->token.count = node1->token.count + node2->token.count;
        temp3->token.symbol = node1->token.symbol + node2->token.symbol;

        temp3->left = node1;
        temp3->right = node2;
    return temp3;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    // YOU HAVE TO COMPLETE THIS PART 
    while(this->priority_queue.token_count > 1)
    {
        
        Node * temp = this->priority_queue.pop();
        Node * temp2 = this->priority_queue.pop();

        Node * temp3 = this->huffman_binary_tree.merge(temp,temp2);

        this->priority_queue.push(temp3);
        
    }
    if (this->priority_queue.token_count == 1)
    {
        this->huffman_binary_tree.root = this->priority_queue.pop();
    }
    
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE
        
    if (traversal->left)
    {
        
        get_codes(traversal->left,codepart+'0');
    }
    if(traversal->right){
        get_codes(traversal->right,codepart+'1');
    }
    if((traversal->right == NULL) && (traversal->left == NULL)){
        

        traversal->token.code=codepart;
        token_array[token_count] = traversal->token;
        token_count++;
        
        // cout<<traversal->token.symbol<<" = "<<codepart<<endl;


        return;
    }


}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
