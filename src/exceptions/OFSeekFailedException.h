/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
 *   Jonathan Schleifer <js@heap.zone>
 *
 * All rights reserved.
 *
 * This file is part of ObjFW. It may be distributed under the terms of the
 * Q Public License 1.0, which can be found in the file LICENSE.QPL included in
 * the packaging of this file.
 *
 * Alternatively, it may be distributed under the terms of the GNU General
 * Public License, either version 2 or 3, which can be found in the file
 * LICENSE.GPLv2 or LICENSE.GPLv3 respectively included in the packaging of this
 * file.
 */

#import "OFException.h"
#import "OFSeekableStream.h"

/*!
 * @class OFSeekFailedException \
 *	  OFSeekFailedException.h ObjFW/OFSeekFailedException.h
 *
 * @brief An exception indicating that seeking in a stream failed.
 */
@interface OFSeekFailedException: OFException
{
	OFSeekableStream *_stream;
	of_offset_t _offset;
	int _whence, _errNo;
}

/*!
 * The stream for which seeking failed.
 */
@property (readonly, retain) OFSeekableStream *stream;

/*!
 * The offset to which seeking failed.
 */
@property (readonly) of_offset_t offset;

/*!
 * To what the offset is relative.
 */
@property (readonly) int whence;

/*!
 * The errno of the error that occurred.
 */
@property (readonly) int errNo;

/*!
 * @brief Creates a new, autoreleased seek failed exception.
 *
 * @param stream The stream for which seeking failed
 * @param offset The offset to which seeking failed
 * @param whence To what the offset is relative
 * @param errNo The errno of the error that occurred
 * @return A new, autoreleased seek failed exception
 */
+ (instancetype)exceptionWithStream: (OFSeekableStream*)stream
			     offset: (of_offset_t)offset
			     whence: (int)whence
			      errNo: (int)errNo;

/*!
 * @brief Initializes an already allocated seek failed exception.
 *
 * @param stream The stream for which seeking failed
 * @param offset The offset to which seeking failed
 * @param whence To what the offset is relative
 * @param errNo The errno of the error that occurred
 * @return An initialized seek failed exception
 */
- initWithStream: (OFSeekableStream*)stream
	  offset: (of_offset_t)offset
	  whence: (int)whence
	   errNo: (int)errNo;
@end
