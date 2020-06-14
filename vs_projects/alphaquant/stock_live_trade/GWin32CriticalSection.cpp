#include "GWin32CriticalSection.h"

//#ifdef HAVE_WIN32_CRITICAL_SECTION_API

Win32CriticalSection::Win32CriticalSection()
{
	::InitializeCriticalSection(&m_CS);
}

Win32CriticalSection::~Win32CriticalSection()
{
	::DeleteCriticalSection(&m_CS);
}

void Win32CriticalSection::Lock()
{
	::EnterCriticalSection(&m_CS);
}

void Win32CriticalSection::Unlock()
{
	::LeaveCriticalSection(&m_CS);
}

//#endif