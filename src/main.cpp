// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
using namespace std;
#include <limits.h>
#include <chrono>
#include <thread>
#include "include/train.h"

// #define PRINT_MAPS
#undef PRINT_MAPS
// #define INDICATE_WAITS
#undef INDICATE_WAITS

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

  Train train1(rail_map, NUM_NODES, adjacent_train_stops[0], 
              adjacent_train_stops[1], "Train A");

  adjacent_train_stops[0].index = 1;
  adjacent_train_stops[0].distance = 1;
  adjacent_train_stops[1].index = 2;
  adjacent_train_stops[1].distance = 2;
  Train train2(rail_map, NUM_NODES, adjacent_train_stops[0], 
              adjacent_train_stops[1], "Train B");

  if(train1.determine_route(2, rail_map) == false)
  {
    cout << "Train 1 route not valid" << endl;
    return 0;
  }
  if(train2.determine_route(2, rail_map) == false)
  {
    cout << "Train 2 route not valid" << endl;
    return 0;
  }
  while(1)
  {
    if((train1.move_train(rail_map) & train2.move_train(rail_map)) == true)
    {
      train1.display_train_position();
      train2.display_train_position();
      break;
    }
    train1.display_train_position();
    train2.display_train_position();
    cout << endl;
    if(train1.train_is_waiting() && train2.train_is_waiting())
    {
      cout << "Trains in gridlock" << endl;
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}