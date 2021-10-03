#include <iostream>
using namespace std;
#include <limits.h>
#include "include/dijkstra.h"


//DIJAKSTRA DISTANCE ALGORITHM
/* This code is taken from "algodaily.com" in the lesson 'an-illustrated-guide-to-dijkstras-algorithm'. 
The code is originally written in python. It has been modified to run in C++.
*/


void dijkstra(int* shortest_distance, node_info* graph, int num_nodes, int src_node)
{
  int checked_nodes = 0;
  int min_node;

  //initialize the shortest distance array
  for(int nodes = 0; nodes < num_nodes; nodes++)
  {
      shortest_distance[nodes] = INF_DIST;
  }
  shortest_distance[src_node] = 0;

  while(checked_nodes < num_nodes)
  {
      min_node = UNDEFINED_NODE;
      
      //Determine which not to start from here
      for(int current_node = 0; current_node < num_nodes; current_node++)
      {
          if(graph[current_node].current_index == IGNORE_NODE)
          {
              continue;
          }
          else if(min_node == UNDEFINED_NODE)
          {
              min_node = current_node;
          }
          else if(shortest_distance[min_node] > shortest_distance[current_node])
          {
              min_node = current_node;
          }
      }

      //check each connection node
      for(int i = 0; i < 3; i++)
      {
          if(graph[min_node].next_node[i].index == NO_CONNECTION)
          {
              continue;
          }

          //check if distance to this node is shorter than existing distance
          else if((graph[min_node].next_node[i].distance + shortest_distance[min_node])\
          < shortest_distance[graph[min_node].next_node[i].index])
          {
              //update the distance with this new shorter distance
              shortest_distance[graph[min_node].next_node[i].index] = \
                  graph[min_node].next_node[i].distance + shortest_distance[min_node];
          }
      }
      checked_nodes++;
      graph[min_node].current_index = IGNORE_NODE;
  }
}