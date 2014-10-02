#include <stdio.h>
#include "io.h"
#include "id3_sort.h"





int main(int argc, char *argv[]) {
    // make sure we got proper amount of arguments
    if (argc < 3) {
        printf("id3_sort <target> <list of files>\n");
        return 0;
    }

    // make sure target directory exist
    char *target = argv[1];
    if (!IO_directory_exist(target)) {
        printf("directory does not exist: %s\n", target);
        return 1;
    }

    // sort the files
    for (int n = 2; n < argc; n++) {
        sort_file(argv[n], target);
    }

    return 0;
}
