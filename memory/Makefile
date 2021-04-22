TARGET = memory

all: good_$(TARGET).c bad_$(TARGET).c
	gcc -fopenmp -Wall -std=c99 -ggdb good_$(TARGET).c -o good_$(TARGET)
	gcc -fopenmp -Wall -std=c99 -ggdb bad_$(TARGET).c -o bad_$(TARGET)

clean: 
	$(RM) good_$(TARGET)
	$(RM) bad_$(TARGET)