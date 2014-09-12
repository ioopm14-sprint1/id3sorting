#include <stdio.h>
#include <stdlib.h>
//#include <inttypes.h>
#include <stdint.h>


// TODO: create typedefs for uint32_t etc.
struct ID3_Header {
    char version[2];
    char flags;
    int size;
};

struct ID3_Header* ID3_Header_new() {
    return (struct ID3_Header*)malloc(sizeof(struct ID3_Header));
}
void ID3_Header_free(struct ID3_Header* header) {
    free(header);
}


struct ID3_Frame {
    char id[5];
    int size;
    char flags[2];
    char encoding;
    char *data;
};

struct ID3_Frame* ID3_Frame_new() {
    return (struct ID3_Frame*)malloc(sizeof(struct ID3_Frame));
}
void ID3_Frame_free(struct ID3_Frame* frame) {

    // only free frame->data if it exist
    if (frame->data) {
        free(frame->data);
        frame->data = NULL;
    }
    free(frame);
}


int ID3_decode_size(char *size_data) {
    return (0x00000000 | size_data[3] | size_data[2] << 7 | size_data[1] << 14 | size_data[0] << 21);
}


struct ID3_Header* ID3_read_header(FILE *file) {

    // read 10 bytes header from file
    char buffer[10];
    fread(&buffer, sizeof(char), 10, file);

    // make sure its a ID3 file
    if (buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != '3') {
        printf("No ID3 data found\n");
        return NULL;
    }

    // allocate header and make sure it's ok
    struct ID3_Header *header = ID3_Header_new();

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
    //0x00000000 | buffer[9] | buffer[8] << 7 | buffer[7] << 14 | buffer[6] << 21;

    /*
       printf("header:\n");
       printf("version: 2.%d.%d\n", header->version[0], header->version[1]);
       printf("flags: %c\n", header->flags);
       printf("size: %d\n", header->size);
       */
    return header;
}

struct ID3_Frame* ID3_read_frame(FILE *file) {

    // read 10 bytes frame header
    char buffer[10];
    fread(&buffer, sizeof(char), 10, file);

    // make sure it's valid
    if (buffer[0] == 0 || buffer[1] == 0 || buffer[2] == 0 || buffer[3] == 0) {
        printf("No frame found\n");
        return NULL;
    }

    // allocate frame and make sure it's ok
    struct ID3_Frame *frame = malloc(sizeof(struct ID3_Frame));

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
    //0x00000000 | frame[7] | frame[6] << 7 | frame[5] << 14 | frame[4] << 21;

    // store frame flags
    frame->flags[0] = buffer[8];
    frame->flags[1] = buffer[9];

    // allocate memory for frame data
    frame->data = malloc(sizeof(char) * frame->size);
    // Size:n är en för mycket

    if (frame->data == NULL) {
        printf("Unable to allocate memory for frame data\n");
        ID3_Frame_free(frame);
        return NULL;
    }

    // read text encoding and frame data
    frame->encoding = fgetc(file);
    frame->size--; // Skip encoding character
    fread(frame->data, sizeof(char), frame->size, file);



    /*
       printf("frame:\n");
       printf("id: %s\n", frame->id);
       printf("size: %d\n", frame->size);
       printf("flags: %c, %c\n", frame->flags[0], frame->flags[0]);
       printf("encoding: 0x%02x\n", frame->encoding);
       printf("data: %s\n", frame->data);
       */
    return frame;
}

int ID3_read_file(char *filename) {

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return 0;
    }


    struct ID3_Header *header = ID3_read_header(file);

    if (header == NULL) {
        printf("Unable to read header\n");
        return 0;
    }

    printf("header:\n");
    printf("version: 2.%d.%d\n", header->version[0], header->version[1]);
    printf("flags: %c\n", header->flags);
    printf("size: %d\n", header->size);

    ID3_Header_free(header);
    header = NULL;

    struct ID3_Frame *frame = NULL;
    int times = 0;
    while ((frame = ID3_read_frame(file)) && times < 20) {
        printf("frame:\n");
        printf("id: %s\n", frame->id);
        printf("size: %d\n", frame->size);
        printf("flags: %c, %c\n", frame->flags[0], frame->flags[0]);
        printf("encoding: 0x%02x\n", frame->encoding);
        printf("data: %s\n", frame->data);
        ID3_Frame_free(frame);
        frame = NULL;
    }


    fclose(file);

    return 1;
}


