// Assignment #7
// Name: Uday Yalamanchili
// ASU Email Address: uyalaman@asu.edu
// Description: This program builds our own custom data structure by defining the methods insertEdge, printList, 
//              LengthOfList constructor and destructor for the class LinkedList.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Vertex represents the node information
struct Vertex
{
    int node;
    int weight;
    string notUsed;
    struct Vertex * next;
};

//class LinkedList will contains a linked list of vertexs
class LinkedList
{
    private:

    public:
    struct Vertex * head;
    LinkedList();
    ~LinkedList();
    bool insertEdge(int node1, int node2, int weight);
    void printList();
    int LengthOfList();
};

//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Description: Destructor to delete every element in the linked list and free the memory
LinkedList::~LinkedList()
{
    struct Vertex * select_element = head;  // The current selection in the list
    struct Vertex * next_element = NULL;   // The next element of the current selection, initialized with NULL
    int k = 0;

    while (select_element != NULL) // deletes each entry starting from head
    {
        next_element = select_element -> next;
        delete select_element;
        select_element = next_element;
        k++;
    }
    
    cout << "The number of deleted nodes is: " << k << "\n" << endl;
}

//Description: This method adds a new edge between the given nodes and weight in increasing order (of nodes, weights)
bool LinkedList::insertEdge(int node1, int node2, int weight)
 {
    struct Vertex * current_node = new Vertex();
    struct Vertex * next_node = new Vertex();
    struct Vertex * new_node = new Vertex();

    current_node = head;
    new_node -> node = node2;
    new_node -> weight = weight;
    new_node -> next = NULL;

    if ((head -> node == node1) && (head -> next == NULL)) // This code helps to insert a new entry as the first entry after the head
    {
        head -> next = new_node;
        return true;
    }

    if ((head -> node == node1) && (head -> next != NULL)) // This code helps to insert a new entry into the linked list based on node2 data and weight
    {
        for(int i=0; i<=LengthOfList(); i++)
        {   
            if (current_node -> next != NULL)
            {
                next_node = current_node -> next;
                if (new_node -> node < next_node -> node) // Inserted in increasing of node values. If they are equal, increasing order of weights is used
                {
                    new_node->next = next_node;
                    current_node -> next = new_node;
                    return true;
                }
                else if (new_node -> node == next_node -> node)
                {
                    if (new_node -> weight < next_node -> weight)
                    {
                        new_node->next = next_node;
                        current_node -> next = new_node;
                        return true;
                    }
                }
            }
            else
            {
                current_node -> next = new_node;
                return true;
            }
            current_node = next_node;
        }
        return true;
    }
    return false;
 }

//Description: This method helps print the edge information with weight value in the given list
void LinkedList::printList()
{
    struct Vertex * temp = new Vertex();
    temp = head;

    while (temp->next != NULL) // iterate and print till the temp pointer reaches the end of list)
    {
        temp = temp -> next;
        cout << "To: " << temp -> node << " with weight " << temp -> weight << "\n";  
    } 
}

//Description: This method returns the length of the given list
int LinkedList::LengthOfList()
{
    struct Vertex * temp = new Vertex();
    temp = head;
    int count = 0;

    while (temp->next != NULL) // iterate and print till the temp pointer reaches the end of list
    {
        temp = temp -> next;
        count++;
    }
    return count;
}   