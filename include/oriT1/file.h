#ifndef _ORIT1_FILES_H
#define _ORIT1_FILES_H	1

#include <stdio.h>
#include <stdbool.h>
#include "records.h"

bool create_empty(char *);
int find_empty(FILE *, Record *);
void insert (Record , char *);
void list (char *);
void search (char *, char *);
void remove_ (char *, char *);
void vacuum (char *);

#endif