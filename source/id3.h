#ifndef __ID3_H__
#define __ID3_H__

#include <stdio.h>

struct ID3_file {
    FILE* file;
    int size;
};


struct ID3_data {
    char *id;
    char encoding;
    char *data;
};


struct ID3_file*   ID3_open(const char *filename);
void               ID3_close(struct ID3_file *file);
struct ID3_data*   ID3_read(struct ID3_file *file);




int ID3_read_file(char* filename);


#endif // __ID3_H__
