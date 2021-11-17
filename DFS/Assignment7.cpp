// Assignment #7
// Name: Uday Yalamanchili
// ASU Email Address: uyalaman@asu.edu
// Description: This program takes a file "graph.txt" with the graph information needed to build an undirected graph 
//              as input. The first line in the file has the information about the number of nodes and edges. 
//              The subsequent lines have the edge information like the nodes and the weight for each edge. 
//              It constructs an undirected graph using this information and performs depth first search. 
//              It prints out the final graph generated as well as the circuit generated after DFS.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
   {
       // local variables, can be accessed anywhere from the main method
       string inputInfo;
       int nodes, edges;
       int node1, node2, weight;
       int count = 0;

       ifstream file;
       file.open("graph.txt");
       file >> nodes >> edges; // get the number of nodes, edges information from the first line

       // Instantiate a Adjacency List object
       AdjacencyList * list = new AdjacencyList(nodes, edges);

       if (file.is_open())
       {
        while (count < edges)
        {
          file >> node1 >> node2 >> weight; // get the edge information (nodes, weight)
          if (node1 != 0 || node2 != 0 || weight != 0)
          {
            list -> makeEdge(node1, node2, weight); // add an edge from node1 to node2 with the given weight
            list -> makeEdge(node2, node1, weight); // add an edge from node2 to node1 with the given weight as it is an undirected graph
            count++;
          }     
        }
       }
       file.close();

       list -> printGraph(); // print the final graph
       cout << "Computing its circuit ....." << endl;
       cout << "\n";
       list -> DFS(); // perform depth first search
       
      return 0;
   }
