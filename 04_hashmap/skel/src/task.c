// problema 315CAa a) si b)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "utils.h"

#define MAX_STRING_SIZE	256

typedef struct product {
	char name[MAX_STRING_SIZE];
	char categorie[MAX_STRING_SIZE];
	float price;
	unsigned int sales;
} product;

void
print_produs(struct product *prod)
{
	if (prod == NULL) {
		printf("Produs inexistent!\n");
		return;
	}
	printf("* Nume: %s; ", prod->name);
	printf("Categorie: %s; ", prod->categorie);
	printf("Pret: %.2f; ", prod->price);
	printf("Numar vanzari: %d\n", prod->sales);
}

void search_product(hashtable_t *ht_prod, char *name) {
	unsigned int found;
	product *prod;
	found = ht_has_key(ht_prod, name);
	if(found) {
		prod = ht_get(ht_prod, name);
		print_produs(prod);
	} else {
		printf("Produsul %s nu face parte din oferta magazinului.\n", name);
	}
}


int main() {

	char name[MAX_STRING_SIZE];
	product *list, *prod;
	
	hashtable_t *ht_prod = ht_create(100, hash_function_string,
						compare_function_strings);

	list = malloc(50 * sizeof(product));
	DIE(list == NULL, "malloc failed");

	strcpy(list[0].name, "lapte");
	strcpy(list[0].categorie, "lactate");
	list[0].price = 3.5;
	list[0].sales = 20;

	ht_put(ht_prod, "lapte", strlen("lapte") + 1, &list[0],
		sizeof(list[0]));

	printf("# 1\n");
	printf("Output:\n");
	search_product(ht_prod, "lapte");
	printf("Output asteptat:\n");
	printf("* Nume: lapte; Categorie: lactate; Pret: 3.50; Numar vanzari: 20\n\n");
	

	strcpy(list[1].name, "savarine");
	strcpy(list[1].categorie, "prajituri");
	list[1].price = 4.6;
	list[1].sales = 17;
	ht_put(ht_prod, "savarine", strlen("savarine") + 1, &list[1],
		sizeof(list[1]));

	printf("# 2\n");
	printf("Output:\n");
	search_product(ht_prod, "savarine");
	printf("Output asteptat:\n");
	printf("* Nume: savarine; Categorie: prajituri; Pret: 4.60; Numar vanzari: 17\n\n");


	printf("# 3\n");
	printf("Output:\n");
	search_product(ht_prod, "peste");
	printf("Output asteptat:\n");
	printf("Produsul peste nu face parte din oferta magazinului.\n\n");


	strcpy(list[2].name, "negrese");
	strcpy(list[2].categorie, "prajituri");
	list[2].price = 5.75;
	list[2].sales = 13;
	ht_put(ht_prod, "negrese", strlen("negrese") + 1, &list[2],
		sizeof(list[2]));

	printf("# 4\n");
	printf("Output:\n");
	search_product(ht_prod, "negrese");
	printf("Output asteptat:\n");
	printf("* Nume: negrese; Categorie: prajituri; Pret: 5.75; Numar vanzari: 13\n\n");


	strcpy(list[3].name, "pui");
	strcpy(list[3].categorie, "carne");
	list[3].price = 8.23;
	list[3].sales = 40;
	ht_put(ht_prod, "pui", strlen("pui") + 1, &list[3],
		sizeof(list[3]));

	printf("# 5\n");
	printf("Output:\n");
	search_product(ht_prod, "pui");
	printf("Output asteptat:\n");
	printf("* Nume: pui; Categorie: carne; Pret: 8.23; Numar vanzari: 40\n\n");


	printf("# 6\n");
	printf("Output:\n");
	search_product(ht_prod, "ulei");
	printf("Output asteptat:\n");
	printf("Produsul ulei nu face parte din oferta magazinului.\n\n");


	strcpy(list[4].name, "oua");
	strcpy(list[4].categorie, "lactate");
	list[4].price = 3.2;
	list[4].sales = 36;
	ht_put(ht_prod, "oua", strlen("oua") + 1, &list[4],
		sizeof(list[4]));

	printf("# 7\n");
	printf("Output:\n");
	search_product(ht_prod, "oua");
	printf("Output asteptat:\n");
	printf("* Nume: oua; Categorie: lactate; Pret: 3.20; Numar vanzari: 36\n\n");


	strcpy(list[5].name, "amandine");
	strcpy(list[5].categorie, "prajituri");
	list[5].price = 4.45;
	list[5].sales = 14;

	ht_put(ht_prod, "amandine", strlen("amandine") + 1, &list[5],
		sizeof(list[5]));

	printf("# 8\n");
	printf("Output:\n");
	search_product(ht_prod, "amandine");
	printf("Output asteptat:\n");
	printf("* Nume: amandine; Categorie: prajituri; Pret: 4.45; Numar vanzari: 14\n");

	free(list);
	ht_free(ht_prod);

	return 0;
}