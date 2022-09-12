#Compilador
CC = g++
#Active debug information
CFLAGS = -g -Wall
Target = ISAC-NAV

main: main.o lector.o radio.o
	$(CC) $(CFLAGS) -o ISAC-NAV Main.o Lector.o Radio.o

main.o: Main.cpp Data.h Lector.h Radio.h
	$(CC) $(CFLAGS) -c Main.cpp
	
lector.o: Data.h
	$(CC) $(CFLAGS) -c Lector.cpp
radio.o: Data.h
	$(CC) $(CFLAGS) -c Radio.cpp

clean: 
	rm Lector.o Main.o Radio.o $(Target) 
