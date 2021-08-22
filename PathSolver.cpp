#include "PathSolver.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

//default constructor
PathSolver::PathSolver(){
    
}

PathSolver::~PathSolver(){
    if (nodesExplored != nullptr) {
        delete nodesExplored;
        nodesExplored = nullptr;
   }if (openList != nullptr) {
        delete openList;
        nodesExplored = openList;
   }
}

NodeList* PathSolver::getNodesExplored(){
    NodeList* closedList= new NodeList(*this->nodesExplored);
    return closedList;
}


void PathSolver::forwardSearch(Env env){
    openList= new NodeList();
    nodesExplored= new NodeList();
    Node* nextNode=nullptr;
    startNode=nullptr;
    endNode=nullptr;

    //obtain posotions of goal and start node
    for (int i=0;i<ENV_DIM;i++){
        for (int x=0;x<ENV_DIM;x++){
            //get the starting node
            if(env[i][x]==SYMBOL_START){
                startNode= new Node(i,x,0);
            }if(env[i][x]==SYMBOL_GOAL){
                endNode= new Node(i,x,0);
            }
        }

    }

    //initalizing values of startnodes and the bool value to run the loop
    nextNode= startNode;
    bool loopC=true;
    
    while(loopC){
        int x= nextNode->getRow();
        int y= nextNode->getCol();

        //initalize lists
        if(nodesExplored->getLength()==0){
            nodesExplored->addElement(nextNode);
        }if(openList->getLength()==0){
            openList->addElement(nextNode);
        }

        //fill out the reachable nodes in the openlist
        nodesReachable(x,y,openList,nodesExplored,nextNode,env);




    //gets the next node that is to be added to nodesExplored
    nextNode= getNextNode(openList,endNode,nodesExplored,true);
    nodesExplored->addElement(nextNode);

    //checks if the current nodes is the last node from the goal node and if thats the case ends the while loop in the next iteration
    for (int i=-1;i<2;i=i+2){
        if((nextNode->getCol() == endNode->getCol()+i) && (nextNode->getRow() == endNode->getRow())){
            loopC=false;
            endNode->setDistanceTraveled(nextNode->getDistanceTraveled()+1);
            nodesExplored->addElement(endNode);
        }else if((nextNode->getCol() == endNode->getCol()) && (nextNode->getRow() == endNode->getRow()+i)){
            endNode->setDistanceTraveled(nextNode->getDistanceTraveled()+1);
            nodesExplored->addElement(endNode);
            loopC=false;
   }
    }

    }
}

//finds the next node to be put into the solution nodesList
Node* PathSolver::solAdd(NodeList* list, Node* node, Env env){
    int x= node->getRow();
    int y= node->getCol();
    NodeList* exc= new NodeList();
    for (int i=-1;i<2;i=i+2){
        if (env[x+(i)][y]==SYMBOL_EMPTY || env[x+(i)][y]==SYMBOL_START){
            exc->addElement(new Node(x+(i),y,0));                                    
        }if(env[x][y+(i)]==SYMBOL_EMPTY || env[x][y+(i)]==SYMBOL_START){
            exc->addElement(new Node(x,y+(i),0));
        }   
    }

    Node* value= new Node(1,2,3);
    for (int i=0;i<list->getLength();i++){
        if((node->getDistanceTraveled()-1) == (list->getNode(i)->getDistanceTraveled())){
            for(int j=0;j<exc->getLength();j++){
                if((list->getNode(i)->getRow()==exc->getNode(j)->getRow()) && (list->getNode(i)->getCol()==exc->getNode(j)->getCol())){
                    value=list->getNode(i);
                }
            }  
        }  
    }
    return value;
}

//checks if a node is in the closed list or not
bool PathSolver::closedCheck2(NodeList* closedList, Node* node){
    bool check=true;
    for(int j=0;j<closedList->getLength();j++){    
        if((node->getRow()==closedList->getNode(j)->getRow()) && (node->getCol()==closedList->getNode(j)->getCol())){    
            check=false;
    }
}
return check;
}

