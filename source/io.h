#ifndef __IO_H__
#define __IO_H__

/*
create directory
exist directory
*/
#include <stdio.h>
#include <stdbool.h>


bool IO_directory_exist(const char *directory);
bool IO_directory_create(const char *directory);
bool IO_directory_remove(const char *directory);


size_t  IO_file_size(const char *filename);
bool IO_file_exist(const char *filename);
bool IO_file_copy(const char *source, const char *destination);
bool IO_file_move(const char *source, const char *destination);
bool IO_file_remove(const char *filename);




#endif // __IO_H__
