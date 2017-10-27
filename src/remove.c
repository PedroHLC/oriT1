#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 3) {
		puts("oriT1.remove [nomedoarquivo] [chave]");
		return 1;
	}

	if (remove (argv[1], argv[2]))
    puts("Registro removido");
  else
    puts("O registro não pode ser removido");

	return 0;
}
