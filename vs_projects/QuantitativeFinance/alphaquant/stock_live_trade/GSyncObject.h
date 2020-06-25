#ifndef GSYNCOBJECT_H_HEADER_INCLUDED_B84DE627
#define GSYNCOBJECT_H_HEADER_INCLUDED_B84DE627

class SyncObject
{
public:
	virtual ~SyncObject() {}
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
};

class NullSyncObject : public SyncObject
{
public:
	virtual ~NullSyncObject() {}
	virtual void Lock() {}
	virtual void Unlock() {}
};

#endif