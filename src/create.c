#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 2) {
		puts("oriT1.create [nomedoarquivo]");
		return 1;
	}

	// Cria diretório quando não existe também
	bool result = create_empty(argv[1]);
	if(result) {
		puts("Arquivo criado com sucesso!");
		return 0;
	} else {
		puts("Não foi possível criar o arquivo.");
		return 2;
	}

}
