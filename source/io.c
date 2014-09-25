#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

bool IO_directory_exist(const char *directory) {
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        return false;
    }
    closedir(dir);
    return true;
}

bool IO_directory_create(const char *directory) {
    if (IO_directory_exist(directory)) {
        return false;
    }
    mkdir(directory, S_IRWXU);
    return true;
}

bool IO_directory_remove(const char *directory) {
    if (!IO_directory_exist(directory)) {
        return false;
    }
    rmdir(directory);
    return true;
}


size_t IO_file_size(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fclose(file);

    return size;
}

bool IO_file_exist(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return false;
    }
    fclose(file);
    return true;
}

bool IO_file_copy(const char *source , const char *destination) {
/*
    if (IO_file_exist(source)) {
        return false;
    }
    FILE *from = fopen(source, "r");
    FILE *to   = fopen(destination, "w");
    if (from == NULL || to == NULL) {
        if (from != NULL) { fclose(from); }
        if (to != NULL)   { fclose(to); }
        return false;
    }

    size_t size = IO_file_size(source);
    char *buffer = malloc(size);
    size_t read = fread(buffer, size, 1, from);
    fwrite(buffer, read, 1, to);


    fclose(from);
    fclose(to);
*/
    assert(false);
    return false; // NOTE: not implemented yet
}

bool IO_file_move(const char *source, const char *destination) {
   if (!IO_file_exist(source) || IO_file_exist(destination)) {
       return false;
   }
   rename(source, destination);
   return true;
}

bool IO_file_remove(const char *filename) {
   if (!IO_file_exist(filename)) {
       return false;
   }
   unlink(filename);
   return true;
}
