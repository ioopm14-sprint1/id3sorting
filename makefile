COMPILER = gcc -std=c99
BUILD_FLAGS = -Wall -ggdb -c
LINK_FLAGS = -Wall -ggdb -o
TARGET = bin/main


main: main.o id3.o io.o id3_helper.o
	mkdir -p bin
	$(COMPILER) $(LINK_FLAGS) $(TARGET) main.o id3.o io.o id3_helper.o
	./$(TARGET) data/*9.mp3 data/

id3.o: source/id3.c source/id3.h
	$(COMPILER) $(BUILD_FLAGS) source/id3.c

main.o: source/main.c source/id3.h source/id3.c
	$(COMPILER) $(BUILD_FLAGS) source/main.c

io.o: source/io.c source/io.h
	$(COMPILER) $(BUILD_FLAGS) source/io.c

id3_helper.o: source/id3_helper.c source/id3_helper.h
	$(COMPILER) $(BUILD_FLAGS) source/id3_helper.c

clean:
	rm $(TARGET)
	rm *.o

tar:
	tar cfv source.tar source/*


#.PHONY: 
