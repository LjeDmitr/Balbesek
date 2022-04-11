.PHONY: all clean

TARGET = SimpleComputer
BIN = main4.o SC.o myTerm.o BigChars.o myReadkey.o

all: $(TARGET)

SC.o: SC.c
		gcc -Wall -c -o SC.o SC.c
myTerm.o: myTerm.c
		gcc -Wall -c -o myTerm.o myTerm.c
BigChars.o: BigChars.c
		gcc -Wall -c -o BigChars.o BigChars.c
myReadkey.o: myReadkey.c
		gcc -Wall -c -o myReadkey.o myReadkey.c
main4.o: main4.c
		gcc -Wall -c -o main4.o main4.c			
$(TARGET): $(BIN)
		gcc -Wall -g -o $(TARGET) $(BIN)
clean:
		rm -rf $(TARGET)
		rm -rf *.o