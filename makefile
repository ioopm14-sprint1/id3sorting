COMPILER = gcc -std=c99
BUILD_FLAGS = -Wall -ggdb -c
LINK_FLAGS = -Wall -ggdb -o
TARGET = bin/main


main: main.o id3.o
	mkdir -p bin
	$(COMPILER) $(LINK_FLAGS) $(TARGET) main.o id3.o
	./$(TARGET)

id3.o: source/id3.c source/id3.h
	$(COMPILER) $(BUILD_FLAGS) source/id3.c

main.o: source/main.c source/id3.h source/id3.c
	$(COMPILER) $(BUILD_FLAGS) source/main.c

clean:
	rm $(TARGET)
	rm *.o

tar:
	tar cfv source.tar source/*