//adds all the viable nodes that can be reached from the current node and adds it to the openList
void PathSolver::nodesReachable(int x, int y, NodeList* openList, NodeList* nodesExplored, Node* nextNode, Env env){
            for (int i=-1;i<2;i=i+2){
            if (env[x+(i)][y]==SYMBOL_EMPTY){
                bool check=false;
                bool verify=true;
                for(int z=0;z<nodesExplored->getLength() && verify;z++){
                    if(!((nodesExplored->getNode(z)->getRow()==x+(i)) && (nodesExplored->getNode(z)->getCol()==y))){
                        check=true;                        
                }else{
                    check=false;
                    verify=false;
                }
            }
            if(check){
                openList->addElement(new Node(x+(i),y,nextNode->getDistanceTraveled()+1));
            }
                            
            }if(env[x][y+(i)]==SYMBOL_EMPTY){
                bool check2=false;
                bool verify2= true;
                for(int z=0;z<nodesExplored->getLength() && verify2;z++){
                    if(!((nodesExplored->getNode(z)->getRow()==x) && (nodesExplored->getNode(z)->getCol()==y+(i)))){
                        check2=true;                 
                }else{
                    check2=false;
                    verify2=false;
                }
            }
            if(check2){
                openList->addElement(new Node(x,y+(i),nextNode->getDistanceTraveled()+1));
            }
        }   
    }

}

//gets the node that is is be added to the closedList (nodesExplored) with the shortest distance or otherwise 
Node* PathSolver::getNextNode(NodeList* openList, Node* endNode, NodeList* closedList, bool check){
    Node* returnVal= nullptr;
    //bool valSet=false; 
    bool banana=true;
    bool valSet=false;
    int minVal=50;
    bool check1=true;
    for(int i=0;i<openList->getLength()&&check1;i++){
            if((openList->getNode(i)->getEstimatedDist2Goal(endNode)<=minVal)){
                minVal=openList->getNode(i)->getEstimatedDist2Goal(endNode);
            //if not in closedL then true
                check=closedCheck2(nodesExplored, openList->getNode(i));
            if(check){
                returnVal= openList->getNode(i);
                valSet=true;
                banana=false;
                check1=false;
        }   
        }

    }

    if(!valSet||banana){
    for(int i=0;i<openList->getLength();i++){
        if(!valSet){ 
            minVal=openList->getNode(i)->getEstimatedDist2Goal(endNode);           
            bool check2=true;
            check2=closedCheck2(nodesExplored, openList->getNode(i));
            if(check2){

                returnVal=openList->getNode(i);
                banana=false;
        }     
        }else if(banana){
            minVal=openList->getNode(i)->getEstimatedDist2Goal(endNode);
            bool check2=true;
            check2=closedCheck2(nodesExplored, openList->getNode(i));
            if(check2){
                returnVal=openList->getNode(i);
        }           
        } 
    }
    }
    return returnVal;
}



// //backtracking provides the final solution path
NodeList* PathSolver::getPath(Env env){
    NodeList* list= new NodeList();
    NodeList* finalList= new NodeList();
    for (int i=0;i<nodesExplored->getLength();i++){
        if (nodesExplored->getNode(i)==endNode){
            list->addElement(nodesExplored->getNode(i));
        }
    }
    bool check=true;
    int apple=0;

    //adding nodes to the solution list
    while(check){
        Node* nxtNode= solAdd(nodesExplored,list->getNode(apple),env);
        list->addElement(nxtNode);
        apple++;
        if(nxtNode==startNode){
            check=false;
        } 
    }

    //traverse the list on distTraveled so we have the startnode at the beginning rather than the end
    int array[list->getLength()]={0};
    for (int i=0;i<list->getLength();i++){
        array[i]=list->getNode(i)->getDistanceTraveled();      
    }

    int n = sizeof(array) / sizeof(array[0]);
    std::sort(array, array + n);

    for (int i=0;i<list->getLength();i++){
        for(int j=0;j<list->getLength();j++){
            if(list->getNode(j)->getDistanceTraveled()==array[i]){
                finalList->addElement(list->getNode(j));
        }
        }
    }

    //make a copy of the solution that is to be returned
    NodeList* pathList= new NodeList(*finalList);
    return pathList;
    
}

//Milestone 4 code:-------------------------------------------------------------------------------

PathSolver::PathSolver(int rows, int columns){
    this->nodesExplored= new NodeList(rows, columns);
    
}


