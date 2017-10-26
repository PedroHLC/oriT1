#include <oriT1/utils.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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

void mkdir_file(char *file) {
	char path[PATH_MAX];
	strcpy(path, file);
	char *lp = strrchr(path, '/');
	if(lp != NULL) {
		*(lp+1) = 0;
		mkdir_p(path);
	}
}

void chdir_pwd() {
	char fname[PATH_MAX];
	readlink("/proc/self/exe", fname, PATH_MAX-1);
	char *lp = strrchr(fname, '/');
	if(lp != NULL) 
		*(lp+1) = 0;
	chdir(fname);
}