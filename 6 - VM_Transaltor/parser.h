#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * next_command(FILE *a);	
char command_type(char *a);
int in_list(char *x, char *list[], int len);
char * arg1(FILE *a);
int arg2(FILE *a);	