#ifndef __ID3_HELPER_H__
#define __ID3_HELPER_H__


struct ID3_info {
    char *title;
    char *artist;
    char *album;
    char *track;
    char *genre;
    char *year;
};
typedef struct ID3_info ID3_info;

ID3_info* ID3_info_read  (const char *filename);
void      ID3_info_free  (ID3_info **id3_info);
void      ID3_info_print (ID3_info *id3_info);

#endif // __ID3_HELPER_H__
