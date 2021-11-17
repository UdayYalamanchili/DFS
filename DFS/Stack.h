// Assignment #7
// Name: Uday Yalamanchili
// ASU Email Address: uyalaman@asu.edu
// Description: This program builds our own custom data structure (LIFO Stack) using arrays by defining the methods 
//              push, pop, printStack, printCircuit, constructor and destructor for the class Stack.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Edge represents each edge and its corressponding weight
struct Edge
{
    int vertex1, vertex2, weight;
};

//class Stack (LIFO) will contain an array of Edges. It has two variables tempStack and Circuit of Stack data structure
class Stack
{
    private:

    public:
    int size;
    struct Edge * tempStack;
    struct Edge * Circuit;
    Stack();
    Stack(int edges);
    ~Stack();
    bool isEmpty(Edge * e);
    bool push(int v1, int v2, int w, Edge * e);
    Edge * pop(Edge * e);
    void printStack();
    void printCircuit();
};

Stack::Stack()
{

}

//Constructor to initialize the stacks
Stack::Stack(int edges)
{

}

//Destructor
//Description: Destructor to delete both the stacks and free the memory
Stack::~Stack()
{
    delete tempStack;
    delete Circuit;
}

//Description: This method checks if the given stack is empty
bool Stack::isEmpty(Edge * e)
{
    if (e[0].vertex1 == 0 && e[0].vertex2 == 0)
        return true;
    return false;
}

//Description: This method pushes a given edge into the given stack
bool Stack::push(int v1, int v2, int w, Edge * e)
 {
    bool status = false;

    // If the stack is empty, the edge is pushed as the first element
    if (isEmpty(e) == true)
    {
        e[0].vertex1 = v1;
        e[0].vertex2 = v2;
        e[0].weight = w;
        status = true;
    }
    // If the stack isn't empty, the new edge is added at the end i.e. last entry
    else
    {
        for (int i = 0; i < size; i++)
        {
            if(e[i].vertex1 == 0 && e[i].vertex2 == 0)
            {
                e[i].vertex1 = v1;
                e[i].vertex2 = v2;
                e[i].weight = w;
                status = true;
                break;
            }
        }
    }
    return status;
 }

//Description: This method pops the last edge of the given stack
Edge * Stack::pop(Edge * e)
 {
    Edge * pop = new Edge();

     // If the stack is empty, the edge is pushed as the first element
    if (isEmpty(e) == true)
    {
        pop->vertex1 = 0;
        pop->vertex2 = 0;
        pop->weight = 0;
        return pop;
    }

    // We pop out the last entry in the stack
    for (int i = 0; i <= size; i++)
    {
        if(e[i].vertex1 == 0 && e[i].vertex2 == 0)
        {
            pop->vertex1 = e[i-1].vertex1;
            pop->vertex2 = e[i-1].vertex2;
            pop->weight = e[i-1].weight;
            e[i-1].vertex1 = 0;
            e[i-1].vertex2 = 0;
            e[i-1].weight = 0;
            break;
        }
    }
    return pop;
 }

//Description: This method helps print all the edges in Circuit and tempStack
void Stack::printStack()
{
    cout << "Circuit:" << " ";

    if (Circuit[0].vertex1 != 0 && Circuit[0].vertex2 != 0)
    {
        for(int i=0; i<size; i++)
        {
            if(Circuit[i].vertex1 != 0 && Circuit[i].vertex2 != 0)
                cout << "(" << Circuit[i].vertex1 << "," << Circuit[i].vertex2 << ")" << " ";
        }
        cout << endl;
    }
   
    else if (Circuit[0].vertex1 == 0 && Circuit[0].vertex2 == 0)
        cout << "Empty" << endl;

    cout << "Stack:" << "   ";

    if(tempStack[0].vertex1 != 0 && tempStack[0].vertex2 != 0)
    {
        for(int j=0; j<size; j++)
        {
            if(tempStack[j].vertex1 != 0 && tempStack[j].vertex2 != 0)
                cout << "(" << tempStack[j].vertex1 << "," << tempStack[j].vertex2 << ")" << " ";
        }
        cout << endl;
    }

    else if (tempStack[0].vertex1 == 0 && tempStack[0].vertex2 == 0)
        cout << "Empty" << endl;
   
    cout << "\n";
}

//Description: This method helps print the edges in the Circuit stack once the DFS is complete
void Stack::printCircuit()
{
    cout << "The circuit is:" << "\n";

    if(Circuit[0].vertex1 == 0 && Circuit[0].vertex2 == 0)
        cout << "Empty" << "\n";

    for(int i=0; i<size; i++)
    {
        if(Circuit[i].vertex1 != 0 && Circuit[i].vertex2 != 0)
            cout << "(" << Circuit[i].vertex1 << "," << Circuit[i].vertex2 << ")" << "\n";
        else
            break;
    }

    cout << "\n";
}