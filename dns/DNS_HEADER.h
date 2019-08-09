#ifndef DNS_HEADER
#define DNS_HEADER

#include<boost/algorithm/string.hpp>
#include<boost/asio.hpp>
using namespace boost;

struct DNSHeader{
	unsigned short transactionID;
	unsigned short flags;
	unsigned short questions;
	unsigned short answerRRs;
	unsigned short authorityRRs;
	unsigned short additionalRRs;
};

struct QuestionFiled{
	std::string name;//”Ú√˚
	unsigned short type_;
	unsigned short class_;
};

struct ResourceRecord{
	std::string name;//”Ú√˚
	unsigned short type_;
	unsigned short class_;
	unsigned int ttl;
	unsigned short data_len;
	std::string data;
};

std::ostream & operator<<(std::ostream &os, const QuestionFiled &q);
std::ostream & operator<<(std::ostream &os, const ResourceRecord &r);


#endif