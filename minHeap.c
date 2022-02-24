#include "minHeap.h"

BinHeap* BinaryHeap(int heapSize){
  //creates a new, empty, binary heap.
  BinHeap *output;
  output = malloc(sizeof(BinHeap));
  output->heap = malloc(sizeof(BinNode*) * (heapSize + 1));
  output->tail = 0;                      // Use 1 based array Indexing
  return output;
}

BinNode *copyNode(BinNode* node){
  BinNode *output = malloc(sizeof(BinNode));
  output->dist = node->dist;
  output->index = node->index;
  output->nodeID = node->nodeID;
  output->parentID = node->parentID;
  output->visited = node->visited;
  return output;
}

int compareNode(BinNode* node1, BinNode* node2){
  // A simple Node comparison between two nodes that returns true
  // only if node1 is greater than node2 (so node2 need to percolate up)
  if(node1->dist > node2->dist)
    return TRUE;
  return FALSE;
}

void adjustNodeUp(BinHeap* binHeap, int nodeIndex){
  int index = nodeIndex;
  BinNode *temp;
  while (index/2 > 0){
    if (compareNode(binHeap->heap[index/2], binHeap->heap[index])) {
      temp = binHeap->heap[index/2];
      binHeap->heap[index/2] = binHeap->heap[index];
      binHeap->heap[index] = temp;
      swapIndex(binHeap->heap[index/2], binHeap->heap[index]);
      index /= 2;
    } else{
      break;
    }
  }
}

void swapIndex(BinNode* node1, BinNode* node2){
  int tempIndex;
  tempIndex = node1->index;
  node1->index = node2->index;
  node2->index = tempIndex;
}

void percolateUp(BinHeap* binHeap){
  int index = size(binHeap);
  BinNode *temp;
  while (index/2 > 0){
    if (compareNode(binHeap->heap[index/2], binHeap->heap[index])) {
      temp = binHeap->heap[index/2];
      binHeap->heap[index/2] = binHeap->heap[index];
      binHeap->heap[index] = temp;
      swapIndex(binHeap->heap[index/2], binHeap->heap[index]);
      index /= 2;
    } else{
      break;
    }
  }
}

void percolateDown(BinHeap* binHeap){
  int index = 1;
  BinNode *temp;
  while (index * 2 <= size(binHeap)){
    // If there are 2 children
    // Find the min child of the node
    if (index * 2 + 1 <= size(binHeap)){
      if(compareNode(binHeap->heap[index * 2], binHeap->heap[index * 2 + 1])){
        // If left child is greater, then right child is less
        if (compareNode(binHeap->heap[index], binHeap->heap[index*2 + 1])) {
          temp = binHeap->heap[index*2 + 1];
          binHeap->heap[index*2 + 1] = binHeap->heap[index];
          binHeap->heap[index] = temp;
          swapIndex(binHeap->heap[index*2+1], binHeap->heap[index]);
          index = index * 2 + 1;
        } else
          break;
      } else{
        // Otherwise left child is the min child
        if (compareNode(binHeap->heap[index], binHeap->heap[index*2])) {
          temp = binHeap->heap[index*2];
          binHeap->heap[index*2] = binHeap->heap[index];
          binHeap->heap[index] = temp;
          swapIndex(binHeap->heap[index*2], binHeap->heap[index]);
          index *= 2;
        } else
          break;
      }
    } else {
      // If there is only 1 child, then only compare the left child node
      if (compareNode(binHeap->heap[index], binHeap->heap[index*2])) {
        temp = binHeap->heap[index*2];
        binHeap->heap[index*2] = binHeap->heap[index];
        binHeap->heap[index] = temp;
        swapIndex(binHeap->heap[index*2], binHeap->heap[index]);
        index *= 2;
      } else
        break;
    }
  }
}

void insertHeap(BinHeap *binHeap, BinNode *node){
  // adds a new item to the heap.
  binHeap->heap[size(binHeap) + 1] = node;
  binHeap->tail += 1;
  node->index = size(binHeap);
  percolateUp(binHeap);
}

