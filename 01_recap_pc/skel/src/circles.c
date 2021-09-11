#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

typedef struct {
	int x, y;
	unsigned int R;
} Circle;

int intersect(Circle cerc1, Circle cerc2) {

	unsigned int dist = sqrt((cerc1.x - cerc2.x) * (cerc1.x - cerc2.x) +
					(cerc1.y - cerc2.y) * (cerc1.y - cerc2.y));

	if(dist <= cerc1.R + cerc2.R) {
		return 1;
	}

	return 0;
}

int main()
{
	int n, count = 0, i, j;
	Circle *cerc;

	scanf("%d", &n);
	
	cerc = malloc(n * sizeof(Circle));

	DIE(cerc == NULL, "malloc failed");
	
	for(i = 0; i < n; i++) {
		scanf("%d%d%u", &cerc[i].x, &cerc[i].y, &cerc[i].R);
	}

	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			if(intersect(cerc[i], cerc[j])){
				count++;
			}
		}
	}

	printf("%d\n", count);
	
	free(cerc);

    return 0;
}
