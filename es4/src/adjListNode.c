#include <stdlib.h>
#include "../include/adjListNode.h"



adjListNode* create_node(int dest, int weight) {
  adjListNode* ret = (adjListNode*) malloc(sizeof(adjListNode)); 
  ret->dest = dest; 
  ret->weight = weight;
  ret->next = NULL; 
  return ret; 
}


int is_parent(adjListNode *u, adjListNode *v) {
  return u->u_d < v->u_d && v->u_d < v->u_f && v->u_f < u->u_f;
}