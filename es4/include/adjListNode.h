#pragma once

typedef struct adjListNode { 
  int dest; 
  int u_d, u_f;
  long weight;
  struct adjListNode* next; 
}adjListNode;
 
typedef struct adjList { 
  adjListNode *head;  
  int parent;
} adjList; 


/**
 * Create new adjacency node object
 * @param dest 	    destination of the adjacency node
 * @param weight 	weight of the adjacency node
 * @return          Pointer to new adjacency node object
*/
adjListNode* create_node(int dest, int weight); 


/**
 * Check if u is parent of v 
 * @param u   first vertex
 * @param v   second vertex
 * @return    1 if u is parent of v, 0 otherwise
*/
int is_parent(adjListNode *u, adjListNode *v);