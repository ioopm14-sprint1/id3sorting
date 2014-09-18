#include "id3.h"


int main(int argc, const char *argv[])
{
    struct ID3_file *file = ID3_open("data/music10.mp3");
    struct ID3_data *data = NULL;

    printf("==================================\n");
    while ((data = ID3_read(file))) {
        printf("%s\n",data->data);
        ID3_data_free(&data);
    }
    printf("==================================\n");

    ID3_close(&file);

    return 0;
}
