#include <oriT1/file.h>
#include <oriT1/records.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
	if(argc != 6) {
		puts("oriT1.insert [nomedoarquivo] [chave] [dummy] [foo] [bar]");
		return 1;
	}

	Record record;
	record.removed = false;
	strcpy(record.key, argv[2]);
	strcpy(record.dummy, argv[3]);
	strcpy(record.foo, argv[4]);
	strcpy(record.bar, argv[5]);

	insert(record, argv[1]);

	return 0;
}
