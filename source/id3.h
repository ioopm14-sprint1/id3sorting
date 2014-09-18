#ifndef __ID3_H__
#define __ID3_H__

#include <stdio.h>


struct ID3_file;

struct ID3_data {
    char id[5];
    int size;
    char *data;
};


struct ID3_file* ID3_open(const char *filename);
void             ID3_close(struct ID3_file **id3_file);
struct ID3_data* ID3_read(struct ID3_file *id3_file);
void             ID3_data_free(struct ID3_data **id3_data);



#endif // __ID3_H__
