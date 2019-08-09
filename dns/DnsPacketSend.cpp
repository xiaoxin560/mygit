#include"DNS_HEADER.h"
#include"DnsPacketSend.h"
#include<boost/thread.hpp>
#include<boost/lexical_cast.hpp>
#include<iostream>
#include <cstdlib>
char* DnsPacketSend::MakeDnsPacket(const char *name)//封装成DNS包
{
	DNSHeader header;//头部
	std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
	header.transactionID = htons(atoi(threadId.c_str()));
	//header.transactionID = htons(0x8008);
	header.flags = htons(0x0180);//RD位（期望递归）与RA位（可用递归）设置为1，
	header.questions = htons(1);
	header.answerRRs = htons(0);
	header.authorityRRs = htons(0);
	header.additionalRRs = htons(0);
	//Queries区域
	//const unsigned short queryType = htons(28);//查询ipv6
	const unsigned short queryType = htons(1);//查询ipv4
	const unsigned short queryClass = htons(1);//查询类设置位1
	
	char *sendbuffer = (char *)malloc(1024 );//不定长。malloc
	char *current = sendbuffer;
	memset(sendbuffer, 0, 1024);
	memcpy(current, &header, sizeof(struct DNSHeader));//拼接头部
	current += sizeof(struct DNSHeader);
	//拼接Name
	const char *domain_ptr = name;
	const char *dot_ptr = NULL;
	unsigned char len;

	while ((dot_ptr = strchr(domain_ptr, '.')) != NULL)
	{
		len = dot_ptr - domain_ptr;
		memcpy(current, &len, sizeof(unsigned char));
		current += sizeof(unsigned char);
		memcpy(current, domain_ptr, len);//3www
		current += len;
		domain_ptr = dot_ptr + sizeof(char);//.bai,从b开始
	}
	//www.bai.com,此时从c开始
	len = strlen(domain_ptr);
	memcpy(current, &len, sizeof(unsigned char));
	current += sizeof(unsigned char);
	memcpy(current, domain_ptr, len);
	current += len;
	memset(current, 0, sizeof(unsigned char));
	current += sizeof(unsigned char);
	//拼接查询类型和查询类，查询类型Type为1（由域名获得IPv4地址），查询类Class为1（表明是Internet数据）
	memcpy(current, &queryType, sizeof(unsigned short));
	current += sizeof(unsigned short);
	memcpy(current, &queryClass, sizeof(unsigned short));
	current += sizeof(unsigned short);
	buflen = current - sendbuffer;
	return sendbuffer;
}

void DnsPacketSend::DNSPacketSende(const char *name)
{
	
	boost::system::error_code error;
	char *sendbuffer = MakeDnsPacket(name);//构造dns包
	socket_.send_to(boost::asio::buffer(sendbuffer, buflen), endpoint);//发送

	char recvbuffer[1024];
	ip::udp::endpoint sender_ep;
	//boost::array<char, 1204> recv_buf;
	recvlen=socket_.receive_from(boost::asio::buffer(recvbuffer), sender_ep);//接收

	recvdata = (char *)malloc(recvlen);
	memcpy(recvdata, recvbuffer, recvlen);

}
