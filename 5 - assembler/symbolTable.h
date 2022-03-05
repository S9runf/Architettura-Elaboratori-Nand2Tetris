#include <stdlib.h>
#include <string.h>

typedef struct pair
{
	char *label;
	int address;

}pair;
typedef struct sym 
{
	pair val;
	struct sym * next;
}sym;

sym * new_table();
sym * new_symbol(char *label, int  addr);
sym * add(sym *x, sym *head);
int contains(sym *head, char *val);

