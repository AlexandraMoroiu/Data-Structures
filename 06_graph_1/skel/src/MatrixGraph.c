#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "MatrixGraph.h"

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */
matrix_graph_t*
mg_create(int nodes) {
	matrix_graph_t *graph = malloc(sizeof(matrix_graph_t));
	DIE(graph == NULL, "malloc failed");

	graph->nodes = nodes;

	// alocare si intitializare matrice
	graph->matrix = malloc(nodes * sizeof(int *));
	DIE(graph->matrix == NULL, "malloc failed");
	for(int i = 0; i < nodes; i++) {
		graph->matrix[i] = malloc(nodes * sizeof(int));
		DIE(graph->matrix[i] == NULL, "malloc failed");
		for(int j = 0; j < nodes; j++) {
			graph->matrix[i][j] = 0;
		}

	}

	return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t* graph, int src, int dest) {
	if(!graph) {
		return;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din matrice\n");
		return;
	}

	// presupun ca graful este neorientat
	graph->matrix[src][dest] = 1;
	graph->matrix[dest][src] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t* graph, int src, int dest) {
	if(!graph) {
		return -1;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din matrice\n");
		return -1;
	}

	if(graph->matrix[src][dest] == 1 && graph->matrix[dest][src] == 1) {
		return 1;
	}
	return 0;
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t* graph, int src, int dest) {
	if(!graph) {
		return;
	}

	if(src > graph->nodes || dest > graph->nodes) {
		printf("Nodurile dorite nu fac parte din matrice\n");
		return;
	}

	// presupun ca graful este neorientat
	graph->matrix[src][dest] = 0;
	graph->matrix[dest][src] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_free(matrix_graph_t* graph) {
	if(!graph) {
		return;
	}

	for(int i = 0; i < graph->nodes; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
}