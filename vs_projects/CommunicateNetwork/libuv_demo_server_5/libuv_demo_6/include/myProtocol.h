#ifndef __MyProtocol_H__
#define __MyProtocol_H__

#include "uv_wrapper.h"

#define MAX_HEARTBEAT 9999
struct TelHead {
	unsigned short id;			// unique
	unsigned short heardBeat;	// 1~9999
	unsigned short length;		// message length
	unsigned short headCheckout;
};

class MyProtocol : public uv::Protocol
{
public:
	MyProtocol();
	MyProtocol(unsigned short id);
	~MyProtocol();

	void SetChannelID(unsigned short id);

	int FramePack(char* pack, int packLen, const char* rawData, int dataLength);
	int ParsePack(char* &packCache, int &size);

private:
	unsigned short calcHeadCheckout(char* head);
	unsigned short getHeartBeat();

private:
	unsigned short m_heartBeat;
	unsigned short m_channelId;
};

#endif // !__MyProtocol_H__
