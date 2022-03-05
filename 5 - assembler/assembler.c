#include "parser.h"
#include "code.h"
#include "symbolTable.h"

//controlla se x è un valore numerico
int is_num(char *x)		
{
	int num = 1;
	for(int i = 0; i < strlen(x); i++)
	{
		if (x[i] < 48 || x[i] > 57)
		{
			num = 0;
			break;
		}
	}
	return(num);
}

//locazione da assegnare alle variabili
int location = 16;

int main(int argc, char *argv[])
{
	
	char fo[strlen(argv[1])+1];		  	//secondo file = argomento - esetnsione (asm) 
	strncpy(fo, argv[1], strlen(argv[1]) - 3);
	fo[strlen(argv[1])-3] = '\0';
	strcat(fo, "hack");				//esetnsione secondo file

	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(fo, "w");

	//tabella con simboli predefiniti
	sym *tab = new_table();
	//contatore locazioni etichette
	int count = 0;

	//prima passata
	while(!feof(fin))
	{
		char *curr = next_command(fin);
		if(command_type(curr) != 'L' && command_type(curr) != 'N')
		{
			count++;
		}
		else if (command_type(curr) == 'L')
		{ 
			sym *x = new_symbol(symbol(curr), count);
			tab = add(x, tab);
		}
		
	}
	fclose(fin);
	

	fin = fopen(argv[1], "r");
	count = 0;

	//seconda passata
	while(!feof(fin))
	{
		char *curr = next_command(fin);
		count++;
		if (command_type(curr) == 'A')
		{	
			char *n;
			int y;
			n = symbol(curr);
			if(!is_num(n))
			{	
				
				if(contains(tab, n) != -1)	//se n è un etichetta assegna ad y l'indirizzo di n nella tabella
					y = contains(tab, n);
				else						//se n è una variabile, aggiunge n alla tabella 
				{
					tab = add(new_symbol(n, location), tab); 	//indirizzo di n == location corrente
					y = location;
					location++;			//prossima location disponibile
				}
			}
			else 			//se n è un numero assegna ad y il suo valore
			{
				y = atoi(n);
			}
			fprintf(fout, "0%s\n", value(y));	
			
		}
		else if(command_type(curr) == 'C')
		{
			if(dest(destm(curr)) == NULL)
			{
				printf("errore, riga %d: destinazione non valida", count);
				break;
			}
			else if(comp(compm(curr)) == NULL)
			{
				printf("errore riga %d: espressione non valida", count);
				break;
			}
			else if(jump(jumpm(curr)) == NULL)
			{
				printf("errore riga %d: salto non valido", count);
				break;
			}
			else
			fprintf(fout, "111%s%s%s\n", comp(compm(curr)), dest(destm(curr)), jump(jumpm(curr)));


		}
	}
	fclose(fin);
	fclose(fout);
	return(0);
}