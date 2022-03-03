#include "parser.h"

char *instructions[9] = {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};

//leggi il prossimo comando
char * next_command(FILE *a)			
{
	char *curr = malloc(100 * sizeof(char)); 
	fscanf(a, "%s", curr);
	if(!feof(a))
	{
		//se trova un commento legge fino alla fine della riga e restituisce una stringa vuota
		if(strncmp(curr, "//", 2) == 0)				
		{
			fgets(curr, 100, a);					
			return("");
		}
		else 	
			return(curr);
	}
	//se arriva alla fine del file restituisce una stringa vuota
	else 
	{
		return("");									
	}
}

int in_list(char *x, char *list[], int len)
{
	int i = 0, found = 0;
	while(i < len && found == 0)
	{
		if(strcmp(x, list[i]) == 0)
		{
			found = 1;
		}
		i++;
	}
	return(found);
}

char command_type(char *a)	
{
	if(in_list(a, instructions, 9))
		return('A');
	else if(strcmp(a, "pop") == 0)
		return('p');
	else if(strcmp(a, "push") == 0)
		return('P');
	else if(strcmp(a, "label") == 0)
		return('L');
	else if(strcmp(a, "function") == 0)
		return('F');
	else if(strcmp(a, "if-goto") == 0)
		return('I');
	else if(strcmp(a, "goto") == 0)
		return('G');
	else if(strcmp(a, "return") == 0)
		return('R');
	else if(strcmp(a, "call") == 0)
		return('C');
	else 
		return('N');		//not a command
}

char * arg1(FILE *a)			
{
	char *curr = malloc(100 * sizeof(char)); 
	fscanf(a, "%s", curr);
	return(curr);
}

int arg2(FILE *a)
{
	int x;
	fscanf(a, "%d", &x);
	return(x);
}	


