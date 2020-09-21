#include <thread>
#include <string>
#include <iostream>
#include "include/myProtocol.h"

class MyServer : public uv::TCPServer {
public:
	MyServer(uv::Protocol* pro);
protected:
	void messageReceived(int cliendid, const char* buf, int bufsize) override;
};

MyServer::MyServer(uv::Protocol * pro) :
	TCPServer(pro)
{
}
void publish();
void MyServer::messageReceived(int cliendid, const char * buf, int bufsize)
{
	std::cout << "received " << bufsize
		<< " bytes from client " << cliendid << std::endl;
	std::string receivedStr(buf);
	if (receivedStr.find("subscribe") != std::string::npos) {
		std::cout << "receivedStr =  " << receivedStr << std::endl;
		std::thread publish_thread(publish);
		publish_thread.detach();
	}
	else {
		SendPack(cliendid, buf, bufsize);
	}	
}

MyProtocol myProtocol(1001);
MyServer server(&myProtocol);

void publish()
{
	/*while (true)
	{
		server.SendPack(2, "publish", 7);
	}*/
}


int main(int argc, char** argv)
{
	server.Start("127.0.0.1", 6969);
}
