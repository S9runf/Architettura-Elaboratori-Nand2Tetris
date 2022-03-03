#include "symbolTable.h"

pair predef[23] = 
{
	"SP", 0, "LCL", 1, "ARG", 2, "THIS", 3, "THAT", 4,
	"R0", 0, "R1", 1, "R2", 2, "R3", 3, "R4", 4, "R5", 5,
	"R6", 6, "R7", 7, "R8", 8, "R9", 9, "R10", 10,
	"R11", 11, "R12", 12, "R13", 13, "R14", 14, "R15", 15,
	"SCREEN", 16384, "KBD", 24576
};

//inizializza tabella con simboli predefiniti
sym * new_table()
{
	sym *tab = NULL;
	for(int i = 0; i < 23; i++)
	{
		sym *n = malloc(sizeof(sym));
		n->val = predef[i];
		n->next = tab;
		tab = n;
	}
	return(tab);
}

sym * new_symbol(char *label, int  addr)
{
	sym *x = malloc(sizeof(sym));
	x->val.label = label;
	x->val.address = addr;
	x->next = NULL;
	return(x);

}

//aggiunge simbolo in testa alla tabella
sym * add(sym *x, sym *head)
{
	x->next = head;
	head = x;
	return(head);
}

// restituisce indirizzo dell'elemento in input o -1 se non è presente
int contains(sym *head, char *x)
{
	int found = -1;
	sym *tmp = head;
	while(tmp != NULL && found == -1)
	{
		if (!strcmp(tmp->val.label, x))
		{
			found = tmp->val.address;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return(found);
}