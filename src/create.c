/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/file.h> /* create_empty() */

/*
 *	Main
 ***********************************************************************/
int main(int argc, char **argv) {
	/* Instruções de uso */
	if(argc != 2) {
		puts("oriT1.create [nomedoarquivo]");
		return 1;
	}

	/* Cria o arquivo  no sistema */
	bool result = create_empty(argv[1]);
	if(result) {
		puts("Arquivo criado com sucesso!");
		return 0;
	} else {
		puts("Não foi possível criar o arquivo.");
		return 2;
	}

}
