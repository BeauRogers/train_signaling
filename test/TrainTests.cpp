#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gtest/gtest_pred_impl.h"
#include "../src/include/merge_sort.h"
#include "../src/include/dijkstra.h"
#include "../src/include/train.h"

#define TEST_MAP_SIZE 6

//We'll use a map for testing purposes
const node_info test_map[TEST_MAP_SIZE] = 
    {
        {
            .current_index = 0,
            .stop_closed = false,
            .next_node[0].distance = 5, 
            .next_node[0].index = 1,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 1, 
            .stop_closed = false,
            .next_node[0].distance = 4, 
            .next_node[0].index = 2,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 2, 
            .stop_closed = false,
            .next_node[0].distance = 4, 
            .next_node[0].index = 1,
            .next_node[1].distance = 5, 
            .next_node[1].index = 3,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 3, 
            .stop_closed = false,
            .next_node[0].distance = 3, 
            .next_node[0].index = 4,
            .next_node[1].distance = 2, 
            .next_node[1].index = 5,
            .next_node[2].distance = 5, 
            .next_node[2].index = 2,
        },
        {
            .current_index = 4, 
            .stop_closed = false,
            .next_node[0].distance = 3, 
            .next_node[0].index = 3,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        },
        {
            .current_index = 5, 
            .stop_closed = false,
            .next_node[0].distance = 2, 
            .next_node[0].index = 3,
            .next_node[1].distance = INF_DIST, 
            .next_node[1].index = NO_CONNECTION,
            .next_node[2].distance = INF_DIST, 
            .next_node[2].index = NO_CONNECTION,
        }
    };


bool compare_array(int* array1, int* array2, int size_array)
{
    for (int i = 0; i < size_array; ++i){
        if (array1[i] != array2[i]){
            return false;
        }
    }

    return true;
}

bool compare_map(node_info* map1, node_info* map2, int size_map)
{
    for (int i = 0; i < size_map; ++i){
        if ((map1[i].current_index != map2[i].current_index) ||
        (map1[i].stop_closed != map2[i].stop_closed)){
            return false;
        }
        for(int j=0; j<3; j++)
        {
            if ((map1[i].next_node[j].distance != map2[i].next_node[j].distance) ||
                (map1[i].next_node[j].index != map2[i].next_node[j].index)){
                    return false;
        }
        }
    }

    return true;
}

TEST(MergeTesting, mergeSort_algorithm)
{
    int input_index_array[4] = {1, 2, 3, 4};
    int input_value_array[4] = {10, 9, 11, 8};
    int exp_index_array[4] = {4, 2, 1, 3};
    int exp_value_array[4] = {8, 9, 10, 11};

    mergeSort(input_index_array, input_value_array, 0, 3);

    EXPECT_TRUE(compare_array(input_index_array, exp_index_array, 
                    sizeof(exp_index_array)/sizeof(int))) << "indexes incorrectly sorted";
    
    EXPECT_TRUE(compare_array(input_value_array, exp_value_array, 
                    sizeof(exp_value_array)/sizeof(int))) << "value incorrectly sorted";
}

TEST(dijkstra, dijkstra_algorithm)
{
    node_info dijkstra_map[TEST_MAP_SIZE];
    memcpy(dijkstra_map, test_map, sizeof(test_map));

    int input_distance_array[TEST_MAP_SIZE];
    int expected_distance_array[TEST_MAP_SIZE] = {0, 5, 9, 14, 17, 16};

    
    dijkstra(input_distance_array, dijkstra_map, TEST_MAP_SIZE, 0);

    EXPECT_TRUE(compare_array(input_distance_array, expected_distance_array, 
                    TEST_MAP_SIZE)) << "dijkstra algorithm error" << endl \
                    << input_distance_array[0] << " " << input_distance_array[1] << " " \
                    << input_distance_array[2] << " " << input_distance_array[3]<< " " \
                    << input_distance_array[4] << " " << input_distance_array[5];
}

