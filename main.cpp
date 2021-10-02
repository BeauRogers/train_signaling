// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
using namespace std;
#include <limits.h>


//DIJAKSTRA DISTANCE ALGORITHM
// Taken from "https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/"

// Number of vertices in the graph
#define V 9

typedef struct next_node_t
{
    int distance;
    int index;
}next_node;

typedef struct node_info_t
{
    int current_index;
    int wait_time;
    next_node next_node[3];
}node_info;

#define NUM_NODES 6
#define INF_DIST 65535
#define NO_CONNECTION -1
#define IGNORE_NODE -2
#define UNDEFINED_NODE -3

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
  /*for(int i=0; i< NUM_NODES; i++)
  {
      cout << "Node is " << shortest_distance[0][i] << " distance is " << shortest_distance[1][i] << endl;
  }*/

}


//MERGE SORTING ALGORITHM
//Taken from "https://www.programiz.com/dsa/merge-sort"


// Merge two subarrays L and M into arr
void merge(int indexes[], int arr[], int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2], X[n1], Y[n2];

  for (int i = 0; i < n1; i++)
  {
      L[i] = arr[p + i]; //lower 
      X[i] = indexes[p + i]; //lower
  }
    
  for (int j = 0; j < n2; j++)
  {
    M[j] = arr[q + 1 + j]; //upper
    Y[j] = indexes[q + 1 + j]; //upper
  }

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i]; //lower 
      indexes[k] = X[i];
      i++;
    } else {
      arr[k] = M[j];//upper
      indexes[k] = Y[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i]; //lower
    indexes[k] = X[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j]; //upper
    indexes[k] = Y[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int indexes[], int arr[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(indexes, arr, l, m);
    mergeSort(indexes, arr, m + 1, r);

    // Merge the sorted subarrays
    merge(indexes, arr, l, m, r);
  }
}


//MAIN PROGRAM

class Train
{
  public:
    Train(node_info* map_arg, int num_stops_arg, next_node stop0_arg, next_node stop1_arg)
    {
      memcpy(map, map_arg, NUM_NODES*sizeof(map[0])); 
      num_stops = num_stops_arg;
      //initialize train's starting position
      map[NUM_NODES].current_index = num_stops_arg;
      map[NUM_NODES].next_node[0] = stop0_arg;
      map[NUM_NODES].next_node[1] = stop1_arg;
      map[NUM_NODES].next_node[2].index = NO_CONNECTION;
      map[NUM_NODES].next_node[2].distance = INF_DIST;
      cout << "Constructor called" << endl;
      for (int i = 0; i < (NUM_NODES + 1); i++)
      cout << "Constructed map " << map[i].current_index << endl;
    }

    bool determine_route(int dest_stop_arg)
    {
      node_info temp_map[NUM_NODES + 1];

      //verify we have a valid destination
      if((dest_stop_arg) >= NUM_NODES || (dest_stop_arg < 0))
      {
        return false;
      }

      //Initialize a map that will be be compromised
      memcpy(temp_map, map, sizeof(map));
      //Initilize the stop order from 0 to last node
      memset(stop_order, 0, sizeof(stop_order));
      for(int i = 0; i<(NUM_NODES + 1); i++)
      {
        stop_order[0][i] = i;
      }

      //use dijkstra to determine shortest time to each stop
      dijkstra(&stop_order[1][0], temp_map, NUM_NODES + 1, NUM_NODES);

      // for (int i = 0; i < (NUM_NODES + 1); i++)
      // cout << "Pre-sort" << stop_order[0][i] << "  " << stop_order[1][i] << endl;

      //sort the stop_order such that a path is shown quickest path to move through all stops
      mergeSort(&stop_order[0][0], &stop_order[1][0], 0, NUM_NODES);

      for (int i = 0; i < (NUM_NODES + 1); i++)
      cout << "After sort" << stop_order[0][i] << "  " << stop_order[1][i] << endl;


      initialize_travel_to_dest(dest_stop_arg);
      return true;
    }
    bool move_train()
    {
      if(waiting == true)
      {
        if(map[stop_order[0][next_index]].wait_time == false)
        {
          //occupy the next stop and de-occupy the current stop
          map[stop_order[0][next_index]].wait_time = true;
          //also occupy the rail line you are using
          map[stop_order[0][completed_index]].wait_time = false;
          //free up the rail line you are using
        }
        else
        {
          return false;
        }
      }
      dist_to_next--;
      
      if(dist_to_next == 0)
      {
        completed_index = next_index;
        //check if we're at our destination
        if(completed_index == dest_index)
        {
          cout << "Destination reached" << endl;
          return true;
        }

        //determine next stop
        next_index++;
        for(int i = 0; i<3; i++)
        {
          if(stop_order[0][next_index] == map[stop_order[0][completed_index]].next_node[i].index)
          {
            dist_to_next = map[stop_order[0][completed_index]].next_node[i].distance;
          }
        }

        //check if we need to wait
        if(map[stop_order[0][next_index]].wait_time == true)
        {
          waiting = true;
        }
        else
        {
          //occupy the next stop and de-occupy the current stop
          map[stop_order[0][next_index]].wait_time = true;
          //also occupy the rail line you are using
          map[stop_order[0][completed_index]].wait_time = false;
          //free up the rail line you are using
        }
      }
      return false;
    }
    private:
      node_info map[NUM_NODES + 1]; 
      int num_stops;
      bool waiting;
      int stop_order[2][NUM_NODES+1];

      //Indexes based on stop_order
      int dest_index;
      int completed_index;
      int next_index;
      int dist_to_next;
      int dist_from_completed;


      void initialize_travel_to_dest(int dest_stop_arg)
      {
        for(int i = 0; i<(NUM_NODES + 1); i++)
        {
          if(dest_stop_arg == stop_order[0][i])
          {
            dest_index = i;
          }
        }
        waiting = false;
        //Last stop of the ordered map
        completed_index = 0;
        next_index = 1;
        //consider adding function to verify next index leads to destination
        for(int i = 0; i<3; i++)
        {
          if(stop_order[0][next_index] == map[stop_order[0][completed_index]].next_node[i].index)
          {
            dist_to_next = map[stop_order[0][completed_index]].next_node[i].distance;
          }
        }
      }
};

// driver program to test above function
int main()
{
  int dist[2][NUM_NODES];
  int src = 0;
	
  node_info graph[NUM_NODES] = 
    {
        {
            .current_index = 0, 
            .next_node[0].index = 1,
            .next_node[0].distance = 5, 
            .next_node[1].distance = 2, 
            .next_node[1].index = 2,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 1, 
            .next_node[0].distance = 5, 
            .next_node[0].index = 0,
            .next_node[1].distance = 4, 
            .next_node[1].index = 2,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 2, 
            .next_node[0].distance = 2, 
            .next_node[0].index = 0,
            .next_node[1].distance = 8, 
            .next_node[1].index = 4,
            .next_node[2].distance = 4, 
            .next_node[2].index = 1,
        },
        {
            .current_index = 3, 
            .next_node[0].distance = 6, 
            .next_node[0].index = 4,
            .next_node[1].distance = 4, 
            .next_node[1].index = 5,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 4, 
            .next_node[0].distance = 8, 
            .next_node[0].index = 2,
            .next_node[1].distance = 6, 
            .next_node[1].index = 3,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 5, 
            .next_node[0].distance = 4, 
            .next_node[0].index = 3,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        }
    };

    next_node adjacent_train_stops[2] =
    {
      {
        .index = 0,
        .distance = 1
      },
      {
        .index = 1,
        .distance = 3
      }
    };
    {

    }
    Train train1(graph, NUM_NODES, adjacent_train_stops[0], adjacent_train_stops[1]);

    train1.determine_route(2);
    while(train1.move_train() != true);

  return 0;
}

// This code is contributed by shivanisinghss2110
