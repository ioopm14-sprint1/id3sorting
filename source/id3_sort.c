#include "id3_sort.h"

#include <stdio.h>
#include <stdbool.h>
#include "id3_helper.h"
#include "io.h"
#include <assert.h>
#include <string.h>



char* get_filename(char *filename) {
    int length = strlen(filename);
    int at = length-1;
    while (filename[at-1] != '/' && at >= 0) {
        at--;
    }
    return filename + at;
}

bool sort_file(char *filename, char *target) {
    assert(filename && strlen(filename) > 0 && target);

    ID3_info *info = ID3_info_read(filename);

    if (info == NULL) {
        return false;
    }

    char path[MAX_PATH];
    memset(path, 0, sizeof(char) * MAX_PATH);

    if (info->artist) {
        sprintf(path, "%s/%s/", target, info->artist);
    } else {
        sprintf(path, "%s/unknown/", target);
    }

    //sprintf(path, "%s/%s/", target, info->artist ? info->artist : "unknown");

    IO_directory_create(path);

    if (info->album) {
        strcat(path, info->album);
        strcat(path, "/");
    }

    IO_directory_create(path);

    if (info->title) {
        strcat(path, info->title);
        strcat(path, ".mp3");
    } else {
        strcat(path, get_filename(filename));
    }

    printf("path: %s\nfilename: %s\n", path, filename);

    IO_file_move(filename, path);
    ID3_info_free(&info);

    return false;
}


