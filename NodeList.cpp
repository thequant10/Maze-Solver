#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
   //initalize the list
   this->length = 0;
   for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE;i++) {
      this->nodes[i] = nullptr;
   }
}


NodeList::~NodeList(){
    for(int i=0;i<NODE_LIST_ARRAY_MAX_SIZE;i++)
    {
        delete nodes[i];
        nodes[i]=NULL;
    }
}


NodeList::NodeList(NodeList& other) {
   this->length = other.length;
   for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++) {
      this->nodes[i] = nullptr;
      if(other.nodes[i] != nullptr) {
        this->nodes[i] = new Node(*other.nodes[i]);
      }
   }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
}

Node* NodeList::getNode(int i){
    return nodes[i];
}


// Milestone 4 code---------------------------------------
NodeList::NodeList(int rows, int columns) {
   //initalize the list
   this->length = 0;
   nodes = nullptr;
   if (rows >= 0 && columns >= 0) {
      for (int i = 0; i < (rows*columns); i++) {
         nodes = new Node*[rows*columns];
         nodes[i] = nullptr;
      }
   }
}

// Milestone 4 Copy Constructor
NodeList::NodeList(NodeList& other, int rows, int columns) {
   //add the copied nodes into the nodes array
   this->length = other.length;
   nodes = new Node*[rows*columns];
   if (rows >= 0 && columns >= 0) {
      for (int i = 0; i < rows*columns; i++) {
         nodes[i] = other.nodes[i];
      }
   }
}
