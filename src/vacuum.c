/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/file.h> /* vacuum() */

/*
 *	Main
 ***********************************************************************/
int main(int argc, char **argv) {
	/* Instruções de uso */
	if(argc != 2) {
		puts("oriT1.vacuum [nomedoarquivo]");
		return 1;
	}

	/* Chama a função de compactação */
	vacuum(argv[1]);
}
