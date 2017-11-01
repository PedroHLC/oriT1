/*
 *	Libraries
 ***********************************************************************/
#include <oriT1/utils.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
 *	Functions
 ***********************************************************************/
/* Cria o diretório informado */
void mkdir_p(char *dir) {
	char tmp[PATH_MAX];
	char *p = NULL;
	size_t len;

	snprintf(tmp, sizeof(tmp),"%s",dir);
	len = strlen(tmp);
	if(tmp[len - 1] == '/')
		tmp[len - 1] = 0;
	for(p = tmp + 1; *p; p++)
		if(*p == '/') {
			*p = 0;
			mkdir(tmp, S_IRWXU);
			*p = '/';
		}
	mkdir(tmp, S_IRWXU);
}

/* Obtém o PATH informado no arquivo */
void mkdir_file(char *file) {
	char path[PATH_MAX];
	strcpy(path, file);
	char *lp = strrchr(path, '/');
	if(lp != NULL) {
		*(lp+1) = 0;
		mkdir_p(path);
	}
}
