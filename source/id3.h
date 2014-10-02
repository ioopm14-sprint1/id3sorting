#ifndef __ID3_H__
#define __ID3_H__




typedef struct ID3_file ID3_file;
typedef struct ID3_frame ID3_frame;

/**
 * @brief Open a ID3 file
 *
 * The caller is responsible for closing the ID3 file using the ID3_close function
 *
 * @param *filename Path to the file
 * @return ID3_file pointer if the file could be opened and holds ID3 data, NULL otherwise
 */
ID3_file*   ID3_open(const char *filename);
/**
 * @brief Close a ID3 file
 *
 * Close the ID3 file pointed to be the Double-pointer and set it to NULL
 *
 * @param **id3_file Double-pointer to a ID3_file
 */
void        ID3_close(ID3_file **id3_file);
/**
 * @brief Read a frame from the ID3 file
 *
 * The caller is responsible for deallocating the ID3 frame using the ID3_frame_free function
 *
 * @param *id3_file Pointer to the ID3 file to read from
 * @return ID3_frame countaining the data read from the frame, NULL if no frame could be read
 */
ID3_frame*  ID3_read(ID3_file *id3_file);

/**
 * @brief Deallocate a ID3_frame
 *
 * Close the ID3 frame pointed to be the Double-pointer and set it to NULL
 *
 * @param **id3_frame Double-pointer to the frame to deallocate
 */
void        ID3_frame_free(ID3_frame **id3_frame);
/**
 * @brief Get id from ID3 frame
 *
 * @param *id3_frame Pointer to the ID3 frame
 * @return A string containing the frames id
 */
char*       ID3_frame_id(ID3_frame *id3_frame);
/**
 * @brief Get data from ID3 frame
 *
 * @param *id3_frame Pointer to the ID3 frame
 * @return The frames data
 */
char*       ID3_frame_data(ID3_frame *id3_frame);
/**
 * @brief Grab the ID3 frames data
 *
 * Take the data from the ID3 frame, the frame will no longer have access to it and the caller is responsible for deallocating it.
 *
 * @param *id3_frame Pointer to the ID3 frame
 * @return The ID3 frames data
 */
char*       ID3_frame_grab_data(ID3_frame *id3_frame);


#endif // __ID3_H__