void insertIfLarger(BinHeap *binHeap, BinNode *node){
  // insert the node into a heap if it is larger than the smallest value
  // As to keep a min heap of all the largest nodes
  if(compareNode(node, findMin(binHeap))){
    free(delMin(binHeap));
    insertHeap(binHeap, copyNode(node));
  }
}


BinNode* findMin(BinHeap *binHeap){
  // returns the item with the minimum key value, leaving item in the heap.
  if (size(binHeap) > 0){
    return binHeap->heap[1];
  }
  return NULL;
}

BinNode* delMin(BinHeap* binHeap){
  // returns the item with the minimum key value, removing the item from the heap.
  if (size(binHeap) < 1)
    return NULL;
  BinNode *node = binHeap->heap[1];
  binHeap->heap[1] = binHeap->heap[size(binHeap)];
  binHeap->heap[1] -> index = 1;
  binHeap->heap[size(binHeap)] = NULL;
  binHeap->tail -= 1;
  percolateDown(binHeap);
  return node;
}

int isEmpty(BinHeap* binHeap){
  // returns true if the heap is empty, false otherwise.
  if(size(binHeap) > 0)
    return FALSE;
  return TRUE;
}

int size(BinHeap* binHeap){
  // returns the number of items in the heap.
  return binHeap->tail;
}

void freeHeap(BinHeap* binHeap){
  // free all nodes still in the heap, and then free the heap itself
  for(int i = 1; i <= size(binHeap); i++){
    free(binHeap->heap[i]);
  }
  free(binHeap->heap);
  binHeap->heap = NULL;
} 

void printHeap(BinHeap* binHeap){
  // prints the array of the BinHeap for debugging purposes
  printf("HeapIndex: ");
  for(int i = 1; i <= size(binHeap); i++){
    printf("%.3d ", binHeap->heap[i]->index);
  }
  printf("\nNodeID   : ");
  for(int i = 1; i <= size(binHeap); i++){
    printf("%.3d ", binHeap->heap[i]->nodeID);
  }
  printf("\nDistance : ");
  for(int i = 1; i <= size(binHeap); i++){
    printf("%.3d ", binHeap->heap[i]->dist);
  }
  printf("\n");
}

void printOutput(BinHeap* binHeap){
  // prints the array of the BinHeap for debugging purposes
  for(int i = 1; i <= size(binHeap); i++){
    BinNode *node = binHeap->heap[i];
    printf("From ID: %d To ID: %d requires %d steps\n", node->parentID, node->nodeID, node->dist);
  }
}


int compareBinNode(const void* node1, const void* node2){
  BinNode *arg1 = *(BinNode**)node1;
  BinNode *arg2 = *(BinNode**)node2;
  //printf("left: %d right: %d",arg1->dist,arg2->dist);
  if(arg1->index < 0 && arg2->index < 0) return 0;
  if(arg1->index < 0) return 1;
  if(arg2->index < 0) return -1;
  
  return arg2->dist - arg1->dist;
}

/*
// Main Program for testing minHeap implementation
void main(int argc, char** argv) {
  BinHeap* heap = BinaryHeap(TESTSIZE);
  BinNode* node;
  int intArray[TESTSIZE] = {47, 17, 64, 56, 90, 59, 58, 94, 33, 3, 83, 36, 10, 7, 12, 39, 9, 74, 100, 53};
  for(int i = 0; i < TESTSIZE; i++){
    node = malloc(sizeof(BinNode));
    node->dist = intArray[i];
    node->nodeID = i+1;
    node->index = i+1;
    insertHeap(heap, node);
    
    //section for testing out qsort functionality
    //heap->heap[i+1] = node;
    //heap->tail += 1;
    //
    printHeap(heap);
  }
  // Section for testing adjust node functionality
  heap->heap[10] = 10;
  adjustNodeUp(heap, 10);
  // testing qsort
  qsort((heap->heap+1), TESTSIZE, sizeof(BinNode*), compareBinNode);
  printHeap(heap);
  // Node size -5 here to test freeHeap function of freeing remaining node
  for(int i = 0; i < TESTSIZE - 5; i ++){
    node = delMin(heap);
    printf("Removed Node Id: %d with distance %d\n", node->nodeID, node->dist);
    free(node);
  }
  printHeap(heap);
  freeHeap(heap);
  printf("Program Finished\n");
}
*/