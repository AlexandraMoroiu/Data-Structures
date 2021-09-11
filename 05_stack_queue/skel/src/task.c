#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "utils.h"

// verific daca doua paranteze sunt perechi
int pair(char par1, char par2) {
	if (par1 == '(' && par2 == ')')
		return 1;
	if (par1 == '{' && par2 == '}')
		return 1;
	if (par1 == '[' && par2 == ']')
		return 1;
	
	return 0;
}

int check_parant(char *ex, stack_t *st) {
	for (int i = 0; i < strlen(ex); i++) {
		if(ex[i] == '(' || ex[i] == '[' || ex[i] == '{') {
			st_push(st, &ex[i]);
		} else if(ex[i] == ')' || ex[i] == ']' || ex[i] == '}') {
			if(st_is_empty(st)) {
				// paranteza nu are cum sa aiba pereche
				return 0;
			}
			if (pair(*(char *)st_peek(st), ex[i]) == 0) {
				return 0;
			}
			if (pair(*(char *)st_peek(st), ex[i])) {
				// sunt perechi deci pot elimina paranteza dn stiva
				st_pop(st);
			}
		}
	}

	// stiva e goala => toate parant au fost inchise corect
	if(st_is_empty(st)) {
		return 1;
	}

	return 0;
}

int main() {
	stack_t *st = st_create(sizeof(char *));

	// Teste
	char ex1[] = "{}[]()";

	printf("#1\nOutput asteptat: Parantezare corecta\nOutput: ");
	if(check_parant(ex1, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);
	

	char ex2[] = "(((())))";

	printf("\n#2\nOutput asteptat: Parantezare corecta\nOutput: ");
	if(check_parant(ex2, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);
	

	char ex3[] = "{[][((()";

	printf("\n#3\nOutput asteptat: Parantezare incorecta\nOutput: ");
	if(check_parant(ex3, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);


	char ex4[] = "}])()([{";

	printf("\n#4\nOutput asteptat: Parantezare incorecta\nOutput: ");
	if(check_parant(ex4, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);


	char ex5[] = "{{[()]}}";

	printf("\n#5\nOutput asteptat: Parantezare corecta\nOutput: ");
	if(check_parant(ex5, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);


	char ex6[] = "{]}](])]";

	printf("\n#5\nOutput asteptat: Parantezare incorecta\nOutput: ");
	if(check_parant(ex6, st)) {
		printf("Parantezare corecta\n");
	} else {
		printf("Parantezare incorecta\n");
	}
	st_clear(st);

	st_free(st);

	return 0;
}
