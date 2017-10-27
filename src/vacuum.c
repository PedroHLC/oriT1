#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 2) {
		puts("oriT1.vacuum [nomedoarquivo]");
		return 1;
	}

	vacuum(argv[1]);
}
