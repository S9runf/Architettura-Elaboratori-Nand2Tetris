#include "parser.h"

//leggi il prossimo comando
char * next_command(FILE *a)			
{
	char *curr = malloc(100 * sizeof(char)); 
	fscanf(a, "%s", curr);
	if(!feof(a))
	{
		if(strncmp(curr, "//", 2) == 0)				//se trova un commento 
		{
			fgets(curr, 100, a);					//legge fino alla fine della riga e restituisce una stringa vuota
			return("");
		}
		else 	
			return(curr);
	}
	else 
	{
		return("");									//se arriva alla fine del file restituisce una stringa vuota
	}
}

char command_type(char *a)	
{
	if(a[0] == '@')
		return('A');
	else if(a[0] == '(')
		return('L');
	else if(strcmp(a, "") && strcmp(a, "\n"))
		return('C');
	else 
		return('N');		//not a command
}

//controlla se il carattere richiesto si trova nella stringa in input 
int is_in(char * a, char x)				 
{
	//restituisce 0 se il carattere non è presente 
	int found = 0, i = 0;				
	while(i < strlen(a) && !found)
	{
	//se il carattere si trova nella stringa ne restituisce la posizione (!= indice)
		if(a[i] == x)
		{
			found = i+1;			
		}
		i++;
	}
	return(found);
}

//restituisce valore numerico o variabile di un A-command
char * symbol(char * a)					
{
	if(command_type(a) != 'A' && command_type(a) != 'L')
	{
		printf("errore: tipo di comando errato");
		return(NULL);						
	} 
	else if(command_type(a) == 'A')
	{
		//ignora "@"
		a = &a[1];					
		return(a);
	}
	else
	{
		// ignora "("
		a = &a[1]; 
		if(is_in(a, ')'))
		{
			char *res = malloc(strlen(a) * sizeof(char));
			for(int i = 0; i < strlen(a)-1; i++)
			{
				res[i] = a[i];
			}
			res[strlen(a)-1] = '\0';
			return(res);
		}
		else 
			printf("errore: dichiarazione etichetta incompleta");
			return(NULL);

	}

}

//restituisce mnemonic della destinazione di un C-command
char * destm (char *a) 					
{
	if(command_type(a) != 'C')
	{
		printf("errore: tipo di comando errato");
		return(NULL);
	}
	else
	{
		char *res = malloc(4 * sizeof(char));			
		int pos = is_in(a, '=');
		//se c'è "=" c'è una destinazione nel comando			
		if(pos)								
		{
			//scorri stringa fino al "="
			for(int i = 0; i < pos-1; i++)				
			{
				//copia caratteri prima del "=" 
				res[i] = a[i];
			}
			res[pos-1] = '\0';				
		}
		//se non c'è uguale non c'è destinazione nel comando
		else res = "";					
		return(res);
	}	
	
}

//restituisce mnemonic dell'espressione di un C-command
char * compm (char *a)						
{
	if(command_type(a) != 'C')
	{
		printf("errore: tipo di comando errato");
		return(NULL);
	}
	else 
	{
		char *res = malloc(4 * sizeof(char));
		int dst = is_in(a, '=');
		//leggi stringa da dopo "=" se c'è, altrimenti parti da 0	
		int i = dst;				
		//leggi fino a ";" (inizio jump), se c'è o fino alla fine della stringa			
		while(i < strlen(a) && a[i] != ';')			
		{
			res[i-dst] = a[i];
			i++;
		}
		res[i-dst] = '\0';

		return(res);
	}

}

//restituisce mnemonic del salto di un C-command
char * jumpm (char *a)							
{
	if(command_type(a) != 'C')
	{
		printf("errore: tipo di comando errato");
		return(NULL);
	}
	else 
	{
		char *res = malloc(4 * sizeof(char));
		int pos = is_in(a, ';');
		if(pos)						
		{
			//comincia a leggere comando dopo ";"					
			for(int i = pos; i < strlen(a); i++)
			{
				res[i-pos] = a[i];
			}
			res[3] = '\0';
		}
		//se non c'è ";" non c'è salto
		else res = "";						
		return(res);
	}
}

