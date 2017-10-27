#include <oriT1/utils.h>
#include <oriT1/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char FILE_NOT_FOUND[] = "ARQUIVO NAO EXISTE";

// Cria um arquivo vazio
bool create_empty(char *fname) {
	mkdir_file(fname);
	// Saudades monads... S2 FP
	FILE *file = fopen(fname, "w");
	if(file != NULL) {
		fclose(file);
		return true;
	} else
		return false;
}

int find_empty(FILE *file, Record *blockBuffer) {
	rewind(file);
	
	Record *worker;
	size_t readBytes;
	int targetRecord;
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		worker = blockBuffer;
		for(targetRecord = 0; targetRecord < RECORDS_PERBLOCK; targetRecord++) {
			if(worker->removed == true) {
				fseek(file, -BLOCK_SIZE, SEEK_CUR);
				return targetRecord;
			}
			worker++;
		}
	}
	
	return (readBytes == 0 ? -1 : -2);
}

void insert (Record newRecord, char *fname) {
	FILE *file = fopen(fname, "r+b");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}
	
	Record block[RECORDS_PERBLOCK];
	int recordIndex = find_empty(file, block);
	printf("ftell: %d, find_empty:%d\n", ftell(file), recordIndex);
	
	if(recordIndex < 0) {
		emptyBlock(block);
		block[0] = newRecord;
	} else {
		block[recordIndex] = newRecord;
	}
	
	fwrite(block, sizeof(Record), RECORDS_PERBLOCK, file);
	fclose(file);
}

void list (char *fname) {
	puts("KEY\tDUMMY\tFOO\tBAR");

	FILE *file = fopen(fname, "rb");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}

	Record blockBuffer[RECORDS_PERBLOCK], *worker, *end;
	size_t readBytes;
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		end = &blockBuffer[RECORDS_PERBLOCK];
		for(worker = blockBuffer; worker < end; worker++) {
			if(worker->removed == true) {
				puts("[REM]\t---\t---\t---");
			} else {
				printf("%s\t%s\t%s\t%s\n", worker->key, worker->dummy, worker->foo, worker->bar);
			}
		}
	}

	if(readBytes != 0)
		printf("BAD BLOCK AT EOF! %d\n", readBytes);

	fclose(file);
}

int find_entry(char *key, FILE *file, Record *blockBuffer) {
	rewind(file);
	
	Record *worker;
	size_t readBytes;
	int targetRecord;
	while (RECORDS_PERBLOCK == (readBytes = fread(blockBuffer, sizeof(Record), RECORDS_PERBLOCK, file))) {
		worker = blockBuffer;
		for(targetRecord = 0; targetRecord < RECORDS_PERBLOCK; targetRecord++) {
			if(worker->removed != true && strcmp(worker->key, key) == 0) {
				fseek(file, -BLOCK_SIZE, SEEK_CUR);
				return targetRecord;
			}
			worker++;
		}
	}
	
	return (readBytes == 0 ? -1 : -2);
}

void search (char *fname, char *key) {
	FILE *file = fopen(fname, "rb");
	if(file == NULL) {
		puts(FILE_NOT_FOUND);
		return;
	}
	
	Record block[RECORDS_PERBLOCK];
	int recordIndex = find_entry(key, file, block);
	printf("ftell: %d, find_entry:%d\n", ftell(file), recordIndex);
	
	if (recordIndex < 0)
		puts("Registro nao encontrado");
	else {
		puts("KEY\tDUMMY\tFOO\tBAR");
		Record *worker = &block[recordIndex];
		printf("%s\t%s\t%s\t%s\n", worker->key, worker->dummy, worker->foo, worker->bar);
	}
}