#include <iostream>
using namespace std;
#include <limits.h>

#ifndef RAIL_PIECES
#define RAIL_PIECES

#define NUM_NODES 7
#define INF_DIST 65535
#define NO_CONNECTION -1
#define IGNORE_NODE -2
#define UNDEFINED_NODE -3

typedef struct next_node_t
{
    int distance;
    int index;
}next_node;

typedef struct node_info_t
{
    int current_index;
    bool stop_closed;
    next_node next_node[3];
}node_info;


node_info* get_rail_map(void);

#endif
