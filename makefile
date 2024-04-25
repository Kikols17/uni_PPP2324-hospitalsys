all: Doente_struct.o Registo_struct.o Data_struct.o
	echo "coco"




test_Doente_struct: Doente_struct.o
	gcc -Wall -Wextra Doente_struct.o -o Doente_struct

test_Registo_struct: Registo_struct.o
	gcc -Wall -Wextra Registo_struct.o -o Registo_struct

test_Data_struct: Data_struct.o
	gcc -Wall -Wextra Data_struct.o -o Data_struct




Doente_struct.o: Doente_struct.c Doente_struct.h
	gcc -Wall -Wextra -c Doente_struct.c

Registo_struct.o: Registo_struct.c Registo_struct.h
	gcc -Wall -Wextra -c Registo_struct.c

Data_struct.o: Data_struct.c Data_struct.h
	gcc -Wall -Wextra -c Data_struct.c



clean:
	rm -f *o
	rm -f Doente_struct Registo_struct Data_struct