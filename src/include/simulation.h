#include "train.h"

bool run_train_simulation(node_info* global_map, Train* trains, int num_trains, int delay_time);

bool verify_valid_routes(Train* trains, int num_trains, int* destinations, node_info* global_map);

void initialize_trains(Train* trains, int num_trains, node_info* global_map, std::string* names, 
    int num_stops, next_node* train_pos);