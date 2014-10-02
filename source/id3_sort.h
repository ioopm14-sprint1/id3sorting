#ifndef __ID3_SORT_H__
#define __ID3_SORT_H__

#include <stdbool.h>

/**
 * @brief maximum path size, including filename
 */
#define MAX_PATH 2048

/**
 * @brief Sort the file according to its ID3 data
 *
 * Read the files ID3 data and move it to the following path: "target/artist/album/title.mp3".
 * If no ID3 data for artist could be found artist will be "unknown"
 * If album is missing, it will be ignored ex: "target/artist/title.mp3"
 * If title is missing, the name of the file being processed will be used instead.
 * Target directory must exist.
 *
 * @param *filename Path to the file being sorted
 * @param *target   Path to directory to sort the file into
 * @return true if file could be sorted, false otherwise
 */
bool sort_file(char *filename, char *target);


#endif // __ID3_SORT_H__
