VMtranslator: VMtranslator.o parser.o codeWriter.o
	gcc -o VMtranslator VMtranslator.o parser.o codeWriter.o

VMtranslator.o: VMtranslator.c parser.h codeWriter.h
	gcc -c VMtranslator.c

parser.o: parser.c parser.h
	gcc -c parser.c

codeWriter.o: codeWriter.c codeWriter.h
	gcc -c codeWriter.c

clean:	
	rm *.o VMtranslator