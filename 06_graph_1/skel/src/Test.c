// daca o dau in bara iar cu git-ul sa-mi spui te rog ^^'

#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 10
static int time;

// generez un graf cu 5 noduri si 5 muchii pt teste:
// 0: 1 2 3
// 1: 0 2
// 2: 0 1 4
// 3: 0
// 4: 2
void generate_lg_graph(list_graph_t* lg, int *numbers) {
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[1], numbers[2]);
	lg_add_edge(lg, numbers[2], numbers[4]);
}

void generate_mg_graph(matrix_graph_t* mg, int *numbers) {
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[0], numbers[2]);
	mg_add_edge(mg, numbers[0], numbers[3]);
	mg_add_edge(mg, numbers[1], numbers[2]);
	mg_add_edge(mg, numbers[2], numbers[4]);
}

void
print_matrix_graph(matrix_graph_t* mg) {
	for(int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

void
print_list_graph(list_graph_t* lg) {
	for(int i = 0; i < lg->nodes; i++) {
		// are vecini
		if(lg->neighbors[i]->size) {
			printf("%d: ", i);
			ll_print_int(lg->neighbors[i]);
		}
	}
}

void
dfs_list_graph_recursive(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_fin) {
	visited[node] = 1;
	t_desc[node] = time++;
	printf("%d ", node);

	ll_node_t *current = lg->neighbors[node]->head;
	while(current != NULL) {
		// daca nodul nu a fost vizitat pana acum
		if(!visited[*(int *)current->data]) {
			dfs_list_graph_recursive(lg, *(int *)current->data, visited, t_desc, t_fin);
		}
		current = current->next;
	}
	t_fin[node] = time++;
}

void
dfs_list_graph_iterative(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_fin) {
	for(int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
	}

	stack_t *st = st_create(sizeof(int));
	visited[node] = 1;
	st_push(st, &node);

	while(!st_is_empty(st)) {
		node = *(int *)st_peek(st);
		st_pop(st);
		t_fin[node]++;
		printf("%d ", node);
		
		ll_node_t *current = lg->neighbors[node]->head;
		while(current != NULL) {
			// daca nodul nu a fost vizitat pana acum
			if(!visited[*(int *)current->data]) {
				visited[*(int *)current->data] = 1;
				t_desc[*(int *)current->data]++;
				st_push(st, current->data);
			}
			current = current->next;
		}
	}

	printf("\n");

	st_free(st);
}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_fin) {
	visited[node] = 1;
	t_desc[node] = time++;

	printf("%d ", node);

	for(int j = 0; j < mg->nodes; j++) {
		// exista muchie si nodul n-a fost inca vizitat
		if(mg->matrix[node][j] == 1 && visited[j] == 0) {
			dfs_matrix_graph(mg, j, visited, t_desc, t_fin);
		}
	}

	t_fin[node] = time++;
}

void
bfs_list_graph(list_graph_t* lg, int* visited, int* parent) {
	int node;
	for(int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
	}

	queue_t *q = q_create(sizeof(int), lg->nodes);
	// incep parcurgerea de la parent
	visited[*parent] = 1;
	q_enqueue(q, parent);

	while(!q_is_empty(q)) {
		node = *(int *)q_front(q);
		printf("%d ", node);
		q_dequeue(q);

		ll_node_t *current = lg->neighbors[node]->head;
		while(current != NULL) {
			// daca nodul nu a fost vizitat pana acum
			if(!visited[*(int *)current->data]) {
				visited[*(int *)current->data] = 1;
				q_enqueue(q, current->data);
			}
			current = current->next;
		}
	}

	printf("\n");

	q_free(q);
}

void
bfs_matrix_graph(matrix_graph_t* mg, int* visited, int* parent) {
	int nodes[mg->nodes];
	for(int i = 0; i < mg->nodes; i++) {
		nodes[i] = -1;
		visited[i] = 0;
	}
	// nodes[] -> nodurile parcurse
	// visited[] -> tin evidenta parcurgerii

	nodes[0] = *parent;
	visited[*parent] = 1;
	int index_node = 0, index_vis = 0;

	// index_node > index_vis => nu mai am nicio alta muchie si ma opresc
	while(index_node <= index_vis) {
		for(int k = 0; k < mg->nodes; k++) {
			// exista muchie si nodul n-a fost inca vizitat
			if(mg->matrix[*parent][k] == 1 && visited[k] == 0) {
				index_vis++;
				nodes[index_vis] = k;
				visited[k] = 1;
			}
		}
		index_node++;
		*parent = nodes[index_node];
	}

	for(int i = 0; i < mg->nodes; i++) {
		if(nodes[i] != -1) {
			printf("%d ", nodes[i]);
		}
	}

	printf("\n");
}

void
bfs_matrix_graph_queue(matrix_graph_t* mg, int* visited, int* parent) {
	int node;
	for(int i = 0; i < mg->nodes; i++) {
		visited[i] = 0;
	}

	queue_t *q = q_create(sizeof(int), mg->nodes);
	// incep parcurgerea de la parent
	visited[*parent] = 1;
	q_enqueue(q, parent);

	while(!q_is_empty(q)) {
		node = *(int *)q_front(q);
		printf("%d ", node);
		q_dequeue(q);

		for(int i = 0; i < mg->nodes; i++) {
			if(mg_has_edge(mg, node, i) && !visited[i]) {
				visited[i] = 1;
				q_enqueue(q, &i);
			}
		}
	}

	printf("\n");
}

void
floyd_warshall(matrix_graph_t* mg)
{
	/* TODO BONUS */
}

int
main() {
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_desc[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	// Test add_edge_list_graph has_edge_list_graph 

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	// Test remove_edge_list_graph 
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);

	printf("-------------------------------- Test BFS_ListGraph "
		"--------------------------------\n");
	lg = lg_create(MAX_NODES);
	generate_lg_graph(lg, numbers);

	printf("#1:\nOutput: ");
	bfs_list_graph(lg, visited, &numbers[2]);
	printf("Output asteptat: 2 0 1 4 3\n");

	printf("#2:\nOutput: ");
	bfs_list_graph(lg, visited, &numbers[1]);
	printf("Output asteptat: 1 0 2 3 4\n");

	printf("-------------------------------- Test DFS_Recursive_ListGraph "
		"--------------------------------\n");

	for(int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
	}

	printf("#1:\nOutput: ");
	dfs_list_graph_recursive(lg, numbers[0], visited, t_desc, t_fin);
	printf("\nOutput asteptat: 0 1 2 4 3\n");

	for(int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
	}

	printf("#2:\nOutput: ");
	dfs_list_graph_recursive(lg, numbers[3], visited, t_desc, t_fin);
	printf("\nOutput asteptat: 3 0 1 2 4\n");

	printf("-------------------------------- Test DFS_Iterative_ListGraph "
		"--------------------------------\n");

	printf("#1:\nOutput: ");
	dfs_list_graph_iterative(lg, numbers[0], visited, t_desc, t_fin);
	printf("Output asteptat: 0 3 2 4 1\n");

	printf("#2:\nOutput: ");
	dfs_list_graph_iterative(lg, numbers[1], visited, t_desc, t_fin);
	printf("Output asteptat: 1 2 4 0 3\n");

	lg_free(lg);

	printf("-------------------------------- Test BFS_MatrixGraph "
		"--------------------------------\n");

	mg = mg_create(MAX_NODES);
	generate_mg_graph(mg, numbers);

	printf("#1:\nOutput: ");
	bfs_matrix_graph(mg, visited, &numbers[2]);
	printf("Output asteptat: 2 0 1 4 3\n");

	printf("#2:\nOutput: ");
	bfs_matrix_graph_queue(mg, visited, &numbers[4]);
	printf("Output asteptat: 4 2 0 1 3\n");

	printf("-------------------------------- Test DFS_MatrixGraph "
		"--------------------------------\n");

	for(int i = 0; i < mg->nodes; i++) {
		visited[i] = 0;
	}

	printf("#1:\nOutput: ");
	dfs_matrix_graph(mg, numbers[3], visited, t_desc, t_fin);
	printf("\nOutput asteptat: 3 0 1 2 4\n");

	for(int i = 0; i < mg->nodes; i++) {
		visited[i] = 0;
	}

	printf("#2:\nOutput: ");
	dfs_matrix_graph(mg, numbers[1], visited, t_desc, t_fin);
	printf("\nOutput asteptat: 1 0 2 4 3\n");

	mg_free(mg);

	return 0;
}
