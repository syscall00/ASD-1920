#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../include/graph.h"

graph* graph_create(int V) { 
  graph* g = (graph*) malloc(sizeof(graph)); 
  g->V = V; 
  g->time = 0;
  g->visited = malloc(sizeof(int) * V);
  g->array = (adjList*) malloc(V * sizeof(adjList)); 

  for (int i = 0; i < V; ++i) {
    g->visited[i] = 0;
    g->array[i].head = NULL;
  } 
  
  return g; 
} 
  
	
void graph_free(graph* g) {

  for(int i = 0; i < g->V; g++) {
    adjListNode* curr = g->array[i].head, *temp;
    if(curr != NULL) free(curr);
    while(curr != NULL) { 
      temp = curr->next;
      free(curr);
      curr = temp;
    }
  }
  free(g->array);
  free(g->visited);
  free(g);
}


void add_edge(graph* g, int src, int dest, long weight) { 
  
  adjListNode* newNode = create_node(dest, weight); 
  newNode->next = g->array[src].head; 
  g->array[src].head = newNode; 
  
  newNode = create_node(src, weight); 
  newNode->next = g->array[dest].head; 
  g->array[dest].head = newNode; 
}


void remove_edge(graph* g, int src, int dest) {
  adjListNode* head = graph_get_adjList(g, src);
  adjListNode* prev = NULL;
  while(head != NULL) {
    if(head->dest == dest) {
      if(prev == NULL) {
        g->array[src].head = head->next;
      }
      else {
        prev->next = head->next;
      }
      break;
    }
    prev = head;
    head = head->next;
  }
  head = graph_get_adjList(g, dest);
  prev = NULL;
  while(head != NULL) {
    if(head->dest == src) {
      if(prev == NULL) {
        g->array[dest].head = head->next;
      }
      else {
        prev->next = head->next;
      }
      break;
    }
    prev = head;
    head = head->next;
  }
}


adjListNode *graph_get_adjList(graph *g, int src) {
  if(src >= 0 && src <= g->V)
    return g->array[src].head;
  else
    return NULL;
}


long adjList_get_weight(adjListNode *adjList, int dest) {
  adjListNode *copy = adjList;
  while(copy != NULL) {
    if(copy->dest == dest) 
      return copy->weight;
    
    copy = copy->next;
  }
  return LONG_MAX;
}


int get_node_parent(graph* g, int src) {
  if(src >= 0 ) 
    return g->array[src].parent;
	else
    return -1;
}


void set_node_parent(graph* g, int src, int val) {
  if(src >= 0) 
    g->array[src].parent = val;
  else 
		return;
}


void t_dfs(graph *g, int vertex) {
  int ret = 0;
  g->time++;
	
  adjListNode* adjList = graph_get_adjList(g, vertex);
  adjListNode* temp = adjList;
	
  g->visited[vertex] = 1;

  if(adjList == NULL) return;
  adjList->u_d = g->time;
	
  ret++;

  while(temp != NULL) {
    int connectedVertex = temp->dest;

    if (g->visited[connectedVertex] == 0) {
      set_node_parent(g, connectedVertex, vertex);
			
      dfs_topological(g, connectedVertex);
    }
		
    temp = temp->next;

  }
  g->time++;
  adjList->u_f = g->time;
}

void timed_dfs(graph *g) {

  t_dfs(g, 1);

}