all: main.o Doente_struct.o Registo_struct.o Data_struct.o
	gcc -Wall -Wextra main.c Doente_struct.o Registo_struct.o Data_struct.o -o main




main.o: main.c
	gcc -Wall -Wextra -c main.c

Doente_struct.o: Doente_struct.c Doente_struct.h
	gcc -Wall -Wextra -c Doente_struct.c

Registo_struct.o: Registo_struct.c Registo_struct.h
	gcc -Wall -Wextra -c Registo_struct.c

Data_struct.o: Data_struct.c Data_struct.h
	gcc -Wall -Wextra -c Data_struct.c




clean:
	rm -f *o
	rm -f Doente_struct Registo_struct Data_struct main