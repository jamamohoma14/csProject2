/* personList.c */

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#include "personNode.h"
#include "personList.h"
#include "person.h"

struct personList *
makeList()
{
	struct personList * plist = malloc(sizeof(struct personList));
	plist->head = NULL;
	plist->size = 0;
	return plist;
}

void
add(struct personList *list, struct person *item)
{
	struct personNode *current, *newNode;
	for (current = list->head; current != NULL; current = current->next)
		if (current->datum == item)
			return;
	newNode = malloc(sizeof(struct personNode *));
	newNode->datum = item;
	newNode->next = list->head;
	list->head = newNode;
	list->size = list->size + 1;

}

void
removePerson(struct personList *list, struct person *item)
{
	if (list->head == NULL)
		return;

	struct personNode *old = NULL;
	if (list->head->datum == item)
	{
		old = list->head;
		list->head = list->head->next;
	}
	else
	{
		struct personNode *current;
		for (current = list->head; current->next != NULL; 
				current = current->next)
			if (current->next->datum == item)
			{
				old = current->next;
				current->next = current->next->next;
				break;
			}
	}
	free(old);
	list->size--;
}

/* remove all people who were born before the given birth year
 * and return them (the removed people) as a list */
struct personList *
removeAllAge(struct personList *list, int minBirthYear)
{
	struct personList *toReturn = makeList();
	while (list->head != NULL && list->head->datum->birthYear < minBirthYear)
	{
		add(toReturn, list->head->datum);
		struct personNode *old = list->head;
		list->head = list->head->next;
		free(old);
		list->size--;
	}
	struct personNode *current;
	for (current = list->head; current != NULL && current->next != NULL;
			current = current->next)

		while(current->next != NULL && 
				current->next->datum->birthYear < minBirthYear)
		{
			add(toReturn, current->next->datum);
			struct personNode *old = current->next;
			current->next = current->next->next;
			free(old);
			list->size--;
		}

	return toReturn;
}



int
easyRand(int max)
{
	static int initialized = 0;
	if (! initialized)
	{
		srand(time(NULL));
		initialized = 1;
	}
	return rand() % max;
}

float
easyRandF()
{
	static int initialized = 0;
	if (! initialized)
	{
		srand(time(NULL));
		initialized = 1;
	}
	return (float)rand() / (float)RAND_MAX;
}

/* pick a random person from the list */
struct person *
getRandom(struct personList *list)
{
	int pos = easyRand(list->size);
	struct personNode *toReturn = list->head;
	int i;
	for (i = 0; i < pos; i++)
		toReturn = toReturn->next;
	if (toReturn == NULL)
		return NULL;
	else
		return toReturn->datum;
}

struct person **
toArray(struct personList *list)
{
  
	struct person ** ptr = malloc(sizeof(struct person *) * list->size);
	struct personNode * temp;// = list->head;
	int i = 0;
	for (temp = list->head; temp != NULL; temp = temp->next) {
		ptr[i] = temp->datum;
		i++;
	}
  	return ptr;

}

struct personList *
getMarriedFemales(struct personList *list)
{
	struct personList *toReturn = makeList();
	struct personNode *current;
	for (current = list->head; current != NULL; current = current->next)
	{
		struct person *currPers = current->datum;
		if (currPers->gender && currPers->spouse != NULL)
			add(toReturn, currPers);
	}
	return toReturn;
}

struct personList *
getMarriableFemales(struct personList *list, int minBirthYear)
{
	struct personList *toReturn = makeList();
	struct personNode *current;
	for (current = list->head; current != NULL; current = current->next)
	{
		struct person *currPers = current->datum;
		if (currPers->gender && currPers->spouse == NULL
				&& currPers->birthYear <= minBirthYear)
			add(toReturn, currPers);
	}
	return toReturn;
}

struct personList *
getMarriableMales(struct personList *list, int minBirthYear)
{
	struct personList *toReturn = makeList();
	struct personNode *current;
	for (current = list->head; current != NULL; current = current->next)
	{
		struct person *currPers = current->datum;
		if (! currPers->gender && currPers->spouse == NULL
				&& currPers->birthYear <= minBirthYear)
			add(toReturn, currPers);
	}
	return toReturn;

}

void
destroyList(struct personList *list)
{
	if (list == NULL) return;
	struct personNode *current = list->head;
	while (current != NULL)
	{
		struct personNode *next = current->next;
		current->next = NULL;
		current->datum = NULL;
		free(current);
		current = next;
	}
	list->head = NULL;
	free(list);
}

void
printStats(struct personList *list, int minAdultBirthYear)
{
	int 
		numAdults = 0,   // number born on or before the birth year
			  numMarried = 0,  // number who have a nonnull spouse
			  numWithChildren = 0,  // number who have at least one child
			  totalChildren = 0;   // sum of all child quantities of all people
	struct personNode *current;
	for (current = list->head; current != NULL; current = current->next) 
	{
		struct person *currPers = current->datum;
		if (currPers->birthYear <= minAdultBirthYear)  numAdults++;
		if (currPers->spouse != NULL) numMarried++;
		struct personList *currChildren = currPers->children;
		if (currChildren->size != 0) 
		{
			numWithChildren++;
			totalChildren += currChildren->size;
		}
	}
	printf("Population size: %d.\n", list->size);
	if (numAdults == 0)
		printf("No adults.\n");
	else
		printf("%f of adults are married.\n", 
				((double) numMarried / numAdults));
	if (numWithChildren == 0)
		printf("Noone with children.\n");
	else
		printf("%d have children, averaging %f children each.\n", 
				numWithChildren, ((double) totalChildren / numWithChildren));
}
