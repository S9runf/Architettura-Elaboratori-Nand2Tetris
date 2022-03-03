#include "codeWriter.h"

int count = 0;

void push(char *a, int x, FILE* f, char *n)
{
	if(!strcmp(a, "constant"))
	{
		fprintf(f, "//Push C\n@%d\nD=A\n", x);
	}
	else if(!strcmp(a, "argument"))
	{
		fprintf(f, "//Push A\n@%d\nD=A\n@ARG\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "local"))
	{
		fprintf(f, "//Push L\n@%d\nD=A\n@LCL\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "static"))
	{
		fprintf(f, "//Push S\n@%s%d\nD=M\n", n, x); 
	}
	else if(!strcmp(a, "this"))
	{
		fprintf(f, "//Push THS\n@%d\nD=A\n@THIS\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "that"))
	{
		fprintf(f, "//Push THT\n@%d\nD=A\n@THAT\nA=M+D\nD=M\n", x);
	}
	else if(!strcmp(a, "pointer"))
	{
		if(x == 0)
		{
			fprintf(f, "//Push Point1\n@THIS\nD=M\n");
		}
		else if(x == 1)
		{
			fprintf(f, "//Push Point2\n@THAT\nD=M\n");
		}
	}
	else if(!strcmp(a, "temp"))
	{
		fprintf(f, "//Push TMP\n@%d\nD=A\n@5\nA=A+D\nD=M\n", x);                           
	}
	fprintf(f, "@SP\nM=M+1\nA=M-1\nM=D\n");
}

void pop(char *a, int x, FILE* f, char *n)
{
	if(!strcmp(a, "pointer"))
	{
		fprintf(f, "//Pop point\n@POP_R%d\nD=A\n", count);
		if(x == 0)
		{
			fprintf(f, "@THS\n0;JMP\n");
		}
		else if(x == 1)
		{
			fprintf(f, "@THT\n0;JMP\n");
		}
		fprintf(f, "(POP_R%d)\n", count);
	}
	else
	{
		fprintf(f, "//Pop\n@POP_R%d\nD=A\n@R14\nM=D\n", count);
		if(!strcmp(a, "argument"))
		{
			fprintf(f, "//A\n@%d\nD=A\n@ARG\nD=D+M\n", x);
		}
		else if(!strcmp(a, "local"))
		{
			fprintf(f, "//L\n@%d\nD=A\n@LCL\nD=D+M\n", x);
		}
		else if(!strcmp(a, "static"))
		{
			fprintf(f, "//S\n@%s%d\nD=A\n", n, x);
		}
		else if(!strcmp(a, "this"))
		{
			fprintf(f, "//THS\n@%d\nD=A\n@THIS\nD=D+M\n", x);
		}
		else if(!strcmp(a, "that"))
		{
			fprintf(f, "//THT\n@%d\nD=A\n@THAT\nD=D+M\n", x);
		}
		else if(!strcmp(a, "temp"))
		{
			fprintf(f, "//TMP\n@%d\nD=A\n@5\nD=D+A\n", x);
		}
		fprintf(f, "@POP\n0;JMP\n(POP_R%d)\n", count);
		
	}
	count++;
}

void arithmetic(char *a, FILE *f)
{	
	if(!strcmp(a, "neg"))
	{
		fprintf(f,  "//NEG\n@SP\nA=M-1\nM=-M\n");
	}
	else if(!strcmp(a, "not"))
	{
		fprintf(f,  "//NOT\n@SP\nA=M-1\nM=!M\n");
	}
	else 
	{
		if(!strcmp(a, "add"))
		{
			fprintf(f, "//ADD\n@ADD_R%d\nD=A\n@ADD\n0;JMP\n(ADD_R%d)\n", count, count);
		}				
		else if(!strcmp(a, "sub"))
		{
			fprintf(f,  "//SUB\n@SUB_R%d\nD=A\n@SUB\n0;JMP\n(SUB_R%d)\n", count, count);
		}
		else if(!strcmp(a, "and"))
		{
			fprintf(f,  "//AND\n@AND_R%d\nD=A\n@AND\n0;JMP\n(AND_R%d)\n", count, count);
		}
		else if(!strcmp(a, "or"))
		{
			fprintf(f,  "//OR\n@OR_R%d\nD=A\n@OR\n0;JMP\n(OR_R%d)\n", count, count);
		}
		if(!strcmp(a, "eq"))
		{
			fprintf(f,  "//EQ\n@n%d\nD=A\n@EQ\n0;JMP\n(n%d)\n", count, count);
		}
		else if(!strcmp(a, "gt"))
		{
			fprintf(f,  "//GT\n@n%d\nD=A\n@GT\n0;JMP\n(n%d)\n", count, count);
		}
		else if(!strcmp(a, "lt"))
		{
			fprintf(f,  "//LT\n@n%d\nD=A\n@LT\n0;JMP\n(n%d)\n", count, count);
		}
		count++;
	}

}

void label(char *a, char *n, FILE *f)
{
	fprintf(f, "(%s%s)\n", n, a);
}

void go_to(char *a, char *n, FILE *f)
{
	fprintf(f, "//goto\n@%s%s\n0;JMP\n", n, a);
}

void if_go_to(char *a, char *n, FILE *f)
{
	fprintf(f, "//if\n@IF%d\nD=A\n@IF\n0;JMP\n(IF%d)\n@%s%s\nD;JNE\n", count, count, n, a);
	count++;
}

void call(char *a, int x, FILE * f)
{
	fprintf(f, "//call\n@RETURN%d\nD=A\n@R13\nM=D\n"   //salva indirizzo di ritorno in R13	
				"(call_%s)\n@%s\nD=A\n@R14\nM=D\n"		//salva indirizzo funzione in R14
				"@%d\nD=A\n" 				//salva numero argomenti funzione corrente in D
				"@CALL\n0;JMP\n(RETURN%d)\n", count, a, a, x, count);
	count++;
}


void function(char *a, int x, FILE *f)
{
	fprintf(f, "//funct\n(%s)\n@%d\nD=A\n@R14\nM=D\n@F%d\nD;JEQ\nD=A\n@FUNCT\n0;JMP\n(F%d)\n", a, x, count, count);	//alloca spazio per variabili locali
	count++;
}

void ret(FILE *f)
{
	fprintf(f, "(RETURNS)\n@LCL\nD=M\n@R13\nM=D\n@5\nD=A\n@R13\nA=M-D\nD=M\n@R14\nM=D\n" //recupera indirizzo di ritorno
				"@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\nD=A\n@SP\nM=D+1\n"  //mette risultato al posto del primo argomento sullo stack e sposta SP all'indirizzo successivo
				"@4\nD=A\n@R13\nA=M-D\nD=M\n@LCL\nM=D\n@3\nD=A\n@R13\nA=M-D\nD=M\n@ARG\nM=D\n"	//ripristina LCL, ARG,
				"@2\nD=A\n@R13\nA=M-D\nD=M\n@THIS\nM=D\n@1\nD=A\n@R13\nA=M-D\nD=M\n@THAT\nM=D\n" 	//THIS e THAT al valore prima dell'invocazione 
				"@R14\nA=M\n0;JMP\n"); 	//ritorna al chiamante
}
