#pragma once
#include "../include/adjListNode.h"


typedef struct graph { 
  int V, time;
  int* visited;
  struct adjList* array; 
} graph; 


/**
 * Create new graph object
 * @param V 	number of vertex in graph
 * @return    Pointer to new graph object
 */
graph* graph_create(int V);


/**
 * Frees up the space of a specific hashMap object
 * @param ht	object to be freed
 */
void graph_free(graph* g);


/**
 * Add a bidirectional edge to graph
 * @param g	      graph object
 * @param src	    source vertex
 * @param dest	  destination vertex
 * @param weight  weight of the edge
 */
void add_edge(graph* g, int src, int dest, long weight);


/**
 * Remove a bidirectional edge to graph
 * @param g	      graph object
 * @param src	    source vertex
 * @param dest	  destination vertex
 */
void remove_edge(graph* g, int src, int dest);


/**
 * get a specific adjacency list
 * @param g	      graph object
 * @param src	    vertex value
 * @return        List of adjacency
 */
adjListNode* graph_get_adjList(graph *g, int src);


/**
 * Get weight of a specific edge
 * @param g	      graph object
 * @param src	    vertex source of the edge
 * @param src	    vertex destination of the edge
 * @return      weight of the edge if found, infinity if not 
 */
long adjList_get_weight(adjListNode *adjList, int dest);


/**
 * Get the parent field of a specific vertex
 * @param g	   graph object
 * @param src	 vertex value
 * @return 		 the value of the node parent
 */
int get_node_parent(graph* g, int src);


/**
 * Set the parent field of a specific vertex 
 * @param g	      graph object
 * @param src	    vertex value
 * @param src	    parent value to be setted
 */
void set_node_parent(graph* g, int src, int val);


/**
 * Using a DFS, marks all vertex with a 
 * discover time and termination time
 * @param g	  graph object
 */
void timed_dfs(graph *g);