#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

list_graph_t*
lg_create(int nodes) {
	list_graph_t *graph = malloc(sizeof(list_graph_t));
	DIE(graph == NULL, "malloc failed");

	graph->nodes = nodes;

	graph->neighbors = malloc(nodes * sizeof(linked_list_t *));
	DIE(graph->neighbors == NULL, "malloc failed");
	for(int i = 0; i < nodes; i++) {
		graph->neighbors[i] = ll_create(sizeof(int));
	}

	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest) {
	if(!graph) {
		return;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din lista\n");
		return;
	}
	// presupun ca graful e neorientat
	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
	ll_add_nth_node(graph->neighbors[dest], graph->neighbors[dest]->size, &src);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest) {
	if(!graph) {
		return -1;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din lista\n");
		return -1;
	}

	ll_node_t *current = graph->neighbors[src]->head;
	while(current != NULL) {
		if(*(int *)current->data == dest) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node) {
	if(!graph) {
		return NULL;
	}

	if(node > graph->nodes) {
		printf("Nodul dorit nu face parte din lista\n");
		return NULL;
	}

	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest) {
	if(!graph) {
		return;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din lista\n");
		return;
	}

	// presupun ca graful e neorientat
	ll_node_t *current = graph->neighbors[src]->head;
	int count = 0, size = graph->neighbors[src]->size;
	while(size--) {
		if(*(int *)current->data == dest) {
			current = ll_remove_nth_node(graph->neighbors[src], count);
			free(current->data);
			free(current);
			return;
		}
		current = current->next;
		count++;
	}

	current = graph->neighbors[dest]->head;
	count = 0;
	size = graph->neighbors[dest]->size;
	while(size--) {
		if(*(int *)current->data == src) {
			current = ll_remove_nth_node(graph->neighbors[dest], count);
			free(current->data);
			free(current);
			return;
		}
		current = current->next;
		count++;
	}
}

void
lg_free(list_graph_t* graph) {
	if(!graph) {
		return;
	}
	
	for(int i = 0; i < graph->nodes; i++) {
		ll_free(&graph->neighbors[i]);
	}
	free(graph->neighbors);
	free(graph);
}