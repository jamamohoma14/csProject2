/* person.h */

#ifndef PERSON_H
#define PERSON_H

#include "names.h"

struct person {
	int givenName;  /* actually a unique integer id */
	char *surname;
	int gender;     /* 0=male 1=female */
	int birthYear;
	struct person *spouse;
	struct personList *children;
};

struct person *makePerson(int givenName, char *surname, int gender,
		int birthYear);

void addChild(struct person *parent, struct person *child);

void destroyPerson(struct person *p);

char *toString(struct person *p);

#endif
