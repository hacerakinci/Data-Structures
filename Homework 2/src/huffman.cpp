//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Hacer Akıncı
//---Student Number: 150200007
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    
    //TODO

    // i is iterator, itarete all the sortedKey
    int i = 0;
    // c keeps the previous character to compare new one and according to that create new node
    char c = sortedKey[0];

    // temp is pointer that keeps character and value
    Node *temp = new Node;

    // initialize temp with first character
    temp->token.symbol = c; 
    int size = sortedKey.size();
    while(i < size){

        // every time if character change to new one I will add to priority queue  
        if(c != sortedKey[i]){
            queue.enque(temp);

            // update the node for new character
            temp = new Node;
            c = sortedKey[i];
            temp->token.symbol = c; 
        }

        // if character is still same, then just increase value of node
        else{
            temp->token.val++;

            // I increase i just here because when the new character come I didn't increase the value to not repeat my code
            i++;
        }
    }
    // I add last character node to queue
    queue.enque(temp);
    
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    //TODO

    // first create priority queue from my sortedKey
    findFrequency();

    // then add to the huffmanTree
    while(queue.head != NULL){
        Node* node1 = queue.dequeue();

        // if there is just one node is left in queue that means that node is root, there is no merge operation
        if(queue.head == NULL){
            huffmanTree.root = node1;
            break;
        }
        // if there are two or more nodes in queue, continue to merge and add to queue
        Node* node2 = queue.dequeue();
        queue.enque(huffmanTree.mergeNodes(node1 ,node2));
    }

};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

bool Huffman::isInclude(char tokenChar, string nodeSymbol){
    // look all the string if it is include the character, then return true 
    int i = 0;
    int size = nodeSymbol.size();

    while(i < size){
        if(nodeSymbol[i] == tokenChar){
            return true;
        }
        i++;
    } 

    // if it is not in the string return false
    return false;
};
//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    //TODO

   //  check with DFS approach

   // if there is a left child and it is include the character we search then add '0' then call funtion again
   if(traverse->left && isInclude(tokenChar, traverse->left->token.symbol)){
        tokenBinary = "0" + getTokenBinary(tokenChar, traverse->left, tokenBinary);
   }

   // if there is a right child and it is include the character we search then add '1' then call funtion again
   if(traverse->right && isInclude(tokenChar, traverse->right->token.symbol)){
        tokenBinary = "1" + getTokenBinary(tokenChar, traverse->right, tokenBinary);
   }

    // if it is leaf, then return
    return tokenBinary;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //TODO
    int size = password.size();

    // I initialize those string for the possibility that asking encode another password in edge cases
    encodedBinaryPassword  = "";
    encodedValPassword = "";
    decodedPassword = "";

    // for every character get Binary expression from huffmanTree
    for(int i=0; i < size; i++){
        string tokenBinary ;
        string temp = getTokenBinary(password[i], huffmanTree.root, tokenBinary);

        encodedBinaryPassword += temp;

        // all the values are equal their lengths
        encodedValPassword += to_string(temp.length());
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    // i is iterating values of password, j is iterating the binary expressions 
    int i = 0, j = 0, size = encodedValPassword.size();

    while(i < size){
        // 48 is ASCII value of 0, so I  can find my encoded binary expression string lenght in integer format
        int val = encodedValPassword[i] - 48;

        // I split the binary expression for every character and encodedToken keeps that substring
        string encodedToken;


        while(val > 0){
            encodedToken += encodedBinaryPassword[j];
            j++;
            val--;
        }

        // after that operation, one character is founded and added to decodedPassword
        decodeToken(encodedToken);
        i++; 
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //TODO

    // start from root and search my character with DFS, and the string shows the direction for every level
    Node* temp = huffmanTree.root;
    int size = encodedToken.size();
    int i = 0;
    
    while(i < size){
        if(encodedToken[i] == '0'){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
        i++;
    }
    // in the end I find the character, so I add to decodedPassword
    decodedPassword += temp->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};