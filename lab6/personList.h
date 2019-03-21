/* personList.h */

#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "names.h"

struct personList {
	struct personNode *head;
	int size;
};


struct personList *makeList();

void add(struct personList *list, struct person *item);

void removePerson(struct personList *list, struct person *item);

int easyRand(int max);

float easyRandF();

/* remove all people who were born before the given birth year
   and return them (the removed people) as a list */
struct personList *removeAllAge(struct personList *list, int minBirthYear);

/* pick a random person from the list */
struct person *getRandom(struct personList *list);

struct person **toArray(struct personList *list);

struct personList *getMarriedFemales(struct personList *list);

struct personList *getMarriableFemales(struct personList *list, int
		minBirthYear);

struct personList *getMarriableMales(struct personList *list, int minBirthYear);

void destroyList(struct personList *list);

void printStats(struct personList *list, int minAdultBirthYear);

#endif
