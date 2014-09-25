#include "id3_helper.h"
#include "id3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//static char *UNKNOWN = "unknown";

ID3_info* ID3_info_new() {
    ID3_info *id3_info = (ID3_info*)malloc(sizeof(ID3_info));
    assert(id3_info != NULL);
    memset(id3_info, 0, sizeof(ID3_info));
    return id3_info;
}

void ID3_info_free(ID3_info **id3_info) {
    assert(id3_info != NULL && *id3_info != NULL);
    ID3_info *info = *id3_info;

    if (info->title)  { free(info->title);  }
    if (info->artist) { free(info->artist); }
    if (info->album)  { free(info->album);  }
    if (info->track)  { free(info->track);  }
    if (info->genre)  { free(info->genre);  }
    if (info->year)   { free(info->year);   }

    free(*id3_info);
    *id3_info = NULL;
}

ID3_info* ID3_info_read(const char *filename) {
    ID3_file *file = ID3_open(filename);
    if (file == NULL) {
        printf("unable to open file: %s\n", filename);
        return NULL;
    }


    ID3_info *info = ID3_info_new();

    ID3_frame *frame = NULL;

#define FRAME_ID_EQUAL(tag) (strcmp(ID3_frame_id(frame), tag) == 0)

    while ((frame = ID3_read(file))) {
               if (FRAME_ID_EQUAL("TIT2")) {
            info->title = ID3_frame_grab_data(frame);
        } else if (FRAME_ID_EQUAL("TPE1")) {
            info->artist = ID3_frame_grab_data(frame);
        } else if (FRAME_ID_EQUAL("TALB")) {
            info->album = ID3_frame_grab_data(frame);
        } else if (FRAME_ID_EQUAL("TRCK")) {
            info->track = ID3_frame_grab_data(frame);
        } else if (FRAME_ID_EQUAL("TCON")) {
            info->genre = ID3_frame_grab_data(frame);
        } else if (FRAME_ID_EQUAL("TYER")) {
            info->year = ID3_frame_grab_data(frame);
        }
        ID3_frame_free(&frame);
    }

#undef FRAME_ID_EQUAL
/*
    if (!info->title)  { info->title  = UNKNOWN; }
    if (!info->artist) { info->artist = UNKNOWN; }
    if (!info->album)  { info->album  = UNKNOWN; }
    if (!info->track)  { info->track  = UNKNOWN; }
    if (!info->genre)  { info->genre  = UNKNOWN; }
    if (!info->year)   { info->year   = UNKNOWN; }
*/


    ID3_close(&file);
    return info;
}



void ID3_info_print(ID3_info *id3_info) {
    printf("============================================\n");
    printf("title:  %s\n", id3_info->title);
    printf("artist: %s\n", id3_info->artist);
    printf("album:  %s\n", id3_info->album);
    printf("track:  %s\n", id3_info->track);
    printf("genre:  %s\n", id3_info->genre);
    printf("year:   %s\n", id3_info->year);
}
