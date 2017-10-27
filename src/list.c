#include <oriT1/file.h>

int main(int argc, char **argv) {
	if(argc != 2) {
		puts("oriT1.list [nomedoarquivo]");
		return 1;
	}

	list(argv[1]);
	
	return 0;
}