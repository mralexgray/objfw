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

#include "config.h"

#import "OFApplication.h"
#import "OFFileManager.h"
#import "OFStdIOStream.h"

#import "GZIPArchive.h"
#import "OFZIP.h"

static OFZIP *app;

static void
setPermissions(OFString *destination, OFString *source)
{
#ifdef OF_HAVE_CHMOD
	OFFileManager *fileManager = [OFFileManager defaultManager];
	mode_t mode;

	mode = [fileManager permissionsOfItemAtPath: source];
	[fileManager changePermissionsOfItemAtPath: destination
				       permissions: mode];
#endif
}

@implementation GZIPArchive
+ (void)initialize
{
	if (self == [GZIPArchive class])
		app = [[OFApplication sharedApplication] delegate];
}

+ (instancetype)archiveWithFile: (OFFile*)file
{
	return [[[self alloc] initWithFile: file] autorelease];
}

- initWithFile: (OFFile*)file
{
	self = [super init];

	@try {
		_stream = [[OFGZIPStream alloc] initWithStream: file];
	} @catch (id e) {
		[self release];
		@throw e;
	}

	return self;
}

- (void)dealloc
{
	[_stream release];

	[super dealloc];
}

- (void)listFiles
{
	[of_stderr writeLine: @"Cannot list files of a .gz archive!"];
	app->_exitStatus = 1;
}

- (void)extractFiles: (OFArray OF_GENERIC(OFString*)*)files
{
	OFString *fileName;
	OFFile *output;

	if ([files count] != 0) {
		[of_stderr writeLine:
		    @"Cannot extract a specific file of a .gz archive!"];
		app->_exitStatus = 1;
		return;
	}

	fileName = [[app->_archivePath lastPathComponent]
	    stringByDeletingPathExtension];

	if (app->_outputLevel >= 0)
		[of_stdout writeFormat: @"Extracting %@...", fileName];

	if (![app shouldExtractFile: fileName
			outFileName: fileName])
		return;

	output = [OFFile fileWithPath: fileName
				 mode: @"wb"];
	setPermissions(fileName, app->_archivePath);

	while (![_stream isAtEndOfStream]) {
		ssize_t length = [app copyBlockFromStream: _stream
						 toStream: output
						 fileName: fileName];

		if (length < 0) {
			app->_exitStatus = 1;
			return;
		}
	}

	if (app->_outputLevel >= 0)
		[of_stdout writeFormat: @"\rExtracting %@... done\n", fileName];
}
@end
