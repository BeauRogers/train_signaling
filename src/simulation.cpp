#include <iostream>
using namespace std;
#include <limits.h>
#include <chrono>
#include <thread>
#include "include/train.h"
#include "include/simulation.h"


void initialize_trains(Train* trains, int num_trains, node_info* global_map, std::string* names, 
    int num_stops, next_node* train_pos)
{
    for(int i=0; i<num_trains; i++)
    {
        trains[i] = Train(global_map, num_stops, train_pos[2*i], 
              train_pos[(2*i) + 1], names[i]);
    }
}

bool verify_valid_routes(Train* trains, int num_trains, int* destinations, node_info* global_map)
{
    for(int i = 0; i<num_trains; i++)
    {
        if(trains[i].determine_route(destinations[i], global_map) == false)
        {
            return false;
        }
    }
    return true;
}

bool run_train_simulation(node_info* global_map, Train* trains, int num_trains, int delay_time)
{
    bool destination_reached = true;
    bool trains_in_gridlock = true;
    for(int i = 0; i<num_trains; i++)
    {
        destination_reached = destination_reached && trains[i].move_train(global_map);
    }
    if(destination_reached == true)
    {
        for(int i = 0; i<num_trains; i++)
        {
            trains[i].display_train_position();
        }
        return true;
    }
    for(int i = 0; i<num_trains; i++)
    {
        trains[i].display_train_position();
    }
    cout << endl;
    for(int i = 0; i<num_trains; i++)
    {
        trains_in_gridlock = trains_in_gridlock && trains[i].is_train_waiting();
    }
    if(trains_in_gridlock == true)
    {
      cout << "Trains in gridlock" << endl;
      return true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));

    return false;
}