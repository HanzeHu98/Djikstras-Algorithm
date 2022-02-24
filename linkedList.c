#include "linkedList.h"

LinkedList* listCreate(int originID){
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->originID = originID;
  return list;
}

void listAppend(LinkedList *list, LLNode *node){
  //printf("Running listAppend on list %d with size %d\n", list->originID, list->size);
  if(list->size == 0){
    list->tail = node;
    list->head = node;
    node->next = NULL;
    list->size += 1;
  } else{
    list->tail->next = node;
    node->prev = list->tail;
    node->next = NULL;
    list->tail = node;
    list->size += 1;
  }
}

LinkedList** NewGraph(FILE *file, int numNodes, int numEdges){
  //FILE *file = fopen("graph0.txt", "r");
  int originID, destID, weight;
  LLNode *node;
  
  /* ------------------------------*/
  /*  DATA READING                 */
  /* ------------------------------*/
  //printf("Allocating Memory to Graph\n");
  LinkedList **graph = malloc(sizeof(LinkedList*) * numNodes);
  for(int i = 0; i < numNodes; i++){
    graph[i] = listCreate(i);
  }
  //printf("Memory Allocated to Graph, reading from graph0\n");

  for(int i = 0; i < numEdges; i++){
    // Read the size of the array (first int)
    fscanf(file, "%d", &originID);
    fscanf(file, "%d", &destID);
    fscanf(file, "%d", &weight);
    node = malloc(sizeof(LLNode));
    node->dist = weight;
    node->toNode = destID;
    node->prev = NULL;
    node->next = NULL;
    listAppend(graph[originID], node);
    //printf("Appending Node to %d, with dest %d and dist %d\n", originID, node->toNode, node->dist);
  }
  //printf("Finished reading graph0\n");
  return graph;
}


void printLList(LinkedList* lList){
  LLNode* nextNode = lList->head;
  while (nextNode != NULL){
    printf("From Vertex ID: %d, To Vertex ID: %d, Distance: %d\n", lList->originID, nextNode->toNode, nextNode->dist);
    nextNode = nextNode->next;
  }
}

void printGraph(LinkedList** graph, int numNodes){
  for(int i = 0; i < numNodes; i++){
    printLList(graph[i]);
  }
}

void freeLList(LinkedList* lList){
  LLNode* currNode, *nextNode;
  currNode = lList->head;
  while (currNode != NULL){
    nextNode = currNode->next;
    //printf("freeing on list %d, the node to %d\n", lList->originID, currNode->toNode);
    free(currNode);
    currNode = nextNode;
  }
  free(lList);
}

void freeGraph(LinkedList** graph, int numNodes){
  for(int i = 0; i < numNodes; i++){
    freeLList(graph[i]);
  }
  free(graph);
  graph = NULL;
}

/*
// Main Loop Used for debugging purposes, reading from a small graph0
void main(){
  int numNodes, numEdges;
  LinkedList** graph;
  FILE *file = fopen("graph1.txt", "r");
  fscanf(file, "%d", &numNodes);
  fscanf(file, "%d", &numEdges);
  graph = NewGraph(file, numNodes, numEdges);
  printGraph(graph, numNodes);
  freeGraph(graph, numNodes);
  fclose(file);
}*/