/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012
 *   Jonathan Schleifer <js@webkeks.org>
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

#define OF_APPLICATION_M

#include <stdlib.h>
#include <string.h>

#import "OFApplication.h"
#import "OFString.h"
#import "OFArray.h"
#import "OFDictionary.h"
#import "OFAutoreleasePool.h"

#import "OFNotImplementedException.h"

#if defined(__MACH__) && !defined(OF_IOS)
# include <crt_externs.h>
#elif !defined(OF_IOS)
extern char **environ;
#endif

static OFApplication *app = nil;

static void
atexit_handler(void)
{
	id <OFApplicationDelegate> delegate = [app delegate];

	[delegate applicationWillTerminate];

	[(id)delegate release];
}

int
of_application_main(int *argc, char **argv[], Class cls)
{
	OFApplication *app = [OFApplication sharedApplication];
	id <OFApplicationDelegate> delegate = [[cls alloc] init];

	[app setArgumentCount: argc
	    andArgumentValues: argv];

	[app setDelegate: delegate];

	[app run];

	return 0;
}

@implementation OFApplication
+ sharedApplication
{
	if (app == nil)
		app = [[self alloc] init];

	return app;
}

+ (OFString*)programName
{
	return [app programName];
}

+ (OFArray*)arguments
{
	return [app arguments];
}

+ (OFDictionary*)environment
{
	return [app environment];
}

+ (void)terminate
{
	exit(0);
}

+ (void)terminateWithStatus: (int)status
{
	exit(status);
}

- init
{
	self = [super init];

	@try {
		OFAutoreleasePool *pool;
#if defined(__MACH__) && !defined(OF_IOS)
		char **env = *_NSGetEnviron();
#elif !defined(OF_IOS)
		char **env = environ;
#else
		char *env;
#endif

		environment = [[OFMutableDictionary alloc] init];

		atexit(atexit_handler);

		pool = [[OFAutoreleasePool alloc] init];
#ifndef OF_IOS
		for (; *env != NULL; env++) {
			OFString *key;
			OFString *value;
			char *sep;

			if ((sep = strchr(*env, '=')) == NULL) {
				fprintf(stderr, "Warning: Invalid environment "
				    "variable: %s\n", *env);
				continue;
			}

			key = [OFString
			    stringWithCString: *env
				     encoding: OF_STRING_ENCODING_NATIVE
				       length: sep - *env];
			value = [OFString
			    stringWithCString: sep + 1
				     encoding: OF_STRING_ENCODING_NATIVE];
			[environment setObject: value
					forKey: key];

			[pool releaseObjects];
		}
#else
		/*
		 * iOS does not provide environ and Apple does not allow using
		 * _NSGetEnviron on iOS. Therefore, we just get a few common
		 * variables from the environment which applications might
		 * expect.
		 */
		if ((env = getenv("HOME")) != NULL)
			[environment
			    setObject: [OFString stringWithCString: env]
			       forKey: @"HOME"];
		if ((env = getenv("PATH")) != NULL)
			[environment
			    setObject: [OFString stringWithCString: env]
			       forKey: @"PATH"];
		if ((env = getenv("SHELL")) != NULL)
			[environment
			    setObject: [OFString stringWithCString: env]
			       forKey: @"SHELL"];
		if ((env = getenv("TMPDIR")) != NULL)
			[environment
			    setObject: [OFString stringWithCString: env]
			       forKey: @"TMPDIR"];
		if ((env = getenv("USER")) != NULL)
			[environment
			    setObject: [OFString stringWithCString: env]
			       forKey: @"USER"];
#endif
		[pool release];

		[environment makeImmutable];
	} @catch (id e) {
		[self release];
		@throw e;
	}

	return self;
}

- (void)setArgumentCount: (int*)argc_
       andArgumentValues: (char***)argv_
{
	OFAutoreleasePool *pool = [[OFAutoreleasePool alloc] init];
	int i;

	[programName release];
	[arguments release];

	argc = argc_;
	argv = argv_;

	programName = [[OFString alloc]
	    initWithCString: (*argv)[0]
		   encoding: OF_STRING_ENCODING_NATIVE];
	arguments = [[OFMutableArray alloc] init];

	for (i = 1; i < *argc; i++)
		[arguments addObject:
		    [OFString stringWithCString: (*argv)[i]
				       encoding: OF_STRING_ENCODING_NATIVE]];

	[arguments makeImmutable];

	[pool release];
}

- (void)getArgumentCount: (int**)argc_
       andArgumentValues: (char****)argv_
{
	*argc_ = argc;
	*argv_ = argv;
}

- (OFString*)programName
{
	return programName;
}

- (OFArray*)arguments
{
	return arguments;
}

- (OFDictionary*)environment
{
	return environment;
}

- (id <OFApplicationDelegate>)delegate
{
	return delegate;
}

- (void)setDelegate: (id <OFApplicationDelegate>)delegate_
{
	delegate = delegate_;
}

- (void)run
{
	[delegate applicationDidFinishLaunching];
}

- (void)terminate
{
	exit(0);
}

- (void)terminateWithStatus: (int)status
{
	exit(status);
}

- (void)dealloc
{
	[arguments release];
	[environment release];

	[super dealloc];
}
@end

@implementation OFObject (OFApplicationDelegate)
- (void)applicationDidFinishLaunching
{
	@throw [OFNotImplementedException exceptionWithClass: isa
						    selector: _cmd];
}

- (void)applicationWillTerminate
{
}
@end
