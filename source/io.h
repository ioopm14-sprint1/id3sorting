#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdbool.h>


/**
 * @brief Check if directory exists
 *
 * @param directory Path to the directory
 * @return true if directory exist, false otherwise
 */
bool IO_directory_exist (const char *directory);
/**
 * @brief Create a new directory
 *
 * @param directory Path to the directory
 * @return true if directory could be created, false otherwise
 */
bool IO_directory_create(const char *directory);
/**
 * @brief Remove a directory
 *
 * @param directory Path to the directory
 * @return true if directory could be removed, false otherwise
 */
bool IO_directory_remove(const char *directory);


/**
 * @brief Get size of file in bytes
 *
 * @param filename Path to the file
 * @return size of the file in bytes, -1 if file doesn't exist or couldn't be opened
 */
size_t  IO_file_size    (const char *filename);
/**
 * @brief Check if file exists
 *
 * @param filename Path to the file
 * @return true if file exist, false otherwise
 */
bool    IO_file_exist   (const char *filename);
/**
 * @brief Copy file from source to destination
 *
 * @warning This function has not been implemented yet
 *
 * @param source Path to the file to be copied
 * @param destination Path to copy to.
 * @return true if file could be copied, false otherwise
 */
bool    IO_file_copy    (const char *source, const char *destination);
/**
 * @brief Move file from source to destination
 *
 * @param source Path to the file being moved
 * @param destination Path where the file should be moved
 * @return true if the file could be moved, false otherwise
 */
bool    IO_file_move    (const char *source, const char *destination);
/**
 * @brief Remove file
 *
 * @param filename Path to the file to be removed
 * @return bool if file could be removed, false otherwise
 */
bool    IO_file_remove  (const char *filename);


#endif // __IO_H__
