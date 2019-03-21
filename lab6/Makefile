CFLAGS = -g -std=c99 -Wall -Werror -Wno-error=unused-variable

.PHONY: all clean
all: population test
clean:
	$(RM) population test *.o

population: population.o personList.o person.o
test: test.o person.o personList.o

population.o: personList.h names.h person.h
personList.o: personList.h names.h person.h personNode.h
person.o: person.h names.h personList.h
test.o: person.h names.h personList.h personNode.h
