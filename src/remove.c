#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 3) {
		puts("oriT1.remove [nomedoarquivo] [chave]");
		return 1;
	}

	remove_ (argv[1], argv[2]);

	return 0;
}
