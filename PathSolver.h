#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);
    
    

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    //checks if a node is viable to be added to openList
    void nodesReachable(int x, int y, NodeList* openList, NodeList* nodesExplored, Node* nextNode, Env env);

    //gives the next node to be added to the solution
    Node* solAdd(NodeList* list, Node* node, Env env);


    //gets the nextNode to be added to the closedList
    Node* getNextNode(NodeList* openList, Node* endNode, NodeList* closedList, bool check);

    //checks if a node is in the closedList
    bool closedCheck2(NodeList* closedList, Node* node);


    NodeList* openList;

    Node* startNode;
    
    Node* endNode;



    //Milestone 4----------------------------------------
   PathSolver(int rows, int columns);

   void forwardSearch(Env env, int rows, int columns);
   
   NodeList* getPath(Env env, int rows, int columns);

   //ms4 closed check
   Node* solAdd(NodeList* list, Node* node, Env env, int rows, int columns);

   
 

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

 


    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER