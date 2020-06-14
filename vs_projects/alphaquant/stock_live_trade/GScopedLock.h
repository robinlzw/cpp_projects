#ifndef GSCOPED_LOCK_H_HEADER_INCLUDED_B84DE627
#define GSCOPED_LOCK_H_HEADER_INCLUDED_B84DE627

#include "GSyncObject.h"

class ScopedLock
{
public:
	ScopedLock(SyncObject& ref) : m_refSyncObj(ref) { m_refSyncObj.Lock(); }
	virtual ~ScopedLock() { m_refSyncObj.Unlock(); }
private:
	SyncObject& m_refSyncObj;
};

#endif