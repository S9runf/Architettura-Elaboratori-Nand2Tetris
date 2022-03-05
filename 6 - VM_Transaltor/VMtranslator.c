#include "parser.h"
#include "codeWriter.h"

int main(int argc, char *argv[])
{
	//secondo file = argomento - esetnsione (vm) + 1 (estensione secondo file = asm)
	char fo[strlen(argv[1])+2];		  	
	strncpy(fo, argv[1], strlen(argv[1]) - 2);
	fo[strlen(argv[1])-2] = '\0';
	//salva nome file per segmento static
	char filename[strlen(fo)+1]; 
	strcpy(filename, fo);
	//aggiunge esensione al nome del file
	strcat(fo, "asm");

	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(fo, "w");
	
	fprintf(fout, "@256\nD=A\n@SP\nM=D\n");		//mette SP all'inizio dello stack

	while(!feof(fin))
	{
		
		char *curr = next_command(fin);
		char ct = command_type(curr);
		//scrive comandi in assembly in base al tipo dell'istruzione vm
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
				label(arg1(fin), fout);
			}
			else if(ct == 'G')
			{
				go_to(arg1(fin), fout);
			}
			else if(ct == 'I')
			{
				if_go_to(arg1(fin), fout);
			}
			else if(ct == 'C')
			{
				call(arg1(fin), arg2(fin), fout);
			}
			else if(ct == 'F')
			{
				function(arg1(fin), arg2(fin), fout);
			}
			else if(ct == 'R')
			{
				ret(fout);
			}
			

		}
	}

	fclose(fin);
	fclose(fout);
	return(0);
}