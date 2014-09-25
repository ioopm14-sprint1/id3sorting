#include "id3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>


#define ID3_HEADER_SIZE 10
#define ID3_FRAME_SIZE  10


/**
 * ID3 size decode
*/
uint32_t ID3_size_decode(uint8_t *size_data) {
    return (0x00000000 | (size_data[3] <<  0)
                       | (size_data[2] <<  7)
                       | (size_data[1] << 14)
                       | (size_data[0] << 21));
}

/**
 * ID3 Header struct
*/
struct ID3_header {
    char version[2];
    char flags;
    uint32_t size;
};
typedef struct ID3_header ID3_header;

ID3_header* ID3_header_new() {
    ID3_header *id3_header = (ID3_header*)malloc(sizeof(ID3_header));
    assert(id3_header != NULL);
    memset(id3_header, 0, sizeof(ID3_header));
    return id3_header;
}

void ID3_header_free(ID3_header** header) {
    assert(header && *header);
    free(*header);
    *header = NULL;
}

ID3_header* ID3_header_read(FILE *file) {

    assert(file != NULL);

    // read ID3_HEADER_SIZE bytes header from file
    uint8_t buffer[ID3_HEADER_SIZE];
    memset(buffer, 0, sizeof(uint8_t)*ID3_HEADER_SIZE);
    fread(&buffer, sizeof(uint8_t), ID3_HEADER_SIZE, file);

    // make sure its a ID3 file
    if (buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != '3') {
        printf("No ID3 data found\n");
        return NULL;
    }

    // allocate header and make sure it's ok
    ID3_header *header = ID3_header_new();

    if (header == NULL) {
        printf("Unable to allocate memory for header\n");
        return NULL;
    }

    // store ID3 version and flags
    header->version[0] = buffer[3];
    header->version[1] = buffer[4];
    header->flags = buffer[5];

    // decode and store ID3 header size
    header->size = ID3_size_decode(buffer+6);

    return header;
}

/**
 * ID3 Frame struct
*/
struct ID3_frame {
    char id[5];
    int size;
    char flags[2];
    char encoding;
    char *data;
};
//typedef struct ID3_frame ID3_frame;

ID3_frame* ID3_frame_new() {
    ID3_frame *id3_frame = (ID3_frame*)malloc(sizeof(ID3_frame));
    assert(id3_frame != NULL);
    memset(id3_frame, 0, sizeof(ID3_frame));
    return id3_frame;
}
void ID3_frame_free(ID3_frame** frame) {
    assert(frame && *frame);
    // only free frame->data if it exist
    if ((*frame)->data) {
        free((*frame)->data);
        (*frame)->data = NULL;
    }
    free(*frame);
    *frame = NULL;
}

char* ID3_frame_id(ID3_frame *id3_frame) {
    assert(id3_frame != NULL);
    return id3_frame->id;
}

char* ID3_frame_data(ID3_frame *id3_frame) {
    assert(id3_frame != NULL);
    return id3_frame->id;
}

char* ID3_frame_grab_data(ID3_frame *id3_frame) {
    assert(id3_frame != NULL);
    char* data = id3_frame->data;
    id3_frame->data = NULL;
    return data;
}

ID3_frame* ID3_frame_read(FILE *file) {
    assert(file != NULL);

    // read ID3_FRAME_SIZE bytes frame header
    uint8_t buffer[ID3_FRAME_SIZE];
    memset(buffer, 0, sizeof(uint8_t)*ID3_FRAME_SIZE);
    fread(&buffer, sizeof(uint8_t), ID3_FRAME_SIZE, file);

    // make sure it's valid
    if (buffer[0] == 0 || buffer[1] == 0 || buffer[2] == 0 || buffer[3] == 0) {
        //printf("No frame found\n");
        return NULL;
    }

    // allocate frame and make sure it's ok
    ID3_frame *frame = ID3_frame_new();

    if (frame == NULL) {
        printf("Unable to allocate memory for frame\n");
        return NULL;
    }

    // store frame identifier
    frame->id[0] = buffer[0];
    frame->id[1] = buffer[1];
    frame->id[2] = buffer[2];
    frame->id[3] = buffer[3];
    frame->id[4] = '\0';


    // decode and store frame size
    frame->size = ID3_size_decode(buffer+4);

    // store frame flags
    frame->flags[0] = buffer[8];
    frame->flags[1] = buffer[9];

    if (frame->id[0] == 'T') {
        // read text encoding and frame data
        frame->encoding = fgetc(file);
        frame->size--; // Skip encoding character
    }

    // allocate memory for frame data
    frame->data = (char*)malloc(sizeof(char) * frame->size);

    if (frame->data == NULL) {
        printf("Unable to allocate memory for frame data\n");
        ID3_frame_free(&frame);
        return NULL;
    }

    fread(frame->data, sizeof(char), frame->size, file);

    return frame;
}



struct ID3_file {
    FILE *file;
    ID3_header *header;
};

ID3_file* ID3_file_new() {
    ID3_file *id3_file = (ID3_file*)malloc(sizeof(ID3_file));
    assert(id3_file != NULL);
    memset(id3_file, 0, sizeof(ID3_file));
    return id3_file;
}

void ID3_file_free(ID3_file **id3_file) {
    assert(id3_file && *id3_file);
    if ((*id3_file)->header) {
        ID3_header_free(&(*id3_file)->header);
    }
    free(*id3_file);
    *id3_file = NULL;
}


ID3_file* ID3_open(const char *filename) {
    struct ID3_file *id3_file = ID3_file_new();

    if (id3_file == NULL) {
        printf("Unable to allocate memory for ID3_file\n");
        return NULL;
    }
    //assert(id3_file != NULL);
    id3_file->file = fopen(filename, "rb");

    if (id3_file->file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return NULL;
    }
    //assert(id3_file->file != NULL);

    id3_file->header = ID3_header_read(id3_file->file);

    if (id3_file->header == NULL) {
        printf("Unable to read header\n");
        ID3_file_free(&id3_file);
        return NULL;
    }

    return id3_file;
}


// TODO: remove dublicated code ID3_file_free
void ID3_close(ID3_file **id3_file) {
    assert(id3_file != NULL && *id3_file != NULL);

    fclose((*id3_file)->file);
    (*id3_file)->file = NULL;

    if ((*id3_file)->header != NULL) {
        ID3_header_free(&(*id3_file)->header);
    }
    free(*id3_file);
    *id3_file = NULL;
}

ID3_frame* ID3_read(ID3_file *id3_file) {
    assert(id3_file != NULL);
    return ID3_frame_read(id3_file->file);
}





