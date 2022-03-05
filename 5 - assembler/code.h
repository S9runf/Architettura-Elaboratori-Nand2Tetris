#include <string.h>
#include <stdlib.h>


typedef struct instr	
{
	char *mnem, *bin;	
}instr;

char * dest(char *a);
char * comp(char *a);
char * jump(char *a);
char * value(int x);
