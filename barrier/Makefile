TARGET = barrier

# build an executable named myprog from myprog.c
all: $(TARGET).c 
	gcc -fopenmp -Wall -std=c99 -pg -o $(TARGET) $(TARGET).c

clean: 
	$(RM) $(TARGET)