void PathSolver::forwardSearch(Env env, int rows, int columns){
    openList= new NodeList(rows, columns);
    nodesExplored= new NodeList(rows, columns);
    Node* nextNode=nullptr;
    startNode=nullptr;
    endNode=nullptr;

    //obtain posotions of goal and start node
    for (int i=0;i<rows;i++){
        for (int x=0;x<columns;x++){
            //get the starting node
            if(env[i][x]==SYMBOL_START){
                startNode= new Node(i,x,0);
            }if(env[i][x]==SYMBOL_GOAL){
                endNode= new Node(i,x,0);
            }
        }

    }

    //initalize start node and condition to run the loop
    nextNode= startNode;
    bool loopC=true;
    
    while(loopC){
        int x= nextNode->getRow();
        int y= nextNode->getCol();

        //initalize lists 
        if(nodesExplored->getLength()==0){
            nodesExplored->addElement(nextNode);
        }if(openList->getLength()==0){
            openList->addElement(nextNode);
        }


        //fill out the reachable nodes in the openlist
        nodesReachable(x,y,openList,nodesExplored,nextNode,env);



        //add element to closedList (nodesExplored )
        nextNode= getNextNode(openList,endNode,nodesExplored,true);
        nodesExplored->addElement(nextNode);

    //checks if the current nodes is the last node from the goal node and if thats the case ends the while loop in the next iteration
    for (int i=-1;i<2;i=i+2){
        if((nextNode->getCol() == endNode->getCol()+i) && (nextNode->getRow() == endNode->getRow())){
            loopC=false;
            endNode->setDistanceTraveled(nextNode->getDistanceTraveled()+1);
            nodesExplored->addElement(endNode);
        }else if((nextNode->getCol() == endNode->getCol()) && (nextNode->getRow() == endNode->getRow()+i)){
            endNode->setDistanceTraveled(nextNode->getDistanceTraveled()+1);
            nodesExplored->addElement(endNode);
            loopC=false;
   }
    }

    }
           
}


//backtracking provides the final solution path
NodeList* PathSolver::getPath(Env env, int rows, int columns){
    NodeList* list= new NodeList(rows, columns);
    NodeList* finalList= new NodeList(rows, columns);
    for (int i=0;i<nodesExplored->getLength();i++){
        if (nodesExplored->getNode(i)==endNode){
            list->addElement(nodesExplored->getNode(i));
        }
    }
    bool check=true;
    int apple=0;

    //adding nodes to the solution list
    while(check){
        Node* nxtNode= solAdd(nodesExplored,list->getNode(apple),env,rows,columns);
        list->addElement(nxtNode);
        apple++;
        if(nxtNode==startNode){
            check=false;
        } 
    }

    //traverse the list on distTraveled so we have the startnode at the beginning rather than the end
    int array[list->getLength()]={0};
    for (int i=0;i<list->getLength();i++){
        array[i]=list->getNode(i)->getDistanceTraveled();      
    }

    int n = sizeof(array) / sizeof(array[0]);
    std::sort(array, array + n);

    for (int i=0;i<list->getLength();i++){
        for(int j=0;j<list->getLength();j++){
            if(list->getNode(j)->getDistanceTraveled()==array[i]){
                finalList->addElement(list->getNode(j));
        }
        }
    }

    //make a copy of the solution that is to be returned
    NodeList* pathList= new NodeList(*finalList,rows,columns);
    return pathList;
    
}

//gives the next node to be added to the solution
Node* PathSolver::solAdd(NodeList* list, Node* node, Env env, int rows, int columns){
    //checks if the curr node has '.' surrounding it
    int x= node->getRow();
    int y= node->getCol();
    NodeList* exc= new NodeList(rows, columns);
    for (int i=-1;i<2;i=i+2){
        if (env[x+(i)][y]==SYMBOL_EMPTY || env[x+(i)][y]==SYMBOL_START){
            exc->addElement(new Node(x+(i),y,0));                                    
        }if(env[x][y+(i)]==SYMBOL_EMPTY || env[x][y+(i)]==SYMBOL_START){
            exc->addElement(new Node(x,y+(i),0));
        }   
    }

    Node* value= new Node(1,2,3);
    //checks if the surrounding nodes are viable or not
    for (int i=0;i<list->getLength();i++){
        if((node->getDistanceTraveled()-1) == (list->getNode(i)->getDistanceTraveled())){
            for(int j=0;j<exc->getLength();j++){
                if((list->getNode(i)->getRow()==exc->getNode(j)->getRow()) && (list->getNode(i)->getCol()==exc->getNode(j)->getCol())){
                    value=list->getNode(i);
                }
            }  
        }  
    }
    return value;
}

//-----------------------------