#include <stdio.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0
#define TESTSIZE 20

typedef struct bin_heap_node_{
  // A node struct for storing data required for djikstra's algorithm
  int nodeID;       // The Node ID as an integer
  int dist;         // The total distance from the initial node
  int parentID;     // The parent ID from which this node is visited
  int visited;
  int index;
} BinNode;

typedef struct binary_heap_{
  // A binary heap structure that uses 1 based indexing to implement a binary heap
  BinNode **heap; // An array of BinNode pointers of the actual heap
  int tail;       // A tail that keeps track of the index of the last element
} BinHeap;

BinHeap* BinaryHeap(int heapSize);
BinNode *copyNode(BinNode* node);
int compareNode(BinNode* node1, BinNode* node2);
void adjustNodeUp(BinHeap* binHeap, int nodeIndex);
void swapIndex(BinNode* node1, BinNode* node2);
void percolateUp(BinHeap* binHeap);
void printHeap(BinHeap* binHeap);
void printOutput(BinHeap* binHeap);
void percolateDown(BinHeap* binHeap);
void insertHeap(BinHeap *binHeap, BinNode *node);
void insertIfLarger(BinHeap *binHeap, BinNode *node);
BinNode* findMin(BinHeap *binHeap);
BinNode* delMin(BinHeap* binHeap);
int isEmpty(BinHeap* binHeap);
int size(BinHeap* binHeap);
void freeHeap(BinHeap* binHeap);
int compareBinNode(const void* node1, const void* node2);