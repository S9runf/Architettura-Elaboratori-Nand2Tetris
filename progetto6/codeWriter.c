#include "codeWriter.h"

char *push_c = "@SP\nM=M+1\nA=M-1\nM=D";
char *pop_c = "@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\nM=0\n@R13\nA=M\nM=D"; 
char *ar_bin = "@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\nA=M-1";		//arithmetic command binario

void push(char *a, int x, FILE* f, char *n)
{
	if(!strcmp(a, "constant"))
	{
		fprintf(f, "@%d\nD=A\n", x);
	}
	else if(!strcmp(a, "argument"))
	{
		fprintf(f, "@%d\nD=A\n@ARG\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "local"))
	{
		fprintf(f, "@%d\nD=A\n@LCL\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "static"))
	{
		fprintf(f, "@%s%d\nD=M\n", n, x); 
	}
	fprintf(f, "%s\n", push_c);


}

void pop(char *a, int x, FILE* f, char *n)
{
	if(!strcmp(a, "argument"))
	{
		fprintf(f, "@%d\nD=A\n@ARG\nD=D+M\n", x);
	}
	else if(!strcmp(a, "local"))
	{
		fprintf(f, "@%d\nD=A\n@LCL\nD=D+M\n", x);
	}
	else if(!strcmp(a, "static"))
	{
		fprintf(f, "@%s%d\nD=A\n", n, x);
	}
	fprintf(f, "%s\n", pop_c);

}


//counter utilizzato per nomi di etichette e variabili
int count = 0; 

void arithmetic(char *a, FILE *f)
{
	
	if(!strcmp(a, "add"))
	{
		fprintf(f, "%s\nM=M+D\n", ar_bin);
	}
	else if(!strcmp(a, "sub"))
	{
		fprintf(f,  "%s\nM=M-D\n", ar_bin);
		
	}
	else if(!strcmp(a, "neg"))
	{
		fprintf(f,  "@SP\nA=M-1\nM=-M\n");
	}
	else if(!strcmp(a, "eq"))
	{
		fprintf(f,  "%s\nD=M-D\nM=0\n@n%d\nD;JNE\n@SP\nA=M-1\nM=M-1\n(n%d)\n", ar_bin, count, count);
		count++;
	}
	else if(!strcmp(a, "gt"))
	{
		fprintf(f,  "%s\nD=M-D\nM=0\n@n%d\nD;JLE\n@SP\nA=M-1\nM=M-1\n(n%d)\n", ar_bin, count, count);
		count++;
	}
	else if(!strcmp(a, "lt"))
	{
		fprintf(f,  "%s\nD=M-D\nM=0\n@n%d\nD;JGE\n@SP\nA=M-1\nM=M-1\n(n%d)\n", ar_bin, count, count);
		count++;
	}
	else if(!strcmp(a, "and"))
	{
		fprintf(f,  "%s\nM=D&M\n", ar_bin);
	}
	else if(!strcmp(a, "or"))
	{
		fprintf(f,  "%s\nM=D|M\n", ar_bin);
	
	}
	else if(!strcmp(a, "not"))
	{
		fprintf(f,  "@SP\nA=M-1\nM=!M\n");
	
	}
}

void label(char *a, FILE *f)
{
	fprintf(f, "(%s)\n", a);
}

void go_to(char *a, FILE *f)
{
	fprintf(f, "@%s\n0;JMP\n", a);
}

void if_go_to(char *a, FILE *f)
{
	fprintf(f, "@SP\nA=M-1\nD=M\nM=0\n@SP\nM=M-1\n@%s\nD;JNE\n", a);
}

void call(char *a, int x, FILE * f)
{
	fprintf(f, "@RETURN%d\nD=A\n%s\n" //salva indirizzo di ritorno
				"@LCL\nD=M\n%s\n@ARG\nD=M\n%s\n@THIS\nD=M\n%s\n@THAT\nD=M\n%s\n" //salva indirizzi di LCL, ARG, THIS e THAT
				"@5\nD=A\n@%d\nD=D+A\n@SP\nD=M-D\n@ARG\nM=D\n" //indirizzo argomenti funzione corrente
				"@SP\nD=M\n@LCL\nM=D\n" //indirizzo variabili locali funzione corrente
				"@%s\n0;JMP\n(RETURN%d)\n", count, push_c, push_c, push_c, push_c, 	push_c, x, a, count );
	count++;
}


void function(char *a, int x, FILE *f)
{
	fprintf(f, "(%s)\n@%d\nD=A\n@SP\nM=M+D\n", a, x);	//alloca spazio per variabili locali
}


void ret(FILE *f)
{
	fprintf(f, "@LCL\nD=M\n@R13\nM=D\n@5\nD=A\n@R13\nA=M-D\nD=M\n@R14\nM=D\n" //recupera indirizzo di ritorno
				"@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\nD=A\n@SP\nM=D+1\n"  //mette risultato al posto del primo argomento sullo stack e sposta SP all'indirizzo successivo
				"@4\nD=A\n@R13\nA=M-D\nD=M\n@LCL\nM=D\n@3\nD=A\n@R13\nA=M-D\nD=M\n@ARG\nM=D\n" //ripristina LCL ed ARG al valore prima dell'invocazione 
				"@R14\nA=M\n0;JMP\n"); 	//ritorna al chiamante
}
