TARGET = barrier

# build an executable named myprog from myprog.c
all: $(TARGET).c 
	gcc -fopenmp -Wall -std=c99 -pg -ggdb $(TARGET).c -o $(TARGET)

clean: 
	$(RM) $(TARGET)