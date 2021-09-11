#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define INT_MAX 2147483647

int main() {

	int i, j, k;
	int min = INT_MAX, max = 1, count = 0;
	int **mat, m, n;

	scanf("%d%d", &n, &m);

	mat = malloc(n * sizeof(int *));
	DIE(mat == NULL, "malloc failed");

	for(i = 0; i < n; i++) {
		mat[i] = malloc(m * sizeof(int));
		DIE(mat[i] == NULL, "malloc failed");
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			scanf("%d", &mat[i][j]);
			if(mat[i][j] < min) {
				min = mat[i][j];
			}
			if(mat[i][j] > max) {
				max = mat[i][j];
			}
		}
	}
	
	for(k = min; k <= max; k++) {
		int found = 0;
		for(i = 0; i < n && !found; i++) {
			for(j = 0; j < m; j++) {
				if(mat[i][j] == k) {
					found = 1;
					mat[i][j] = -1;
					count++;
					break;
				}
			}
		}
	}


	if(count == n * m && count == max - min + 1) {
		printf("Matricea are elemente consecutive\n");
	}
	else {
		printf("Nope\n");
	}

	for(int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);

	return 0;
}
