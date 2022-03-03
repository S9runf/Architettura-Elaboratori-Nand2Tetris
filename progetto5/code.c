#include "code.h"
#include "symbolTable.h"


#define num_dest 8
#define num_comp 28
#define num_jmp 8

instr l_dest[num_dest] = 
{
	"", "000", "M", "001", "D", "010", "MD", "011",
	"A", "100", "AM", "101", "AD", "110", "AMD", "111"
};

instr l_comp[num_comp] =
{
	"0", "0101010", "1", "0111111", "-1", "0111010", "D", "0001100", "A", "0110000", "!D", "0001101",
	"!A", "0110001", "-D", "0001111", "-A", "0110011", "D+1", "0011111", "A+1", "0110111",  
	"D-1", "0001110", "A-1", "0110010", "D+A", "0000010", "D-A", "0010011",  "A-D", "0000111", 
	"D&A", "0000000", "D|A", "0010101","M", "1110000","!M", "1110001", "-M", "1110011","M+1", "1110111",
	"M-1", "1110010","D+M", "1000010","D-M", "1010011","M-D", "1000111","D&M", "1000000", "D|M", "1010101"
};

instr l_jmp[num_dest] = 
{
	"", "000", "JGT", "001", "JEQ", "010", "JGE", "011", 
	"JLT", "100", "JNE", "101", "JLE", "110", "JMP", "111"
};

//cerca binaries corrispondenti al mnemonic passato in input restituisce NULL se non li trova 
char * binary(char * a, instr x[], int len) {
	int i = 0;
	char *s = NULL; 
	while(i < len && s == NULL) 	//scorre tutta la lista di istruzioni
	{
		if (!strcmp(x[i].mnem, a))	//se il menmonic dell'elemento corrente == alla stringa in input
		{
			s = x[i].bin;							//risultato = binario corrispondente al mnemonic attuale
		}
		else 
			i++;
			
	}
	return(s);
}

char * dest(char *a)
{
	char *s = binary(a, l_dest, num_dest);
	return(s);
	
}



char * comp(char *a)
{
	char *s = binary(a, l_comp, num_comp);
	return(s);
	
}


char * jump( char *a)
{
	char *s = binary(a, l_jmp, num_jmp);
	return(s);

}


char * value(int x)
{
	int i = 0;
	char r[16] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
	char *s = malloc(sizeof(char[16]));
	for(int j = 0; j < 16; j++)
	{
		s[j] = r[j];
	}
	if(x != 0)
	{	
		while(x != 0)
		{
			if (x%2 != 0)
			{
				s[14-i] = '1';
			}
			x = x / 2;
			i++;
		}

	}
	return(s);
	

}



