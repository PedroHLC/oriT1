/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/records.h>
#include <stdbool.h>

/*
 *	Functions
 ***********************************************************************/
/* Limpa um registro */
void emptyBlock(Record* block) {
	Record *worker, *end = &block[8];
	for(worker = block; worker < end; worker++)
		*worker = (Record){true, "", "", "", ""};
}
