#include <iostream>
using namespace std;
#include <limits.h>
#include <chrono>
#include <thread>
#include "include/train.h"
#include "include/simulation.h"

// driver program to test above function
int main()
{
  node_info* rail_map = get_rail_map();
  bool valid_route;

  //input train's initial position
  next_node adjacent_train_stops[4] =
  {
    { .index = 0, .distance = 3},
    { .index = 1, .distance = 1},
    { .index = 1, .distance = 1},
    { .index = 2, .distance = 3}
  };
  int destinations[2] = {5, 5};
  std:string train_names[2] = {"Train A", "Train B"};

  Train* train_list = (Train*)malloc(sizeof(Train) * 2);

  initialize_trains(train_list, 2, rail_map, train_names, NUM_NODES, adjacent_train_stops);

  valid_route = verify_valid_routes(train_list, 2, destinations, rail_map);
  while(valid_route)
  {
    if(run_train_simulation(rail_map, train_list, 2, 1500) == true)
    {
      break;
    }
  }
  return 0;
}