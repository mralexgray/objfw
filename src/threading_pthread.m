/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013, 2014
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

#import "threading.h"

bool
of_thread_new(of_thread_t *thread, id (*function)(id), id data)
{
	return (pthread_create(thread, NULL, (void*(*)(void*))function,
	    (__bridge void*)data) == 0);
}

bool
of_thread_join(of_thread_t thread)
{
	void *ret;

	if (pthread_join(thread, &ret) != 0)
		return false;

#ifdef PTHREAD_CANCELED
	return (ret != PTHREAD_CANCELED);
#else
	return true;
#endif
}

bool
of_thread_detach(of_thread_t thread)
{
	return (pthread_detach(thread) == 0);
}

void OF_NO_RETURN
of_thread_exit(void)
{
	pthread_exit(NULL);

	OF_UNREACHABLE
}

void
of_once(of_once_t *control, void (*func)(void))
{
	pthread_once(control, func);
}

bool
of_mutex_new(of_mutex_t *mutex)
{
	return (pthread_mutex_init(mutex, NULL) == 0);
}

bool
of_mutex_lock(of_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex) == 0);
}

bool
of_mutex_trylock(of_mutex_t *mutex)
{
	return (pthread_mutex_trylock(mutex) == 0);
}

bool
of_mutex_unlock(of_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex) == 0);
}

bool
of_mutex_free(of_mutex_t *mutex)
{
	return (pthread_mutex_destroy(mutex) == 0);
}

bool
of_condition_new(of_condition_t *condition)
{
	return (pthread_cond_init(condition, NULL) == 0);
}

bool
of_condition_signal(of_condition_t *condition)
{
	return (pthread_cond_signal(condition) == 0);
}

bool
of_condition_broadcast(of_condition_t *condition)
{
	return (pthread_cond_broadcast(condition) == 0);
}

bool
of_condition_wait(of_condition_t *condition, of_mutex_t *mutex)
{
	return (pthread_cond_wait(condition, mutex) == 0);
}

bool
of_condition_timed_wait(of_condition_t *condition, of_mutex_t *mutex,
    of_time_interval_t timeout)
{
	struct timespec ts;

	ts.tv_sec = (time_t)timeout;
	ts.tv_nsec = lrint((timeout - ts.tv_sec) * 1000000000);

	return (pthread_cond_timedwait(condition, mutex, &ts) == 0);
}

bool
of_condition_free(of_condition_t *condition)
{
	return (pthread_cond_destroy(condition) == 0);
}