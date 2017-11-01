/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/file.h> /* list() */

/*
 *	Main
 ***********************************************************************/
int main(int argc, char **argv) {
	/* Instruções de uso */
	if(argc != 2) {
		puts("oriT1.list [nomedoarquivo]");
		return 1;
	}

	/* Chama a função de listagem de registros */
	list(argv[1]);

	return 0;
}
