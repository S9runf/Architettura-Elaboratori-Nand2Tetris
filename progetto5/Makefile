assembler: assembler.o code.o parser.o symbolTable.o
	gcc -o assembler assembler.o parser.o code.o symbolTable.o

assembler.o: assembler.c parser.h code.h symbolTable.h
	gcc -c assembler.c

code.o: code.c code.h symbolTable.h
	gcc -c code.c

parser.o: parser.c parser.h
	gcc -c parser.c

SymbolTable.o: SymbolTable.c symbolTable.h
	gcc -c SymbolTable.c

clean: 
	rm *.o assembler
