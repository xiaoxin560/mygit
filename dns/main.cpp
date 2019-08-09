#include"DNS_HEADER.h"
#include"DnsPacketSend.h"
#include"DNSPacketParser.h"
#include<boost/asio.hpp>
#include<iostream>
#include<vector>
#include <string>
#include <cstdlib>

void printip(std::vector<std::string> recvip)
{
	std::vector<std::string>::iterator it = recvip.begin();
	std::cout << "解析的IP" << std::endl;
	while (it != recvip.end())
	{
		std::cout << *it<<std::endl;
		++it;
	}
		
}

int main(int argc, char* argv[])
{	
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: ping <host>" << std::endl;
			return 1;
		}
		std::vector <std::string> recvip;
		char*domain_name = "www.baidu.com";	
		char*ser_ip="114.114.114.114";
		int ser_port = 53;

		boost::asio::io_service io_service;
		//DnsPacketSend p(io_service, ser_ip, ser_port, domain_name);
		DnsPacketSend p(io_service, argv[1], ser_port, argv[2]);
		int recvlen = p.getrecvlen();
		char *recvdata = p.getrecvdata();//接收到的dns数据
		//解析dns数据
		DNSPacketParser parser(recvdata, recvlen);
		parser.parse(recvdata, recvlen);
		recvip = parser.getip();//得到的结果为一个vector存储string类型的ip地址
		
		io_service.run();
		free(recvdata);
		printip(recvip);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

