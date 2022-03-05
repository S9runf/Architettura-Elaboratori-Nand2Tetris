#include <dirent.h>
#include "parser.h"
#include "codeWriter.h"

typedef struct functions 
{
	char nome[50];
	struct functions * next;
}functions;

functions * head_insert(functions * head, char n[])
{
	functions * tmp = malloc(sizeof(functions));
	strcpy(tmp->nome, n);
	tmp->next = head;
	return(tmp);
}

//lista di funzioni già chiamate
functions * used  = NULL;

int called(char n[])
{
	if(used == NULL)
	{
		return(0);
	}
	else
	{
		functions * tmp = used; 
		int found = 0;
		while(tmp != NULL)
		{
			if(!strcmp(tmp->nome, n))
			{
				found = 1;
			}
			tmp = tmp->next;
		}
		return(found);	
	}
}

int counter = -1;

int main(int argc, char *argv[])
{
  DIR *folder;
    struct dirent *entry;
	//secondo file = nome directory + esetnsione .asm
	char fo[strlen(argv[1])+5];
	//copia nome directory	
    strcpy(fo, argv[1]);
	//aggiunge estensione
	strcat(fo, ".asm");


	//apre file output
	FILE *fout = fopen(fo, "w");
	

	//mette SP all'inizio dello stack
	fprintf(fout, "@256\nD=A\n@SP\nM=D\n");

	//salta a sys.init
	fprintf(fout, "@Sys.init\n0;JMP\n");

	//call utilizzato da tutte le funzioni del programma
	fprintf(fout, "(CALL)\n@R15\nM=D\n"
					"@R13\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n" //salva indirizzo di ritorno nello stack
					"@LCL\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n@ARG\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n" 	//salva indirizzi di LCL, ARG,
					"@THIS\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n@THAT\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n" //THIS e THAT nello stack";
					"@5\nD=A\n@R15\nD=D+M\n@SP\nD=M-D\n@ARG\nM=D\n"		//indirizzo argomenti funzione corrente in ARG
					"@SP\nD=M\n@LCL\nM=D\n" //indirizzo parametri locali funzione corrente
					"@R14\nA=M\n0;JMP\n");	//salta alla funzione

	//return utilizzato da tutte le funzioni del programma
	ret(fout);

	//codice riutilizzabile stampato una volta sola

	fprintf(fout, "(ADD)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nM=M+D\n@R13\nA=M\n0;JMP\n"
	 				"(SUB)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nM=M-D\n@R13\nA=M\n0;JMP\n"
	 				"(AND)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nM=M&D\n@R13\nA=M\n0;JMP\n"
	 				"(OR)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nM=M|D\n@R13\nA=M\n0;JMP\n"
					"(EQ)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nD=M-D\nM=-1\n@FALSE\nD;JNE\n@R13\nA=M\n0;JMP\n"
					"(GT)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nD=M-D\nM=-1\n@FALSE\nD;JLE\n@R13\nA=M\n0;JMP\n"
					"(LT)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1\nD=M-D\nM=-1\n@FALSE\nD;JGE\n@R13\nA=M\n0;JMP\n"
					"(FALSE)\n@SP\nA=M-1\nM=0\n@R13\nA=M\n0;JMP\n");
				

	fprintf(fout, "(FUNCT)\n@R13\nM=D\n@R14\nD=M\n(F_LOOP)\n@SP\nM=M+1\nA=M-1\nM=0\nD=D-1\n@F_LOOP\nD;JGT\n@R13\nA=M\n0;JMP\n");
	fprintf(fout, "(IF)\n@R13\nM=D\n@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\n@R13\nA=M\n0;JMP\n");
	fprintf(fout, "(POP)\n@R13\nM=D\n@SP\nAM=M-1\nD=M\nM=0\n@R13\nA=M\nM=D\n@R14\nA=M\n0;JMP\n"
					"(THS)\n@R14\nM=D\n@THIS\nD=A\n@POP\n0;JMP\n"
					"(THT)\n@R14\nM=D\n@THAT\nD=A\n@POP\n0;JMP\n");


    //apre directory passata come argomento
    folder = opendir(argv[1]);

    //legge elementi della directory
    while((entry=readdir(folder)))
    {
        //traduzione comincia solo se l'elemento corrente è un file
        if(entry->d_type == 8)
        {
			//nome file per segmento static
			char filename[strlen(entry->d_name)-1];
			strncpy(filename, entry->d_name, strlen(entry->d_name)-2);
			filename[strlen(entry->d_name)-2] = '\0';

			//path del file nella directory
			char input[strlen(argv[1]) + strlen(entry->d_name) + 2];
			strcpy(input, argv[1]);
			strcat(input, "/");
			strcat(input, entry->d_name);


			//apre file presenti nella directory
			FILE *fin = fopen(input, "r");
			
			while(!feof(fin))
			{
				char *funz;
				char *curr = next_command(fin);
				char ct = command_type(curr);
				if(ct != 'N')
				{
					if(ct == 'P')
					{
						push(arg1(fin), arg2(fin), fout, filename);	
					}
					else if(ct == 'p')
					{
						pop(arg1(fin), arg2(fin), fout, filename);
					}
					else if(ct == 'A')
					{
						arithmetic(curr, fout);
					}
					else if(ct == 'L')
					{
						label(arg1(fin), funz, fout);
					}
					else if(ct == 'G')
					{
						go_to(arg1(fin), funz, fout);
					}
					else if(ct == 'I')
					{
						if_go_to(arg1(fin), funz, fout);
					}
					else if(ct == 'C')
					{
						//se la funzione non è mai stata chiamata stampa la call
						char *funct = arg1(fin);
						if(!called(funct))
						{
							call(funct, arg2(fin), fout);
							used = head_insert(used, funct);
						}
						//se è già stata chiamata riutilizza chiamata già stampata
						else 
						{
							//cambia indirizzo di ritorno
							fprintf(fout, "@RETURN%d\nD=A\n@R13\nM=D\n@call_%s\n0;JMP\n(RETURN%d)\n", counter, funct, counter);
							counter--;
						}
					}
					else if(ct == 'F')
					{
						funz = arg1(fin);
						function(funz, arg2(fin), fout);
					}
					else if(ct == 'R')
					{
						fprintf(fout, "@RETURNS\n0;JMP\n");
					}
				}
						
			}
           fclose(fin);
        }
	}

    closedir(folder);
   	fclose(fout);
    return(0);
}