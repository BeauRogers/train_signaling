// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
using namespace std;
#include <limits.h>


//DIJAKSTRA DISTANCE ALGORITHM

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[])
{
	cout <<"Vertex \t Distance from Source" << endl;
	for (int i = 0; i < V; i++)
		cout << i << " \t\t"<<dist[i]<< endl;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int* dist, int graph[V][V], int src)
{
	//int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	//printSolution(dist);
}

//MERGE SORTING ALGORITHM


// Merge two subarrays L and M into arr
void merge(int indexes[], int arr[], int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2], X[n1], Y[n2];

  for (int i = 0; i < n1; i++)
  {
      L[i] = arr[p + i]; //lower 
      X[i] = indexes[p + i]; //lower
  }
    
  for (int j = 0; j < n2; j++)
  {
    M[j] = arr[q + 1 + j]; //upper
    Y[j] = indexes[q + 1 + j]; //upper
  }

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i]; //lower 
      indexes[k] = X[i];
      i++;
    } else {
      arr[k] = M[j];//upper
      indexes[k] = Y[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i]; //lower
    indexes[k] = X[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j]; //upper
    indexes[k] = Y[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int indexes[], int arr[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(indexes, arr, l, m);
    mergeSort(indexes, arr, m + 1, r);

    // Merge the sorted subarrays
    merge(indexes, arr, l, m, r);
  }
}


//MAIN PROGRAM

// driver program to test above function
int main()
{
    int dist[2][V];
    int src = 0;
	/* Let us create the example graph discussed above */
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    for(int num = 0; num<V; num++)
    {
        dist[0][num] = num;
    }

	dijkstra(&dist[1][0], graph, src);

    int path[V];
    int goal = 2;
    //Let's say we want to get to some node. Let's say node 2, let's 
    //see the path

    for (int i = 0; i < V; i++)
		cout << "Pre-sort" << dist[0][i] << "  " << dist[1][i] << endl;

    mergeSort(&dist[0][0], &dist[1][0], 0, V - 1);

    for (int i = 0; i < V; i++)
		cout << "After sort" << dist[0][i] << "  " << dist[1][i] << endl;
	
    return 0;
}

// This code is contributed by shivanisinghss2110
