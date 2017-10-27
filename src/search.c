#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 3) {
		puts("oriT1.search [nomedoarquivo] [chave]");
		return 1;
	}

	search (argv[1], argv[2]);
	
	return 0;
}