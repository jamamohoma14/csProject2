/* person.c */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "person.h"
#include "personList.h"

struct person *
makePerson(int givenName, char *surname, int gender, int birthYear) 
{
	struct person * a = malloc(sizeof(struct person));
	a->givenName = givenName;
	a->surname = surname;
	a->gender = gender;
	a->birthYear = birthYear;
	a->spouse= NULL;
	a->children = makeList();
	
	return a;
}

void
addChild(struct person *parent, struct person *child)
{
	add(parent->children, child);
}

void
destroyPerson(struct person *p)
{
  	p->givenName = 0;
	p->surname = NULL;
	p->gender = 0;
	p->birthYear = 0;
	p->spouse = NULL;
	destroyList(p->children);
	free(p);
}

char *
toString(struct person *p)
{
	char *nameStr = calloc(9, sizeof(char));
	snprintf(nameStr, 8, "%d", p->givenName);

	char *yearStr = calloc(9, sizeof(char));
	snprintf(yearStr, 8, "%d", p->birthYear);

	char *toReturn = calloc(strlen(nameStr) + strlen(yearStr) +
			strlen(p->surname) + 5, sizeof(char));

	strcpy(toReturn, nameStr);
	strcat(toReturn, " ");

	strcat(toReturn, p->surname);
	strcat(toReturn, " (");

	strcat(toReturn, yearStr);
	strcat(toReturn, ")");

	free(nameStr);
	nameStr = NULL;
	free(yearStr);
	yearStr = NULL;
	return toReturn;
}