TEST(train_object, constructor)
{
    node_info constructor_map[TEST_MAP_SIZE];
    memcpy(constructor_map, test_map, sizeof(test_map));

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 0},
        .next_node[1] = {2, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(constructor_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    EXPECT_TRUE(compare_map(constructor_map, test_train.get_local_map(), 
                    TEST_MAP_SIZE)) << "local map does not match";
    
    EXPECT_TRUE(compare_map(&train_node, &test_train.get_local_map()[TEST_MAP_SIZE], 1))\
        << "Train position does not match";
    
    EXPECT_TRUE(test_train.get_train_name() == "test_train") << "train name is " \
            << test_train.get_train_name();
}

TEST(train_object, route_valid)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    int expected_stop_order[TEST_MAP_SIZE+1] = {6, 1, 2, 3, 5, 4, 0};
    int expected_dist_order[TEST_MAP_SIZE+1] = {0, 1, 2, 7, 9, 10, INF_DIST};
    int* stop_order;
    int* dist_order;

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 2},
        .next_node[1] = {1, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    EXPECT_TRUE(test_train.determine_route(4, route_map)) << "route_valid failure";

    stop_order = test_train.get_stop_order();
    dist_order = test_train.get_stop_order_distance();

    EXPECT_TRUE(
        (compare_array(stop_order, expected_stop_order, TEST_MAP_SIZE+1)) && \
        (compare_array(dist_order, expected_dist_order, TEST_MAP_SIZE)) && \
        (dist_order[TEST_MAP_SIZE]>=INF_DIST)
        ) << " stop: " << stop_order[0] << " dist: " << dist_order[0] \
        << " stop: " << stop_order[1] << " dist: " << dist_order[1] \
        << " stop: " << stop_order[2] << " dist: " << dist_order[2] \
        << " stop: " << stop_order[3] << " dist: " << dist_order[3] \
        << " stop: " << stop_order[4] << " dist: " << dist_order[4] \
        << " stop: " << stop_order[5] << " dist: " << dist_order[5] \
        << " stop: " << stop_order[6] << " dist: " << dist_order[6];
}

TEST(train_object, route_invalid)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 2},
        .next_node[1] = {1, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    EXPECT_FALSE(test_train.determine_route(0, route_map)) << "route_invalid failure";
}

TEST(train_object, move_one_segment)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    next_node first_position;
    next_node second_position;

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 2},
        .next_node[1] = {1, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    test_train.determine_route(4, route_map);
   
    first_position = test_train.get_position();
    test_train.move_train(route_map);
    second_position = test_train.get_position();

    //check position and if train is waiting
    EXPECT_TRUE(first_position.index == second_position.index);
    EXPECT_TRUE(first_position.distance == (second_position.distance+1));
    EXPECT_FALSE(test_train.is_train_waiting());
}

TEST(train_object, waiting_for_train)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    next_node first_position;
    next_node second_position;

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 2},
        .next_node[1] = {2, 3},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train1(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train1");

    train_node.next_node[0] = {1, 4};
    train_node.next_node[1] = {1, 3};

    Train test_train2(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train2");


    EXPECT_TRUE(test_train1.determine_route(5, route_map));
    EXPECT_TRUE(test_train2.determine_route(5, route_map));

    EXPECT_FALSE(test_train1.is_train_waiting()) << "train 1 supposed to be waiting";
    EXPECT_TRUE(test_train2.is_train_waiting()) << "train 2 supposed to be waiting";
    EXPECT_TRUE(route_map[3].stop_closed) << "expected stop 3 to be closed";

    //check if train 1 moving and train 2 isn't
    first_position = test_train1.get_position();
    test_train1.move_train(route_map);
    second_position = test_train1.get_position();
    EXPECT_TRUE(first_position.index == second_position.index);
    EXPECT_TRUE(first_position.distance == (second_position.distance+1)) << "train 1 not moving";

    first_position = test_train2.get_position();
    test_train2.move_train(route_map);
    second_position = test_train2.get_position();
    EXPECT_TRUE(first_position.index == second_position.index) << "train 2 moving";
    EXPECT_TRUE(first_position.distance == (second_position.distance)) << "train 2 moving";
}

TEST(train_object, changing_stations)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    int expected_stop_order[TEST_MAP_SIZE+1] = {6, 1, 2, 3, 5, 4, 0};
    int expected_dist_order[TEST_MAP_SIZE+1] = {0, 1, 2, 7, 9, 10, INF_DIST};

    next_node first_position;
    next_node second_position;

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {2, 2},
        .next_node[1] = {1, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    test_train.determine_route(3, route_map);
   
    first_position = test_train.get_position();
    test_train.move_train(route_map);
    test_train.move_train(route_map);
    second_position = test_train.get_position();

    //check position and if train is waiting
    EXPECT_TRUE(first_position.index == 2) << "first stop is " << first_position.index;
    EXPECT_TRUE(second_position.index == 3) << "second stop is " << second_position.index;
    EXPECT_TRUE(first_position.distance == 2) << "first distance is " << first_position.distance;
    EXPECT_TRUE(second_position.distance == 5) << "second distance is " << second_position.distance;
}

TEST(train_object, destination_reached)
{
    node_info route_map[TEST_MAP_SIZE];
    memcpy(route_map, test_map, sizeof(test_map));

    node_info train_node = 
    {
        .current_index = TEST_MAP_SIZE,
        .stop_closed = false,
        .next_node[0] = {1, 2},
        .next_node[1] = {2, 1},
        .next_node[2] = {INF_DIST, NO_CONNECTION}
    };

    Train test_train(route_map, TEST_MAP_SIZE, train_node.next_node[0], 
          train_node.next_node[1], "test_train");

    test_train.determine_route(2, route_map);

    EXPECT_TRUE(route_map[2].stop_closed);
    EXPECT_TRUE(test_train.move_train(route_map)) << "Expected to reach destination";
    EXPECT_FALSE(route_map[2].stop_closed);
}