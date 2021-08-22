/*
MileStone 1
This was very simple I just created enviroments with differnt dimentions and multile paths to the goal to accomodate for
any kind of enviroment that the forwardsearch may encounter.


MileStone 2
The only hard bit for this one was the pathsolver and putting the pesudocode into actual code.
I did implement the openList and closedList mehtods but insted of deleting the previous nodes 
from openlist I kept it there as I had already gotten quite far also my forwardsearch was working
without deleting it so I kept it there. My forwardsearch is pretty much the same as the pesudocode
except for the difference that I used a bool value to run my while loop and I added the goalNode
once I reached the node before it and made the boolvalue false to stop the while loop.

MileSote 3
This was very stright forward but the main  issue I initally encountered when just finding the path
based on distance travelled -1 was that it would not always give me the shorted path so I also looked
around the node so that I wasen't getting any nodes that were not next to the current node. Also at the
end once I got my solution list I sorted it so I would have the start node at the beginning.

MileStone 4
The was the hardest once to implement as since it was dyamic I wasn't sure how to obtain the dimentions
but since I knew that a string was essentially a char array I knew that I could store my input inside of
it. Also since at the end of every row there is a /n char it was easy to obtain the number of rows and columns.
Everything else was pretty stright forward once I could read an enviroment of any size as all I had to do in my other
classes was to replace every method that used ENV_DIM with rows; and columns. I did this by passing the rows and column 
values as parameters in my methods and constructors so I had access to them thorughout my program. I also created a ms4 method
so that it would be easier to run the code from ms4 and also stop the main method from being too crowded.

Problems:
A problem I encountered was that I was unable to delete anything from the heap as deleting them resulted in a segmentation error 
which I couldn't fix. This was because of the dynamic dimentions and as I couldn't pass the rows and coloums as parameters so I couldn't
delete the elements in the nodes array.


*/

//TO USE THE MILESTONE 1-3 code please uncomment the commented code and commment the ms4 code

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"
#include "milestone4.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

bool checkSol(int x,int y, NodeList* solution);
void ms4();

// Milestone 4:
Env make_env(const int rows, const int columns, std::string temp);
void printEnvStdout(Env env, NodeList* solution, int rows, int columns);
void delete_env(Env env, int rows, int columns);
void printDirections(Env env, NodeList* solution, int rows, int columns);




int main(int argc, char** argv){
    // // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // // AS YOU GO ALONG.
    // // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // // testNode();
    // // testNodeList();
    // // std::cout << "DONE TESTING" << std::endl << std::endl;

    // // Load Environment 
    // Env env;
    // readEnvStdin(env);
    
    // // Solve using forwardSearch
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    // PathSolver* pathSolver = new PathSolver();
    // pathSolver->forwardSearch(env);

    // //NodeList* exploredPositions = nullptr;
    // //exploredPositions = pathSolver->getNodesExplored();

    // // Get the path
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3

    // NodeList* solution = pathSolver->getPath(env);
    // printEnvStdout(env,solution);


    // delete pathSolver;
    // delete exploredPositions;
    // delete solution;
    ms4();
}

void readEnvStdin(Env env) {
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cin >> env[i][j];
        }
    }
}


//Mileston 4 start--------------------------------------------------------------------------------------
void ms4(){
    std::string temp = "";
    
    // Rows start at 1 because we start counting from 0 and the loop stops before appedning the fianl value
    
    int rows = 1;
    int columns = 0;

    /*
        The dimentions are determined by appending each char to a string.
        The rows are obtained by counting the number of new line chars while
        the columns are equivalent to the string length divided by number of rows.
        The loop keeps on occuring until we reach the end of input.
    */
        char c;
        while (!std::cin.eof()) {
            std::cin.get(c);
            if (c == SYMBOL_EMPTY || c == SYMBOL_START || c == SYMBOL_GOAL || c == SYMBOL_WALL) {
                temp += c;
            }
            //we know we have reached the end of a row once the \n is found
            if (c == '\n') {
                rows++;
            }
        }
    
    columns = temp.length()/rows;
    


    Env env;
    env = make_env(rows, columns,temp);


    PathSolver* pathSolver = new PathSolver(rows,columns);
    pathSolver->forwardSearch(env, rows, columns);
    //std::cout<<" "<<std::endl;
    NodeList* solution = pathSolver->getPath(env,rows, columns);

    printEnvStdout(env,solution,rows,columns);  

    //pathSolver->~PathSolver();
    //delete pathSolver;
    //delete exploredPositions;
    //delete solution;  
}

//makes new enviroment and appends each character to a char array(string)
Env make_env(const int rows, const int columns, std::string temp){   
    Env env = nullptr;
    int length = temp.length();
    int curr = 0;
    //creating the dymanic dimentions
    if (rows >= 0 && columns >= 0) {
        env = new char*[rows];
        for (int i = 0; i != rows; i++) {
            env[i] = new char[columns];
        }
    }
    //loops through the new enviroment and adds values to it by using the temp array
    while(curr<length-1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                env[i][j] = temp[curr];
                curr++;
            }
        }
    }
    return env;
}

