# Example Makefile 

CC=gcc -Wall 
CLIB=-lgps

dcgps: dcgps.o gps-utils.o gpsprint.o
	$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o $(CLIB)

clean:
	rm -f *.o core.* dcgps
dcgps.o: dcgps.c
	$(CC) -c dcgps.c 
gps-utils.o: gps-utils.h gps-utils.c
	$(CC) -c gps-utils.c
gpsprint.o: gpsprint.h gpsprint.c
	$(CC) -c gpsprint.c
