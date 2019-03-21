/* population.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "personList.h"
#include "person.h"


/* fraction of single adults who get married per year */
double marriageRate = .3;

/* fraction of married females who give birth per year */
double birthRate = .16;

/* fraction of people who die (not because of age) per year */
double prematureDeathRate = .01;

/* fraction of birth per year which produce two children */
double twinRate = .15;

/* the age at which a person can become married */
int marriageAge = 18;

/* the age at which a person "dies" of old age */
int ageLimit = 40;

/* naming policy; 0 = patriarchal, 1 = savant, 2 = antisavant */
int namingPolicy;

char *surnames[] = { "VanDrunen", "Potoshnick", "Tapply", "Bierma",
                     "Lagastee", "Junkman", "Morgridge", "Langley", "Ackersen",
                     "Tobin", "Horton", "Powell", "Leman", "Vander Veen", "Tan",
                     "Pohly", "Brabenec", "Vanderschoot", "Diedrichs", "Kim", 
                     "Perciante", "VanDrunen", "Delzell", "Isihara", "Lovett",
                     "Pierotti", "Cantor", "Euler", "Gauss", "Leibniz",
                     "Newton", "Fourier", "Poisson", "Turing", "McCarthy",
                     "Hopper", "Hoare", "Wirth", "Calvin", "Luther", "Zwingli",
                     "Knox", "Bucer", "Farel", "Beza", "Bullinger",
                     "Obama", "Bush", "Clinton", "Reagan", "Carter", "Ford",
                     "Nixon", "Johnson", "Kennedy", "Eisenhower", "Truman",
                     "Roosevelt", "Hoover", "Coolidge", "Harding"};
const int TOTAL_NAMES = sizeof(surnames) / sizeof(surnames[0]);

char *chooseChildName(struct person *father, struct person *mother, int gender);


