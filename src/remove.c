/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/file.h> /* remove_() */

/*
 *	Main
 ***********************************************************************/
int main(int argc, char **argv) {
	/* Instruções de uso */
	if(argc != 3) {
		puts("oriT1.remove [nomedoarquivo] [chave]");
		return 1;
	}

	/* Remove um registro */
	remove_ (argv[1], argv[2]);

	return 0;
}
