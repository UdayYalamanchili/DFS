// Assignment #7
// Name: Uday Yalamanchili
// ASU Email Address: uyalaman@asu.edu
// Description: This program builds our own custom data structure by defining the methods makeEdge, printGraph, 
// DFS, DFS_visit, updateUse, constructor and destructor for the class AdjacencyList. The methods DFS, DFS_visit 
// help in performing the depth first search for a given graph.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include "LinkedList.h"
#include "Stack.h"

using namespace std;

//class AdjacencyList will contain an array of pointers each pointing to a linked list and a LIFO stack
class AdjacencyList
{
    private:
    string *color;
    int *pi;
    int *d;
    int *f;
    int time;

    public:
    int n_nodes, n_edges;
    LinkedList **list;
    Stack *st;
    AdjacencyList(int nodes, int edges);
    ~AdjacencyList();
    bool makeEdge(int node1, int node2, int weight);
    void printGraph();
    void DFS();
    void DFS_visit(Vertex *v, int length);
    void updateUse(int node1, int node2, int weight);
};

//Constructor to initialize the AdjacencyList
AdjacencyList::AdjacencyList(int nodes, int edges)
{
    this->time = 0;
    this->n_nodes = nodes;
    this->n_edges = edges;
    this->list = new LinkedList * [n_nodes];
    this->color = new string[n_nodes+1];
    this->pi = new int[n_nodes+1];
    this->d = new int[n_nodes+1];
    this->f = new int[n_nodes+1];
    this->st = new Stack[n_edges];

    // Initialize the array of pointers to NULL
    for (int j = 0; j < n_nodes; ++j) 
    {
        *(list + j) = NULL;
    }

    // Traverse the pointer array and update it with default values
    for (int k = 0; k < n_nodes; ++k) 
    {
        list[k] = new LinkedList(); // each pointer in the array points towards a linked list
        Vertex * n = new Vertex;
        n->node = k+1;
        n->notUsed = "NotUsed";
        n->weight = 0;
        n->next = NULL;
        list[k]->head = n;
        *(list + k) = list[k]; // update the pointer location with the new linked list location
        color[k] = "white";
        pi[k] = 0;
        d[k] = 0;
        f[k] = 0;
    }

    // Dynamic allocation of size to tempStack and Circuit based on the number of edges
    this->st->size = edges;
    this->st->tempStack = new Edge[n_edges];
    this->st->Circuit = new Edge[n_edges];

    // Traverse both the stacks and update it with defaut values
    for(int i = 0; i < n_edges; i++)
    {
        this->st->tempStack[i] = Edge();
        this->st->Circuit[i] = Edge();
        this->st->tempStack[i].vertex1 = 0;
        this->st->tempStack[i].vertex2 = 0;
        this->st->tempStack[i].weight = 0;
        this->st->Circuit[i].vertex1 = 0;
        this->st->Circuit[i].vertex2 = 0;
        this->st->Circuit[i].weight = 0;
    }
}

//Destructor
//Description: Destructor to delete the created linked lists, stacks and free the memory
AdjacencyList::~AdjacencyList()
{
    for (int k = 0; k < n_nodes; ++k)
    {
        delete list[k];
    }
    delete list;
    delete st;
}

//Description: This method adds a new edge between the given nodes and weight in increasing order (of nodes followed 
//             by weights) by calling the insertEdge method from the LinkedList class.
bool AdjacencyList::makeEdge(int node1, int node2, int weight)
 {
    int i = 0;
    bool status = false;
    for(i=0; i<n_nodes; i++)
    {
        if (list[i]->head->node == node1)
        {
            status = list[i]->insertEdge(node1, node2, weight);
        }
    }
    return status;
 }

//Description: This method helps print out all the nodes and their edges in the graph
void AdjacencyList::printGraph()
{
    cout << "The Graph contains:" << endl;
    cout << "-------------------" << endl;

    for(int i=0; i<n_nodes; i++)
    {
        if (list[i]->LengthOfList() > 0)
        {
            cout << "From: " << list[i]->head->node << " with its degree " << list[i]->LengthOfList() << "\n";
            list[i]->printList();
            cout << "\n";
        }
    }
}

//Description: This method performs the depth first search
void AdjacencyList::DFS()
{
    for(int i = 0; i <= n_nodes; i++)
    {
        color[i] = "white";
        pi[i] = 0;
        d[i] = 0;
        f[i] = 0;
    }
    for (int j = 0; j < n_nodes; j++)
    {
        if (color[list[j]->head->node] == "white" || color[list[j]->head->node] == "grey")
            DFS_visit(list[j]->head, list[j]->LengthOfList());
    }
    st->printCircuit();
}

//Description: This method visits each node as part of depth first search and updates relevant content
void AdjacencyList::DFS_visit(Vertex * v, int length)
{
    int u = v->node;

    Vertex *current_node = new Vertex();
    Vertex *next_node = new Vertex();

    current_node = v;
    color[u] = "grey";
    time++;
    d[u] = time;
    for(int i=0; i < length; i++)
    {
        next_node = current_node->next;
        if (color[next_node->node] != "black" && next_node->notUsed != "used")
        {
            pi[next_node->node] = current_node->node; // update the pi array with the parent node
            next_node->notUsed = "used"; // update the notUsed attribute with "used" once it has been visited
            updateUse(next_node->node, v->node, next_node->weight); // update the notUsed attribute with "used" for the duplicate edge as well (as it is an undirected graph)
            bool status1 = st->push(v->node,next_node->node,next_node->weight,st->tempStack); // push the edge into tempStack
            if (status1 == true)
                st->printStack();
            DFS_visit(list[(next_node->node)-1]->head, list[(next_node->node)-1]->LengthOfList()); // recursion on DFS_visit
        }
        current_node = next_node;
    }
    Edge *circuit_edge = new Edge();
    circuit_edge = st->pop(st->tempStack); // pop the last edge out of tempStack
    bool status2 = st->push(circuit_edge->vertex2,circuit_edge->vertex1,circuit_edge->weight,st->Circuit); // push the popped edge into Circuit stack
    if  (status2 == true)
        st->printStack();
    color[u] = "black";
    time++;
    f[u] = time;
}

// Description: This method updates the notUsed attribute of an edge to "used" once it has been visited.
//              Useful when trying to update the duplciate edges in the undirected graph
void AdjacencyList::updateUse(int node1, int node2, int weight)
{
    Vertex *dummy = new Vertex();
    
    for (int i = 0; i < n_nodes; i++)
    {
        dummy = list[i]->head;
        if (list[i]->head->node == node1)
        {
            do
            {
                dummy = dummy->next;
                if (dummy->node == node2 && dummy->weight == weight)
                    dummy->notUsed = "used";
            } 
            while (dummy->next != NULL);
        }
    }
}