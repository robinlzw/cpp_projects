#ifndef GWIN32EVENT_H_HEADER_INCLUDED_B84DE627
#define GWIN32EVENT_H_HEADER_INCLUDED_B84DE627

#include <Windows.h>

class Win32Event
{
public:
	typedef HANDLE EVENT_HANDLE;

	Win32Event() { m_hEvent = ::CreateEvent(0, false, false, 0); }
	virtual ~Win32Event() { ::CloseHandle(m_hEvent); }
	
	EVENT_HANDLE Handle() { return m_hEvent; }
	void Signal() { ::SetEvent(m_hEvent); }
	void Wait(DWORD dwMilliseconds = INFINITE) { ::WaitForSingleObject(m_hEvent, dwMilliseconds); }

private:
	EVENT_HANDLE m_hEvent;
};

#endif