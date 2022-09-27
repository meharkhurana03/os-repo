a.out: test.o
	gcc -no-pie test.o


test.o: 2021541_A0.asm
	yasm 2021541_A0.asm -f elf64 -o test.o

all:
	yasm 2021541_A0.asm -f elf64 -o test.o
	gcc -no-pie test.o


