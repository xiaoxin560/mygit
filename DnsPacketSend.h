//https://github.com/liuenyan

#ifndef DNS_PACKGE_SEND
#define DNS_PACKGE_SEND
#include <boost/asio.hpp>
using namespace boost::asio;

class DnsPacketSend
{
public:
	DnsPacketSend(boost::asio::io_service& io_service, const char* ser_ip, int port,const char * name)
		:resolver_(io_service), domain_name(name), socket_(io_service), endpoint(ip::address_v4::from_string(ser_ip), port)
	{
		socket_.open(endpoint.protocol());
		//sendbuffer = new char(1024) ;
		//sendbuffer = (char *)malloc(1024);
		DNSPacketSende(domain_name);
	}

	char *	MakeDnsPacket(const char *name);
	void DNSPacketSende(const char *name);
	int getrecvlen(){ return recvlen; }
	char*getrecvdata(){ return recvdata; }
private:
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint  endpoint;
	boost::asio::ip::udp::resolver resolver_;
	boost::asio::ip::udp::endpoint destination_;
	const char * domain_name;//域名
	
	int buflen = 0;//发送包的长度
	int recvlen = 0;//接收包长度
	char *recvdata;

};
#endif