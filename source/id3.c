#include "id3.h"
#include <stdio.h>
#include <stdlib.h>
//#include <inttypes.h>
#include <stdint.h>


// TODO: create typedefs for uint32_t etc.
struct ID3_header {
    char version[2];
    char flags;
    int size;
};

struct ID3_header* ID3_header_new() {
    return (struct ID3_header*)malloc(sizeof(struct ID3_header));
}
void ID3_header_free(struct ID3_header** header) {
    free(*header);
    *header = NULL;
}

void ID3_header_print(struct ID3_header* header) {
    if (header) {
        printf("header:\n");
        printf("version: 2.%d.%d\n", header->version[0], header->version[1]);
        printf("flags: %c\n", header->flags);
        printf("size: %d\n", header->size);
    }
}


struct ID3_frame {
    char id[5];
    int size;
    char flags[2];
    char encoding;
    char *data;
};

struct ID3_frame* ID3_frame_new() {
    return (struct ID3_frame*)malloc(sizeof(struct ID3_frame));
}
void ID3_frame_free(struct ID3_frame** frame) {

    // only free frame->data if it exist
    if ((*frame)->data) {
        free((*frame)->data);
        (*frame)->data = NULL;
    }
    free(*frame);
    *frame = NULL;
}

void ID3_frame_print(struct ID3_frame *frame) {
    if (frame) {
        printf("frame:\n");
        printf("id: %s\n", frame->id);
        printf("size: %d\n", frame->size);
        printf("flags: %c, %c\n", frame->flags[0], frame->flags[0]);
        printf("encoding: 0x%02x\n", frame->encoding);
        printf("data: %s\n", frame->data);
    }
}


int ID3_decode_size(char *size_data) {
    return (0x00000000 | size_data[3] | size_data[2] << 7 | size_data[1] << 14 | size_data[0] << 21);
}


struct ID3_header* ID3_read_header(FILE *file) {

    // read 10 bytes header from file
    char buffer[10];
    fread(&buffer, sizeof(char), 10, file);

    // make sure its a ID3 file
    if (buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != '3') {
        printf("No ID3 data found\n");
        return NULL;
    }

    // allocate header and make sure it's ok
    struct ID3_header *header = ID3_header_new();

    if (header == NULL) {
        printf("Unable to allocate memory for header\n");
        return NULL;
    }

    // store ID3 version and flags
    header->version[0] = buffer[3];
    header->version[1] = buffer[4];
    header->flags = buffer[5];

    // decode and store ID3 header size
    header->size = ID3_decode_size(buffer+6);

    return header;
}

struct ID3_frame* ID3_read_frame(FILE *file) {

    // read 10 bytes frame header
    char buffer[10];
    fread(&buffer, sizeof(char), 10, file);

    // make sure it's valid
    if (buffer[0] == 0 || buffer[1] == 0 || buffer[2] == 0 || buffer[3] == 0) {
        printf("No frame found\n");
        return NULL;
    }

    // allocate frame and make sure it's ok
    struct ID3_frame *frame = malloc(sizeof(struct ID3_frame));

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
    frame->size = ID3_decode_size(buffer+4);

    // store frame flags
    frame->flags[0] = buffer[8];
    frame->flags[1] = buffer[9];

    // allocate memory for frame data
    frame->data = malloc(sizeof(char) * frame->size);
    // Size:n är en för mycket

    if (frame->data == NULL) {
        printf("Unable to allocate memory for frame data\n");
        ID3_frame_free(&frame);
        return NULL;
    }

    // read text encoding and frame data
    frame->encoding = fgetc(file);
    frame->size--; // Skip encoding character
    fread(frame->data, sizeof(char), frame->size, file);

    return frame;
}

int ID3_read_file(char *filename) {

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return 0;
    }


    struct ID3_header *header = ID3_read_header(file);

    if (header == NULL) {
        printf("Unable to read header\n");
        return 0;
    }

    ID3_header_print(header);

    struct ID3_frame *frame = NULL;
    int times = 0;
    while ((frame = ID3_read_frame(file)) && times < 20) {
        ID3_frame_print(frame);
        ID3_frame_free(&frame);
    }

    ID3_header_free(&header);

    fclose(file);

    return 1;
}


//===============================================================

struct ID3_file {
  FILE *file;
  int size;
  };



struct ID3_file* ID3_file_new() {
    return (struct ID3_file*)malloc(sizeof(struct ID3_file));
}
void ID3_file_free(struct ID3_file** file) {
    free(*file);
    *file = NULL;
}

struct ID3_data* ID3_data_new() {
    return (struct ID3_data*)malloc(sizeof(struct ID3_data));
}

struct ID3_file* ID3_open(const char*filename) {

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return NULL;
    }

    struct ID3_header *header = ID3_read_header(file);

    if (header == NULL) {
        printf("Unable to read header\n");
        return NULL;
    }

    struct ID3_file *id3_file = ID3_file_new();

    if (id3_file == NULL) {
        printf("Unable to allocate memory for ID3_file\n");
        ID3_header_free(&header);
        return NULL;
    }

    id3_file->file = file;
    id3_file->size = header->size;

    return id3_file;
}

void ID3_close(struct ID3_file **id3_file) {
  if (*id3_file) {
    fclose((*id3_file)->file);
    ID3_file_free(id3_file);
  }
}

struct ID3_data* ID3_read(struct ID3_file *id3_file) {
  if (id3_file == NULL) {
    printf("Can't read from NULL file\n");
    return NULL;
  }
  
  struct ID3_frame *frame = ID3_read_frame(id3_file->file);
    if (frame == NULL) {
      return NULL;
    }
  
  struct ID3_data *id3_data = ID3_data_new();
  if (id3_data == NULL) {
    printf("Unable to allocate memory for ID3 data\n");
    ID3_frame_free(&frame);
    return NULL;
  }
  
  id3_data->id[0] = frame->id[0];
  id3_data->id[1] = frame->id[1];
  id3_data->id[2] = frame->id[2];
  id3_data->id[3] = frame->id[3];
  id3_data->id[4] = '\0';
  
  id3_data->size = frame->size;

  // FIXME: Transfer memory responsibility
  id3_data->data = frame->data;
  frame->data = NULL;
  ID3_frame_free(&frame);
  
  return id3_data;
}

void ID3_data_free(struct ID3_data **id3_data) {
  
  // only free id3_data->data if it exist
    if ((*id3_data)->data) {
        free((*id3_data)->data);
        (*id3_data)->data = NULL;
    }
    free(*id3_data);
    *id3_data = NULL;
}
