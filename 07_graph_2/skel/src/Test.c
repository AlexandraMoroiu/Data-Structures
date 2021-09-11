// am rezolvat toate problemele (comentate in main)
// si am facut si niste fisiere.in (poate te ajuta)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(list_graph_t *lg,
					int node,
					int *visited,
					linked_list_t *component) {
	visited[node] = 1;

	ll_add_nth_node(component, component->size, &node);

	ll_node_t *current = lg->neighbors[node]->head;
	while(current != NULL) {
		// daca nodul nu a fost vizitat pana acum
		if(!visited[*(int *)current->data]) {
			dfs_connected_comps(lg, *(int *)current->data, visited, component);
		}
		current = current->next;
	}
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");

	*num_comp = 0;

	for(int i = 0; i < lg->nodes; i++) {
		if(!visited[i]) {
			comps[*num_comp] = ll_create(sizeof(int));
			dfs_connected_comps(lg, i, visited, comps[*num_comp]);
			(*num_comp)++;
		}
	}

	return comps;
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	/* TODO */
}

// algoritmul Khan
static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	
	// vector de grade interne
	int grade_in[MAX_NODES];

	for(int i = 0; i < lg->nodes; i++) {
		grade_in[i] = 0;
	}

	// setare valori vector de grade
	for(int i = 0; i < lg->nodes; i++) {
		ll_node_t *current = lg->neighbors[i]->head;
		while(current != NULL) {
			grade_in[*(int *)current->data]++;
			current = current->next;
		}
	}

	int visited_count = 0;
	queue_t *q = q_create(sizeof(int), lg->nodes);

	for(int i = 0; i < lg->nodes; i++) {
		if(grade_in[i] == 0) {
			q_enqueue(q, &i);
		}
	}

	while(!q_is_empty(q)) {
		int node = *(int *)q_front(q);
		q_dequeue(q);

		ll_add_nth_node(sorted, sorted->size, &node);

		ll_node_t *current = lg->neighbors[node]->head;
		while(current != NULL) {
			grade_in[*(int *)current->data]--;

			if(grade_in[*(int *)current->data] == 0) {
				q_enqueue(q, current->data);
			}
			current = current->next;
		}
		visited_count++;
	}

	q_free(q);

	if(visited_count != lg->nodes) {
		printf("Avem ciclu in graf\n");
		ll_free(&sorted);
		lg_free(lg);
		return NULL;
	}

	return sorted;
}

static void
min_path(list_graph_t *lg, int start, int *dist)
{
	queue_t *q = q_create(sizeof(int), lg->nodes);
	dist[start] = 0;
	q_enqueue(q, &start);

	int visited[lg->nodes];
	for(int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
	}

	visited[start] = 1;

	while(!q_is_empty(q)) {
		int node = *(int *)q_front(q);
		q_dequeue(q);

		ll_node_t *current = lg->neighbors[node]->head;
		while(current != NULL) {
			if(!visited[*(int *)current->data]) {
				visited[*(int *)current->data] = 1;
				dist[*(int *)current->data] = dist[node] + 1;
				q_enqueue(q, current->data);
			}
			current = current->next;
		}
	}
	q_free(q);
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	queue_t *q = q_create(sizeof(int), lg->nodes);

	for(int i = 0; i < lg->nodes; i++) {
		if(!color[i]) {
			color[i] = 1;
			q_enqueue(q, &i);
		}

		while(!q_is_empty(q)) {
			int node = *(int *)q_front(q);
			q_dequeue(q);

			ll_node_t *current = lg->neighbors[node]->head;
			while(current != NULL) {
				if(!color[*(int *)current->data]) {
					color[*(int *)current->data] =  3 - color[node];
					q_enqueue(q, current->data);
				} else if(color[*(int *)current->data] == color[node]) {
					// 2 noduri consecutive au aceiasi culoare
					return 0;
				}
				current = current->next;
			}
		}
	}
	q_free(q);

	return 1;
}

static void
dfs_hamilton(list_graph_t *lg, int node, int *visited, int *size, int *cycle) {
	cycle[*size] = node;
	*size = *size + 1;
	visited[node] = 1;

	ll_node_t *current = lg->neighbors[node]->head;
	while(current != NULL) {
		if(!visited[*(int *)current->data]) {
			dfs_hamilton(lg, *(int *)current->data, visited, size, cycle);
		} else if(*(int *)current->data == cycle[0] && *size == lg->nodes) {
			// am ajuns de unde am plecat
			for(int i = 0; i < *size; i++) {
				printf("%d ", cycle[i]);
			}
			// afisez si nodul de start
			printf("%d\n", *(int *)current->data);
		}
		current = current->next;
	}

	*size = *size - 1;
	visited[node] = 0;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	if(sorted) {
		printf("Topologically sorted nodes:\n");
		ll_print_int(sorted);
		printf("\n");

		ll_free(&sorted);
		lg_free(lg);
	}
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

static void
test_bonus(void)
{
	unsigned int i, nodes, edges;
	int x, y, node, size = 0;
	int visited[MAX_NODES] = {0};
	int cycle[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the hamiltonian bonus:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i)
	{
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	printf("Pick start node: ");
	scanf("%d", &node);
	printf("Cycles:\n");
	dfs_hamilton(lg, node, visited, &size, cycle);

	lg_free(lg);
}

int
main(void)
{
	// /* Ex 1 */
	// test_connected_comp();

	// /* Ex 2 */
	// test_topo_sort();

	// /* Ex 3 */
	// test_min_dist();

	// /* Ex 4 */
	// test_bipartite();

	// /* Ex bonus */
	// test_bonus();
	return 0;
}
