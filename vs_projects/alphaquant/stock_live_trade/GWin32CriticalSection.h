#ifndef GWIN32CRITICALSECTION_H_HEADER_INCLUDED_B84DE627
#define GWIN32CRITICALSECTION_H_HEADER_INCLUDED_B84DE627


//#ifdef HAVE_WIN32_CRITICAL_SECTION_API
#include <windows.h>
#include "GSyncObject.h"

class Win32CriticalSection : public SyncObject
{
public:
	Win32CriticalSection();
	virtual ~Win32CriticalSection();

	virtual void Lock();
	virtual void Unlock();

private:
	CRITICAL_SECTION m_CS;
};

//#endif

#endif