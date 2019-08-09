#include"DNS_HEADER.h"
#include"DnsPacketSend.h"
#include<boost/thread.hpp>
#include<boost/lexical_cast.hpp>
#include<iostream>
#include <cstdlib>
char* DnsPacketSend::MakeDnsPacket(const char *name)//��װ��DNS��
{
	DNSHeader header;//ͷ��
	std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
	header.transactionID = htons(atoi(threadId.c_str()));
	//header.transactionID = htons(0x8008);
	header.flags = htons(0x0180);//RDλ�������ݹ飩��RAλ�����õݹ飩����Ϊ1��
	header.questions = htons(1);
	header.answerRRs = htons(0);
	header.authorityRRs = htons(0);
	header.additionalRRs = htons(0);
	//Queries����
	//const unsigned short queryType = htons(28);//��ѯipv6
	const unsigned short queryType = htons(1);//��ѯipv4
	const unsigned short queryClass = htons(1);//��ѯ������λ1
	
	char *sendbuffer = (char *)malloc(1024 );//��������malloc
	char *current = sendbuffer;
	memset(sendbuffer, 0, 1024);
	memcpy(current, &header, sizeof(struct DNSHeader));//ƴ��ͷ��
	current += sizeof(struct DNSHeader);
	//ƴ��Name
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
		domain_ptr = dot_ptr + sizeof(char);//.bai,��b��ʼ
	}
	//www.bai.com,��ʱ��c��ʼ
	len = strlen(domain_ptr);
	memcpy(current, &len, sizeof(unsigned char));
	current += sizeof(unsigned char);
	memcpy(current, domain_ptr, len);
	current += len;
	memset(current, 0, sizeof(unsigned char));
	current += sizeof(unsigned char);
	//ƴ�Ӳ�ѯ���ͺͲ�ѯ�࣬��ѯ����TypeΪ1�����������IPv4��ַ������ѯ��ClassΪ1��������Internet���ݣ�
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
	char *sendbuffer = MakeDnsPacket(name);//����dns��
	socket_.send_to(boost::asio::buffer(sendbuffer, buflen), endpoint);//����

	char recvbuffer[1024];
	ip::udp::endpoint sender_ep;
	//boost::array<char, 1204> recv_buf;
	recvlen=socket_.receive_from(boost::asio::buffer(recvbuffer), sender_ep);//����

	recvdata = (char *)malloc(recvlen);
	memcpy(recvdata, recvbuffer, recvlen);

}
