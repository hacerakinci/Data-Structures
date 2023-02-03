//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Hacer Akıncı
//---Student Number: 150200007
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //TODO
    // initialize head to NULL 
    head = NULL; 
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    //TODO
    
    // cursor start from head and keep going until to find bigger element than my newnode or NULL 
    Node* cursor = this->head;

    // temp pointer first is NULL but then it keeps the previous pointer of cursor so I can add my newnode temp->next  
    Node* temp = NULL;

    while(cursor != NULL && cursor->token.val <= newnode->token.val){
        // update pointers
        temp = cursor;
        cursor = cursor->next;
    }
    
    // if temp is NULL that means either my queue is empty or newnode value is smaller than head 
    if(temp == NULL){
        head=newnode;

        // if queue is empty, I just assign NULL to head->next
        head->next = cursor;
        return;
    }
    // if temp is not NULL, then assign newnode to the between two nodes
    temp->next = newnode;
    newnode->next = cursor;
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //TODO     
    
    // keep the head pointer to return it
    Node* temp = this->head;

    // I don't need to check if head is NULL because I check when I call the dequeue function
    this-> head = this-> head->next;
    return temp;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //TODO
    root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    //TODO
    
    // call the function for recursive approach 
    deleteTree(this->root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    
    // if the root is NULL, then I should check that condition
    if(node == NULL){
        return;
    }

    // call function for its childs if there are.

    if(node->right){
        deleteTree(node->right);
    }
    if(node->left){
        deleteTree(node->left);
    }
    
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
   //TODO
   Node* merged = new Node;

   // initialize the stmbol and val with temp1 and temp2
   merged->token.symbol = temp1->token.symbol + temp2->token.symbol;
   merged->token.val = temp1->token.val + temp2->token.val;

   // assign right and left child
   merged->left = temp1;
   merged->right = temp2;
   
   return merged;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};