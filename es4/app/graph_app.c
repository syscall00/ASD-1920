#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"  	

typedef struct edge {
  int src, dest;
  long weight;
}edge;


void load_values(char *path, graph **g, edge **edges, int *edges_number) {
  int count = 0, vertex_num, n;	
  int src, dest;
  long weight;

  FILE *file;
	
  file = fopen(path, "r");
  if (!file) {
    printf("No such file or directory %s\n",path);
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d",&vertex_num);
  *g = graph_create(vertex_num);

  while (count < (vertex_num-1)) {

    n = fscanf(file, "%d %d %ld", &src,&dest,&weight);
    if(n != 3) {
      if(feof(file)) continue;

      printf("Error while reading file at line: %d.\nMake sure your file is formatted properly.\n", count);
      exit(EXIT_FAILURE);
    }
		
    add_edge(*g, src, dest, weight);		
		
    count++;
  }

  count = 0;

  fscanf(file, "%d",edges_number);
  *edges = malloc(sizeof(edge) * (*edges_number));
  while(!feof(file) ) {
    n = fscanf(file, "%d %d %ld", &src, &dest, &weight);

    if(n != 3) {
      if(feof(file)) continue;

      printf("Error while reading file at line: %d.\nMake sure your file is formatted properly.\n", count);
      exit(EXIT_FAILURE);
    }
    (*edges)[count].src = src;
    (*edges)[count].dest = dest;
    (*edges)[count].weight = weight;
    count++;

  }

  fclose(file);
}


int test_edge(graph *g, edge e) {
	
  int v1 = e.src, v2 = e.dest, weight = e.weight;
  int i = v1, j = v2;

  while(i>=0 && j >=0 && i != j) {
    adjListNode * u = graph_get_adjList(g, i);
    adjListNode *v = graph_get_adjList(g, j);

    if(is_parent(u,v)) {
			
      while(v2 != i) {
        adjListNode * copy = graph_get_adjList(g, v2);
        int w = adjList_get_weight(copy, get_node_parent(g, v2));
        if(w > weight) return 1;
		
        v2 = get_node_parent(g, v2);
      }

      break;
      }
    else if(is_parent(v,u)) {

      while(v1 != j) {
        adjListNode * copy = graph_get_adjList(g, v1);
        int w = adjList_get_weight(copy, get_node_parent(g, v1));
        if(w > weight) return 1;
		
        v1 = get_node_parent(g, v1);
      }

      break;
    }
    else { 
			
      int w;
      adjListNode *copy;
			
      copy = graph_get_adjList(g, j);
      w = adjList_get_weight(copy, get_node_parent(g, j));
      if(w > weight) return 1;
      j = get_node_parent(g, j);	
			
      copy = graph_get_adjList(g, i);
      w = adjList_get_weight(copy, get_node_parent(g, i));
      if(w > weight) return 1;
			
      i = get_node_parent(g, i);		
			
    }
  }
  return 0;
} 


int main(int argc, char*argv[]) { 
  graph * g;
  edge* edges;
  int edges_number;

  char* dataset = argv[1];
  char* output = argv[2];
	
  FILE *file = fopen(output,"w");

  load_values(dataset, &g, &edges, &edges_number);

  timed_dfs(g);

  for(int i = 0; i < edges_number; i++) {
    int result = test_edge(g, edges[i]);
    fprintf(file, "%s\n", result == 1? "YES":"NO");
  }

  fclose(file);
  free(edges);
	
  return 0;
}
