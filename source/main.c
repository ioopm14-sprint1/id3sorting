#include <stdio.h>
#include "id3_helper.h"
#include "io.h"






int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("id3_sort <list of files> <target>\n");
        return 0;
    }


    //ID3_info *info = ID3_info_read("data/music0.mp3");
    //ID3_info_print(info);
    //ID3_info_free(&info);
    //id3_sort(argc - 1, argv, destination);
    int count = argc-1;
    for (int i = 1; i < count; i++) {
        ID3_info *info = ID3_info_read(argv[i]);
        ID3_info_print(info);
        ID3_info_free(&info);
    }



    return 0;
}
