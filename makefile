COMPILER = gcc -std=c99
BUILD_FLAGS = -Wall -ggdb -c
LINK_FLAGS = -Wall -ggdb -o
TARGET = bin/main


main: main.o id3.o io.o id3_helper.o
	mkdir -p bin
	mkdir -p bin/music
	cp -r data/ bin/data/
	$(COMPILER) $(LINK_FLAGS) $(TARGET) main.o id3.o io.o id3_helper.o
	./$(TARGET) bin/music bin/data/*.mp3
	echo;
	tree bin/music

id3.o: source/id3.c source/id3.h
	$(COMPILER) $(BUILD_FLAGS) source/id3.c

main.o: source/main.c source/id3.h source/id3.c
	$(COMPILER) $(BUILD_FLAGS) source/main.c

io.o: source/io.c source/io.h
	$(COMPILER) $(BUILD_FLAGS) source/io.c

id3_helper.o: source/id3_helper.c source/id3_helper.h
	$(COMPILER) $(BUILD_FLAGS) source/id3_helper.c

valgrind: 
	valgrind --leak-check=yes ./$(TARGET) bin/music bin/data/*.mp3

clean:
	#rm $(TARGET)
	rm -f main.o id3.o io.o id3_helper.o
	rm -rf bin/music/*

tar:
	tar cfv source.tar source/*

.PHONY: valgrind
