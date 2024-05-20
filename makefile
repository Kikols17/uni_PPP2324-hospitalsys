all: main.o Commands.o Doente_struct.o Registo_struct.o Data_struct.o
	gcc -Wall -Wextra main.c Commands.o Doente_struct.o Registo_struct.o Data_struct.o -o main.exe


DOENTE_TEST: Doente_struct.o Data_struct.o
	gcc -Wall -Wextra -c DOENTES_TESTC.c
	gcc -Wall -Wextra DOENTES_TESTC.o Doente_struct.o Data_struct.o -o test.exe

REGISTO_TEST: Registo_struct.o Data_struct.o
	gcc -Wall -Wextra -c REGISTO_TESTC.c
	gcc -Wall -Wextra REGISTO_TESTC.o Registo_struct.o Data_struct.o -o test.exe

COMMANDS_TEST: Commands.o Doente_struct.o Registo_struct.o Data_struct.o
	gcc -Wall -Wextra -c COMMANDS_TESTC.c
	gcc -Wall -Wextra COMMANDS_TESTC.o Commands.o Doente_struct.o Registo_struct.o Data_struct.o -o test.exe




main.o: main.c
	gcc -Wall -Wextra -c main.c

Doente_struct.o: Doente_struct.c Doente_struct.h
	gcc -Wall -Wextra -c Doente_struct.c

Registo_struct.o: Registo_struct.c Registo_struct.h
	gcc -Wall -Wextra -c Registo_struct.c

Data_struct.o: Data_struct.c Data_struct.h
	gcc -Wall -Wextra -c Data_struct.c

Commands.o: Commands.c Commands.h
	gcc -Wall -Wextra -c Commands.c




clean:
	rm -f *o
	rm -f *.exe