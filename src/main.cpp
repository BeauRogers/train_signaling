// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
using namespace std;
#include <limits.h>
#include "include/dijkstra.h"
#include "include/merge_sort.h"

// #define PRINT_MAPS
#undef PRINT_MAPS
// #define INDICATE_WAITS
#undef INDICATE_WAITS

//Train Object
class Train
{
  public:
    Train(node_info* map_arg, int num_stops_arg, next_node stop0_arg, next_node stop1_arg)
    {
      //get map train will use
      memcpy(map, map_arg, NUM_NODES*sizeof(map[0])); 
      num_stops = num_stops_arg;
      //initialize train's starting position
      map[NUM_NODES].current_index = num_stops_arg;
      map[NUM_NODES].next_node[0] = stop0_arg;
      map[NUM_NODES].next_node[1] = stop1_arg;
      map[NUM_NODES].next_node[2].index = NO_CONNECTION;
      map[NUM_NODES].next_node[2].distance = INF_DIST;
      cout << "Constructor called" << endl;
#ifdef PRINT_MAPS
      for (int i = 0; i < (NUM_NODES + 1); i++)
      cout << "Constructed map " << map[i].current_index << endl;
#endif
    }

    bool determine_route(int dest_stop_arg, node_info* global_map)
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

#ifdef PRINT_MAPS
      for (int i = 0; i < (NUM_NODES + 1); i++)
      cout << "Pre-sort" << stop_order[0][i] << "  " << stop_order[1][i] << endl;
#endif
      //sort the stop_order such that a path is shown quickest path to move through all stops
      mergeSort(&stop_order[0][0], &stop_order[1][0], 0, NUM_NODES);

#ifdef PRINT_MAPS
      for (int i = 0; i < (NUM_NODES + 1); i++)
      cout << "After sort" << stop_order[0][i] << "  " << stop_order[1][i] << endl;
#endif

      return initialize_travel_to_dest(dest_stop_arg, global_map);
    }
    bool move_train(node_info* global_map)
    {
      if(completed_index == dest_index)
      {
        return true;
      }
      else if(waiting == true)
      {
        if(global_map[stop_order[0][next_index]].stop_closed == false)
        {
#ifdef INDICATE_WAITS
          cout << "Waitmode cleared for completed index of " << completed_index << endl;
#endif
          close_next_open_last_stop(global_map, completed_index, next_index);
          waiting = false;
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
          global_map[stop_order[0][completed_index]].stop_closed = false;
          return true;
        }

        //determine next stop
        next_index = determine_next_index(completed_index, completed_index, stop_order[1][completed_index]);
        for(int i = 0; i<3; i++)
        {
          if(stop_order[0][next_index] == map[stop_order[0][completed_index]].next_node[i].index)
          {
            dist_to_next = map[stop_order[0][completed_index]].next_node[i].distance;
          }
        }

        //check if we need to wait
        if(global_map[stop_order[0][next_index]].stop_closed == true)
        {
#ifdef INDICATE_WAITS
          cout << "Wait mode set of completed index of " << completed_index << endl;
#endif
          waiting = true;
        }
        else
        {
          close_next_open_last_stop(global_map, completed_index, next_index);
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


      bool initialize_travel_to_dest(int dest_stop_arg, node_info* global_map)
      {
        //get the index of our stop in our sorted stop order list
        for(int i = 0; i<(NUM_NODES + 1); i++)
        {
          if(dest_stop_arg == stop_order[0][i])
          {
            dest_index = i;
          }
        }

        //verify the destination is reachable
        if(stop_order[1][dest_index] >= INF_DIST)
        {
          return false;
        }

        //Last stop of the ordered map
        completed_index = 0;
        next_index = determine_next_index(completed_index, completed_index, stop_order[1][completed_index]);//1;
        //consider adding function to verify next index leads to destination
        for(int i = 0; i<3; i++)
        {
          if(stop_order[0][next_index] == map[stop_order[0][completed_index]].next_node[i].index)
          {
            dist_to_next = map[stop_order[0][completed_index]].next_node[i].distance;
          }
        }
        //check if we need to wait
        if(global_map[stop_order[0][next_index]].stop_closed == true)
        {
          // cout << "Wait mode set for completed index of " << completed_index << endl;
          waiting = true;
        }
        else
        {
#ifdef INDICATE_WAITS
          cout << "Closing connection for " << next_index << endl;
#endif
          close_next_open_last_stop(global_map, completed_index, next_index);
        }
        return true;
      }
      void close_next_open_last_stop(node_info* global_map, int current_index, int next_index)
      {
        //occupy the next stop and de-occupy the current stop
        global_map[stop_order[0][next_index]].stop_closed = true;
        
        if(completed_index != 0)//this stop doesn't exist in global map
        {
          global_map[stop_order[0][completed_index]].stop_closed = false;
        }
      }
      int determine_next_index(int root_index, int last_index, int dist_travelled)
      {
        int next_dist_travelled;
        //loop through possible roots starting from last_index
        for(int stop_index = last_index+1; stop_index<(NUM_NODES+1); stop_index++)
        {
          for(int i = 0; i<3; i++)
          {
            if(map[stop_order[0][last_index]].next_node[i].index == map[stop_order[0][stop_index]].current_index)
            {
              next_dist_travelled = dist_travelled + map[stop_order[0][last_index]].next_node[i].distance;

              if(next_dist_travelled == stop_order[1][stop_index])
              {
                if(stop_index == dest_index)
                {
                  return stop_index;
                }
                //from this index, see if the paths following it are the shortest path that we've already found
                if(determine_next_index(root_index, stop_index, next_dist_travelled) > root_index)
                {
                  return stop_index;
                }
              }
            }
          }
        }
        //If destination not found, return the root_index
        return root_index;
      }
};



// driver program to test above function
int main()
{
  node_info* rail_map = get_rail_map();

  //input train's initial position
  next_node adjacent_train_stops[2] =
  {
    {
      .index = 0,
      .distance = 3
    },
    {
      .index = 1,
      .distance = 1
    }
  };
  Train train1(rail_map, NUM_NODES, adjacent_train_stops[0], adjacent_train_stops[1]);

  adjacent_train_stops[0].index = 1;
  adjacent_train_stops[0].distance = 1;
  adjacent_train_stops[1].index = 2;
  adjacent_train_stops[1].distance = 2;
  Train train2(rail_map, NUM_NODES, adjacent_train_stops[0], adjacent_train_stops[1]);

  if(train1.determine_route(4, rail_map) == false)
  {
    cout << "Train 1 route not valid" << endl;
    return 0;
  }
  if(train2.determine_route(2, rail_map) == false)
  {
    cout << "Train 2 route not valid" << endl;
    return 0;
  }
  while((train1.move_train(rail_map) != true) || (train2.move_train(rail_map) != true));

  return 0;
}

// This code is contributed by shivanisinghss2110
