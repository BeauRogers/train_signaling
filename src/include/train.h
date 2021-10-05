#include <iostream>
using namespace std;
#include <limits.h>
#include "rail_pieces.h"

// #define PRINT_MAPS
#undef PRINT_MAPS
// #define INDICATE_WAITS
#undef INDICATE_WAITS

class Train
{
  public:
    Train(node_info* map_arg, int num_stops_arg, next_node stop0_arg, 
          next_node stop1_arg, std::string name_arg);

    /*Determine shortest distance to each stop and determine the first stop 
    Return true is destination can be reached. False otherwise
    */
    bool determine_route(int dest_stop_arg, node_info* global_map);

    /*move train to next track segment. 
    Return true is destination reached. False otherwise
    */
    bool move_train(node_info* global_map);
    
    void display_train_position(void);

    bool is_train_waiting(void);
    node_info* get_local_map(void);
    int* get_stop_order(void);
    int* get_stop_order_distance(void);
    std::string get_train_name(void);
    next_node get_position(void);

    private:
      node_info map[NUM_NODES + 1]; 
      int num_stops;
      bool waiting;
      int stop_order[2][NUM_NODES+1];
      std::string train_name; 

      //Indexes based on stop_order
      int dest_index;
      int completed_index;
      int next_index;
      int dist_to_next;
      int dist_from_completed;

      /*
      Determine how many stops to destination and next stop 
      Return true is destination can be reached. False otherwise
      */
      bool initialize_travel_to_dest(int dest_stop_arg, node_info* global_map);

      /*
      Set the next stop to a closed state to ensure no other trains can
      move to that stop. Open up the current stop again since the train will
      be leaving from there
      */
      void close_next_open_last_stop(node_info* global_map, int current_index, int next_index);

      /*
      Recursive function to determine the next index that will be the 
      shortest path to the destination based on the stop_order[][] array
      found in determine_route(). This function assumes destination is reachable
      */
      int determine_next_index(int root_index, int last_index, int dist_travelled);
};