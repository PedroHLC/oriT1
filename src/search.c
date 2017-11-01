/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/file.h> /* search() */

/*
 *	Main
 ***********************************************************************/
int main(int argc, char **argv) {
	/* Instruções de uso */
	if(argc != 3) {
		puts("oriT1.search [nomedoarquivo] [chave]");
		return 1;
	}

	/* Busca por um registro */
	search (argv[1], argv[2]);

	return 0;
}
