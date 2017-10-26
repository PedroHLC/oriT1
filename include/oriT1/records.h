#ifndef _ORIT1_RECORDS_H
#define _ORIT1_RECORDS_H	1

#include <stdbool.h>

typedef struct {
	bool removed;
	char key[10];
	char dummy[20];
	char foo[20];
	char bar[20];
} Record;

#define RECORDS_PERBLOCK 8
#define BLOCK_SIZE (sizeof(Record) * RECORDS_PERBLOCK)

void emptyBlock(Record*);


#endif