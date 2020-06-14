#include "GWin32Thread.h"

//#ifdef HAVE_WIN32_THREAD_API

Win32Thread::Win32Thread()
{
	m_hThread = NULL;
	m_idThread = 0;
}

Win32Thread::~Win32Thread()
{
	if (m_hThread)
		::CloseHandle(m_hThread);
}
	
void Win32Thread::StartThread()
{
	m_hThread = ::CreateThread(NULL, 0, ThreadProc, this, 0, &m_idThread);
}

void Win32Thread::StartThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
{
	m_hThread = ::CreateThread(NULL, 0, lpStartAddress, lpParameter, 0, &m_idThread);
}

void Win32Thread::Join()
{
	::WaitForSingleObject(m_hThread, INFINITE);
}
	
u_long WINAPI Win32Thread::ThreadProc( LPVOID lParam )
{
	Win32Thread *this_ptr = (Win32Thread*)lParam;

	return this_ptr->Run();
}

//#endif