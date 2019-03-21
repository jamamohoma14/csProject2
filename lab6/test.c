#include <stdio.h>
#include <string.h>

#include "person.h"
#include "personList.h"
#include "personNode.h"

int
main()
{
	printf("A: makePerson\n");
	struct person *p = makePerson(12, "Vercingetorix", 0, 8);

	if (strcmp(toString(p), "12 Vercingetorix (8)") == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	printf("\nB: destroyPerson\n");
	destroyPerson(p);
	printf("DIDN'T CRASH\n");

	printf("\nC: makeList\n");
	struct personList *list = makeList();
	printf("DIDN'T CRASH\n");

	printf("\nE. add\n");
	add(list, makePerson(14, "Ozymandias", 0, 30));
	if (list->size > 0 && strcmp(toString(getRandom(list)), "14 Ozymandias (30)") == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	printf("\nF: addChild\n");
	p = makePerson(12, "Vercingetorix", 0, 8);
	addChild(p, makePerson(13, "Vercingetorix", 1, 28));
	addChild(p, makePerson(15, "Vercingetorix", 0, 33));
	if (p->children->size == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	printf("\nG: get marrieds and mariables\n");
	struct person *q = makePerson(16, "Crysanthemum", 1, 3),
	       *r = makePerson(17, "Delphinium", 1, 3),
	       *s = makePerson(18, "Telemachus", 0, 4);
	r->spouse = s;
	s->spouse = r;
	add(list, q);
	add(list, r);
	add(list, s);

	printf("Ga: getMarriedFemales\n");
	struct personList *other = getMarriedFemales(list);
	if (other->size > 0 && strcmp(toString(getRandom(other)), "17 Delphinium (3)")==0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	printf("Gb: getMarriableFemales\n");
	other = getMarriableFemales(list, 30);
	if (other->size > 0 && strcmp(toString(getRandom(other)), "16 Crysanthemum (3)")==0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	printf("Gc: getMariableMales\n");
	other = getMarriableMales(list, 30);
	if (other->size > 0 && strcmp(toString(getRandom(other)), "14 Ozymandias (30)")==0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	printf("\nH: toArray\n");
	struct person **person_array = toArray(list);
	int i = 0;
	struct personNode *current = list->head;
	int ok = 1;
	if (person_array == NULL) 
		ok = 0;
	else 
		while (i < list->size) 
		{
			ok = ok && current->datum == person_array[i];
			i++;
			current = current->next;
		}
	if (ok)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	return 0;
}
