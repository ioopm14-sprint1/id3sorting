#include <stdio.h>
#include <stdlib.h>


int read_header(char *filename) {

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return 0;
    }


    char header[10];
    fread(&header, sizeof(char), 10, file);


    char header_id[4];
    header_id[0] = header[0];
    header_id[1] = header[1];
    header_id[2] = header[2];
    header_id[3] = '\0';

    char version[2];
    version[0] = header[3];
    version[1] = header[4];

    char header_flags = header[5];

    int header_size = 0x00000000 | header[9] | header[8] << 7 | header[7] << 14 | header[6] << 21;


    printf("header:\n");
    printf("id: %s\n", header_id);
    printf("version: 2.%d.%d\n", version[0], version[1]);
    printf("flags: %c\n", header_flags);
    printf("size: %d\n", header_size);


    for(int n=0; n < 4; ++n) {



        char frame[10];
        fread(&frame, sizeof(char), 10, file);

        char frame_id[5];
        frame_id[0] = frame[0];
        frame_id[1] = frame[1];
        frame_id[2] = frame[2];
        frame_id[3] = frame[3];
        frame_id[4] = '\0';


        int frame_size = 0x00000000 | frame[7] | frame[6] << 7 | frame[5] << 14 | frame[4] << 21;


        char frame_flags[2];
        frame_flags[0] = frame[8];
        frame_flags[1] = frame[9];


        char *buffer = malloc(sizeof(char) * frame_size);

        if (buffer == NULL) {
            printf("Unable to allocate memory\n");
            return 0;
        }

        fgetc(file);
        frame_size--;
        fread(buffer, sizeof(char), frame_size, file);



        printf("frame:\n");
        printf("id: %s\n", frame_id);
        printf("size: %d\n", frame_size);
        printf("flags: %c, %c\n", frame_flags[0], frame_flags[0]);
        printf("data: %s\n", buffer);

        free(buffer);
    }


    //for (int n=0; n<10; ++n) {
    //    printf("%c\n", frame[n]);
    //}


    return 0;
}





int main(int argc, const char *argv[])
{
    read_header("data/music10.mp3");

   // int size = 0x00000000 | 0x2a | 0x01 << 7 | 0x00 << 14 | 0x00 << 21;
   // printf("size: 0x%08x\n", size);


    
    return 0;
}
