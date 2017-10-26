#include <oriT1/utils.h>
#include <oriT1/file.h>

int main(int argc, char **argv) {
	chdir_pwd();

	if(argc != 2) {
		puts("oriT1.list [nomedoarquivo]");
		return 1;
	}

	list(argv[1]);
	
	return 0;
}