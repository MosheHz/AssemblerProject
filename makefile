assembler: assembler.o macro.o checker.o process.o instruction.o label.o data.o replace.o out.o directive.o util.o
	gcc -g -ansi -pedantic -Wall assembler.o macro.o checker.o process.o instruction.o label.o data.o replace.o out.o directive.o util.o -o assembler 

assembler.o: assembler.c assembler.h 
	gcc -c -g -ansi -pedantic -Wall assembler.c -o assembler.o
macro.o: macro.c macro.h
	gcc -c -g -ansi -pedantic -Wall macro.c -o macro.o
checker.o: checker.c checker.h
	gcc -c -g -ansi -pedantic -Wall checker.c -o checker.o
process.o: process.c process.h
	gcc -c -g -ansi -pedantic -Wall process.c -o process.o
instruction.o: instruction.c instruction.h
	gcc -c -g -ansi -pedantic -Wall instruction.c -o instruction.o
label.o: label.c label.h
	gcc -c -g -ansi -pedantic -Wall label.c -o label.o
data.o: data.c data.h
	gcc -c -g -ansi -pedantic -Wall data.c -o data.o
replace.o: replace.c replace.h
	gcc -c -g -ansi -pedantic -Wall replace.c -o replace.o
out.o: out.c out.h
	gcc -c -g -ansi -pedantic -Wall out.c -o out.o
directive.o: directive.c directive.h
	gcc -c -g -ansi -pedantic -Wall directive.c -o directive.o
util.o: util.c util.h
	gcc -c -g -ansi -pedantic -Wall util.c -o util.o
