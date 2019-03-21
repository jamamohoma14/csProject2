/* personNode.h */

#ifndef PERSONNODE_H
#define PERSONNODE_H

#include "names.h"

struct personNode {
	struct person *datum;
	struct personNode *next;
};

#endif
