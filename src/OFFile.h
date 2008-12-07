/*
 * Copyright (c) 2008
 *   Jonathan Schleifer <js@webkeks.org>
 *
 * All rights reserved.
 *
 * This file is part of libobjfw. It may be distributed under the terms of the
 * Q Public License 1.0, which can be found in the file LICENSE included in
 * the packaging of this file.
 */

#import <stdio.h>
#import <sys/types.h>

#import "OFObject.h"
#import "OFStream.h"

/**
 * The OFFile class provides functions to read, write and manipulate files.
 */
@interface OFFile: OFObject <OFStream>
{
	FILE *fp;
}

/**
 * \param path The path to the file to open as a C string
 * \param mode The mode in which the file should be opened as a C string
 * \return A new OFFile
 */
+ newWithPath: (const char*)path
      andMode: (const char*)mode;
/**
 * Changes the mode of a file.
 *
 * \param path The path to the file of which the mode should be changed as a
 *	  C string
 * \param mode The new mode for the file
 * \return A boolean whether the operation succeeded
 */
+ (BOOL)changeModeOfFile: (const char*)path
		  toMode: (mode_t)mode;

/**
 * Changes the owner of a file.
 *
 * \param path The path to the file of which the owner should be changed as a
 *	  C string
 * \param owner The new owner for the file
 * \param group The new group for the file
 * \return A boolean whether the operation succeeded
 */
+ (BOOL)changeOwnerOfFile: (const char*)path
		  toOwner: (uid_t)owner
		 andGroup: (gid_t)group;

/**
 * Deletes a file.
 *
 * \param path The path to the file of which should be deleted as a C string
 * \return A boolean whether the operation succeeded
 */
+ (BOOL)delete: (const char*)path;

/**
 * Hardlinks a file.
 *
 * \param src The path to the file of which should be linked as a C string
 * \param dest The path to where the file should be linked as a C string
 * \return A boolean whether the operation succeeded
 */
+ (BOOL)link: (const char*)src
	  to: (const char*)dest;

/**
 * Symlinks a file.
 *
 * \param src The path to the file of which should be symlinked as a C string
 * \param dest The path to where the file should be symlinked as a C string
 * \return A boolean whether the operation succeeded
 */
+ (BOOL)symlink: (const char*)src
	     to: (const char*)dest;

/**
 * Initializes an already allocated OFFile.
 *
 * \param path The path to the file to open as a C string
 * \param mode The mode in which the file should be opened as a C string
 * \return An initialized OFFile
 */
- initWithPath: (const char*)path
       andMode: (const char*)mode;

- free;

/**
 * \return A boolean whether the end of the file has been reached
 */
- (BOOL)atEndOfFile;

/**
 * Reads from the file into a buffer.
 *
 * \param buf The buffer into which the data is read
 * \param size The size of the data that should be read.
 *	  The buffer MUST be at least size * nitems big!
 * \param nitems nitem The number of items to read
 *	  The buffer MUST be at least size * nitems big!
 * \return The number of bytes read
 */
- (size_t)readNItems: (size_t)nitems
	      ofSize: (size_t)size
	  intoBuffer: (uint8_t*)buf;

/**
 * Reads from the file into a buffer.
 *
 * \param buf The buffer into which the data is read
 * \param size The size of the data that should be read.
 *	  The buffer MUST be at least size big!
 * \return The number of bytes read
 */
- (size_t)readNBytes: (size_t)size
	  intoBuffer: (uint8_t*)buf;

/**
 * Reads from the file into a new buffer.
 *
 * \param size The size of the data that should be read
 * \param nitem The number of items to read
 * \return A new buffer with the data read.
 *	   It is part of the memory pool of the OFFile.
 */
- (uint8_t*)readNItems: (size_t)nitems
		ofSize: (size_t)size;
/**
 * Reads from the file into a new buffer.
 *
 * \param size The size of the data that should be read
 * \return A new buffer with the data read.
 *	   It is part of the memory pool of the OFFile.
 */
- (uint8_t*)readNBytes: (size_t)size;

/**
 * Writes from a buffer into the file.
 *
 * \param buf The buffer from which the data is written to the file
 * \param size The size of the data that should be written
 * \param nitem The number of items to write
 * \return The number of bytes written
 */
- (size_t)writeNItems: (size_t)nitems
	       ofSize: (size_t)size
	   fromBuffer: (const uint8_t*)buf;

/**
 * Writes from a buffer into the file.
 *
 * \param buf The buffer from which the data is written to the file
 * \param size The size of the data that should be written
 * \return The number of bytes written
 */
- (size_t)writeNBytes: (size_t)size
	   fromBuffer: (const uint8_t*)buf;

/**
 * Writes a C string into the file, without the trailing zero.
 *
 * \param str The C string from which the data is written to the file
 * \return The number of bytes written
 */
- (size_t)writeCString: (const char*)str;

/**
 * Writes a C string into the file, without the trailing zero.
 *
 * \param str The wide C string from which the data is written to the file
 * \return The number of bytes written
 */
- (size_t)writeWideCString: (const wchar_t*)str;
@end
