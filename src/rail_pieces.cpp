
#include "include/rail_pieces.h"

node_info map[NUM_NODES] = 
    {
        {
            .current_index = 0,
            .stop_closed = false,
            .next_node[0].index = 1,
            .next_node[0].distance = 5, 
            .next_node[1].distance = 2, 
            .next_node[1].index = 2,
            .next_node[2].distance = 3, 
            .next_node[2].index = 0,
        },
        {
            .current_index = 1, 
            .stop_closed = false,
            .next_node[0].distance = 5, 
            .next_node[0].index = 0,
            .next_node[1].distance = 4, 
            .next_node[1].index = 2,
            .next_node[2].distance = 3, 
            .next_node[2].index = 3,
        },
        {
            .current_index = 2, 
            .stop_closed = false,
            .next_node[0].distance = 2, 
            .next_node[0].index = 0,
            .next_node[1].distance = 8, 
            .next_node[1].index = 4,
            .next_node[2].distance = 4, 
            .next_node[2].index = 1,
        },
        {
            .current_index = 3, 
            .stop_closed = false,
            .next_node[0].distance = 6, 
            .next_node[0].index = 4,
            .next_node[1].distance = 4, 
            .next_node[1].index = 5,
            .next_node[2].distance = 3, 
            .next_node[2].index = 1,
        },
        {
            .current_index = 4, 
            .stop_closed = false,
            .next_node[0].distance = 8, 
            .next_node[0].index = 2,
            .next_node[1].distance = 6, 
            .next_node[1].index = 3,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 5, 
            .stop_closed = false,
            .next_node[0].distance = 4, 
            .next_node[0].index = 3,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
    };



    node_info* get_rail_map(void)
    {
        return map;
    }