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

#import "OFObject.h"
#import "OFSerialization.h"

@class OFString;
@class OFConstantString;

/**
 * \brief A class for storing, accessing and comparing dates.
 */
@interface OFDate: OFObject <OFCopying, OFComparing, OFSerialization>
{
	double seconds;
}

/**
 * \brief Creates a new OFDate with the current date and time.
 *
 * \return A new, autoreleased OFDate with the current date and time
 */
+ date;

/**
 * \brief Creates a new OFDate with the specified date and time since
 *	  1970-01-01T00:00:00Z.
 *
 * \param seconds The seconds since 1970-01-01T00:00:00Z
 * \return A new, autoreleased OFDate with the specified date and time
 */
+ dateWithTimeIntervalSince1970: (double)seconds;

/**
 * \brief Creates a new OFDate with the specified date and time since now.
 *
 * \param seconds The seconds since now
 * \return A new, autoreleased OFDate with the specified date and time
 */
+ dateWithTimeIntervalSinceNow: (double)seconds;

/**
 * \brief Creates a new OFDate with the specified string in the specified
 *	  format.
 *
 * The time zone used is UTC. If a time zone is specified anyway, an
 * OFInvalidFormatException is thrown. See +[dateWithLocalDateString:format:]
 * if you want to specify a time zone.
 *
 * See the manpage for strftime for information on the format.
 *
 * \warning The format is currently limited to the following format specifiers:
 *	    %%d, %%e, %%H, %%m, %%M, %%S, %%y, %%Y, %%, %%n and %%t.
 *
 * \param string The string describing the date
 * \param format The format of the string describing the date
 * \return A new, autoreleased OFDate with the specified date and time
 */
+ dateWithDateString: (OFString*)string
	      format: (OFString*)format;

/**
 * \brief Creates a new OFDate with the specified string in the specified
 *	  format.
 *
 * If no time zone is specified, local time is assumed.
 *
 * See the manpage for strftime for information on the format.
 *
 * \warning The format is currently limited to the following format specifiers:
 *	    %%d, %%e, %%H, %%m, %%M, %%S, %%y, %%Y, %%, %%n and %%t.
 *
 * \param string The string describing the date
 * \param format The format of the string describing the date
 * \return A new, autoreleased OFDate with the specified date and time
 */
+ dateWithLocalDateString: (OFString*)string
		   format: (OFString*)format;

/**
 * \brief Returns a date in the distant future.
 *
 * The date is system-dependant.
 *
 * \return A date in the distant future
 */
+ distantFuture;

/**
 * \brief Returns a date in the distant past.
 *
 * The date is system-dependant.
 *
 * \return A date in the distant past
 */
+ distantPast;

/**
 * \brief Initializes an already allocated OFDate with the specified date and
 *	  time since 1970-01-01T00:00:00Z.
 *
 * \param seconds The seconds since 1970-01-01T00:00:00Z
 * \return An initialized OFDate with the specified date and time
 */
- initWithTimeIntervalSince1970: (double)seconds;

/**
 * \brief Initializes an already allocated OFDate with the specified date and
 *	  time since now.
 *
 * \param seconds The seconds since now
 * \return An initialized OFDate with the specified date and time
 */
- initWithTimeIntervalSinceNow: (double)seconds;

/**
 * \brief Initializes an already allocated OFDate with the specified string in
 *	  the specified format.
 *
 * The time zone used is UTC. If a time zone is specified anyway, an
 * OFInvalidFormatException is thrown. See -[initWithLocalDateString:format:]
 * if you want to specify a time zone.
 *
 * See the manpage for strftime for information on the format.
 *
 * \warning The format is currently limited to the following format specifiers:
 *	    %%d, %%e, %%H, %%m, %%M, %%S, %%y, %%Y, %%, %%n and %%t.
 *
 * \param string The string describing the date
 * \param format The format of the string describing the date
 * \return An initialized OFDate with the specified date and time
 */
- initWithDateString: (OFString*)string
	      format: (OFString*)format;

