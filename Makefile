out: main.o matrix.o
	gcc -o out main.o matrix.o

main.o: main.c
	gcc -c main.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

clean:
	rm *.o out //remove todos os arquivos com extensão .o e o arquivo out que é gerado