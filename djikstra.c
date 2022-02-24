#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>
#include "linkedList.h"
#include "minHeap.h"
#include "timer.h"

#define OutputSize 10

BinHeap *djikstra(int rootID, LinkedList** graph, int numNodes){
  /* Takes a graph and a starting ID and knowing the number of nodes in the graph 
   * Calculates the shortest distance to all the nodes in the graph from the
   * starting ID and return a minHeap of size OutputSize of the longest
   * paths from this starting ID
   */

  BinNode **nodeArray = malloc(numNodes * sizeof(BinNode*));
  BinHeap *heap = BinaryHeap(numNodes);
  BinHeap *output = BinaryHeap(OutputSize);
  BinNode *node, *prevNode;
  LLNode  *nextLLNode;

  // Define a BinNode for every node in an array for easy access
  for (int i = 0; i < numNodes; i++){
    node = malloc(sizeof(BinNode));
    node->dist = INT_MAX;
    node->nodeID = i;
    node->visited = FALSE;
    node->parentID = rootID;
    node->index = -1;
    nodeArray[i] = node;
  }
  
  for (int i = 0; i < OutputSize; i++){
    node = malloc(sizeof(BinNode));
    node->dist = -1;
    node->nodeID = -1;
    node->visited = FALSE;
    node->index = i+1;
    node->parentID = rootID;
    output->heap[i+1] = node;
    output->tail += 1;
  }

  prevNode = nodeArray[rootID];
  prevNode->dist = 0;
  while(prevNode != NULL){
    // If the node has not been visited
    if(!prevNode->visited){
      // Iterate through all of its destinations
      nextLLNode = graph[prevNode->nodeID]->head;
      while(nextLLNode != NULL){
        node = nodeArray[nextLLNode->toNode];
        // Check if the node has already been visited/ worked on
        if(!node->visited){
          // If The distance is less, update distance and insert into node
          if(node->dist > prevNode->dist + nextLLNode->dist){
            node->dist = prevNode->dist + nextLLNode->dist;
            node->parentID = prevNode->nodeID;
            if(node->index < 0)
              insertHeap(heap, node);
            else
              adjustNodeUp(heap, node->index);
          }
        }
        nextLLNode = nextLLNode->next;
      }
      // Mark the node as visited
      prevNode->visited = TRUE;
      
      // Inserting into outputHeap if it is larger than the smallest node
      insertIfLarger(output, prevNode);
    }
    prevNode = delMin(heap);
  }

  /*
  array implementation
  qsort(nodeArray, numNodes, sizeof(BinNode*), compareBinNode);
  for (int i = OutputSize; i < numNodes; i++){
    free(nodeArray[i]);
  }
  realloc(nodeArray, OutputSize * sizeof(BinNode*));
  */

  for (int i = 0; i < numNodes; i++){
    free(nodeArray[i]);
  }
  free(nodeArray);
  freeHeap(heap);
  free(heap);
  return output;
}

void main(int argc, char** argv){
  int numNodes, numEdges;
  int threadNum = 16;
  LinkedList** graph;

  if (argc > 1)
    threadNum  = atoi(argv[1]);

  /* ------------------------------*/
  /*  Data Reading Phase           */
  /* ------------------------------*/
  FILE *file = fopen("graph1.txt", "r");
  fscanf(file, "%d", &numNodes);
  fscanf(file, "%d", &numEdges);
  graph = NewGraph(file, numNodes, numEdges);
  fclose(file);
  //printf("Graph Read\n");

  /* ------------------------------*/
  /*  Main Loop Execution          */
  /* ------------------------------*/
  BinNode **output = malloc(sizeof(BinNode*) * OutputSize * numNodes);
  StartTimer();
  #pragma omp parallel for num_threads(threadNum) schedule(dynamic, 2)
    for(int i = 0; i < numNodes; i++){
      BinHeap *received = djikstra(i, graph, numNodes);
      //BinNode **received = djikstra(i, graph, numNodes);
      for(int j = 0; j < OutputSize; j ++){
        // Array Implementation
        //received->heap[j]->parentID = i;
        //output[i*OutputSize + j] = received->heap[j+1];
        output[i*OutputSize + j] = received->heap[j+1];
        output[i*OutputSize + j]->parentID = i;
      }
      free(received->heap);
      free(received);
      // Array Implementation
      // free(received);
    }
  
  double timer = GetTimer()/1000.0;
  printf("Time Taken: %lf \n", timer);

  // Sort the whole output Array and output the 10 longest
  qsort(output, numNodes*OutputSize, sizeof(BinNode*), compareBinNode);
  for (int i = 0; i < OutputSize; i++){
    printf("start Vertex %d, end vertex %d, distance %d\n", output[i]->parentID, output[i]->nodeID, output[i]->dist);
  }


  /* ------------------------------*/
  /*  Memory Deallocation          */
  /* ------------------------------*/
  for (int i = 0; i < numNodes * OutputSize; i++){
    free(output[i]);
  }
  free(output);
  
  /* Array Implementation
  for(int i = 0; i < OutputSize * numNodes; i++){
    free(output[i]);
  }
  free(output);
  */
  freeGraph(graph, numNodes);
  
}