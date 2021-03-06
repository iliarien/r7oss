/*
 *
 *  D-Bus++ - C++ bindings for D-Bus
 *
 *  Copyright (C) 2005-2007  Paolo Durante <shackan@gmail.com>
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#ifndef __DBUSXX_EVENTLOOP_H
#define __DBUSXX_EVENTLOOP_H

#include <list>
#include <time.h>

#include "api.h"
#include "util.h"

namespace DBus {

/*
 * these Default *classes implement a very simple event loop which
 * is used here as the default main loop, if you want to hook
 * a different one use the Bus *classes in eventloop-integration.h
 * or the Glib::Bus *classes as a reference
 */

class DefaultMainLoop;

class DXXAPI DefaultTimeout
{
public:

	DefaultTimeout(int interval, bool repeat, DefaultMainLoop *);

	bool enabled(){ return _enabled; }
	void enabled(bool e);

	int interval(){ return _interval; }
	void interval(int i){ _interval = i; }

	bool repeat(){ return _repeat; }
	void repeat(bool r){ _repeat = r; }

	void *data(){ return _data; }
	void data(void *d){ _data = d; }

	Slot<void, DefaultTimeout &> expired;

	void remove();
protected:
	virtual ~DefaultTimeout();

private:

	bool _enabled;

	int _interval;
	bool _repeat;

	struct timespec _expiration;

	void *_data;

	DefaultMainLoop *_disp;

friend class DefaultMainLoop;
friend class RefPtrI<DefaultTimeout>;
};

typedef std::list< RefPtrI<DefaultTimeout> > DefaultTimeouts;

class DXXAPI DefaultWatch
{
public:

	DefaultWatch(int fd, int flags, DefaultMainLoop *);

	bool enabled(){ return _enabled; }
	void enabled(bool e);

	int descriptor(){ return _fd; }

	int flags(){ return _flags; }
	void flags(int f){ _flags = f; }

	int state(){ return _state; }

	void *data(){ return _data; }
	void data(void *d){ _data = d; }

	Slot<void, DefaultWatch &> ready;

	void remove();
protected:
	virtual ~DefaultWatch();

private:

	bool _enabled;

	int _fd;
	int _flags;
	int _state;

	void *_data;

	DefaultMainLoop *_disp;

friend class DefaultMainLoop;
friend class RefPtrI<DefaultWatch>;
};

typedef std::list< RefPtrI<DefaultWatch> > DefaultWatches;

class DXXAPI DefaultMainLoop
{
public:

	DefaultMainLoop();

	virtual ~DefaultMainLoop();

	virtual void dispatch();

protected:
	void wake();

	void remove(DefaultWatch *);
	void remove(DefaultTimeout *);

	int _fdunlock[2];

private:

	DefaultMutex _mutex_t;
	DefaultTimeouts _timeouts;

	DefaultMutex _mutex_w;
	DefaultWatches _watches;

friend class DefaultTimeout;
friend class DefaultWatch;
};

} /* namespace DBus */

#endif//__DBUSXX_EVENTLOOP_H

/* vim:set noexpandtab sw=4 ts=4 sts=4: */
