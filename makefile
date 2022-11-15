# Macros ========================================

CC=g++
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -O -Wconversion
DIR=gnu/

OBJECTS=$(DIR)driver.o $(DIR)List.o $(DIR)PRNG.o

DRMEMFLAGS=-static-libgcc -static-libstdc++ -ggdb 

EXE=gnu.exe

# Targets ========================================

$(DIR)$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(DIR)$(EXE)
	tablen -v *.cpp
	$(DIR)$(EXE) > myoutput.txt
	diff myoutput.txt output-all.txt --strip-trailing-cr

$(DIR)driver.o : driver.cpp $(DIR)List.o $(DIR)PRNG.o
	$(CC) $(CFLAGS) -c driver.cpp -o $(DIR)driver.o

$(DIR)List.o : List.cpp $(DIR)PRNG.o
	$(CC) $(CFLAGS) -c List.cpp -o $(DIR)List.o
	
$(DIR)PRNG.o : PRNG.cpp
	$(CC) $(CFLAGS) -c PRNG.cpp -o $(DIR)PRNG.o

clean :
	rm $(DIR)$(EXE) $(OBJECTS)

rebuild : 
	$(MAKE) clean
	$(MAKE)

drmemory :
	$(CC) List.cpp driver.cpp PRNG.cpp $(DRMEMFLAGS) -o $(EXE)
	drmemory $(EXE)