/**
 * \brief Initializes an already allocated OFDate with the specified string in
 *	  the specified format.
 *
 * If no time zone is specified, local time is assumed.
 *
 * See the manpage for strftime for information on the format.
 *
 * \warning The format is currently limited to the following format specifiers:
 *	    %%d, %%e, %%H, %%m, %%M, %%S, %%y, %%Y, %%, %%n and %%t.
 *
 * \param string The string describing the date
 * \param format The format of the string describing the date
 * \return An initialized OFDate with the specified date and time
 */
- initWithLocalDateString: (OFString*)string
		   format: (OFString*)format;

/**
 * \brief Returns the microsecond of the date.
 *
 * \return The microsecond of the date
 */
- (uint32_t)microsecond;

/**
 * \brief Returns the second of the date.
 *
 * \return The second of the date
 */
- (uint8_t)second;

/**
 * \brief Returns the minute of the date.
 *
 * \return The minute of the date
 */
- (uint8_t)minute;

/**
 * \brief Returns the hour of the date.
 *
 * \return The hour of the date
 */
- (uint8_t)hour;

/**
 * \brief Returns the hour of the date in local time.
 *
 * \return The hour of the date in local time
 */
- (uint8_t)localHour;

/**
 * \brief Returns the day of the month.
 *
 * \return The day of the month of the date
 */
- (uint8_t)dayOfMonth;

/**
 * \brief Returns the day of the month of the date in local time.
 *
 * \return The day of the month of the date in local time
 */
- (uint8_t)localDayOfMonth;

/**
 * \brief Returns the month of the year of the date.
 *
 * \return The month of the year of the date
 */
- (uint8_t)monthOfYear;

/**
 * \brief Returns the month of the year of the date in local time.
 *
 * \return The month of the year of the date in local time
 */
- (uint8_t)localMonthOfYear;

/**
 * \brief Returns the year of the date.
 *
 * \return The year of the date
 */
- (uint16_t)year;

/**
 * \brief Returns the year of the date in local time.
 *
 * \return The year of the date in local time
 */
- (uint16_t)localYear;

/**
 * \brief Returns the day of the week of the date.
 *
 * \return The day of the week of the date
 */
- (uint8_t)dayOfWeek;

/**
 * \brief Returns the day of the week of the date in local time.
 *
 * \return The day of the week of the date in local time
 */
- (uint8_t)localDayOfWeek;

/**
 * \brief Returns the day of the year of the date.
 *
 * \return The day of the year of the date
 */
- (uint16_t)dayOfYear;

/**
 * \brief Returns the day of the year of the date in local time.
 *
 * \return The day of the year of the date in local time
 */
- (uint16_t)localDayOfYear;

/**
 * \brief Creates a string of the date with the specified format.
 *
 * See the manpage for strftime for information on the format.
 *
 * \param format The format for the date string
 * \return A new, autoreleased OFString
 */
- (OFString*)dateStringWithFormat: (OFConstantString*)format;

/**
 * \brief Creates a string of the local date with the specified format.
 *
 * See the manpage for strftime for information on the format.
 *
 * \param format The format for the date string
 * \return A new, autoreleased OFString
 */
- (OFString*)localDateStringWithFormat: (OFConstantString*)format;

/**
 * \brief Returns the earlier of the two dates.
 *
 * \param date Another date
 * \return The earlier date of the two dates
 */
- (OFDate*)earlierDate: (OFDate*)otherDate;

/**
 * \brief Returns the later of the two dates.
 *
 * \param date Another date
 * \return The later date of the two dates
 */
- (OFDate*)laterDate: (OFDate*)otherDate;

/**
 * \brief Returns the seconds since 1970-01-01T00:00:00Z.
 *
 * \return The seconds since 1970-01-01T00:00:00Z
 */
- (double)timeIntervalSince1970;

/**
 * \brief Returns the seconds the receiver is after the date.
 *
 * \param date Date date to generate the difference with receiver
 * \return The seconds the receiver is after the date.
 */
- (double)timeIntervalSinceDate: (OFDate*)otherDate;

/**
 * \brief Returns the seconds the receiver is in the future.
 *
 * \return The seconds the receiver is in the future
 */
- (double)timeIntervalSinceNow;

/**
 * \brief Creates a new date with the specified time interval added.
 *
 * \param seconds The seconds after the date
 * \return A new, autoreleased OFDate
 */
- (OFDate*)dateByAddingTimeInterval: (double)seconds;
@end
