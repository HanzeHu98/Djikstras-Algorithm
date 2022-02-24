# Djikstra's Shortest Path Algorithm Implemented in C
**Name**: Hanze HU

## Description
An improved version of the Djikstra's algorithm from the [version implemented in 2018](https://github.com/HanzeHu98/ShortestPathAlgorithm), now accepts a much wider range graphical inputs and can run on a much larger graph with A multi-threaded program.<br>
A C program that solves the all source shortest path problem by applying Dijkstra n = |V| times –– that is, once for each vertex in the input graph G. To speed up execution of the large graph, the code is parallelize using OpenMP. Rather than saving all of the path data, output only the 10 longest paths in a file with format:

start vertex 1, end vertex 1, distance 1<br>
start vertex 2, end vertex 2, distance 2<br>
...<br>
...<br>
start vertex 10, end vertex 10, distance 10

## Input 
A text file such as graph0 and graph1, where the first two integers represents the number of nodes in the graph and the number of edges in the graph respectively. Then, list all the edges in the graph in `from   to   distance` format.<br>
E.g.<br>
num_nodes    num_edges <br>
edge_1_from  edge_1_to  edge_1_distance<br>
edge_2_from  edge_2_to  edge_2_distance<br>
...<br>
...<br>

## Compiling and running
#### Djikstra Algorithm
`make djiksstra` and then `./djikstra THREADNUM` <br/>
THREADNUM specifies the number of threads to use for OpenMP execution, 16 by default <br/>
Global Variable in djikstra.c `OutputSize` can be changed to fit number of outputs required (10 by default), but cannot exceed number of nodes.

#### Clean
`make clean` to remove all object files and executable files

## Correctness
#### Min Heap
The minHeap was tested on a much smaller input of 20 items, with the main program used commented out at the bottem of minHeap.c
#### Graph as Linked List
The linked list implementation of a graph is tested on a much smaller graph called graph0, with 8 nodes and 17 edges. The main program used to test this is also commented out at the bottom of linkedList.c
#### Djikstra
The Djikstra's algorithm was tested on a much smaller graph graph0 to ensure correctness (compared to results from calculating shortest path by hand), and then running on graph1 and graph2 and comparing results with peer's outputs to ensure that the correct 10 nodes were produced.

## Speed
The algorithm is extremely slow when running on large graphs such as graph2 and this is the nature of the Djikstra;s Algorithm (and most algorithms on graphs). <br/>
Several changes were proposed and tried to make this algorithm more efficient:
1. A MinHeap was used as the output format of a single Djikstra Run, as it is determined that keeping a small minHeap (OutputSize = 10) is more efficient than performing a qsort on all of the nodes at the end of the run. Their performance tests are shown in the second table, a performance advantage of around 40% is achieved over the array implementation.
2. Different types of scheduling (work distribution) of OpenMP were also tested to determin which of them were the fastest and dynamic scheduling with chunksize 2. Their performance are shown in the third table, a performance advantage of around 25% is achieved over static scheduling.

## Limitations
The Output Size must be greater than the number of nodes, as this implementation returns OutputSize number of longest paths from each Djikstra() function call, if the OutputSize is smaller than number of nodes then it will result in errors due to not enough nodes for a full output.

## Valgrind Report
Valgrind report ran on Djikstra reading graph0 and in serial execution <br/>
Valgrind report ran with Clean Heap and No Errors.