//printing the path for the dynamic enviroment
void printEnvStdout(Env env, NodeList* solution, int rows, int columns){

    //to get the solution direction matrix
    int gx=0;
    int gy=0;
    for(int i=0;i<solution->getLength();i++){
        if(env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()]==SYMBOL_GOAL){
            gx=solution->getNode(i)->getRow();
            gy=solution->getNode(i)->getCol();
        }
    }

    for(int i=0;i<solution->getLength();i++){
        int x=solution->getNode(i)->getRow();
        int y=solution->getNode(i)->getCol();

        for (int j=-1;j<2;j=j+2){
            if (env[x+(j)][y]==SYMBOL_EMPTY && checkSol(x+(j),y,solution)){
                if(j<0){
                    env[x+(j)][y]='^';
                }else if(env[x+(j)][y]==SYMBOL_EMPTY && checkSol(x+(j),y,solution)){
                    if(j>0){
                        env[x+(j)][y]='V';

                    }
                }                           
             }if (env[x][y+(j)]==SYMBOL_EMPTY && checkSol(x,y+(j),solution)){
                    if(j<0){
                        env[x][y+(j)]='<';
                    }else if(env[x][y+(j)]==SYMBOL_EMPTY && checkSol(x,y+(j),solution)){
                        if(j>0){
                            env[x][y+(j)]='>';
                    }
                }                           
            }
    }
}

    //to point to goal node
    for (int j=-1;j<2;j=j+2){
        if (checkSol(gx+(j),gy,solution)){
                if(j<0){
                    env[gx+(j)][gy]='V';
                }else if(checkSol(gx+(j),gy,solution)){
                    if(j>0){
                        env[gx+(j)][gy]='^';

                    }
                }                           
             }if (checkSol(gx,gy+(j),solution)){
                    if(j<0){
                        env[gx][gy+(j)]='>';
                    }else if(checkSol(gx,gy+(j),solution)){
                        if(j>0){
                            env[gx][gy+(j)]='<';

                    }
                }                           
            }
    }


    // Prints out the path taken
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << env[i][j];
            }
        std::cout << std::endl;
    }
}





//Milestone 4 end-----------------------------------------------------------------------------------------


//checks of a node is in the solution or not
bool checkSol(int x,int y, NodeList* solution){
    bool check=false;
    for(int i=0;i<solution->getLength();i++){
        if(solution->getNode(i)->getRow()==x && solution->getNode(i)->getCol()==y){
            check=true;

        }
    }
    return check;
}

void printEnvStdout(Env env, NodeList* solution){

    //to get the solution direction matrix
    int gx=0;
    int gy=0;
    for(int i=0;i<solution->getLength();i++){
        if(env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()]==SYMBOL_GOAL){
            gx=solution->getNode(i)->getRow();
            gy=solution->getNode(i)->getCol();
        }
    }

    for(int i=0;i<solution->getLength();i++){
        int x=solution->getNode(i)->getRow();
        int y=solution->getNode(i)->getCol();

        for (int j=-1;j<2;j=j+2){
            if (env[x+(j)][y]==SYMBOL_EMPTY && checkSol(x+(j),y,solution)){
                if(j<0){
                    env[x+(j)][y]='^';
                }else if(env[x+(j)][y]==SYMBOL_EMPTY && checkSol(x+(j),y,solution)){
                    if(j>0){
                        env[x+(j)][y]='V';

                    }
                }                           
             }if (env[x][y+(j)]==SYMBOL_EMPTY && checkSol(x,y+(j),solution)){
                    if(j<0){
                        env[x][y+(j)]='<';
                    }else if(env[x][y+(j)]==SYMBOL_EMPTY && checkSol(x,y+(j),solution)){
                        if(j>0){
                            env[x][y+(j)]='>';
                    }
                }                           
            }
    }
}

    //to point to goal node
    for (int j=-1;j<2;j=j+2){
        if (checkSol(gx+(j),gy,solution)){
                if(j<0){
                    env[gx+(j)][gy]='V';
                }else if(checkSol(gx+(j),gy,solution)){
                    if(j>0){
                        env[gx+(j)][gy]='^';

                    }
                }                           
             }if (checkSol(gx,gy+(j),solution)){
                    if(j<0){
                        env[gx][gy+(j)]='>';
                    }else if(checkSol(gx,gy+(j),solution)){
                        if(j>0){
                            env[gx][gy+(j)]='<';
                    }
                }                           
            }
    }



    // Prints out the path taken
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cout << env[i][j];
            }
        std::cout << std::endl;
    }
}


void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size   
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    //Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
    
}