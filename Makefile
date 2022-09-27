test.o: assn1.s
	yasm assn1.s -f elf64 -o test.o

output: test.o
	gcc -no-pie test.o -o output

