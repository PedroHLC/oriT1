#include <oriT1/utils.h>
#include <oriT1/file.h>
#include <oriT1/records.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

void emptyBlock(Record* block) {
	Record *worker, *end = &block[8];
	for(worker = block; worker < end; worker++)
		*worker = (Record){true, "", "", "", ""};
}