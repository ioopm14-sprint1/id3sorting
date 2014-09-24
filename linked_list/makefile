COMPILER = gcc
VERSION = -std=c99
BUILD_FLAGS = -Wall -ggdb -c
LINK_FLAGS = -Wall -ggdb -o
TARGET = bin/main


main: */*.c */*.h 
	mkdir -p bin
	$(COMPILER) $(VERSION) $(LINK_FLAGS) $(TARGET) */*.c
	./$(TARGET) | column -t


#id3.o: source/id3.c source/id3.h
#	$(COMPILER) $(VERSION) $(BUILD_FLAGS) source/id3.c
#
#main.o: source/main.c source/id3.h source/id3.c
#	$(COMPILER) $(VERSION) $(BUILD_FLAGS) source/main.c

clean:
	rm $(TARGET)
	rm *.o

tar:
	tar cfv source.tar source/*

