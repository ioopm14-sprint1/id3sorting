#ifndef __ID3_H__
#define __ID3_H__


typedef struct ID3_file ID3_file;
typedef struct ID3_frame ID3_frame;

ID3_file*   ID3_open(const char *filename);
void        ID3_close(ID3_file **id3_file);
ID3_frame*  ID3_read(ID3_file *id3_file);

void        ID3_frame_free(ID3_frame **id3_frame);
char*       ID3_frame_id(ID3_frame *id3_frame);
char*       ID3_frame_data(ID3_frame *id3_frame);
char*       ID3_frame_grab_data(ID3_frame *id3_frame);


#endif // __ID3_H__
