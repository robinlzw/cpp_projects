#include <thread>
#include <string>
#include <iostream>
#include "include/myProtocol.h"

// #pragma comment(lib, "libuvWrapper.lib")

class MyClient : public uv::TCPClient {
public:
	MyClient(uv::Protocol* protocol);
protected:
	void messageReceived(int cliendid, const char* buf, int bufsize) override;
};

MyClient::MyClient(uv::Protocol* protocol) :
	TCPClient(protocol)
{

}

void MyClient::messageReceived(int cliendid, const char* buf, int bufsize) 
{
	std::cout << buf << std::endl;
}

MyProtocol myProtocol(1001);
MyClient client(&myProtocol);
bool bTrackConnected(false);

void thread_main()
{
	bTrackConnected = client.connect("127.0.0.1", 6969);
}



int main()
{
	std::thread comm_thread(thread_main);
	comm_thread.detach();

	while (true)
	{
		if (bTrackConnected)
		{
			std::string text;
			std::cin >> text;
			// getline(std::cin, text);
			client.SendPack(text.c_str(), text.size());
		}
	}
	return 0;
}
