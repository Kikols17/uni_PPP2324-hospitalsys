all: main.o Commands.o Doente_struct.o Registo_struct.o Data_struct.o
	gcc -Wall -Wextra main.c Commands.o Doente_struct.o Registo_struct.o Data_struct.o -o main.exe



files:
	> doentes.txt
	echo "1\nPaulo Silva\n3/10/2002\n04936886-7-ZX2\n960786543\npSilva@dei.uc.pt" >> doentes.txt
	echo "2\nAna Maria Silva\n30/10/2000\n04236786-7-ZX2\n939786543\nanaSilva@dei.uc.pt" >> doentes.txt
	echo "3\nJoao Silva\n3/10/2002\n04936896-7-ZX2\n960786543\njoao.s@gmail.com" >> doentes.txt

	> registos.txt
	echo "2\n23/5/2023\n125\n80\n56\n160" >> registos.txt
	echo "1\n6/1/2024\n128\n78\n55\n160" >> registos.txt
	echo "1\n1/5/2024\n120\n90\n56\n161" >> registos.txt
	echo "1\n5/5/2024\n121\n100\n56\n162" >> registos.txt




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




clean: files
	rm -f *o
	rm -f *.exe