#include <string>
#include "../include/myProtocol.h"

MyProtocol::MyProtocol():
	m_heartBeat(0),
	m_channelId(0)
{
}

MyProtocol::MyProtocol(unsigned short id):
	m_heartBeat(0),
	m_channelId(id)
{
}

MyProtocol::~MyProtocol()
{
}

void MyProtocol::SetChannelID(unsigned short id)
{
	m_channelId = id;
}

int MyProtocol::FramePack(char* pack, int packLen, const char* rawData, int dataLength)
{
	if ((size_t)packLen < sizeof(TelHead) + dataLength) {
		return 0;
	}
	TelHead* pHead = (TelHead*)pack;
	pHead->id = m_channelId;
	pHead->heardBeat = getHeartBeat();
	pHead->length = dataLength;
	pHead->headCheckout = calcHeadCheckout((char*)pack);
	memcpy((pack + sizeof(TelHead)), rawData, dataLength);
	return sizeof(TelHead) + dataLength;
}

int MyProtocol::ParsePack(char* &packCache, int &size)
{
	if (size < sizeof(TelHead))
	{
		return 0;
	}

	int payLoadLength = 0;
	// find head
	for (; size >= sizeof(TelHead); size--, packCache++)
	{
		payLoadLength = 0;

		TelHead* pHead = (TelHead*)packCache;
		if (pHead->id != m_channelId)
		{
			continue;
		}

		unsigned short checkout = calcHeadCheckout(packCache);
		if (checkout != pHead->headCheckout)
		{
			continue;
		}

		payLoadLength = pHead->length;
		break;
	}

	// not a integral message, cache payload
	if ((size_t)size < (sizeof(TelHead) + payLoadLength))
	{
		return 0;
	}
	// find a integral message
	size -= sizeof(TelHead);
	packCache += sizeof(TelHead);
	return payLoadLength;
}

unsigned short MyProtocol::calcHeadCheckout(char * head)
{
	unsigned short result = 0;

	for (int i = 0; i < (sizeof(TelHead) - sizeof(TelHead::headCheckout)); i++)
	{
		result += (unsigned short)head[i];
	}

	return result;
}

unsigned short MyProtocol::getHeartBeat()
{
	if (++m_heartBeat > MAX_HEARTBEAT)
	{
		m_heartBeat = 1;
	}

	return m_heartBeat;
}
