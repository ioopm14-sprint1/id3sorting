#ifndef __ID3_HELPER_H__
#define __ID3_HELPER_H__


typedef struct ID3_info {
    char *title;
    char *artist;
    char *album;
    char *track;
    char *genre;
    char *year;
} ID3_info;

/**
 * @brief Read basic text frames from file
 *
 * Read title, artist, album, track, genre and year from ID3 file.
 * Missing fields will be set to NULL.
 *
 * @param *filename Path to the file
 * @return ID3_info struct containing the basic data
 */
ID3_info* ID3_info_read  (const char *filename);
/**
 * @breif Deallocate a ID3_info struct
 * 
 * Deallocate the ID3_info pointed to be the Double-pointer and set it to NULL
 *
 * @param **id3_info Double-pointer to the ID3_info struct to remove
 */
void      ID3_info_free  (ID3_info **id3_info);
/**
 * @breif Print ID3_info struct
 * 
 * @param *id3_info ID3_info struct to print
 */
void      ID3_info_print (ID3_info *id3_info);

#endif // __ID3_HELPER_H__
