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