int main(int argc, char **argv)
{
	int i, j;

	/* Process the flags */
	for (i = 1; i < argc; i+=2)
	{
		char *flag = argv[i];

		if (strcmp(flag, "-p") == 0)
		{ namingPolicy = 0; i--; }
		else if (strcmp(flag, "-s") == 0)
		{ namingPolicy = 1; i--; }
		else if (strcmp(flag, "-as") == 0)
		{ namingPolicy = 2; i--; }
		else 
		{

			float val = atof(argv[i+1]);

			if (strcmp(flag, "-mr") == 0)
				marriageRate = val;
			else if (strcmp(flag, "-br") == 0)
				birthRate = val;
			else if (strcmp(flag, "-pdr") == 0)
				prematureDeathRate = val;
			else if (strcmp(flag, "-tr") == 0)
				twinRate = val;
			else if (strcmp(flag, "-ma") == 0)
				marriageAge = val;
			else if (strcmp(flag, "-al") == 0)
				ageLimit = val;
		}
	}

	/*  variable to keep track of "given names" */
	int nameGen = 0;

	/* the population itself */
	struct personList *population = makeList();

	/* make initial population of 300 19-year-olds, 
	   5 for each surname  */
	for (i = 0; i < TOTAL_NAMES; i++)
		for (j = 0; j < 5; j++)
			add(population, makePerson(nameGen++, surnames[i],
						easyRand(2), -19));


	/* for 500 years....  */
	for (i = 0; i < 500; i++) {

		/* ---- births ---- */
		/* find all married females */
		struct personList *marriedFemales = getMarriedFemales(population);
		int numMarriedFemales = marriedFemales->size;

		/* generate a random child for a certain fraction of them */
		for (j = 0; j < birthRate  *numMarriedFemales; j++) {
			struct person *mother = getRandom(marriedFemales); /* child's mother */
			removePerson(marriedFemales, mother);
			struct person *father = mother->spouse;  /* child's father */
			int gender = easyRand(2);   /* child's gender */
			char *childSurname = chooseChildName(father, mother, gender); 
			struct person *child =   /* the child itself */
				makePerson(nameGen++, childSurname, gender, i);
			addChild(mother, child);
			addChild(father, child);
			add(population, child);

			/* based on the twin rate, randomly generate
			   a random second child for some  */
			if (easyRandF() < twinRate) {
				gender = easyRand(2);
				childSurname = chooseChildName(father, mother, gender);
				child = makePerson(nameGen++, childSurname, gender, i);
				addChild(mother, child);
				addChild(father, child);
				add(population, child);
			}
		}
		destroyList(marriedFemales);
		marriedFemales = NULL;

		/* ---- marriages ----*/
		/* find all marriagble females and males */
		struct personList *availableFemales = 
			getMarriableFemales(population, i - marriageAge);
		struct personList *availableMales = 
			getMarriableMales(population, i -  marriageAge);
		int numAvailableFemales = availableFemales->size;

		/* based on the marriage rate, marry off that many
		   available females, assuming there are sufficient
		   available males   */

		for (j = 0; j < numAvailableFemales  *marriageRate && 
				availableMales->size > 0; 
				j++) 
		{
			struct person *bride = getRandom(availableFemales);  /* female to marry */
			removePerson(availableFemales, bride);
			struct person *groom = getRandom(availableMales);   /* male to marry */
			removePerson(availableMales, groom);
			bride->spouse = groom;
			groom->spouse = bride;
		}
		destroyList(availableFemales);
		availableFemales = NULL;
		destroyList(availableMales);
		availableMales = NULL;

		/* ---- premature deaths ---- */
		/* remove a certain percentage of the population */
		int popSize = population->size;
		for (j = 0; j < popSize  *prematureDeathRate; j++) 
		{
			struct person *toDie = getRandom(population);  /* person that we're removing */
			removePerson(population, toDie);
			/* this person's spouse is now single */
			if (toDie->spouse != NULL)
				toDie->spouse->spouse = NULL;

			destroyPerson(toDie);
		}

		/* ---- deaths of "old age" ---- */
		/* remove all individuals older than a certain age */
		struct personList *deadList = removeAllAge(population, i - ageLimit);
		struct person **deadArray = toArray(deadList);
		/* their spouses are now single */
		for (j = 0; j < deadList->size; j++)
		{
			if (deadArray[j]->spouse != NULL)
				deadArray[j]->spouse->spouse = NULL;
			destroyPerson(deadArray[j]);
			deadArray[j] = NULL;
		}
		/* every 10 years, report statistics */
		if (i % 10 == 0) 
		{
			printf("Year %d:\n", i);
			printStats(population, i - marriageAge);
		}
		destroyList(deadList);
		deadList = NULL;
		free(deadArray);
		deadArray = NULL;
	}


	/* --- uncomment the following section for part 5 --- */


	/* Now, after 500 years, report on surname statistics.
	   These two arrays represent the number of females and males,
	   respectively, in the population with the various possible surnames.
	   For example, femalesPerName[10] is the number of Person objects
	   in the population which are female and have whatever surname is
	   in surname[10].
	   */
	int *femalesPerName = (int*) calloc(sizeof(int), TOTAL_NAMES);
	int *malesPerName = (int*) calloc(sizeof(int), TOTAL_NAMES);

	/* We want to iterate through the population ourselves
	   (ie, here in the main methond, not in the PersonList class),
	   so we put the Person objects into an array.  */

	struct person **finalPopulation = toArray(population);

	for (i = 0; i < population->size; i++) 
	{
		/* current surname */
		char *surname = finalPopulation[i]->surname;
		j = 0;
		while (strcmp(surnames[j], surname)) j++;
		if (finalPopulation[i]->gender)
			femalesPerName[j]++;
		else
			malesPerName[j]++;

	}
	/* report on the number of individuals and fraction female/male
	   for each surname */
	for (i = 0; i < TOTAL_NAMES; i++) 
	{
		int numOfName = femalesPerName[i] + malesPerName[i];
		printf("%s : %d", surnames[i], numOfName);
		if (numOfName != 0)
			printf(" (%f/%f)\n", ((double) femalesPerName[i] / numOfName),
					((double) malesPerName[i] / numOfName));
		else
			printf("\n");


	}

	destroyList(population);
	free(femalesPerName);
	femalesPerName = NULL;
	free(malesPerName);
	malesPerName = NULL;
	free(finalPopulation);
	finalPopulation = NULL;

	return 0;
}

char *chooseChildName(struct person *father, struct person *mother, int gender)
{
	// Adjust this in part 4
	return father->surname; 
}
