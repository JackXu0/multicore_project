TARGET = critical_region

all: $(TARGET).c no_$(TARGET).c
	gcc -fopenmp -Wall -std=c99 -ggdb $(TARGET).c -o $(TARGET)
	gcc -fopenmp -Wall -std=c99 -ggdb no_$(TARGET).c -o no_$(TARGET)

clean: 
	$(RM) $(TARGET)
	$(RM) no_$(TARGET)