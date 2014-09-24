#include "id3.h"


#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 500

struct File_info {
    char filename[MAX_SIZE];
    char artist[MAX_SIZE];
    char album[MAX_SIZE];
    char title[MAX_SIZE];
};

struct File_info* File_info_new() {
    struct File_info *file_info = malloc(sizeof(struct File_info));
    assert(file_info);
    memset(file_info, 0, sizeof(struct File_info));
    return file_info;
}

void File_info_free(struct File_info **file_info) {
    assert(file_info && *file_info);
    free(*file_info);
    *file_info = NULL;
}




void read_mp3_file(const char *filename) {
    printf("filepath: %s\n", filename);
    struct ID3_file *file = ID3_open(filename);
    struct ID3_data *data = NULL;

    if (file == NULL) {
        printf("unable to open file\n");
        return;
    }

    printf("==================================\n");

    struct File_info *file_info = File_info_new();

    while ((data = ID3_read(file))) {
        //printf("%s: %s\n",data->id, data->data);
        if (strcmp(data->id, "TPE1") == 0) {
            strcpy(file_info->artist, data->data);
        } else if (strcmp(data->id, "TALB") == 0) {
            strcpy(file_info->album, data->data);
        } else if (strcmp(data->id, "TIT2") == 0) {
            strcpy(file_info->title, data->data);
        }
        ID3_data_free(&data);
    }


    printf("%s/%s/%s.mp3\n", file_info->artist, file_info->album, file_info->title);

    printf("==================================\n");

    File_info_free(&file_info);

    ID3_close(&file);
}




int string_suffix(const char *str) {
    int length = strlen(str);
    //printf("lenght of %s is %d\n", str, length);

    if (length >= 4 && strcmp(str+length-4, ".mp3") == 0) {
        return 1;
    }
    return 0;
}

int test_opendir() {

    DIR *dir = opendir("data/");

    if (dir == NULL) {
        printf("unable to read directory\n");
        return 0;
    }

    struct dirent *entry = NULL;
    while ((entry = readdir(dir))) {
        if(string_suffix(entry->d_name)) {
            printf("filename: %s\n", entry->d_name);
            char buffer[1000];
            memset(buffer, 0, sizeof(char)*1000);
            strcat(buffer, "data/");
            strcat(buffer, entry->d_name);
            read_mp3_file(buffer);
        }

    }

    closedir(dir);
    return 1;
}






int main(int argc, const char *argv[])
{
    test_opendir();
    /*
    struct ID3_file *file = ID3_open("data/music10.mp3");
    struct ID3_data *data = NULL;

    if (file == NULL) {
        printf("unable to open file\n");
        return 1;
    }

    printf("==================================\n");

    while ((data = ID3_read(file))) {
        printf("%s: %s\n",data->id, data->data);
        ID3_data_free(&data);
    }

    printf("==================================\n");

    ID3_close(&file);
    */

    return 0;
}
