#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list_node_{
  // A node struct for storing data required for djikstra's algorithm
  struct linked_list_node_ *next;   // Next Node
  struct linked_list_node_ *prev;   // Previous Node
  int toNode;       // The destination Node ID
  int dist;         // The distance to the destination Node
} LLNode;

typedef struct linked_list_{
  // A binary heap structure that uses 1 based indexing to implement a binary heap
  LLNode *head;       // An array of BinNode pointers of the actual heap
  LLNode *tail;       // Address of the tail of the linked list
  int size;           // Size of the Linked List
  int originID;       // The ID of the origin ID
} LinkedList;

LinkedList* listCreate(int originID);
void listAppend(LinkedList *list, LLNode *node);
LinkedList** NewGraph(FILE *file, int numNodes, int numEdges);
void printLList(LinkedList* lList);
void printGraph(LinkedList** graph, int numNodes);
void freeLList(LinkedList* lList);
void freeGraph(LinkedList** graph, int numNodes);