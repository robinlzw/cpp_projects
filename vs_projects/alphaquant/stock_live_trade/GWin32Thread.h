#ifndef GWIN32THREAD_H_HEADER_INCLUDED_B84DE627
#define GWIN32THREAD_H_HEADER_INCLUDED_B84DE627

//#ifdef HAVE_WIN32_THREAD_API

#include <windows.h>

class Win32Thread
{
public:
	typedef u_long ThreadId;

	Win32Thread();
	virtual ~Win32Thread();

	void StartThread();
	void StartThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter);
	void Join();

	static void Sleep(u_int nMillSec) { ::Sleep(nMillSec); }
	static ThreadId GetCurrentThreadId() { return ::GetCurrentThreadId(); }
	virtual u_int Run() { return 0; }

private:
	static u_long WINAPI ThreadProc(LPVOID lParam);

	HANDLE m_hThread;
    ThreadId  m_idThread;
};

//#endif

#endif